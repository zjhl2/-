#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000005 ;
const int CN = 26 ;

int nxt[MAXN][CN] ;//nxt指针，nxt指针和字典树类似，指向的串为当前串两端加上同一个字符构成
int fail[MAXN] ;//fail指针，失配后跳转到fail指针指向的节点
int cnt[MAXN] ;//cnt[i]表示节点i表示的本质不同的串的个数（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
int num[MAXN] ;//num[i]表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
int len[MAXN] ;//len[i]表示节点i表示的回文串的长度
int s[MAXN] ;//存放添加的字符
int diff[MAXN] ;
int slink[MAXN] ;
int sans[MAXN] ;
int last ;//指向上一个字符所在的节点，方便下一次add
int n ;//字符数组指针
int p ;//节点指针

int newnode ( int l ) {//新建节点
    for ( int i = 0 ; i < CN ; ++ i ) nxt[p][i] = 0 ;
    cnt[p] = 0 ;
    num[p] = 0 ;
    len[p] = l ;
    return p ++ ;
}

void init () {//初始化
    p = 0 ;
    newnode (  0 ) ;
    newnode ( -1 ) ;
    last = 0 ;
    n = 0 ;
    s[n] = -1 ;//开头放一个字符集中没有的字符，减少特判
    fail[0] = 1 ;
}

int get_fail ( int x ) {//和KMP一样，失配后找一个尽量最长的
    while ( s[n - len[x] - 1] != s[n] ) x = fail[x] ;
    return x ;
}

void add ( int c ) {
    c -= 'a' ;
    s[++ n] = c ;
    int cur = get_fail ( last ) ;//通过上一个回文串找这个回文串的匹配位置
    if ( !nxt[cur][c] ) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
        int now = newnode ( len[cur] + 2 ) ;//新建节点
        fail[now] = nxt[get_fail ( fail[cur] )][c] ;//和AC自动机一样建立fail指针，以便失配后跳转
        nxt[cur][c] = now ;
        num[now] = num[fail[now]] + 1 ;
        diff[now]=len[now]-len[fail[now]];
        if(diff[now] == diff[fail[now]])
            slink[now] = slink[fail[now]];
        else
            slink[now] = fail[now];
    }
    last = nxt[cur][c] ;
    cnt[last] ++ ;
}

void count () {
    for ( int i = p - 1 ; i >= 0 ; -- i ) 
        cnt[fail[i]] += cnt[i] ;
    //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
}


char s1[MAXN];
char s2[MAXN];

const int N=1000005,mo=1e9+7;
int f[N];
int m;
int main(){
    scanf("%s",s1+1);
    int slen=strlen(s1+1);
    for (int i=1,j=slen;i<=j;i++,j--) 
    {
        s2[++m]=s1[i];
        if (j!=i) s2[++m]=s1[j];
    }
    s2[m+1]=0;
    //printf("%s\n",s2+1);
    init();
    f[0]=1;
    for (int i=1;i<=m;i++){
        add(s2[i]);
        for (int v=last;len[v]>0;v=slink[v]){
            int pos=i-(len[slink[v]]+diff[v]);
            sans[v]=f[pos];
            if (diff[v]==diff[fail[v]])
                sans[v]=(sans[v]+sans[fail[v]])%mo;
            f[i]=(f[i]+sans[v])%mo;
        }
        if (i&1) f[i]=0;
    }
    printf("%d\n",f[m]);
}