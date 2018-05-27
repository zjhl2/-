#include<bits/stdc++.h>
//#include<cstdio>
//#include<cmath>
//#include<algorithm>
using namespace std;
typedef long double lod; //long long 或者long double
typedef long long ll;
typedef long double ld;
const ld eps=1e-8;
const ld pi=acos(-1.0);
int sgn(ld x)
{
	if (x<-eps) return -1;
	if (x>eps) return 1;
	return 0;
}

struct P; //点，向量
struct LINE; //线段，射线，直线;
struct CIRCLE;
struct TRIANGLE;
struct POLYGON;

void kr(ld &x)
{
	double t; scanf("%lf",&t);
	x=t;
}
void kr(ll &x)
{
	scanf("%lld",&x);
}
struct P
{
	lod x,y;
	void read()
	{
		kr(x); kr(y);
	}
    P operator+(const P &t)const
    {
        return {x+t.x,y+t.y};
    }
    P operator-(const P &t)const
    {
        return {x-t.x,y-t.y};
    }
    P operator*(ld t)const
    {
    	return {x*t,y*t};
    }
	P operator/(ld t)const
    {
    	return {x/t,y/t};
    }
    lod operator*(const P &t)const
    {
        return x*t.y-y*t.x;
	} //叉积
    lod operator%(const P &t)const
    {
        return x*t.x+y*t.y;
    } //点积
    bool operator<(const P &t)const
    {
    	return sgn(x-t.x)<0||sgn(x-t.x)==0&&sgn(y-t.y)<0;
    }
    bool operator==(const P &t)const
    {
    	return sgn(x-t.x)==0&&sgn(y-t.y)==0;
    }
    ld ang()const
    {
    	return atan2(y,x);
    }
    ld length()const
    {
    	return sqrt(x*x+y*y);
    }
	P rotate(const P &t,ld sita)const
	{
		return {(x-t.x)*cos(sita)-(y-t.y)*sin(sita)+t.x,
				(x-t.x)*sin(sita)+(y-t.y)*cos(sita)+t.y};
	} //逆时针转sita
	ld btang(const P &t)const
	{
		return acos( (*this%t)/length()/t.length() );
	} //向量夹角
	P midvec(const P &t)const
	{
		return (*this)/length()+t/t.length();
	} //角平分向量
};

struct LINE
{
	P p1,p2;
	void read()
	{
		p1.read(); p2.read();
	}
	LINE midLINE()
	{
        P midp=(p1+p2)/2;
        P v=p2-p1;
        v=v.rotate({0,0},pi/2);
        return {midp,midp+v};
	} //中垂线
    bool have1(const P &p)const
    {
    	return sgn( (p-p1)*(p-p2) )==0&&sgn( (p-p1)%(p-p2) )<=0;
    } //线段上有点
	bool have2(const P &p)const
    {
    	return sgn( (p-p1)*(p-p2) )==0&&sgn( (p-p1)%(p2-p1) )>=0;
    } //射线上有点
	bool have3(const P &p)const
    {
    	return sgn( (p-p1)*(p-p2) )==0;
    } //直线上有点
    lod areawith(const P &p)const
    {
    	return abs( (p1-p)*(p2-p)/2 );
    } //线段和点围成面积
    P vecfrom(const P &p)const
    {
		P v=(p2-p1);
		v=v.rotate({0,0},pi/2);
		ld s1=(p1-p)*(p2-p);
		ld s2=v*(p2-p1);
		v=v*(s1/s2);
		return v;
    }//点到直线垂足的向量
    P footfrom(const P &p)const
    {
		P v=vecfrom(p);
		return p+v;
    } //点到直线垂足
    ld dis1from(const P &p)const
    {
    	P foot=footfrom(p);
		if (have1(foot)) return (foot-p).length();
		return min( (p1-p).length(),(p2-p).length());
    }//点到线段距离
    ld dis2from(const P &p)const
    {
    	P foot=footfrom(p);
		if (have2(foot)) return (foot-p).length();
		return (p1-p).length();
    }//点到射线距离
    ld dis3from(const P &p)const
    {
		return vecfrom(p).length();
    }//点到直线距离
    P symP(const P &p)const
    {
        P v=vecfrom(p);
        return p+v*2;
    } //点关于直线的对称点



	//1线段 2射线 3直线
	bool isct11(const LINE &L)const
	{
		P a1=p1,a2=p2;
		P b1=L.p1,b2=L.p2;
		if (sgn( max(a1.x,a2.x)-min(b1.x,b2.x) )<0||
			sgn( max(b1.x,b2.x)-min(a1.x,a2.x) )<0||
			sgn( max(a1.y,a2.y)-min(b1.y,b2.y) )<0||
			sgn( max(b1.y,b2.y)-min(a1.y,a2.y) )<0)
				return 0;
		lod tmp1=(a2-a1)*(b1-a1);
		lod tmp2=(a2-a1)*(b2-a1);
		if (sgn(tmp1)<0&&sgn(tmp2)<0||sgn(tmp1)>0&&sgn(tmp2)>0) return 0;
		tmp1=(b2-b1)*(a1-b1);
		tmp2=(b2-b1)*(a2-b1);
		if (sgn(tmp1)<0&&sgn(tmp2)<0||sgn(tmp1)>0&&sgn(tmp2)>0) return 0;
		return 1;
	}
	bool isct21(const LINE &L)const
	{
		P v=p2-p1;
		P a=p1;
		P b1=L.p1,b2=L.p2;
		lod tmp1=v*(b1-a);
		lod tmp2=v*(b2-a);
		if (sgn(tmp1)<0&&sgn(tmp2)<0||sgn(tmp1)>0&&sgn(tmp2)>0) return 0;
		if (tmp1>tmp2) swap(b1,b2);
		if (sgn( (b1-a)*(b2-a) )>0) return 1;
		if (sgn( (b1-a)*(b2-a) )<0) return 0;
		//最后排除共线但不相交的情况
		return L.have1(a)||have2(b1)||have2(b2);
	}
	bool isct31(const LINE &L)const
	{
		P v=p2-p1;
		P a=p1;
		lod tmp1=v*(L.p1-a);
		lod tmp2=v*(L.p2-a);
		if (sgn(tmp1)<0&&sgn(tmp2)<0||sgn(tmp1)>0&&sgn(tmp2)>0) return 0;
		return 1;
	}
	bool isct22(const LINE &L)const
	{
		if (have2(L.p1)||L.have2(p1)) return 1;
		P v=vecfrom(L.p1);
		if (sgn( v%(L.p2-L.p1) )<=0) return 0;
		v=L.vecfrom(p1);
		if (sgn( v%(p2-p1) )<=0) return 0;
		return 1;
	}
	bool isct32(const LINE &L)const
	{
		if (have3(L.p1)) return 1;
		P v=vecfrom(L.p1);
		if (sgn( v%(L.p2-L.p1) )<=0) return 0;
		return 1;
	}
	bool isct33(const LINE &L)const
	{
		if (have3(L.p1)) return 1;
		return sgn( (p2-p1)*(L.p2-L.p1) )!=0;
	}

	//前提是不重合且有交点,p1沿p2-p1方向到达L上的长度，负数表示反向
	//直线交多边形需要用到
	ld dis33(const LINE &L)const
	{
		return (L.p1-p1)*(L.p2-p1) / ( (p2-p1)*(L.p2-L.p1) )
				* (p2-p1).length();
	}
	P isctPoint(const LINE &L)const
	{
		ld len=dis33(L);
		P v=p2-p1;
		return p1+v*(len/v.length());
	}//直线交点坐标

};

struct CIRCLE
{
	P cent;
	lod r;
	void read()
	{
		cent.read(); kr(r);
	}
	ld area()const
	{
		return pi*r*r;
	}
	bool have(const P &p)const
	{
		return sgn( (p-cent).length()-r ) <=0;
	}//点在圆内
	P LeftcutPoint(const P &p)const
	{
		P v=p-cent;
        ld sita=acos(r/v.length());
        v=v.rotate({0,0},sita);
        v=v/v.length()*r;
        return cent+v;
	}//左切点
	P RightcutPoint(const P &p)const
	{
		P v=p-cent;
        ld sita=acos(r/v.length());
        v=v.rotate({0,0},-sita);
        v=v/v.length()*r;
        return cent+v;
	}//右切点
	bool isct3(const LINE &L)const
	{
		return sgn(L.dis3from(cent)-r)<=0;
	}//圆与直线相交
	P vecto(const LINE &L)const
	{
		P v=L.p2-L.p1;
		v=v.rotate({0,0},pi/2);
		if (sgn(v%(L.p1-cent))<0) v=v.rotate({0,0},pi);
		return v/v.length()*r;
	}//从圆心垂直射向直线的向量，长度为r
	P LeftisctPoint(const LINE &L)const
	{
		P v=vecto(L);
		ld d=L.dis3from(cent);
		ld sita=acos(d/r);
		return cent+v.rotate({0,0},sita);
	}//左交点
	P RightisctPoint(const LINE &L)const
	{
		P v=vecto(L);
		ld d=L.dis3from(cent);
		ld sita=acos(d/r);
		return cent+v.rotate({0,0},-sita);
	}//右交点
	bool separate(const CIRCLE &C)const
	{
		ld d=(cent-C.cent).length();
		return sgn(r+C.r-d)<=0;
	}//相离
	bool contain(const CIRCLE &C)const
	{
		if (sgn(r-C.r)<0) return 0;
		ld d=(cent-C.cent).length();
		return sgn( d+C.r-r)<=0;
	}//包含
	ld isctarea(const CIRCLE &C)const
	{
		if (separate(C)) return 0;
		if (contain(C)) return C.area();
		if (C.contain(*this)) return area();
		ld d=(cent-C.cent).length();
		ld ang1=acos( (r*r+d*d-C.r*C.r)/2/r/d );
		ld ang2=acos( (C.r*C.r+d*d-r*r)/2/C.r/d);
		return ang1*r*r+ang2*C.r*C.r
			   -r*r*sin(2*ang1)/2-C.r*C.r*sin(2*ang2)/2;
	}//圆相交面积，分两个三角形减，否则被codeforces卡精度
};


struct TRIANGLE
{
	P a[3];
	void read()
	{
		for (int i=0;i<3;i++) a[i].read();
	}
	ld area()const
	{
		ld ret=0;
		for (int i=0;i<3;i++)
			ret+=a[i]*a[(i+1)];
		return abs(ret);
	}
	P center1()const
	{
		return (a[0]+a[1]+a[2])/3;
	}//重心
	P center2()const
	{
		LINE L1={a[0],a[1]};
		LINE L2={a[1],a[2]};
		return L1.midLINE().isctPoint(L2.midLINE());
	}//外心
	P center3()const
	{
		P v0=(a[1]-a[0]).midvec(a[2]-a[0]);
		P v1=(a[0]-a[1]).midvec(a[2]-a[1]);
		LINE L1={a[0],a[0]+v0};
		LINE L2={a[1],a[1]+v1};
		return L1.isctPoint(L2);
	}//内心
	bool have(const P &p)const
	{
		lod tmp1=0;
		for (int i=0;i<3;i++)
			tmp1+=a[i]*a[(i+1)%3];
		tmp1=abs(tmp1);
		lod tmp2=0;
		for (int i=0;i<3;i++)
			tmp2+=abs( (a[i]-p)*(a[(i+1)%2]-p) );
		return sgn(tmp1-tmp2)==0;
	}//点在三角形内
	bool isctLINE1(const LINE &L)const
	{
		for (int i=0;i<3;i++)
		{
			LINE R={a[i],a[(i+1)%3]};
			if (L.isct11(R)) return 1;
		}
		return 0;
	}//与线段相交
	bool isctLINE2(const LINE &L)const
	{
		for (int i=0;i<3;i++)
		{
			LINE R={a[i],a[(i+1)%3]};
			if (L.isct21(R)) return 1;
		}
		return 0;
	}//与射线相交
	bool isctLINE3(const LINE &L)const
	{
		for (int i=0;i<3;i++)
		{
			LINE R={a[i],a[(i+1)%3]};
			if (L.isct31(R)) return 1;
		}
		return 0;
	}//与直线相交
	P FirstisctPoint(const LINE &L)const;//与有向直线第一个交点
	P SecondisctPoint(const LINE &L)const;//与有向直线第二个交点

	bool isct(const TRIANGLE &TRI)const
	{
		for (int i=0;i<3;i++)
		{
			LINE L={a[i],a[(i+1)%3]};
			for (int j=0;j<3;j++)
			{
				LINE R={TRI.a[j],TRI.a[(j+1)%3]};
				if (L.isct11(R)) return 1;
			}
		}
		return 0;
	}//三角形相交
	bool contain(const TRIANGLE &TRI)const
	{
		for (int j=0;j<3;j++)
			if (!have(TRI.a[j])) return 0;
		return 1;
	}//当前三角形包含TRI
	bool separate(const TRIANGLE &TRI)const
	{
		return !isct(TRI)&&!contain(TRI)&&!TRI.contain(*this);
	}//互相分离
	ld isctarea(const TRIANGLE &TRI)const;
};




const int POLNUM=1005;
struct PL
{
	ld len;
	int v;
}stk[POLNUM];
int top;
bool cmplen(const PL &a,const PL &b)
{
	return a.len<b.len;
}
P cent;
bool cmpang(const P &p1,const P &p2)
{
	int tmp=sgn( (p1-cent).ang() - (p2-cent).ang() );
	if (tmp!=0) return tmp<0;
	return (p1-cent).length() < (p2-cent).length();
}
struct POLYGON
{
	int n;
	P a[POLNUM];
	void read(int k)
	{
		for (int i=1;i<=k;i++) a[i].read();
		n=k;
	}
	void ChangetoConvex()
	{
		for (int i=2;i<=n;i++)
			if (a[i].x<a[1].x||a[i].x==a[1].x&&a[i].y<a[1].y)
				swap(a[1],a[i]);
		cent=a[1];
		sort(a+2,a+n+1,cmpang);
		int top=2;
		for (int i=3;i<=n;i++)
		{
			while(top>=2&&
				sgn((a[top]-a[top-1])*(a[i]-a[top]))<=0 )
					top--;
			a[++top]=a[i];
		}
		n=top;
	}//变凸包！(逆时针)
	ld Clength()const
	{
		ld ret=0;
		for (int i=2;i<=n;i++) ret+=(a[i]-a[i-1]).length();
		if (n>2) ret+=(a[1]-a[n]).length(); //防止n==2重复计算
		return ret;
	}//周长
	bool have(const P p)
	{
		int k,d1,d2,wn=0;
		a[0]=a[n];
		for (int i=1;i<=n;i++)
		{
			LINE L={a[i-1],a[i]};
			if (L.have1(p)) return 1;
			k=sgn( (a[i]-a[i-1])*(p-a[i-1]) );
			d1=sgn( a[i-1].y-p.y );
			d2=sgn( a[i].y-p.y );
			if (k>0&&d1<=0&&d2>0) wn++;
			if (k<0&&d2<=0&&d1>0) wn--;
		}
		return wn!=0;
	}//点在多边形内
	ld cutlength(const LINE &L)
	{
		a[0]=a[n]; top=0;
		for (int i=1;i<=n;i++)
		{
			LINE R={a[i-1],a[i]};
			lod s1=sgn( (L.p2-L.p1)*(R.p1-L.p1) );
			lod s2=sgn( (L.p2-L.p1)*(R.p2-L.p1) );
			if (s1<0&&s2<0||s1==0&&s2==0||s1>0&&s2>0) continue;
			if (s1<s2) stk[++top]={L.dis33(R),(s1!=0&&s2!=0?2:1)};
			else stk[++top]={L.dis33(R),(s1!=0&&s2!=0?-2:-1)};
		}
		sort(stk+1,stk+top+1,cmplen);
		int cnt=0;
		ld ret=0;
		for (int i=1;i<=top;i++)
		{
			if (cnt) ret+=stk[i].len-stk[i-1].len;
			cnt+=stk[i].v;
		}
		return ret;
	}//直线和多边形的交线总长，两个多边形一顺一逆可求只被覆盖一次的长度，多个同方向可求直线与多个多边形的交线总长
	bool isct(const POLYGON &POL)const
	{
		for (int i=2;i<=n;i++)
			for (int j=2;j<=POL.n;j++)
			{
				LINE L1={a[i-1],a[i]};
				LINE L2={POL.a[j-1],POL.a[j]};
				if (L1.isct11(L2)) return 1;
			}
		return 0;
	}//多边形相交，当前是两链相交判断
	ld isctarea(const POLYGON &POL)const;
};
/////////////////////////////////////////
