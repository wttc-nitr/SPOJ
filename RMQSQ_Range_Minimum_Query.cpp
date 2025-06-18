/*
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
*/
#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vb vector<bool>
#define vi vector<int>
#define vc vector<char>
#define INF (1LL << 60)
#define inf (1 << 30)

// concept: basic segment tree
vector<ll> tree;

ll get_min (int node, int node_left, int node_right, int query_left, int query_right) {
	// disjoint
	if (node_right < query_left || query_right < node_left)
		return INF;

	// interval inside query
	if (query_left <= node_left && node_right <= query_right)
		return tree[node];

	// partially inside
	int mid = node_left + (node_right - node_left) / 2;

	auto left_min = get_min (2 * node, node_left, mid, query_left, query_right);
	auto right_min = get_min (2 * node + 1, mid + 1, node_right, query_left, query_right);

	return min (left_min, right_min);
}

void solve(void) {
    int N; cin >> N;
    vector<ll> arr(N); for (auto &x : arr) cin >> x;

    while (__builtin_popcount(N) != 1)
    	N++;

    tree.resize(2 * N, INF);

    for (int i = 0; i < (int)arr.size(); i++)
    	tree[N + i] = arr[i];

    // generate min
    for (int i = N-1; i >= 1; i--)
    	tree[i] = min (tree[2 * i], tree[2 * i + 1]);

    int Q; cin >> Q;

    while (Q-- > 0) {
    	int i, j; cin >> i >> j;
    	cout << get_min (1, N, 2 * N -1, N + i, N + j) << '\n';
    }
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int test_cases = 1; 
    while (test_cases-- > 0) {
        solve();
    }

#ifndef ONLINE_JUDGE
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}