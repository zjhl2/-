#include<bits/stdc++.h>
using namespace std;
const int N=100005;

namespace Splay{
    int ch[N][2],fa[N],sz[N],rev[N];
    int val[N];
    int tot,root;
    void init(){
        tot=0;
        root=0;
    }
    int newnode(){
        tot++;
        ch[tot][0]=ch[tot][1]=0;
        fa[tot]=0; sz[tot]=1; rev[tot]=0; 
        val[tot]=0;
        return tot;
    }
    bool get(int x){
        return ch[fa[x]][1]==x;
    }
    void up(int x){
        sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
    }
    void push(int x){
        if (rev[x]){
            rev[x]=0;
            swap(ch[x][0],ch[x][1]);
            rev[ch[x][0]]^=1;
            rev[ch[x][1]]^=1;
        }
    }
    void rotate(int x){
        int old=fa[x],oldf=fa[old];
        int w=get(x);
        ch[old][w]=ch[x][w^1]; fa[ch[old][w]]=old;
        ch[x][w^1]=old; fa[old]=x;
        fa[x]=oldf;
        if (oldf)
            ch[oldf][ch[oldf][1]==old]=x;
        up(old); up(x);
    }
    int stk[N],top;
    void splay(int x,int goal){
        top=0;
        for (int f=x;f!=goal;f=fa[f]) stk[++top]=f;
        for (int i=top;i>=1;i--) push(stk[i]);
        for (int f;(f=fa[x])!=goal;rotate(x))
        if (fa[f]!=goal)
            rotate((get(x)==get(f))?f:x);
        if (goal==0) root=x;
    }
    int find(int u,int k){
        push(u);
        int num=sz[ch[u][0]]+1;
        if (k<num) return find(ch[u][0],k);
        if (k>num) return find(ch[u][1],k-num);
        return u;
    }
    void reverse(int l,int r){
        if (l>r) return;
        int st=find(root,l),ed=find(root,r+2);
        splay(st,0); splay(ed,st); 
        int x=ch[ed][0];
        rev[x]^=1;
    }
}
using namespace Splay;

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    init();
    root=newnode(); val[root]=0;
    for (int i=1;i<=n+1;i++){
        int x=newnode(); val[x]=i;
        ch[root][1]=x; fa[x]=root;
        splay(x,0);
    }
    while(m--){
        int l,r; scanf("%d%d",&l,&r); r+=l-1;
        reverse(1,l-1);
        reverse(l,r);
        reverse(1,r);
    }
    for (int i=2;i<=n+1;i++){
        int x=find(root,i); splay(x,0);
        printf("%d%c",val[x]," \n"[i==n+1]);
    }
}

