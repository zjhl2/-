#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b)    for (int i(a); i <= (b); ++i)
#define dec(i, a, b)    for (int i(a); i >= (b); --i)
typedef long long LL;
const LL mod = 998244353;
const LL g   = 3;

const int N=400005;
vector <LL> v[N << 1];
LL x1[N << 1], x2[N << 1];
LL fac[N];
LL ans, flag;
int T;
int n, all, cnt;
int sz;

inline LL Pow(LL a, LL b, LL mod){
	LL ret(1);
	for (; b; b >>= 1, (a *= a) %= mod) if (b & 1) (ret *= a) %= mod;
	return ret;
}

inline LL C(LL n, LL m){ return m > n ? 0 : fac[n] * Pow(fac[m] * fac[n - m] % mod, mod - 2, mod) % mod; }

struct cmp{
	bool operator ()(int a, int b){
		return v[a].size() > v[b].size();
	}
};

priority_queue <LL, vector <LL>, cmp> q;

void change(LL y[], int len){
	for (int i = 1, j = len / 2; i < len - 1; i++){
		if (i < j) swap(y[i], y[j]);
		int k = len / 2;
		while (j >= k){
			j -= k;
			k /= 2;
		}
		if (j < k) j += k;
	}
}

void ntt(LL y[], int len, int on){
	change(y, len);
	for (int h = 2; h <= len; h <<= 1){
		LL wn = Pow(g, (mod - 1) / h, mod);
		if (on == -1) wn = Pow(wn, mod - 2, mod);
		for (int j = 0; j < len; j += h){
			LL w = 1ll;
			for (int k = j; k < j + h / 2; k++){
				LL u = y[k];
				LL t = w * y[k + h / 2] % mod;
				y[k] = (u + t) % mod;
				y[k + h / 2] = (u - t + mod) % mod;
				w = w * wn % mod;
			}
		}
	}

	if (on == -1){
		LL t = Pow(len, mod - 2, mod);
		rep(i, 0, len - 1) y[i] = y[i] * t % mod;
	}
}

void mul(vector <LL> &a, vector <LL> &b, vector <LL> &c){
	int len = 1;
	int sz1 = a.size(), sz2 = b.size();

	while (len <= sz1 + sz2 - 1) len <<= 1;

	rep(i, 0, sz1 - 1) x1[i] = a[i];
	rep(i, sz1, len)   x1[i] = 0;

	rep(i, 0, sz2 - 1) x2[i] = b[i];
	rep(i, sz2, len)   x2[i] = 0;

	ntt(x1, len, 1);
	ntt(x2, len, 1);

	rep(i, 0, len - 1) x1[i] = x1[i] * x2[i];

	ntt(x1, len, -1);

	vector <LL>().swap(c);
	rep(i, 0, sz1 + sz2 - 2) c.push_back(x1[i]);
}