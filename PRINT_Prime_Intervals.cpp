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

// use Segmented Sieve

const int MAX = sqrt(2147483647) + 5;
bitset<MAX+1> primes;

void generatePrimes (void) {
	primes[2] = 1;

	for (int i = 3; i <= MAX; i += 2)
		primes[i] = 1;

	for (int i = 3; i * i <= MAX; i += 2) {
		if (primes[i]) {
			for (int j = i * i; j <= MAX; j += 2 * i)
				primes[j] = 0;
		}
	}
}

void solve(void) {
	ll N, M; cin >> M >> N;

	M = max(2LL, M); // avoid 1, in segment it will be present at index 1 & composites start from 4, 
	// so it won't get cancelled

    const int SEGMENT_SIZE = 1000000 + 5;
    bitset<SEGMENT_SIZE+1> segment;
    segment.set();

    // remove all the even numbers first
    for (ll j = (M + 2 - 1) / 2 * 2; j <= N; j += 2) {
    	if (j == 2)
    		continue;

    	segment[j - M + 1] = 0;
    }

    // take care of odd numbers here
    for (ll i = 3; i * i <= N; i = primes._Find_next(i)) {
    	for (ll j = (M + i - 1) / i * i; j <= N; j += (j & 1) ? 2 * i : i) {
    		if (j == i)
    			continue;

    		segment[j - M + 1] = 0;
 
    		/* j += (j & 1) ? 2 * i : i  -> check only odd j */
    	}
    }

    for (ll j = M; j <= N; j++) {
    	if (segment[j - M + 1])
    		cout << j << '\n';
    }

    // cout << '\n';
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);

    generatePrimes();
    
    int test_cases = 1; cin >> test_cases;
    while (test_cases-- > 0) {
        solve();
    }

#ifndef ONLINE_JUDGE
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}