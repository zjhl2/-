#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int N=100005;

struct P{
    double x,y;
    double len()const {
        return sqrt(x*x+y*y);
    }
    P operator+(const P &t)const{
        return {x+t.x,y+t.y};
    }
    P operator-(const P &t)const{
        return {x-t.x,y-t.y};
    }
	P operator/(double t)const{
    	return {x/t,y/t};
    }
}a[N];

double dis(const P &a,const P &b){
    return (a-b).len();
}

bool incircle(const P &a,const P &O,double R){
    return dis(a,O)<=R;
}

P circumcenter(const P &a,const P &b,const P &c){
	P ret; 
	double a1=b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1)/2;
	double a2=c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2)/2;
	double d=a1*b2-a2*b1;
	ret.x=a.x+(c1*b2-c2*b1)/d;
	ret.y=a.y+(a1*c2-a2*c1)/d;
	return ret; 
}

int main(){
    int n; 
    while(scanf("%d",&n),n){
        for (int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
        random_shuffle(a+1,a+n+1);
        double R=0; P O={0,0};
        for (int i=1;i<=n;i++) 
        if (!incircle(a[i],O,R)){
            O=a[i]; R=0;
            for (int j=1;j<i;j++) 
            if (!incircle(a[j],O,R)){
                O=(a[i]+a[j])/2; R=dis(O,a[i]);
                for (int k=1;k<j;k++)
                if (!incircle(a[k],O,R)){
                    //i'm sure i,j,k not on the same line
                    O=circumcenter(a[i],a[j],a[k]);
                    R=dis(a[i],O);
                }
            }
        }
        printf("%.2f %.2f %.2f\n",O.x,O.y,R);
    }

}