#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mo=1e9+7;

ll Pow(ll x,ll y){
    ll ret=1;
    while(y){
        if (y&1) ret=ret*x%mo;
        y/=2; x=x*x%mo;
    }
    return ret;
}

ll inv(ll x){
    return Pow(x,mo-2);
}

struct polynomial{
    static const int mxN=1000005;
    ll f[mxN];
    ll fac[mxN];
    ll ul[mxN];
    ll ur[mxN];
    int n;
    //丢进n个数产生最高次为n-1的多项式
    //丢进的必须是f(0)到f(n-1)
    void init(const vector<ll> &V){
        n=V.size();
        fac[0]=1;
        for (int i=1;i<n;i++) fac[i]=fac[i-1]*i%mo;
        for (int i=0;i<n;i++) f[i]=V[i];
    }
    //获取f(x)
    ll get(ll x){
        ul[0]=1;
        for (int i=1;i<n;i++) ul[i]=ul[i-1]*(x-(i-1))%mo;
        ur[n-1]=1;
        for (int i=n-2;i>=0;i--) ur[i]=ur[i+1]*(x-(i+1))%mo;
        ll ret=0;
        for (int i=0;i<n;i++){
            ll tmp1=ul[i]*ur[i]%mo;
            ll tmp2=inv(fac[i]*fac[n-1-i]%mo);
            ll tmp3=f[i];
            if ((n-1-i)&1) tmp3*=-1;
            ret=(ret+tmp1*tmp2%mo*tmp3%mo)%mo;
        }
        return (ret+mo)%mo;
    }
}Po;

int main(){
    int n,k; scanf("%d%d",&n,&k);
    vector<ll> f(k+2);
    f[0]=0;
    for (int i=1;i<k+2;i++) f[i]=(f[i-1]+Pow(i,k))%mo;
    Po.init(f);
    printf("%lld\n",Po.get(n));
}