#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
typedef map<ll,ll>::iterator itr;

P operator-(P &a,P &b){
    return {a.x-b.x,a.y-b.y};
}
ll operator*(P &a,P &b){
    return a.x*b.x+a.y*b.y;
}
ll operator^(P &a,P &b){
    return a.x*b.y-a.y*b.x;
}
double slope(P &a,P &b){
    return 1.0*(b.y-a.y)/(b.x-a.x);
}
struct up_hull{
    map<ll,ll>s;
    int tp; //0 up  1 down
    itr mid,l,r,p1,p2;
    void init(){
        s.clear(); 
    }
    itr pre(itr it){
        if (it==s.end()) return it;
        if (it==s.begin()) return s.end();
        return --it;
    }
    itr suc(itr it){
        if (it==s.end()) return it;
        return ++it;
    }
    bool del(P p1,P p2,P p3){
        if (tp==0) return slope(p1,p2)<=slope(p2,p3);
        else return slope(p1,p2)>=slope(p2,p3);
    }
    bool inside(P p){
        if (s.empty()) return 0;
        r=s.lower_bound(p.x);
        if (r==s.end()) return 0;
        if (r->x==p.x) return tp==0?p.y<=r->y:p.y>=r->y;
        if (r==s.begin()) return 0;
        l=r; l--;
        return del(*l,p,*r);  
    }
    void add(P p){
        if (inside(p)) return;
        s[p.x]=p.y;
        mid=s.find(p.x);
        p1=suc(mid); p2=suc(p1);
        while(p1!=s.end()&&p2!=s.end()&&del(*mid,*p1,*p2))  
            s.erase(p1),p1=p2,p2=suc(p2);
        p1=pre(mid); p2=pre(p1);
        while(p1!=s.end()&&p2!=s.end()&&del(*p2,*p1,*mid))  
            s.erase(p1),p1=p2,p2=pre(p2);
    }
}up,down;
int n;
int main(){
    up.tp=0; down.tp=1;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int tp,x,y;
		scanf("%d%d%d",&tp,&x,&y);
		if (tp==1){
			if (!up.inside({x,y})) up.add({x,y});
			if (!down.inside({x,y})) down.add({x,y});
		}
		else{
			printf(up.inside({x,y})&&down.inside({x,y})?"YES\n":"NO\n");
		}
	}
}