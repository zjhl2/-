#include<bits/stdc++.h>
using namespace std;

const int N=100005;
const double eps=1e-8;
int sgn(double x){
    if (x>eps) return 1;
    if (x<-eps) return -1;
    return 0;
}
struct P{ 
    double x,y;
    P operator+(const P &b)const{
        return {x+b.x,y+b.y};
    }
    P operator-(const P &b)const{
        return {x-b.x,y-b.y};
    }
    double operator^(const P &b)const{
        return x*b.y-y*b.x;
    }
    P operator*(double t)const{
        return {x*t,y*t};
    }
}a[N],p[N];
struct L{
    P p,v;
    double k;
    bool operator<(const L &l)const{
        return k<l.k;
    }
}line[N],stk[N];
bool left(const P &p,const L &l){
    return sgn(l.v^(p-l.p))>0;
}
P isct(const L &a,const L &b){
    P v1=b.p-a.p; 
    double tmp=(v1^b.v)/(a.v^b.v);
    return a.p+a.v*tmp;
}
int tot;
int head,tail;
double halfplane(){
    for (int i=1;i<=tot;i++) line[i].k=atan2(line[i].v.y,line[i].v.x);
    sort(line+1,line+tot+1);
    head=tail=1;
    stk[1]=line[1];
    for (int i=2;i<=tot;i++){
        while(head<tail&&!left(p[tail-1],line[i])) tail--;
        while(head<tail&&!left(p[head],line[i])) head++;
// cout<<(stk[tail].v^line[i].v)<<endl;
        if (sgn(stk[tail].v^line[i].v)==0) 
            stk[tail]=left(stk[tail].p,line[i])?stk[tail]:line[i];
        else stk[++tail]=line[i];
        if (head<tail) p[tail-1]=isct(stk[tail],stk[tail-1]);
    }
    while(head<tail&&!left(p[tail-1],stk[head])) tail--;
    p[tail]=isct(stk[tail],stk[head]);
    if (tail-head+1<=2) return 0;
    double ret=0;
    for (int i=head;i<tail;i++) ret+=p[i]^p[i+1];
    ret+=p[tail]^p[head];
    return abs(ret)/2;
}
int main(){
    int n; 
    while(scanf("%d",&n),n){
        double area=0;
        for (int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
        a[0]=a[n];
        tot=0;
        for (int i=1;i<=n;i++){
            line[++tot]={a[i],a[i-1]-a[i]};
            area+=a[i]^a[i-1];
        }
        scanf("%d",&n);
        for (int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
        a[0]=a[n];
        for (int i=1;i<=n;i++){
            line[++tot]={a[i],a[i-1]-a[i]};
            area+=a[i]^a[i-1];
        }
        printf("%8.2f",area/2-2*halfplane());
    }
    puts("");
}
