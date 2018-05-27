#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=200005;
int s[N];  


//注意数组开多少
struct ST 
{
    int f[N][20];
    void make(int *a,int n)
    {
        for (int i=1;i<=n;i++) f[i][0]=a[i];
        for (int j=1;j<20;j++)
            for (int i=1;i<=n+1-(1<<j);i++)
                f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
    }
    int get(int l,int r)
    {
        int k=log(r-l+1)/log(2);
        return min(f[l][k],f[r+1-(1<<k)][k]);
    }
}H;
struct suffixarray
{
    int sa[N],rk[N],h[N];
    int cnt[N],sa2[N],rk2[N];
    int n;
    bool cmp(int i,int j,int len)
    {
        if (rk2[i]==rk2[j]&&rk2[i+len]==rk2[j+len]) return 0;
        return 1;
    } 
    void make(int *s,int len)
    {
        s[len+1]=-1;  //按情况修改
        n=len;
        int m=9;   //按情况修改
        for (int i=0;i<=m;i++) cnt[i]=0;   
        for (int i=1;i<=n;i++) cnt[s[i]]++;
        for (int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
        for (int i=n;i>=1;i--) sa[cnt[s[i]]--]=i;
        int k=1; rk[sa[1]]=1;
        for (int i=2;i<=n;i++)
        {
            if (s[sa[i]]!=s[sa[i-1]]) k++;
            rk[sa[i]]=k;
        }
        rk2[n+1]=0;
        for (int j=1;k<n&&j<=n;j*=2)
        {
            int tot=0;
            for (int i=n-j+1;i<=n;i++) sa2[++tot]=i;
            for (int i=1;i<=n;i++)
                if (sa[i]>j) sa2[++tot]=sa[i]-j;
            m=k;
            for (int i=1;i<=m;i++) cnt[i]=0;
            for (int i=1;i<=n;i++) cnt[rk[i]]++;
            for (int i=2;i<=m;i++) cnt[i]+=cnt[i-1];
            for (int i=n;i>=1;i--) sa[ cnt[rk[sa2[i]]]-- ]=sa2[i];
            for (int i=1;i<=n;i++) rk2[i]=rk[i];
            k=1; rk[sa[1]]=1;
            for (int i=2;i<=n;i++)
            {
                if (cmp(sa[i],sa[i-1],j)) k++;
                rk[sa[i]]=k;
            }
        }
        for (int i=1;i<=n;i++)
        {
            if (rk[i]==1)
            {
                h[rk[i]]=0;  //这里很容易错
                continue;
            }
            k=h[rk[i-1]];
            if (k>0) k--;
            int j=sa[rk[i]-1];
            while(s[i+k]==s[j+k]) k++;
            h[rk[i]]=k;
        }
    }
    int lcp(ST &H,int i,int j)
    {
        int l=rk[i],r=rk[j];  //是否有l==r
        if (l>r) swap(l,r);
        return H.get(l+1,r);
    }
    void show()
	{
		for (int i=1;i<=n;i++)
        {
            for (int j=sa[i];j<=n;j++)
             printf("%d",s[j]);
            printf(" %d\n",h[i]);
        }
	}
}SA;
void solve(int len,int n,int m)
{
    H.make(SA.h,len);
    int i=1,j=1;
    while(i<=n||j<=m)
    {
        if (i>n)
        {
            printf("%d",s[n+1+j]);
            j++;
            continue;
        }
        if (j>m)
        {
            printf("%d",s[i]);
            i++;
            continue;
        }
        int p=SA.lcp(H,i,n+1+j);
        if (s[i+p]>s[n+1+j+p])
        {
            printf("%d",s[i]);
            i++;
            continue;
        }
        else
        {
            printf("%d",s[n+1+j]);
            j++;
            continue;
        }
    }
    printf("\n");
}
int main()
{
    int t; scanf("%d",&t);
    int cas=0;
    while(t--)
    {
        int n,m; scanf("%d%d",&n,&m);
        s[0]=-1;
        for (int i=1;i<=n;i++) scanf("%d",&s[i]);
        s[n+1]=0;
        for (int i=1;i<=m;i++) scanf("%d",&s[n+1+i]);
        printf("Case %d: ",++cas);
        SA.make(s,n+1+m);
        //SA.show();
        solve(n+1+m,n,m);
    }
}
/*
1
5 5
9 8 7 6 5
9 8 7 6 3


098763 5
3 0
5098763 0
63 1
65098763 1
763 2
765098763 2
8763 3
8765098763 3
98763 4
98765098763 4
*/
