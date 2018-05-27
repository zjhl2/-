#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1100000,INF=0x3f3f3f3f;
int t,v[26],f[N],g[N],sum[N],p[N];
char s[N],c[N];
void manacher(int l)
{
    c[0]='('; c[1]='#';
    int len=1;
    for (int i=1;i<=l;i++) c[++len]=s[i],c[++len]='#';
    c[++len]=')';
    int mx=0,id=0;
    for (int i=1;i<len;i++)
    {
        if (i<=mx) p[i]=min(mx-i,p[id*2-i]);
        else p[i]=0;
        while(c[i+p[i]+1]==c[i-p[i]-1]) p[i]++;
        if (i+p[i]>mx) mx=i+p[i],id=i;
        if (i-1==p[i]) f[p[i]]=sum[p[i]];
    }
}