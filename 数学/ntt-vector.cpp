#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const ll g   = 3;

const int N=400005; 

inline ll Pow(ll a, ll b, ll mod){
    ll ret(1);
    for (; b; b >>= 1, (a *= a) %= mod) if (b & 1) (ret *= a) %= mod;
    return ret;
}
ll fac[N];
inline ll C(ll n, ll m){ return m > n ? 0 : fac[n] * Pow(fac[m] * fac[n - m] % mod, mod - 2, mod) % mod; }

void change(ll y[], int len){
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

void ntt(ll y[], int len, int on){
    change(y, len);
    for (int h = 2; h <= len; h <<= 1){
        ll wn = Pow(g, (mod - 1) / h, mod);
        if (on == -1) wn = Pow(wn, mod - 2, mod);
        for (int j = 0; j < len; j += h){
            ll w = 1ll;
            for (int k = j; k < j + h / 2; k++){
                ll u = y[k];
                ll t = w * y[k + h / 2] % mod;
                y[k] = (u + t) % mod;
                y[k + h / 2] = (u - t + mod) % mod;
                w = w * wn % mod;
            }
        }
    }
    if (on == -1){
        ll t = Pow(len, mod - 2, mod);
        for (int i = 0; i < len; i ++) y[i] = y[i] * t % mod;
    }
}

ll x1[N],x2[N];
vector<ll> mul(const vector <ll> &p,const vector <ll> &q){
    int len = 1;
    while (len < p.size() + q.size() - 1) len <<= 1;
    for (int i = 0; i < len; i++)
    {
        if (i < p.size()) x1[i] = p[i];
        else x1[i] = 0;
        if (i < q.size()) x2[i] = q[i];
        else x2[i] = 0;
    }
    ntt(x1, len, 1);
    ntt(x2, len, 1);
    for (int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
    ntt(x1, len, -1);
    vector<ll> ret;
    for (int i = 0; i < p.size() + q.size() - 1; i++) 
        ret.emplace_back(x1[i]);
    return ret;
}

int a[N],b[N];
vector<ll> solve(int l,int r){
    if (l==r){
        vector<ll> ret(min(a[l],b[l])+1);
        for (int i=0;i<=min(a[l],b[l]);i++)
            ret[i]=C(a[l],i)*C(b[l],i)%mod*fac[i]%mod;
        return ret;
    }
    int mid=(l+r)/2;
    return mul(solve(l,mid),solve(mid+1,r));
}
void look(const vector<ll> &V){
    for (int v:V) printf("%lld ",(v+mod)%mod);
    puts("");
}
int main(){
    fac[0]=1;
    for (int i=1;i<N;i++) fac[i]=fac[i-1]*i%mod;
    int t; scanf("%d",&t);
    while(t--){
        int n; scanf("%d",&n);
        int m=0;
        for (int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]),m+=a[i];
        vector<ll> ret=solve(1,n);
        //look(ret);
        ll ans=0;
        for (int i=0;i<ret.size();i++){
            ll tmp=fac[m-i];
            tmp=tmp*ret[i]%mod;
            if (i&1) ans=(ans-tmp)%mod;
            else ans=(ans+tmp)%mod;
        }
        printf("%lld\n",(ans+mod)%mod);
    }
}