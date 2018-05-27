#include<cstdio>
#include<cstring>
using namespace std;
const int N=500000;
int tree[N][26],cnt[N];
char c[20];
int tot;
void add(char* c)
{
    int l=strlen(c);
    int now=0;
    for (int i=0;i<l;i++)
    {
        int w=c[i]-'a';
        if (tree[now][w]==0) tree[now][w]=++tot;
        now=tree[now][w];
        cnt[now]++;
    }
}
int get(char* c)
{
    int l=strlen(c);
    int now=0;
    for (int i=0;i<l;i++)
    {
        int w=c[i]-'a';
        if (tree[now][w]==0) return 0;
        now=tree[now][w];
    }
    return cnt[now];
}
int main()
{
    while(gets(c)&&strcmp(c,"")!=0)
    {
        add(c);
    }
    while(gets(c))
    {
        printf("%d\n",get(c));
    }
}
