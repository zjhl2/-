int egcd(int a,int b,int &x,int &y)
{
	if (b==0){x=1; y=0; return a;}
	int tmp=egcd(b,a%b,y,x);
	y-=a/b*x;
	return tmp;
}
//ax+by=gcd(a,b)的最小解
//x+b/g*n是通解

int ny(int a,int mo)
{
	int x,y;
	int gcd=egcd(a,mo,x,y);
	return (x+mo)%mo;
}
求出x加模取模即为逆元
满足a*k≡1 (mod p)的k值就是a关于p的乘法逆元
