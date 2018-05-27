struct ACM
{
    int ch[N][26],fail[N],cnt[N];
    int tot;
    void init()
    {
        tot=0;
        for (int i=0;i<26;i++) ch[tot][i]=0;
        fail[tot]=0; cnt[tot]=0;
    }
    int newnode()
    {
        tot++;
        for (int i=0;i<26;i++) ch[tot][i]=0;
        fail[tot]=0;  cnt[tot]=0;
        return tot;
    }
    void insert(char *s)
    {
        int now=0;
        for (int i=0;s[i];i++)
        {
            int w=s[i]-'a';
            if (!ch[now][w]) ch[now][w]=newnode();
            now=ch[now][w];
        }
        cnt[now]=1;
    }
    void build()
    {
        queue<int>Q;
        fail[0]=0;
        for (int i=0;i<26;i++)
        {
            if (!ch[0][i]) ch[0][i]=0;
            else
            {
                int cch=ch[0][i];
                fail[cch]=0;
                Q.push(cch);
            }
        }
        while(!Q.empty())
        {
            int u=Q.front(); Q.pop();
            for (int i=0;i<26;i++)
            {
                int v=ch[u][i];
                if (v)
                {
                    fail[v]=ch[fail[u]][i];
                    Q.push(v);
                }
                else ch[u][i]=ch[fail[u]][i];
            }
        }
    }
}AC;


//map类通用AC自动机，bzoj 2754，多个长串，多个短串，问长串被匹配数目，以及短串匹配数目，复杂度O(len*log(字符集))

#include<cstdio>
#include<vector>
#include<map>
#include<queue>
using namespace std;
const int N=100005;
vector<int>vecl[20005][2];
vector<int>vecs[50005];

int time;
struct ACM
{
	map<int,int>ch[N];
	map<int,int>::iterator it;
    int fail[N],cnt[N];
    int tot;
    int vis[N],add[N];
    void init()
    {
    	for (int i=0;i<=tot;i++)
		{
			ch[i].clear();
			fail[i]=cnt[i]=add[i]=vis[i]=0;
		}
        tot=0;
    }
    int newnode()
    {
        tot++;
        return tot;
    }
    void insert(const vector<int> &s)
    {
        int now=0;
        for (int i=0;i<s.size();i++)
        {
            int w=s[i];
            if (!ch[now][w]) ch[now][w]=newnode();
            now=ch[now][w];
        }
        cnt[now]++;
    }
    void build()
    {
        queue<int>Q;
        for (it=ch[0].begin();it!=ch[0].end();it++)
        {
			int cch=it->second;
			fail[cch]=0;
			Q.push(cch);
        }
        while(!Q.empty())
        {
            int u=Q.front(); Q.pop();
            for (it=ch[u].begin();it!=ch[u].end();it++)
            {
                int v=it->second;
                int tmp=fail[u];
                while(tmp&&!ch[tmp][it->first]) tmp=fail[tmp];
				fail[v]=ch[tmp][it->first];
				Q.push(v);
            }
        }
    }
    int go(const vector<int> &s)
    {
    	int ret=0;
        int now=0;
        for (int i=0;i<s.size();i++)
        {
            int w=s[i];
            while(now&&!ch[now][w]) now=fail[now];
            now=ch[now][w];
            int tmp=now;
            while(tmp&&vis[tmp]<time)
			{
				vis[tmp]=time;
				ret+=cnt[tmp];
				add[tmp]++;
				tmp=fail[tmp];
			}
        }
        return ret;
    }
    int get(const vector<int> &s)
    {
        int now=0;
        for (int i=0;i<s.size();i++)
        {
            int w=s[i];
            now=ch[now][w];
        }
        return add[now];
    }
}AC;

int ans1[N],ans2[N];
int main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		for (int i=1;i<=n;i++)
		{
			for (int tp=0;tp<2;tp++)
			{
				int k;scanf("%d",&k);
				for (int j=1;j<=k;j++)
				{
					int x; scanf("%d",&x);
					vecl[i][tp].push_back(x);
				}
			}
		}
		AC.init();
		for (int i=1;i<=m;i++)
		{
			int k; scanf("%d",&k);
			for (int j=1;j<=k;j++)
			{
				int x; scanf("%d",&x);
				vecs[i].push_back(x);
			}
			AC.insert(vecs[i]);
		}
		AC.build();
		for (int i=1;i<=n;i++)
		{
			time++;
			ans2[i]=0;
			ans2[i]+=AC.go(vecl[i][0]);
			ans2[i]+=AC.go(vecl[i][1]);
		}
		for (int i=1;i<=m;i++)
			ans1[i]=AC.get(vecs[i]);
		for (int i=1;i<=m;i++) printf("%d\n",ans1[i]);
		for (int i=1;i<=n;i++)
		{
			printf("%d",ans2[i]);
			if (i<n) printf(" ");
		}
		printf("\n");

		for (int i=1;i<=n;i++) vecl[i][0].clear(),vecl[i][1].clear();
		for (int i=1;i<=m;i++) vecs[i].clear();
	}
}

