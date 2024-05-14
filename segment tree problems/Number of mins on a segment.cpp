#include <iostream>
using namespace std;
//#include <bits/stdc++.h>
#include <vector>
#include <map>
typedef long long int ll ;
struct segtree{
    int size = 1 ;
    vector<pair<ll,ll>> minWC ;
    void init(int n){
        while(size < n) size *= 2 ;
        minWC.resize(2*size, {0,0});
    }
    void set(ll i , ll v, ll x , ll lx, ll rx ){
        if(rx-lx == 1){
            minWC[x] = {v,1};
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
        if(p1.first == p2.first){
            minWC[x] = {p1.first,p1.second+p2.second};
        }
        else if(p1.first < p2.first){
            minWC[x] = p1 ;
        }
        else{
            minWC[x] = p2 ;
        }
    }
    void set(ll i , ll v){
        set(i,v,0,0,size);
    }
    pair<ll,ll> op(ll l, ll r, ll lx, ll rx, ll x){
        if(l <= lx and rx <= r){// is the range [l,r[ completely inclusive
            return minWC[x] ;
        }
        else if(rx <= l or r <= lx){// is the range [l,r] completely inclusive ?
            return {1e9+1,0};
        }
        else{
            ll m = (lx+rx)/ 2 ;
            auto s1 = op(l,r,lx,m,2*x+1) ;
            auto s2 = op(l,r,m,rx,2*x+2);
            if(s1.first == s2.first){
                return {s1.first,s1.second+s2.second};
            }
            else if(s1.first < s2.first){
                return s1 ;
            }
            else{
                return s2 ;
            }
        }
    }
    pair<ll,ll> sum(ll l, ll r){
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
            auto temp = st.sum(l,r) ;
            cout << temp.first << " " << temp.second << endl ;
        }
 
    }
}
