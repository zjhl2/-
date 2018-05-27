#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=100005;
struct dot{
    double x,y;
}a[N],c[N];

bool cmpy(dot a,dot b){return a.y<b.y;}
bool cmpx(dot a,dot b){return a.x<b.x;}
double dis2(dot a,dot b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
double dis(dot a,dot b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double get(int l,int r)
{
    if (l==r) return 1e20;
    if (l+1==r) return dis(a[l],a[r]);
    int mid=(l+r)/2;
    double ans=min(get(l,mid),get(mid+1,r));
    int cnt=0;
    for (int i=l;i<=r;i++)
        if (a[i].x>a[mid].x-ans&&a[i].x<a[mid].x+ans) c[++cnt]=a[i];
    sort(c+1,c+cnt+1,cmpy);
    for (int i=1;i<cnt;i++)
        for (int j=i+1;j<=cnt;j++)
        {
            if (c[j].y>c[i].y+ans) break;
            if (dis(c[i],c[j])<ans) ans=dis(c[i],c[j]);
        }
    return ans;
}
int main()
{
    int n;
    while(~scanf("%d",&n)&&n)
    {
        for (int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
        sort(a+1,a+n+1,cmpx);
        printf("%.2f\n",get(1,n)/2);
    }
}

