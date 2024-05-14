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
    vector<param> assignment ;
 
 
    void init(ll n){
        while(size < n) size *= 2 ;  // Get the first power of 2 bigger than n
        assignment.resize(2*size, {-1}); // 2^n for leaf nodes and 2^n for non leaf nodes
    }
 
    ll operation(ll a , ll b){
        if(b == -1){
            return a ;
        }
        else{
            return b;
        }
    }
    void propogate(ll i, ll lx, ll rx){
        if((rx-lx) != 1){
            assignment[2*i+1].value = operation(assignment[2*i+1].value,assignment[i].value);
            assignment[2*i+2].value = operation(assignment[2*i+2].value,assignment[i].value);
            assignment[i].value = -1 ;
        }
        return ;
    }
    void modify(ll i, ll lx, ll rx, ll l, ll r, ll v){
         propogate(i,lx,rx);
         if(lx >= r or rx <= l) return ;
         else if(rx-lx == 1){
            assignment[i].value = v ;
            return ;
        }
        if(lx >= l and rx <= r){
            assignment[i].value = v ;
            return ;
        }
        else{
            ll m = (lx + rx)/ 2 ;
            modify(2*i+1,lx,m,l,r,v);
            modify(2*i+2,m,rx,l,r,v);
        }
    }
    void modify(ll l, ll r, ll v){
        modify(0,0,size,l,r,v);
    }
    ll get(ll i , ll lx , ll rx, ll x){
        if(assignment[i].value != -1){
            return assignment[i].value ;
        }
        if((rx-lx) == 1){
            return assignment[i].value;
        }
        ll m = (lx+rx)/2;
        if(x < m){
            return get(2*i+1,lx,m,x);
        }
        else{
            return get(2*i+2,m,rx,x);
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
//        st.modify(i,v);
//    }
    while(m--){
        ll op ;
        cin >> op ;
        if(op == 1){
            ll l , r , v ;
            cin >> l >> r >> v ;
            st.modify(l,r,v);
        }
        else{
            ll i ;
            cin >> i ;
            ll val = st.value(i);
            if(val == -1){
                cout << 0 << '\n' ;
            }
            else{
                cout << val << '\n' ;
            }
        }
 
 
    }
}
