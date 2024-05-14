#include <iostream>
using namespace std;
//#include <bits/stdc++.h>
#include <vector>
#include <map>
typedef long long int ll ;
struct param {
    ll value ;
};
struct segtree{
    ll size = 1 ;
    vector<param> minWC ;
    void init(ll n){
        while(size < n) size *= 2 ;  // Get the first power of 2 bigger than n
        minWC.resize(2*size, {0}); // 2^n for leaf nodes and 2^n for non leaf nodes
    }
    void set(ll i, ll lx, ll rx, ll l, ll r, ll v){
         if(lx >= r or rx <= l){
            return ;
        }// i is the index A[i] , v is the value , x is the index of the needed node to insert in, (lx,rx) is the llerval
         else if(rx-lx == 1){
            minWC[i].value += v ;
            return ;
        }
        if(lx >= l and rx <= r){
            minWC[i].value += v ;
            return ;
        }
 
        else{
            ll m = (lx + rx)/ 2 ;
                set(2*i+1,lx,m,l,r,v);
                set(2*i+2,m,rx,l,r,v);
        }
    }
    void set(ll l, ll r, ll v){
        set(0,0,size,l,r,v);
    }
    ll get(ll i , ll lx , ll rx, ll x){
        if((rx-lx) == 1){
            return minWC[i].value;
        }
        ll m = (lx+rx)/2 ;
        if(x < m){
            return minWC[i].value + get(2*i+1,lx,m,x);
        }
        else{
            return minWC[i].value + get(2*i+2,m,rx,x);
        }
    }
    ll value(ll i){
        return get(0,0,size,i);
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
//        st.set(i,v);
//    }
    while(m--){
        ll op ;
        cin >> op ;
        if(op == 1){
            ll l , r , v ;
            cin >> l >> r >> v ;
            st.set(l,r,v);
        }
        else{
            ll i ;
            cin >> i ;
            cout << st.value(i) << endl;
        }
 
 
    }
}
