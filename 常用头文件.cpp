#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b)    for (int i(a); i <= (b); ++i)
#define dec(i, a, b)    for (int i(a); i >= (b); --i)
typedef long long LL;
const LL mod = 998244353;
const LL g   = 3;

const int N=400005;
inline LL Pow(LL a, LL b, LL mod){
	LL ret(1);
	for (; b; b >>= 1, (a *= a) %= mod) if (b & 1) (ret *= a) %= mod;
	return ret;
}
inline LL C(LL n, LL m){ return m > n ? 0 : fac[n] * Pow(fac[m] * fac[n - m] % mod, mod - 2, mod) % mod; }
