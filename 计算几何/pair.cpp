#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld,ld> P;
#define X first
#define Y second
 
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
