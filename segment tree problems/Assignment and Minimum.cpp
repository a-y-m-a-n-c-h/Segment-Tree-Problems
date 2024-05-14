#include <iostream>
using namespace std;
//#include <bits/stdc++.h>
#include <vector>
#include <map>
typedef long long int ll ;
struct param {
    ll min ;
    ll assignedVal ;
};
struct segtree{
    ll size = 1 ;
    vector<param> minSeg ;
 
//    void build(ll i , ll lx , ll rx){
//        if(rx-lx == 1){
//            return ;
//        }
//        ll m = (lx + rx) / 2 ;
//        build(2*i+1 , lx, m);
//        build(2*i+2,m,rx);
//        minSeg[i].min = (minSeg[2*i+1].min + minSeg[2*i+2].min)   ;
//    }
    void init(ll n){
        while(size < n) size *= 2 ;  // Get the first power of 2 bigger than n
        minSeg.resize(2*size, {0,LLONG_MAX}); // 2^n for leaf nodes and 2^n for non leaf nodes
//        build(0,0,size);
    }
 
    void propogate(ll i, ll lx, ll rx){
        if((rx-lx) != 1){
            minSeg[2*i+1].assignedVal = operation(minSeg[2*i+1].assignedVal,minSeg[i].assignedVal);
            minSeg[2*i+1].min = operation(minSeg[2*i+1].min,minSeg[i].assignedVal);
            minSeg[2*i+2].assignedVal = operation(minSeg[2*i+2].assignedVal,minSeg[i].assignedVal);
            minSeg[2*i+2].min = operation(minSeg[2*i+2].min,minSeg[i].assignedVal);
            minSeg[i].assignedVal = LLONG_MAX ;
        }
        return ;
    }
    ll operation(ll a , ll b){
        if(b == LLONG_MAX){
            return a ;
        }
        else{
            return b;
        }
    }
    void assignedVal(ll i, ll lx, ll rx, ll l, ll r, ll v){
         propogate(i,lx,rx);
         if(lx >= r or rx <= l){
             return ;
         }
        if(lx >= l and rx <= r){
            minSeg[i].assignedVal = v ;
            minSeg[i].min = v ;
            return ;
        }
        else{
            ll m = (lx + rx)/ 2 ;
            assignedVal(2*i+1,lx,m,l,r,v);
            assignedVal(2*i+2,m,rx,l,r,v);
            minSeg[i].min = min(minSeg[2*i+1].min, minSeg[2*i+2].min);
        }
    }
    void assignedVal(ll l, ll r, ll v){
        assignedVal(0,0,size,l,r,v);
    }
    ll minInterval(ll i, ll lx , ll rx, ll l , ll r){
        if(lx >= r or rx <= l){
            return LLONG_MAX ;
        }
 
        if(lx >= l and rx <= r){
            if(minSeg[i].assignedVal != LLONG_MAX){
                return minSeg[i].assignedVal ;
            }
            return minSeg[i].min ;
        }
        if(minSeg[i].assignedVal != LLONG_MAX){
            return minSeg[i].assignedVal ;
        }
        ll m = (lx+rx)/2;
        ll minLeft  = minInterval(2*i+1,lx,m,l,r) ;
        ll minRight = minInterval(2*i+2,m,rx,l,r) ;
        return min(minLeft,minRight);
    }
    ll minInterval(ll l , ll r){
        return minInterval(0,0,size,l,r);
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
            st.assignedVal(l,r,v);
        }
        else{
            ll l , r ;
            cin >> l >> r ;
            ll val = st.minInterval(l,r);
            if (val == LLONG_MAX){
                cout << 0 << endl ;
            }
            else{
                cout << val << endl ;
            }
        }
 
 
    }
}
