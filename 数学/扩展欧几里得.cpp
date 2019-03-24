int egcd(int a,int b,int &x,int &y){
	if (b==0){ x=1; y=0; return a;}
	int tmp=egcd(b,a%b,y,x);
	y-=a/b*x;
	return tmp;
}
//ax+by=gcd(a,b)的最小解
//x+b/g*n是通解
//ax+by=d*gcd(a,b) 求出x后,x=x*d%(b/g)

