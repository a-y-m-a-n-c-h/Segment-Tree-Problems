#include <iostream>
using namespace std;
//#include <bits/stdc++.h>
#include <vector>
#include <map>
typedef long long int ll ;
struct param {
    ll value ;
    ll valueAdded ;
};
struct segtree{
    ll size = 1 ;
    vector<param> minSeg ;
 
 
    void init(ll n){
        while(size < n) size *= 2 ;  // Get the first power of 2 bigger than n
        minSeg.resize(2*size, {0,0}); // 2^n for leaf nodes and 2^n for non leaf nodes
    }
 
//    void propogate(ll i, ll lx, ll rx){
//        if((rx-lx) != 1){
//            minSeg[2*i+1].value = operation(minSeg[2*i+1].value,minSeg[i].value);
//            minSeg[2*i+2].value = operation(minSeg[2*i+2].value,minSeg[i].value);
//            minSeg[i].value = -1 ;
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
    void add(ll i, ll lx, ll rx, ll l, ll r, ll v){
//         propogate(i,lx,rx);
         if(lx >= r or rx <= l){
             return ;
         }
        if(lx >= l and rx <= r){
            minSeg[i].valueAdded += v ;
            minSeg[i].value += v ;
            return ;
        }
        else{
            ll m = (lx + rx)/ 2 ;
            add(2*i+1,lx,m,l,r,v);
            add(2*i+2,m,rx,l,r,v);
            minSeg[i].value = min(minSeg[2*i+1].value,minSeg[2*i+2].value);
            minSeg[i].value += minSeg[i].valueAdded ;
        }
    }
    void add(ll l, ll r, ll v){
        add(0,0,size,l,r,v);
    }
    ll minimumInterval(ll i, ll lx , ll rx, ll l , ll r){
        if(lx >= r or rx <= l){
            return LLONG_MAX;
        }
        if(lx >= l and rx <= r){
            return minSeg[i].value ;
        }
        ll m = (lx+rx)/2;
        ll minLeft = minimumInterval(2*i+1,lx,m,l,r) ;
        ll minRight = minimumInterval(2*i+2,m,rx,l,r) ;
        return min(minLeft,minRight) + minSeg[i].valueAdded;
        }
    ll minValue(ll l , ll r){
        return minimumInterval(0,0,size,l,r);
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
//        st.add(i,v);
//    }
    while(m--){
        ll op ;
        cin >> op ;
        if(op == 1){
            ll l , r , v ;
            cin >> l >> r >> v ;
            st.add(l,r,v);
        }
        else{
            ll l , r ;
            cin >> l >> r ;
            ll val = st.minValue(l,r);
            cout << val << endl ;
        }
 
 
    }
}
