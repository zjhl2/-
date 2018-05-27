//hdu5955

#include<bits/stdc++.h>
using namespace std;
const int N=105;

int s[15][15];
int ans[15];
int n,l;
double a[N][N];
double x[N];
struct ACM
{
    int ch[N][7],fail[N];
    int tot;
    void clear()
    {
        tot=0;
        for (int i=1;i<=6;i++) ch[tot][i]=0;
        fail[tot]=0;
    }
    int newnode()
    {
        tot++;
        for (int i=1;i<=6;i++) ch[tot][i]=0;
        fail[tot]=0;
        return tot;
    }
    void insert(int id,int *s)
    {
        int now=0;
        for (int i=1;i<=l;i++)
        {
            if (!ch[now][s[i]]) ch[now][s[i]]=newnode();
            now=ch[now][s[i]];
        }
        ans[id]=now;
    }
    void build()
    {
        queue<int>Q;
        fail[0]=0;
        for (int i=1;i<=6;i++)
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
            for (int i=1;i<=6;i++)
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

//列主元法
void gauss(int n)
{
    for (int i=0;i<=n;i++)
    {
		int k=i;
		for (int j=i+1;j<=n;j++)
			if (abs(a[j][i])>abs(a[k][i])) k=j;
        if (k!=i)
            for (int j=0;j<=n+1;j++) swap(a[i][j],a[k][j]);
		for (k=i+1;k<=n;k++)
		{
			double l=a[k][i]/a[i][i];
			for (int j=i;j<=n+1;j++) a[k][j]-=l*a[i][j];
		}
    }
	x[n]=a[n][n+1]/a[n][n];
	for (int i=n-1;i>=0;i--)
	{
		for (int j=i+1;j<=n;j++)
			a[i][n+1]-=a[i][j]*x[j];
		x[i]=a[i][n+1]/a[i][i];
	}
}

//LU分解法
void LU(int n)
{
    for (int i=0;i<=n;i++)
    {
        for (int j=i;j<=n;j++)
            for (int k=0;k<i;k++) a[i][j]-=a[i][k]*a[k][j];
        for (int j=i+1;j<=n;j++)
        {
            for (int k=0;k<i;k++) a[j][i]-=a[j][k]*a[k][i];
            a[j][i]/=a[i][i];
        }
        for (int j=0;j<i;j++) a[i][n+1]-=a[i][j]*a[j][n+1];
    }
    x[n]=a[n][n+1]/a[n][n];
    for (int i=n-1;i>=0;i--)
    {
        for (int j=i+1;j<=n;j++)
            a[i][n+1]-=a[i][j]*x[j];
        x[i]=a[i][n+1]/a[i][i];
    }
}

int main()
{
    int t; scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&l);
        for (int i=1;i<=n;i++)
            for (int j=1;j<=l;j++) scanf("%d",&s[i][j]);
        AC.clear();
        for (int i=1;i<=n;i++) AC.insert(i,s[i]);
        AC.build();
        for (int i=0;i<=AC.tot;i++)
            for (int j=0;j<=AC.tot+1;j++) a[i][j]=0;
        for (int i=0;i<=AC.tot;i++)
        {
            a[i][i]=-1;
            for (int j=1;j<=6;j++)
            {
                int v=AC.ch[i][j];
                a[v][i]+=1.0/6;
            }
        }
        for (int i=1;i<=n;i++)
        {
            int u=ans[i];
            for (int j=1;j<=6;j++)
            {
                int v=AC.ch[u][j];
                a[v][u]-=1.0/6;
            }
        }
        a[0][AC.tot+1]=-1;
        LU(AC.tot);
        for (int i=1;i<=n;i++)
        {
            if (i>1) printf(" ");
            printf("%.6f",x[ans[i]]);
        }
        printf("\n");
    }
}
