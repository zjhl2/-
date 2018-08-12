#include<cstdio>
const int N=55;
int a[N][N];
int num[N],n,ans;
int wait[N][N];
bool dfs(int *pre,int tot,int deep){
    if (tot==0){
        if (deep>ans) return ans=deep,1;
        else return 0;
    }
    int *now=wait[deep];
    int tot2;
    for (int i=1;i<=tot;i++){
        if (deep+tot-i+1<=ans) return 0;
        if (deep+num[pre[i]]<=ans) return 0;
        tot2=0;
        for (int j=i+1;j<=tot;j++)
            if (a[pre[i]][pre[j]]) now[++tot2]=pre[j];
        if (dfs(now,tot2,deep+1)) return 1;
    }
    return 0;
}
int maxclique(){
    ans=0;
    for (int i=n;i;i--){
        int *now=wait[0];
        int tot=0;
        for (int j=i+1;j<=n;j++)
            if (a[i][j]) now[++tot]=j;
        dfs(now,tot,1);
        num[i]=ans;
    }
    return ans;
}
int main(){
    while(~scanf("%d",&n)&&n){
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++) scanf("%d",&a[i][j]);
        printf("%d\n",maxclique());
    }
}