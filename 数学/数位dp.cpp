#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=705,mo=1e9+7;
int n;
char s[N];
int a[N];
ll g[N],mul[11][N];
ll c[N][N],f[N][10];
ll dfs(int pos,int dg,int same,int up)
{
    if (pos==n)
    {
        return dg*g[same]%mo*mul[10][up]%mo;
    }
    ll ret=dfs(pos+1,dg,same+(a[pos]==dg),up+(a[pos]>dg));
    int d=min(dg,a[pos]);
    int sa=a[pos]>dg;
    int u=max(a[pos]-dg-1,0);
    for (int i=0;i<n-pos;i++)
    {
        ret+=d*c[n-pos-1][i]%mo*g[same+i]%mo*f[n-pos-1-i][dg]%mo*mul[10][up]%mo*dg%mo;
        ret+=sa*c[n-pos-1][i]%mo*g[same+i+1]%mo*f[n-pos-1-i][dg]%mo*mul[10][up]%mo*dg%mo;
        ret+=u*c[n-pos-1][i]%mo*g[same+i]%mo*f[n-pos-1-i][dg]%mo*mul[10][up+1]%mo*dg%mo;
        ret%=mo;
    }
    return ret;
}
ll get(int dg)
{
    return dfs(0,dg,0,0);
}
int main()
{
    c[0][0]=1;
    for (int i=1;i<N;i++)
    {
        c[i][0]=1;
        for (int j=1;j<N;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mo;
    }
    for (int i=1;i<N;i++) g[i]=(g[i-1]*10+1)%mo;
    for (int i=0;i<=10;i++)
    {
        mul[i][0]=1;
        for (int j=1;j<N;j++) mul[i][j]=mul[i][j-1]*i%mo;
    }
    for (int i=0;i<N;i++)
        for (int dg=0;dg<10;dg++)
        {
            for (int j=0;j<=i;j++)
                f[i][dg]=(f[i][dg]+c[i][j]*mul[9-dg][j]%mo*mul[dg][i-j]%mo*mul[10][j])%mo;
        }
    scanf("%s",s);
    n=strlen(s);
    for (int i=0;i<n;i++) a[i]=s[i]-'0';
    ll ans=0;
    for (int i=1;i<10;i++) ans=(ans+get(i))%mo;
    printf("%I64d\n",ans);
}

http://codeforces.com/contest/908/problem/G
