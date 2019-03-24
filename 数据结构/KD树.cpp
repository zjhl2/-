#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100005;

int cmpd;
struct node{
    int d[2];
    int l,r;
    int Max[2],Min[2];
    bool operator<(const node &b)const{
        return d[cmpd]<b.d[cmpd];
    }
}a[N];

void up(int x){
    if (a[x].l){
        for (int i=0;i<2;i++)
            a[x].Max[i]=max(a[x].Max[i],a[a[x].l].Max[i]),
            a[x].Min[i]=min(a[x].Min[i],a[a[x].l].Min[i]);
    }
    if (a[x].r){
        for (int i=0;i<2;i++)
            a[x].Max[i]=max(a[x].Max[i],a[a[x].r].Max[i]),
            a[x].Min[i]=min(a[x].Min[i],a[a[x].r].Min[i]);
    }
}
int build(int l,int r,int D){
    int mid=(l+r)/2;
    cmpd=D;
    nth_element(a+l,a+mid,a+r+1);
    a[mid].Max[0]=a[mid].Min[0]=a[mid].d[0];
    a[mid].Max[1]=a[mid].Min[1]=a[mid].d[1];
    if (l<mid) a[mid].l=build(l,mid-1,!D); else a[mid].l=0;
    if (mid<r) a[mid].r=build(mid+1,r,!D); else a[mid].r=0;
    up(mid);
    return mid;
}
bool check(int x,ll A,ll B){
    ll tmp1=B*a[x].Min[0]+A*a[x].Min[1]-A*B;
    ll tmp2=B*a[x].Max[0]+A*a[x].Max[1]-A*B;
    if (tmp1<0&&tmp2<0||tmp1>0&&tmp2>0) return 0;
    return 1;
}
int get(int x,ll A,ll B){
    int ret=0;
    if (B*a[x].d[0]+A*a[x].d[1]==A*B) ret++;
    if (a[x].l&&check(a[x].l,A,B)) ret+=get(a[x].l,A,B);
    if (a[x].r&&check(a[x].r,A,B)) ret+=get(a[x].r,A,B);
    return ret;
}
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n,m; scanf("%d%d",&n,&m);
        for (int i=1;i<=n;i++)
            for (int j=0;j<2;j++) scanf("%d",&a[i].d[j]);
        int root=build(1,n,0);
        while(m--){
            ll A,B; scanf("%lld%lld",&A,&B);
            printf("%d\n",get(root,A,B));
        }
    }
}
// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=5730
// 问线段上出现了多少点