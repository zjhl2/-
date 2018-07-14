#include<cstdio>
#include<algorithm>
using namespace std;

const int mxN=505,INF=0x3f3f3f3f;
struct Stoer_Wagner{
    int edge[mxN][mxN],pe[mxN][mxN]; 
    int nxt[mxN];
    bool vis[mxN];
    int wage[mxN];//连通度
    int n;
    void init(int sz){
        for (int i=1;i<=sz;i++)
            for (int j=1;j<=sz;j++) edge[i][j]=0;
        n=sz;
    }
    void link(int x,int y,int z){
        edge[x][y]+=z; edge[y][x]+=z;
    }
    int mincutST(int &S,int &T){
        for (int i=1;i<=n;i++) wage[i]=0,vis[i]=0;
        wage[0]=-1;
        for (int i=1;i<=n;i++){
            int k=0;
            for (int j=1;j<=n;j++) 
            if (!vis[j]&&wage[j]>wage[k]) k=j;
            if (!k) return 0;//图本身就不连通，不需要割
            vis[k]=1; S=T; T=k;
            for (int j=1;j<=n;j++)
            if (!vis[j]) wage[j]+=edge[k][j];
        }
        return wage[T];
    }
    int mincut(){
        int ret=INF;
        while(n>1){
            int S,T;
            ret=min(ret,mincutST(S,T));
            if (ret==0) return 0; //图本身就不连通，不需要割
            int tot=0;
            for (int i=1;i<=n;i++)
            if (i!=T) nxt[i]=++tot;
            nxt[T]=nxt[S];
            for (int i=1;i<=n;i++)
                for (int j=1;j<=n;j++) 
                    pe[i][j]=edge[i][j],edge[i][j]=0;
            for (int i=1;i<=n;i++)
                for (int j=1;j<=n;j++) 
                    edge[nxt[i]][nxt[j]]+=pe[i][j];
            n--;            
        }
        return ret;
    }
}SW;

int main(){
    int n,m;
    while(~scanf("%d%d",&n,&m)){
        SW.init(n);
        for (int i=1;i<=m;i++){
            int x,y,z; scanf("%d%d%d",&x,&y,&z);
            x++; y++;
            SW.link(x,y,z);
        }
        printf("%d\n",SW.mincut());
    }
}

