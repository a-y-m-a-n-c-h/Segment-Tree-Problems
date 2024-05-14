#include <iostream>
using namespace std;
//#include <bits/stdc++.h>
#include <vector>
#include <map>
typedef long long int ll ;
struct param {
    ll index ;
    ll max ;
};
struct segtree{
    ll size = 1 ;
    vector<param> minWC ;
    void init(ll n){
        while(size < n) size *= 2 ;  // Get the first power of 2 bigger than n
        minWC.resize(2*size, {0,0}); // 2^n for leaf nodes and 2^n for non leaf nodes
    }
    void set(ll i , ll v, ll x , ll lx, ll rx ){ // i is the index A[i] , v is the value , x is the index of the needed node to insert in, (lx,rx) is the llerval
        if(rx-lx == 1){
            minWC[x].max = v ;
            minWC[x].index = i ;
            return ;
        }
        ll m = (lx + rx)/ 2 ;
        if(i < m){
            set(i,v,2*x+1,lx,m);
        }
        else{
            set(i,v,2*x+2,m,rx);
        }
        auto p1 = minWC[2*x+1];
        auto p2 = minWC[2*x+2];
        minWC[x].max = max(p1.max, p2.max) ;
    }
    void set(ll i , ll v){
        set(i,v,0,0,size);
    }
    ll op(ll lx, ll rx, ll v, ll x, ll l){
        if(rx-lx == 1){
            if(minWC[x].max >= v){
                return minWC[x].index ;
            }
            else{
                return -1 ;
            }
        }
        ll m = (lx+rx)/2 ;
        ll temp ;
        bool left = false ;
        if(l < m){
            left = true ;
            temp = op(lx,m,v,2*x+1,l);
        }
        else{
            temp = op(m,rx,v,2*x+2,l);
        }
        if(temp != -1 or (not left)){
            return temp ;
        }
        else{
            auto rightNodeS = minWC[2*x+2].max ;
 
            if(v <= rightNodeS){
                return op(m,rx,v,2*x+2);
            }
            else{
                return -1 ;
            }
        }
    }
    ll leftMostBiggestLowerBoundedByl(ll k, ll l){
        return op(0,size,k,0,l);
    }
    ll op(ll lx, ll rx, ll v, ll x){
        if(rx-lx == 1){
            if(minWC[x].max >= v){
                return minWC[x].index ;
            }
            else{
                return -1 ;
            }
        }
        auto leftNodeS = minWC[2*x+1].max ;
        ll m = (lx+rx)/2 ;
        if(v <= leftNodeS){
            return op(lx,m,v,2*x+1);
        }
        else{
            return op(m,rx,v,2*x+2);
        }
    }
    ll leftMostBiggest(ll k ){
        return op(0,size,k,0);
    }
 
 
};
 
 
int main() {
    ios::sync_with_stdio(false);
 
    ll n , m ;
    cin >> n >> m ;
    segtree st ;
    st.init(n);
    for(ll i = 0 ; i < n ; i++){
        ll v ;
        cin >> v ;
        st.set(i,v);
    }
    while(m--){
        ll op ;
        cin >> op ;
        if(op == 1){
            ll i , v ;
            cin >> i >> v ;
            st.set(i,v);
        }
        else{
            ll v, l ;
            cin  >> v ;
            cin >> l ;
            cout << st.leftMostBiggestLowerBoundedByl(v, l) << endl ;
        }
 
 
    }
}
