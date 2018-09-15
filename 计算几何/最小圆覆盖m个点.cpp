#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8,pi=acos(-1);
int sgn(double x){
    if (x<-eps) return -1;
    if (x>eps) return 1;
    return 0;
}
double fm(double x){
    while(x>pi) x-=2*pi;
    while(x<-pi) x+=2*pi;
    return x;
}
struct P{
    double x,y;
    double len(){
        return sqrt(x*x+y*y);
    }
    bool operator<(const P &t)const{
        return x<t.x||x==t.x&&y>t.y;
    }
    bool operator==(const P &t)const{
        return x==t.x&&y==t.y;
    }
    P operator-(const P &t)const{
        return {x-t.x,y-t.y};
    }
    double slope(){
        return atan2(y,x);
    }
};
double dis(const P &a,const P &b){
    return (a-b).len();
}

const int N=305;
P a[N],stk[N*2];
bool check(int n,int S,double R){
    int ans=0;
    for (int i=1;i<=n;i++){
        int cnt=0;
        int top=0;
        for (int j=1;j<=n;j++){
            if (a[i]==a[j]){
                cnt++;
                continue;
            }
            if (sgn(dis(a[i],a[j])-2*R)>=0) continue;
            double alpha=acos(dis(a[i],a[j])/2/R);
            double k=(a[j]-a[i]).slope();
            double st=fm(k-alpha),ed=fm(k+alpha);
            if (st<ed){
                stk[++top]={st,1};
                stk[++top]={ed,-1};
            }
            else{
                cnt++;
                stk[++top]={ed,-1};
                stk[++top]={st,1};
            }
        }
        sort(stk+1,stk+top+1);
        if (cnt>=S) return 1;
        for (int i=1;i<=top;i++){
            if (stk[i].y<0) cnt--;
            else cnt++;
            if (cnt>=S) return 1;
        }
    }
    return 0;
}
double solve(int n,int S){
    double l=0,r=0; 
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++) r=max(r,dis(a[i],a[j]));
    while(r-l>1e-6){
        double mid=(l+r)/2;
        if (!check(n,S,mid)) l=mid;
        else r=mid;
    }
    return l;
}
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n,S; scanf("%d%d",&n,&S);
        for (int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
        double R; scanf("%lf",&R);
        if (S>n) printf("The cake is a lie.\n");
        else printf("%.4f\n",solve(n,S)+R);
    }
}

//n*n*log(n)*log(1000/eps)