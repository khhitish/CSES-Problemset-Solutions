#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
ll mod = 1e9 + 7;
#define nl "\n"
#define dbg(x) cout << #x << " = " << x << nl

void dfs(ll curr, ll prev, vector<vector<ll>>& adj, vector<vector<ll>>& parent, ll currlvl, vector<ll>& level)
{
    // pre computation for binary lifting parent array and the levels array
    parent[curr][0] = prev;
    level[curr] = currlvl;
    for(ll i=1;i<18;i++)
    {
        ll temp = parent[curr][i-1];
        if(temp == -1) break;
        temp = parent[temp][i-1];
        if(temp == -1) break;
        parent[curr][i] = temp;
        // 2^(i-1)th parent of 2^(i-1)th parent of curr node is the ith parent of current node. If any of them dont exist break the loop since no higher parents will be present
        // since we are doing dfs, all the parents of the current node would have been already calculated/visited 
    }
    for(auto&x : adj[curr])
    {
        if(x!=prev)
        {
            dfs(x,curr,adj,parent,currlvl+1,level);
        }
    }
}

ll findLCA(ll a, ll b, vector<vector<ll>>& parent, vector<ll>& level)
{
    // making a and b to be at equal level
    ll k = abs(level[a] - level[b]);
    if(level[b] > level[a])swap(b,a);
    ll cnt = 0;
    ll node = a;
    // cout<<a<<" "<<b<<nl;
    while(k>0)
    {
        if(k&1)
        {
            node = parent[node][cnt];
        }
        k>>=1;
        cnt++;
    }
    a = node;
    if(a == b) return a;
    for(ll i=17;i>=0;i--)
    {
        if(parent[a][i]!=parent[b][i])
        {
            a = parent[a][i];
            b = parent[b][i];
        }
        // cout<<a<<" "<<b<<nl;
    }
    return parent[a][0];
    
}

void solve()
{
    // q queries for lca
    ll n,q;
    cin>>n>>q;
    vector<vector<ll>> adj(n+1);
    // 0 based indexing for nodes and taking edge list as input
    for(ll i=2;i<=n;i++)
    {
        ll u,v;
        u = i;
        cin>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<ll> level(n+1);
    vector<vector<ll>> parent(n+1, vector<ll> (18,-1));
    
    dfs(1,-1,adj,parent,1,level);
    
    for(ll i=0;i<q;i++)
    {
        ll a,b;
        cin>>a>>b;
        cout<<findLCA(a,b,parent,level)<<nl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll testcases = 1;
    // cin >> testcases;
    for (ll testcase = 1; testcase <= testcases; testcase++)
    {
        // cout << "Case #" << testcase << ": ";
        solve();
    }
    return 0;
}