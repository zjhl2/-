//多个连通块的无向图，通过给奇点加边生成欧拉路
#include<bits/stdc++.h>
using namespace std;
#define ms(a) memset(a,0,sizeof(a))
const int N=400005;

int base[N],pre[N],nxt[N],eid[N],tot;
bool vis[N],del[N];
int deg[N];
int stk[N*2],top;
void link(int x,int y,int z){
    tot++; 
    nxt[tot]=y; pre[tot]=base[x]; base[x]=tot; eid[tot]=z;
}
void dfs(int u){
    del[u]=1;
    for (int &i=base[u];i;i=pre[i]) if (!vis[i]){
        vis[i]=vis[i^1]=1;
        int id=eid[i];
        dfs(nxt[i]);
        stk[++top]=id;
    }
}
void print(vector<int> &V){
    printf("%d",V.size());
    for (int v:V) printf(" %d",v);
    V.clear();
    puts("");
}
int main(){
    int n,m; 
    while(~scanf("%d%d",&n,&m)){
        tot=1;
        ms(base); ms(vis); ms(deg); ms(del);
        for (int i=1;i<=m;i++){
            int x,y; scanf("%d%d",&x,&y);
            link(x,y,i); link(y,x,-i);
            deg[x]++; deg[y]++;
        }
        int last=1;
        vector<int>V;
        for (int i=1;i<=n;i++)
            if (deg[i]&1) V.emplace_back(i),last=i;
        for (int i=1;i<V.size();i+=2){
            int x=V[i-1],y=V[i];
            link(x,y,0); link(y,x,0);
        }
        top=0; stk[++top]=0;
        dfs(last);
        for (int i=1;i<=n;i++)
            if (!del[i]&&deg[i]&1) stk[++top]=0,dfs(i);
        for (int i=1;i<=n;i++)
            if (!del[i]) stk[++top]=0,dfs(i);
        int ans=0;
        for (int i=2;i<=top;i++)
            if (stk[i]&&!stk[i-1]) ans++;
        printf("%d\n",ans);
        V.clear();
        for (int i=top;i>=1;i--){
            if (!stk[i]){
                if (!V.empty()) print(V);
            }
            else V.emplace_back(stk[i]);
        }
    }
}