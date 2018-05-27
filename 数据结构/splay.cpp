#include<bits/stdc++.h>
using namespace std;
const int N=300005;

int ch[N][2],fa[N],size[N],rev[N];
int root;
int n,m;
char s[10];

bool get(int x)
{
    return ch[fa[x]][1]==x;
}
void update(int x)
{
	if (x==0) root/=0;
	size[x]=1;
	if (ch[x][0]) size[x]+=size[ch[x][0]];
	if (ch[x][1]) size[x]+=size[ch[x][1]];
}
void pushdown(int x)
{
	if (rev[x])
	{
		rev[x]=0;
		swap(ch[x][0],ch[x][1]);
		if (ch[x][0]) rev[ch[x][0]]^=1;
		if (ch[x][1]) rev[ch[x][1]]^=1;
	}
}
void rotate(int x)
{
    int old=fa[x],oldf=fa[old];
    int whichx=get(x);
    ch[old][whichx]=ch[x][whichx^1]; fa[ch[old][whichx]]=old;
    ch[x][whichx^1]=old; fa[old]=x;
    fa[x]=oldf;
    if (oldf)
        ch[oldf][ch[oldf][1]==old]=x;
    update(old); update(x);
}
int stk[N],top;
void splay(int x,int goal)
{
	top=0;
	for (int f=x;f!=goal;f=fa[f]) stk[++top]=f;
	for (int i=top;i>=1;i--) pushdown(stk[i]);
	for (int f;(f=fa[x])!=goal;rotate(x))
	  if (fa[f]!=goal)
        rotate((get(x)==get(f))?f:x);
	if (goal==0) root=x;
}
int find(int k)
{
    int now=root;
    //if (k<1||k>size[now]) root/=0;
    while(1)
	{
		//if (now==0) root/=0;
		pushdown(now);
		int tmp=size[ch[now][0]]+1;
        if (k<tmp) now=ch[now][0];
        if (k==tmp) return now;
        if (k>tmp) now=ch[now][1],k-=tmp;
    }
}
int nxt()
{
	int now=root;
	pushdown(now);
	now=ch[now][1];
	pushdown(now);
	while(ch[now][0]) now=ch[now][0],pushdown(now);
	return now;
}
int cnt;
void dfs(int u)
{
	pushdown(u);
	if (ch[u][0]) dfs(ch[u][0]);
	cnt++;
	if (cnt>1) printf(" ");
	printf("%d",u-1);
	if (ch[u][1]) dfs(ch[u][1]);
}
void look(int n)
{
	splay(1,0);
	splay(n,1);
	cnt=0;
	dfs(ch[n][0]);
	printf("\n");
}
int main()
{
	while(scanf("%d%d",&n,&m),n>=0)
	{
		n+=2;
		root=1;
		for (int i=1;i<=n;i++)
		{
			if (i<n) ch[i][1]=i+1;
			else ch[i][1]=0;
			ch[i][0]=0;
			fa[i]=i-1;
			size[i]=n-i+1;
			rev[i]=0;
		}
		//look(n);
		while(m--)
		{
			scanf("%s",s);
			if (strcmp(s,"CUT")==0)
			{
				int a,b,c; scanf("%d%d%d",&a,&b,&c);
				a++; b++; c++;
				int l=find(a-1); splay(l,0);
				int r=find(b+1); splay(r,l);
				int now=ch[r][0];
				ch[r][0]=0; fa[now]=0;
				size[l]-=size[now];
				size[r]-=size[now];
				splay(r,0);
				//if (size[root]!=n-(b-a+1)) root/=0;
				//if (c<1||c>=n-size[now]) root/=0;
				int x=find(c); splay(x,0);
				//int z=nxt();
				int y=find(c+1); splay(y,x);
				//if (z!=y) root/=0;
				ch[y][0]=now;
				fa[now]=y;
				size[x]+=size[now];
				size[y]+=size[now];
				splay(now,0);
				//if (size[root]!=n) root/=0;
				//look(n);
			}
			else
			{
				//if (strcmp(s,"FLIP")!=0) root/=0;
				int a,b; scanf("%d%d",&a,&b);
				a++; b++;
				int l=find(a-1); splay(l,0);
				int r=find(b+1); splay(r,l);
				int now=ch[r][0];
				rev[now]^=1;
				//look(n);
			}
			if (size[0]!=0) root/=0;
		}
		look(n);
	}
}
/*

300000 7
CUT 1 99 1
CUT 1 99 1
CUT 1 99 1
CUT 1 99 1
CUT 1 99 1
FLIP 1 100
FLIP 1 2
*/



//网上的优秀模板
#include<iostream>  
#include<cstring>  
#include<cstdio>  
using namespace std;  
#define MAXN 1000000  
int ch[MAXN][2],f[MAXN],size[MAXN],cnt[MAXN],key[MAXN];   //cnt表示出现次数
int sz,root;  
inline void clear(int x){  
    ch[x][0]=ch[x][1]=f[x]=size[x]=cnt[x]=key[x]=0;  
}  
inline bool get(int x){  
    return ch[f[x]][1]==x;  
}  
inline void update(int x){  
    if (x){  
        size[x]=cnt[x];  
        if (ch[x][0]) size[x]+=size[ch[x][0]];  
        if (ch[x][1]) size[x]+=size[ch[x][1]];  
    }  
}  
inline void rotate(int x){  
    int old=f[x],oldf=f[old],whichx=get(x);  
    ch[old][whichx]=ch[x][whichx^1]; f[ch[old][whichx]]=old;  
    ch[x][whichx^1]=old; f[old]=x;  
    f[x]=oldf;  
    if (oldf)  
        ch[oldf][ch[oldf][1]==old]=x;  
    update(old); update(x);  
}  
inline void splay(int x){  
    for (int fa;fa=f[x];rotate(x))  
      if (f[fa])  
        rotate((get(x)==get(fa))?fa:x);  
    root=x;  
}  
inline void splay(int x,int goal){
	for (int fa;(fa=f[x])!=goal;rotate(x))
	  if (f[fa]!=goal)
        rotate((get(x)==get(fa))?fa:x);  
	root=x;
}
		
inline void insert(int x){  
    if (root==0){sz++; ch[sz][0]=ch[sz][1]=f[sz]=0; root=sz; size[sz]=cnt[sz]=1; key[sz]=x; return;}  
    int now=root,fa=0;  
    while(1){  
        if (x==key[now]){  
            cnt[now]++; update(now); update(fa); splay(now); break;  
        }  
        fa=now;  
        now=ch[now][key[now]<x];  
        if (now==0){  
            sz++;  
            ch[sz][0]=ch[sz][1]=0;  
            f[sz]=fa;  
            size[sz]=cnt[sz]=1;  
            ch[fa][key[fa]<x]=sz;  
            key[sz]=x;  
            update(fa);  
            splay(sz);  
            break;  
        }  
    }  
}  
inline int find(int x){  //查询x的排名
    int now=root,ans=0;  
    while(1){  
        if (x<key[now])  
          now=ch[now][0];  
        else{  
            ans+=(ch[now][0]?size[ch[now][0]]:0);  
            if (x==key[now]){  
                splay(now); return ans+1;  
            }  
            ans+=cnt[now];  
            now=ch[now][1];  
        }  
    }  
}  
inline int findx(int x){  //查询第k大
    int now=root;  
    while(1){  
        if (ch[now][0]&&x<=size[ch[now][0]])  
          now=ch[now][0];  
        else{  
            int temp=(ch[now][0]?size[ch[now][0]]:0)+cnt[now];  
            if (x<=temp) return key[now];  
            x-=temp; now=ch[now][1];  
        }  
    }  
}  
inline int pre(){  
    int now=ch[root][0];  
    while (ch[now][1]) now=ch[now][1];  
    return now;  
}  
inline int next(){  
    int now=ch[root][1];  
    while (ch[now][0]) now=ch[now][0];  
    return now;  
}  
inline void del(int x){  
    int whatever=find(x);  
    if (cnt[root]>1){cnt[root]--; update(root); return;}  
    if (!ch[root][0]&&!ch[root][1]) {clear(root); root=0; return;}  
    if (!ch[root][0]){  
        int oldroot=root; root=ch[root][1]; f[root]=0; clear(oldroot); return;  
    }  
    else if (!ch[root][1]){  
        int oldroot=root; root=ch[root][0]; f[root]=0; clear(oldroot); return;  
    }  
    int leftbig=pre(),oldroot=root;  
    splay(leftbig);  
    ch[root][1]=ch[oldroot][1];  
    f[ch[oldroot][1]]=root;  
    clear(oldroot);  
    update(root);   
}  
int main(){  
    int n,opt,x;  
    scanf("%d",&n);  
    for (int i=1;i<=n;++i){  
        scanf("%d%d",&opt,&x);  
        switch(opt){  
            case 1: insert(x); break;  
            case 2: del(x); break;  
            case 3: printf("%d\n",find(x)); break;  
            case 4: printf("%d\n",findx(x)); break;  
            case 5: insert(x); printf("%d\n",key[pre()]); del(x); break;  
            case 6: insert(x); printf("%d\n",key[next()]); del(x); break;  
        }  
    }  
}  