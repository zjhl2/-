#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int N=100005;

int n; 
int fa[N];
vector<int>link[N];
int deep[N],son[N],sz[N];
void dfs1(int u,int d){
    deep[u]=d;
    son[u]=-1;
    sz[u]=1;
    for (int v:link[u]){
        dfs1(v,d+1);
        sz[u]+=sz[v];
        if (son[u]==-1||sz[v]>sz[son[u]]) son[u]=v;
    }
}
int top[N],id[N],rd[N];
int T;
void dfs2(int u,int p){
    top[u]=p;
    id[u]=++T;
    rd[T]=u;
    if (son[u]!=-1) dfs2(son[u],p);
    for (int v:link[u]){
        if (v==son[u]) continue;
        dfs2(v,v);
    }
}

ll sum[4*N],lazya[4*N],lazym[4*N];
void build(int i,int l,int r){
    sum[i]=lazya[i]=0;
    lazym[i]=1;
    if (l==r) return;
    int mid=(l+r)/2;
    build(i*2,l,mid);
    build(i*2+1,mid+1,r);
}
void push(int i,int l,int r){
    if (lazym[i]!=1){
        sum[2*i]*=lazym[i];
        sum[2*i+1]*=lazym[i];
        lazym[2*i]*=lazym[i];
        lazym[2*i+1]*=lazym[i];
        lazya[2*i]*=lazym[i];
        lazya[2*i+1]*=lazym[i];
        lazym[i]=1;
    }
    if (lazya[i]){
        int mid=(l+r)/2;
        sum[2*i]+=lazya[i]*(mid-l+1);
        sum[2*i+1]+=lazya[i]*(r-mid);
        lazya[2*i]+=lazya[i];
        lazya[2*i+1]+=lazya[i];
        lazya[i]=0;
    }
}
void up(int i){
    sum[i]=sum[i*2]+sum[i*2+1];
}
void modi(int i,int l,int r,int x,int y,int tp,ll val){
    if (x<=l&&r<=y){
        if (tp==1) sum[i]*=val,lazym[i]*=val,lazya[i]*=val;
        if (tp==2) sum[i]+=val*(r-l+1),lazya[i]+=val;
        if (tp==3) sum[i]=-sum[i]-(r-l+1),lazym[i]*=-1,lazya[i]*=-1,lazya[i]--;
        return;
    }
    push(i,l,r);
    int mid=(l+r)/2;
    if (x<=mid) modi(i*2,l,mid,x,y,tp,val);
    if (y>mid) modi(i*2+1,mid+1,r,x,y,tp,val);
    up(i);
}
ll get(int i,int l,int r,int x,int y){
    if (x<=l&&r<=y) return sum[i];
    push(i,l,r);
    int mid=(l+r)/2;
    ll ret=0;
    if (x<=mid) ret+=get(i*2,l,mid,x,y);
    if (y>mid) ret+=get(i*2+1,mid+1,r,x,y);
    ll tmp=sum[i];
    up(i);
    assert(tmp==sum[i]);
    return ret;
}
int getlca(int x,int y){
    int f1=top[x],f2=top[y];
    while(f1!=f2){
        if (deep[f1]<deep[f2]) swap(f1,f2),swap(x,y);
        x=fa[f1],f1=top[x];
    }
    if (deep[x]<deep[y]) swap(x,y);
    return y;
}
ll cg(int l,int r,int tp,ll val){
    if (tp==4)
        return get(1,1,n,l,r);
    modi(1,1,n,l,r,tp,val);
    return 0;
}
ll line(int tp,int x,int lca,ll val){
    ll ret=0;
    while(x!=lca&&deep[top[x]]>deep[lca]){
        ret+=cg(id[top[x]],id[x],tp,val);
        x=fa[top[x]];
    }
    if (x!=lca) ret+=cg(id[lca]+1,id[x],tp,val);
    return ret;
}
ll route(int tp,int x,int y,ll val){
    int lca=getlca(x,y);
    ll ret1=line(tp,x,lca,val);
    ll ret2=line(tp,y,lca,val);
    ll ret3=cg(id[lca],id[lca],tp,val);
    return ret1+ret2+ret3;
}
int main(){
    while(~scanf("%d",&n)){
        for (int i=2;i<=n;i++){
            int x; scanf("%d",&x);
            fa[i]=x;
            link[x].emplace_back(i);
        }
        dfs1(1,1);
        dfs2(1,1);
        build(1,1,n);
        int m; scanf("%d",&m);
        while(m--){
            int tp,x,y; ll val;
            scanf("%d%d%d",&tp,&x,&y);
            if (tp<=2) scanf("%llu",&val);
            ll ret=route(tp,x,y,val);
            if (tp==4) printf("%llu\n",ret);
        }
        for (int i=1;i<=n;i++) link[i].clear();
        T=0;
    }
}