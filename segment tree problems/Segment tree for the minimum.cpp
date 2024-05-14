#include <iostream>
using namespace std;
//#include <bits/stdc++.h>
#include <vector>
typedef long long int ll ;
struct segtree{
    int size = 1 ;
    vector<ll> sums ;
    void init(int n){
        while(size < n) size *= 2 ;
        sums.resize(2*size,0LL);
    }
    void set(ll i , ll v, ll x , ll lx, ll rx ){
        if(rx-lx == 1){
            sums[x] = v ;
            return ;
        }
        ll m = (lx + rx)/ 2 ;
        if(i < m){
            set(i,v,2*x+1,lx,m);
        }
        else{
            set(i,v,2*x+2,m,rx);
        }
        sums[x] = min(sums[2*x+1] , sums[2*x+2]);
    }
    void set(ll i , ll v){
        set(i,v,0,0,size);
 
    }
    ll op(ll l, ll r, ll lx, ll rx, ll x){
        if(l <= lx and rx <= r){// is the range [l,r[ completely inclusive
            return sums[x];
        }
        else if(rx <= l or r <= lx){// is the range [l,r] completely inclusive ?
            return 1e9 + 1 ;
        }
        else{
            ll m = (lx+rx)/ 2 ;
            ll s1 = op(l,r,lx,m,2*x+1) ;
            ll s2 = op(l,r,m,rx,2*x+2);
            return  min(s1,s2) ;
        }
    }
    ll sum(ll l, ll r){
        return op(l,r,0,size, 0);
    }
 
};
 
 
int main() {
    ios::sync_with_stdio(false);
 
    int n , m ;
    cin >> n >> m ;
    segtree st ;
    st.init(n);
    for(int i = 0 ; i < n ; i++){
        int v ;
        cin >> v ;
        st.set(i,v);
    }
    while(m--){
        int op ;
        cin >> op ;
        if(op == 1){
            int i , v ;
            cin >> i >> v ;
            st.set(i,v);
        }
        else{
            int l , r ;
            cin >> l >> r ;
            cout << st.sum(l,r) << "\n" ;
 
        }
 
    }
}
