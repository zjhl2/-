#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld,ld> P;
#define X first
#define Y second
#define O first
#define R second
 
const ld eps=1e-6,pi=acos(-1);
 
int sgn(ld x){
    if (x<-eps) return -1;
    if (x>eps) return 1;
    return 0;
}
void read(ld &x){
    static double d;
    scanf("%lf",&d);
    x=d;
}
 
P operator+(const P &p1,const P &p2){
    return {p1.X+p2.X,p1.Y+p2.Y};
}
P operator-(const P &p1,const P &p2){
    return {p1.X-p2.X,p1.Y-p2.Y};
}
P operator*(const P &p,ld x){
    return {p.X*x,p.Y*x};
}
ld operator*(const P &p1,const P &p2){
    return p1.X*p2.X+p1.Y*p2.Y;
}
ld operator^(const P &p1,const P &p2){
    return p1.X*p2.Y-p2.X*p1.Y;
}
ld len(const P &p){
    return sqrt(p.X*p.X+p.Y*p.Y);
}
ld angle(const P &p1,const P &p2){
    assert(sgn(len(p1))>0&&sgn(len(p2))>0);
    return acos(p1*p2/len(p1)/len(p2));
}
ld dist(const P &p1,const P &p2){
    return len(p1-p2);
}
void rotate(P &p,ld sita){
    P tmp;
    tmp.X=p.X*cos(sita)-p.Y*sin(sita);
    tmp.Y=p.X*sin(sita)+p.Y*cos(sita);
    p=tmp;
}
P foot_to(const P &p,const P &p1,const P &p2){
    P v=p2-p1;
    rotate(v,pi/2);
    ld s1=(p1-p)^(p2-p);
    ld s2=v^(p2-p1);
    v=v*(s1/s2);
    return p+v;
}
 
const int N=205;
P a[N];
P C;
int n;
//tp表示可能的交点个数
ld CIRCLE_LINE(P C,ld R,P p1,P p2,int tp=2){
    if (tp==0){
        if (sgn(dist(C,p1)-R)<=0&&sgn(dist(C,p2)-R)<=0)
            return abs((p1-C)^(p2-C))/2;
        else{
            assert(sgn(dist(C,p1)-R)>=0&&sgn(dist(C,p2)-R)>=0);
            if (sgn((p1-C)^(p2-C))==0) return 0;
            ld sita=angle(p1-C,p2-C);
            return R*R*sita/2;
        }
    }
    P foot=foot_to(C,p1,p2);
    if (tp==1){
        if (sgn(dist(C,p1)-R)<=0&&sgn(dist(C,p2)-R)<=0||
            sgn(dist(C,p1)-R)>=0&&sgn(dist(C,p2)-R)>=0)
            return CIRCLE_LINE(C,R,p1,p2,0);
        if (dist(C,p1)>dist(C,p2)) swap(p1,p2);
        ld d=dist(foot,C);
        ld veclen=sqrt(R*R-d*d);
        P isctp=foot+(p2-foot)*(veclen/dist(p2,foot));
        return CIRCLE_LINE(C,R,p1,isctp,0)+
               CIRCLE_LINE(C,R,isctp,p2,0);
    }
    if (sgn((p1-foot)*(p2-foot))<0)
        return CIRCLE_LINE(C,R,p1,foot,1)+
               CIRCLE_LINE(C,R,foot,p2,1);
    else
        return CIRCLE_LINE(C,R,p1,p2,1);
}
ld getisctarea(const P &C,const ld R){
    ld ret=0;
    for (int i=1;i<=n;i++){
        ld tmp;
        tmp=CIRCLE_LINE(C,R,a[i-1],a[i]);
        if (((a[i-1]-C)^(a[i]-C))>0) ret+=tmp;
        else ret-=tmp;
    }
    return abs(ret);
}
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        read(a[i].X); read(a[i].Y);
    }
    ld area=0;
    a[0]=a[n];
    for (int i=1;i<=n;i++)
        area+=a[i]^a[i-1];
    area=abs(area/2);
    int m; scanf("%d",&m);
    while(m--){
        read(C.X); read(C.Y);
        ld p,q;
        read(p); read(q);
        ld minarea=area*(1-p/q);
        ld l=0,r=2000*sqrt(2)+1;
        while(l<r-eps&&(r-l)/r>eps){
            ld mid=(l+r)/2;
            if (getisctarea(C,mid)<minarea) l=mid;
            else r=mid;
        }
        printf("%.12f\n",double(l));
    }
}