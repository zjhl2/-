int egcd(int a,int b,int &x,int &y)
{
	if (b==0){x=1; y=0; return a;}
	int tmp=egcd(b,a%b,y,x);
	y-=a/b*x;
	return tmp;
}
//ax+by=gcd(a,b)����С��
//x+b/g*n��ͨ��

int ny(int a,int mo)
{
	int x,y;
	int gcd=egcd(a,mo,x,y);
	return (x+mo)%mo;
}
���x��ģȡģ��Ϊ��Ԫ
����a*k��1 (mod p)��kֵ����a����p�ĳ˷���Ԫ
