#include <iostream>
using namespace std;
//#include <bits/stdc++.h>
#include <vector>
#include <map>
typedef long long int ll ;
struct param {
    ll sum ;
    ll addV ;
};
struct segtree{
    ll size = 1 ;
    vector<param> sumSeg ;
 
//    void build(ll i , ll lx , ll rx){
//        if(rx-lx == 1){
//            return ;
//        }
//        ll m = (lx + rx) / 2 ;
//        build(2*i+1 , lx, m);
//        build(2*i+2,m,rx);
//        sumSeg[i].sum = (sumSeg[2*i+1].sum + sumSeg[2*i+2].sum)   ;
//    }
    void init(ll n){
        while(size < n) size *= 2 ;  // Get the first power of 2 bigger than n
        sumSeg.resize(2*size, {0,0}); // 2^n for leaf nodes and 2^n for non leaf nodes
//        build(0,0,size);
    }
 
//    void propogate(ll i, ll lx, ll rx){
//        if((rx-lx) != 1){
//            sumSeg[2*i+1].value = operation(sumSeg[2*i+1].value,sumSeg[i].value);
//            sumSeg[2*i+2].value = operation(sumSeg[2*i+2].value,sumSeg[i].value);
//            sumSeg[i].value = -1 ;
//        }
//        return ;
//    }
//    ll operation(ll a , ll b){
//        if(b == -1){
//            return a ;
//        }
//        else{
//            return b;
//        }
//    }
    void addV(ll i, ll lx, ll rx, ll l, ll r, ll v){
//         propogate(i,lx,rx);
         if(lx >= r or rx <= l){
             return ;
         }
        if(lx >= l and rx <= r){
            sumSeg[i].addV += v ;
            sumSeg[i].sum += v*(rx-lx);
            return ;
        }
        else{
            ll m = (lx + rx)/ 2 ;
            addV(2*i+1,lx,m,l,r,v);
            addV(2*i+2,m,rx,l,r,v);
            sumSeg[i].sum = sumSeg[2*i+1].sum + sumSeg[2*i+2].sum;
            sumSeg[i].sum += sumSeg[i].addV*(rx-lx);
        }
    }
    void addV(ll l, ll r, ll v){
        addV(0,0,size,l,r,v);
    }
    pair<ll,ll> sumInterval(ll i, ll lx , ll rx, ll l , ll r){
        if(lx >= r or rx <= l){
            return {0,0} ;
        }
 
        if(lx >= l and rx <= r){
            return {sumSeg[i].sum,rx-lx};
        }
        ll m = (lx+rx)/2;
        pair<ll,ll> sumLeft  = sumInterval(2*i+1,lx,m,l,r) ;
        pair<ll,ll> sumRight = sumInterval(2*i+2,m,rx,l,r) ;
        ll contained = sumLeft.second + sumRight.second ;
        return {(sumLeft.first+sumRight.first)+(sumSeg[i].addV*contained),contained} ;
    }
    pair<ll,ll> sumInterval(ll l , ll r){
        return sumInterval(0,0,size,l,r);
    }
 
 
};
 
 
int main() {
    ios::sync_with_stdio(false);
    ll n , m ;
    cin >> n >> m ;
    segtree st ;
    st.init(n);
//    for(ll i = 0 ; i < n ; i++){
//        ll v ;
//        cin >> v ;
//        st.multiply(i,v);
//    }
    while(m--){
        ll op ;
        cin >> op ;
        if(op == 1){
            ll l , r , v ;
            cin >> l >> r >> v ;
            st.addV(l,r,v);
        }
        else{
            ll l , r ;
            cin >> l >> r ;
            pair<ll,ll> val = st.sumInterval(l,r);
            cout << (val.first) << endl ;
        }
 
 
    }
}
