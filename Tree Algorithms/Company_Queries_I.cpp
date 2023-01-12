#include <bits/stdc++.h>
using namespace std;

typedef int ll;
typedef long double ld;
ll mod = 1e9 + 7;
#define nl "\n"
#define dbg(x) cout << #x << " = " << x << nl

void dfs(ll curr, ll prev, vector<vector<ll>>& adj, vector<vector<ll>>& par)
{
    par[curr][0] = prev;
    for(ll i=1;i<18;i++)
    {
        ll temp = par[curr][i-1];
        if(temp == -1) break;
        temp = par[temp][i-1];
        if(temp == -1) break;
        par[curr][i] = temp;
    }
    for(auto&x : adj[curr])
    {
        if(x!=prev)
        {
            dfs(x,curr,adj,par);
        }
    }
}

void solve()
{
    ll n,q;
    cin>>n>>q;
    vector<vector<ll>> par(n+1, vector<ll>(18,-1));
    vector<vector<ll>> adj(n+1);
    for(ll i=2;i<=n;i++)
    {
        ll t;
        cin>>t;
        adj[i].push_back(t);
        adj[t].push_back(i);
    }
    dfs(1,-1,adj,par);
    for(ll i=0;i<q;i++)
    {
        ll node,k;
        cin>>node>>k;
        if(log2(k)>=18) // not possible to have that many parents with given constraints
        {
            cout<<-1<<nl;
            continue;
        }
        ll cnt = 0;
        while(k>0 && node!=-1)
        {
            if(k&1)
            {
                node = par[node][cnt];
            }
            k>>=1;
            cnt++;
        }
        cout<<node<<nl;
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