#include <iostream>
using namespace std;
//#include <bits/stdc++.h>
#include <vector>
#include <map>
typedef long long int ll ;
struct param {
    ll mp ;
    ll ms ;
    ll sum ;
    ll msSum ;
    ll v ;
};
struct segtree{
    int size = 1 ;
    vector<param> minWC ;
    void init(int n){
        while(size < n) size *= 2 ;  // Get the first power of 2 bigger than n
        minWC.resize(2*size, {0,0,0,0,0}); // 2^n for leaf nodes and 2^n for non leaf nodes
    }
    void set(ll i , ll v, ll x , ll lx, ll rx ){ // i is the index A[i] , v is the value , x is the index of the needed node to insert in, (lx,rx) is the interval
        if(rx-lx == 1){
            minWC[x] = {v,v,v,v,v};
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
        minWC[x].sum = p1.sum + p2.sum ;
        minWC[x].mp = max(p1.mp,p1.sum+p2.mp);
        minWC[x].ms = max(p2.ms,p2.sum+p1.ms);
        minWC[x].msSum = max(p1.msSum,p2.msSum);
        minWC[x].msSum = max(minWC[x].msSum,p1.ms + p2.mp);
    }
    void set(ll i , ll v){
        set(i,v,0,0,size);
    }
//    pair<ll,ll> op(ll l, ll r, ll lx, ll rx, ll x){
//        if(l <= lx and rx <= r){// is the range [l,r[ completely inclusive
//            return minWC[x] ;
//        }
//        else if(rx <= l or r <= lx){// is the range [l,r] completely inclusive ?
//            return {1e9+1,0};
//        }
//        else{
//            ll m = (lx+rx)/ 2 ;
//            auto s1 = op(l,r,lx,m,2*x+1) ;
//            auto s2 = op(l,r,m,rx,2*x+2);
//            if(s1.first == s2.first){
//                return {s1.first,s1.second+s2.second};
//            }
//            else if(s1.first < s2.first){
//                return s1 ;
//            }
//            else{
//                return s2 ;
//            }
//        }
//    }
    ll maxSegmentSum(){
        return minWC[0].msSum ;
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
    cout << ((st.maxSegmentSum() <= 0) ? 0 : st.maxSegmentSum()) << endl;
    while(m--){
        int i ,v ;
        cin >> i >> v ;
        st.set(i,v);
        ll x = st.maxSegmentSum();
        cout << ((x <= 0) ? 0 : x) << endl;
 
    }
}
