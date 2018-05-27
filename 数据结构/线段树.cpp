#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<functional>
typedef long long ll;
using namespace std;
const int N=100005;
ll sum[N*4],tag[N*4],a[N];
int n,q,i,x,y,z;
char ch[10];
void up(int i){sum[i]=sum[i*2]+sum[i*2+1];}
void clean(int i,int l,int r)
{
    if (tag[i])
    {
        int mid=(l+r)/2;
        sum[i*2]+=(mid-l+1)*tag[i];tag[i*2]+=tag[i];
        sum[i*2+1]+=(r-mid)*tag[i];tag[i*2+1]+=tag[i];
        tag[i]=0;
    }
}
void build(int i,int l,int r)
{
    tag[i]=0;
    if (l==r){sum[i]=a[l];return;}
    int mid=(l+r)/2;
    build(i*2,l,mid),build(i*2+1,mid+1,r),up(i);
}
void change(int i,int l,int r,int x,int y,int z)
{
    if (x<=l&&r<=y){sum[i]+=z*(r-l+1);tag[i]+=z;return;}
    clean(i,l,r);
    int mid=(l+r)/2;
    if (x<=mid) change(i*2,l,mid,x,y,z);
    if (y>mid) change(i*2+1,mid+1,r,x,y,z);
    up(i);
}
ll query(int i,int l,int r,int x,int y)
{
    if (x<=l&&r<=y) return sum[i];
    clean(i,l,r);
    int mid=(l+r)/2;ll tmp=0;
    if (x<=mid) tmp+=query(i*2,l,mid,x,y);
    if (y>mid) tmp+=query(i*2+1,mid+1,r,x,y);
    return tmp;
}
int main()
{
    while(~scanf("%d%d",&n,&q))
    {
        for (i=1;i<=n;i++) scanf("%lld",&a[i]);
        build(1,1,n);
        for (i=1;i<=q;i++)
        {
            scanf("%s",ch);
            if (ch[0]=='Q')
            {
                scanf("%d%d",&x,&y);
                printf("%lld\n",query(1,1,n,x,y));
            }else
            {
                scanf("%d%d%d",&x,&y,&z);
                change(1,1,n,x,y,z);
            }
        }
    }
}
