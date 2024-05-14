#include <iostream>
using namespace std;
//#include <bits/stdc++.h>
#include <vector>
#include <map>
typedef long long int ll ;
struct param {
    ll andVal ;
    ll orOps ;
};
struct segtree{
    ll size = 1 ;
    vector<param> andSeg ;
 
//    void build(ll i , ll lx , ll rx){
//        if(rx-lx == 1){
//            return ;
//        }
//        ll m = (lx + rx) / 2 ;
//        build(2*i+1 , lx, m);
//        build(2*i+2,m,rx);
//        andSeg[i].sum = (andSeg[2*i+1].sum + andSeg[2*i+2].sum)   ;
//    }
    void init(ll n){
        while(size < n) size *= 2 ;  // Get the first power of 2 bigger than n
        andSeg.resize(2*size, {0,0}); // 2^n for leaf nodes and 2^n for non leaf nodes
//        build(0,0,size);
    }
 
//    void propogate(ll i, ll lx, ll rx){
//        if((rx-lx) != 1){
//            andSeg[2*i+1].value = operation(andSeg[2*i+1].value,andSeg[i].value);
//            andSeg[2*i+2].value = operation(andSeg[2*i+2].value,andSeg[i].value);
//            andSeg[i].value = -1 ;
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
    void orOp(ll i, ll lx, ll rx, ll l, ll r, ll v){
//         propogate(i,lx,rx);
         if(lx >= r or rx <= l){
             return ;
         }
        if(lx >= l and rx <= r){
            andSeg[i].andVal |= v ;
            andSeg[i].orOps |= v ;
            return ;
        }
        else{
            ll m = (lx + rx)/ 2 ;
            orOp(2*i+1,lx,m,l,r,v);
            orOp(2*i+2,m,rx,l,r,v);
            andSeg[i].andVal = (andSeg[2*i+1].andVal & andSeg[2*i+2].andVal) ;
            andSeg[i].andVal |= andSeg[i].orOps ;
        }
    }
    void orOp(ll l, ll r, ll v){
        orOp(0,0,size,l,r,v);
    }
    ll andInterval(ll i, ll lx , ll rx, ll l , ll r){
        if(lx >= r or rx <= l){
            return 0xFFFFFFFF ;
        }
        if(lx >= l and rx <= r){
            return andSeg[i].andVal;
        }
        ll m = (lx+rx)/2;
        ll sumLeft  = andInterval(2*i+1,lx,m,l,r) ;
        ll sumRight = andInterval(2*i+2,m,rx,l,r) ;
        return ((((sumLeft & sumRight)) | andSeg[i].orOps));
        }
    ll andInterval(ll l , ll r){
        return andInterval(0,0,size,l,r);
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
            st.orOp(l,r,v);
        }
        else{
            ll l , r ;
            cin >> l >> r ;
            ll val = st.andInterval(l,r);
            cout << (val) << endl ;
        }
 
 
    }
}
