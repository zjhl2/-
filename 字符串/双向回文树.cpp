#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Palindromic_Tree{
    static const int maxN=200005,CN=26;
    int ch[maxN][CN];
    int fail[maxN],len[maxN],num[maxN],cnt[maxN];
    int str[maxN],L,R;
    int last[2],tot;
    ll sum;
    int newnode(int _len){
        tot++;
        for (int i=0;i<CN;i++) ch[tot][i]=0;
        len[tot]=_len;
        num[tot]=cnt[tot]=0;
        return tot;
    }
    void init(){
        tot=-1; sum=0;
        newnode(0); newnode(-1);
        fail[0]=1; fail[1]=0;
        last[0]=last[1]=0;
        L=maxN/2; R=L-1;
        str[L-1]=str[R+1]=-1;
    }
    int getfail(int x,bool right){
        if (right) 
            while(str[R-1-len[x]]!=str[R]) 
                x=fail[x];
        else
            while(str[L+1+len[x]]!=str[L]) 
                x=fail[x];
        return x;
    }
    void insert(int w,bool right){
        if (right) str[++R]=w,str[R+1]=-1;
        else str[--L]=w,str[L-1]=-1;
        int u=getfail(last[right],right);
        if (!ch[u][w]){
            int v=newnode(len[u]+2);
            fail[v]=ch[getfail(fail[u],right)][w];
            ch[u][w]=v;
            num[v]=num[fail[v]]+1;
        }
        last[right]=ch[u][w];
        if (len[last[right]]==R-L+1) last[!right]=last[right];
        cnt[last[right]]++;
        sum+=num[last[right]];
    }
    void count(){
        for (int i=tot;i>=0;i--) cnt[fail[i]]+=cnt[i];
    }
}G;

int main(){
    int n;
    while(~scanf("%d",&n)){
        G.init();
        for (int i=1;i<=n;i++){
            int tp; scanf("%d",&tp);
            if (tp<=2){
                char s[3];
                scanf("%s",s);
                G.insert(s[0]-'a',tp-1);
            }
            if (tp==3) printf("%d\n",G.tot-1);
            if (tp==4) printf("%lld\n",G.sum);
        }
    }
}