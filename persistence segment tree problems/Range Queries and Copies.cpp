// C++ program to implement persistent segment
// tree.
#include "bits/stdc++.h"
using namespace std;
typedef long long int ll ;
#define MAXN 100
 
/* data type for individual
 * node in the segment tree */
struct node
{
    // stores sum of the elements in node
    ll val;
 
    // poller to left and right children
    node* left, *right;
 
    // required constructors........
    node() {}
    node(node* l, node* r, ll v)
    {
        left = l;
        right = r;
        val = v;
    }
};
 
 
 
 
// Constructs Version-0
// Time Complexity : O(nlogn)
void build(node* n,ll low,ll high, vector<ll> & A)
{
    if (low==high)
    {
        n->val = A[low];
        return;
    }
    ll mid = (low+high) / 2;
    n->left = new node(NULL, NULL, 0);
    n->right = new node(NULL, NULL, 0);
    build(n->left, low, mid,A);
    build(n->right, mid+1, high,A);
    n->val = n->left->val + n->right->val;
}
 
/**
 * Upgrades to new Version
 * @param prev : polls to node of previous version
 * @param cur  : polls to node of current version
 * Time Complexity : O(logn)
 * Space Complexity : O(logn)  */
void upgrade(node* prev, node* cur, ll low, ll high,
             ll idx, ll value)
{
    if (idx > high or idx < low or low > high)
        return;
 
    if (low == high)
    {
        // modification in new version
        cur->val = value;
        return;
    }
    ll mid = (low+high) / 2;
    if (idx <= mid)
    {
        // link to right child of previous version
        cur->right = prev->right;
 
        // create new node in current version
        cur->left = new node(NULL, NULL, 0);
 
        upgrade(prev->left,cur->left, low, mid, idx, value);
    }
    else
    {
        // link to left child of previous version
        cur->left = prev->left;
 
        // create new node for current version
        cur->right = new node(NULL, NULL, 0);
 
        upgrade(prev->right, cur->right, mid+1, high, idx, value);
    }
 
    // calculating data for current version
    // by combining previous version and current
    // modification
    cur->val = cur->left->val + cur->right->val;
}
 
ll query(node* n, ll low, ll high, ll l, ll r)
{
    if (l > high or r < low or low > high)
        return 0;
    if (l <= low and high <= r)
        return n->val;
    ll mid = (low+high) / 2;
    ll p1 = query(n->left,low,mid,l,r);
    ll p2 = query(n->right,mid+1,high,l,r);
    return p1+p2;
}
 
int main(int argc, char const *argv[])
{
    ll n , q  ;
    cin >> n >> q ;
    vector<ll> A(n) ;
    for (ll i=0; i<n; i++)
        cin >> A[i] ;
 
    // creating Version-0
    vector<node * > version ;
    node* root = new node(NULL, NULL, 0);
    build(root, 0, n-1,A);
    // storing root node for version-0
    version.push_back(root);
    while(q--){
        ll type ;
        cin >> type ;
        if(type == 1){
            ll k , index , v ;
            cin >> k >> index >> v ;
            node* newVersion = new node(NULL, NULL, 0);
            upgrade(version[k-1], newVersion, 0, n-1, index-1, v);
            version[k-1] = newVersion ;
        }
        else if (type == 2){
            ll k , l , r ;
            cin >> k >> l >> r ;
            cout << query(version[k-1],0,n-1,l-1,r-1) << "\n" ;
        }
        else{
            ll k ;
            cin >> k ;
            node * newVersion = version[k-1] ;
            version.push_back(newVersion);
        }
    }
 
}
