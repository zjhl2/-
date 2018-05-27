int p[N],r[N];
int egcd(int a,int b,int &x,int &y)
{
	if (b==0){x=1; y=0; return a;}
	int tmp=egcd(b,a%b,y,x);
	y-=a/b*x;
	return tmp;
}
int CNA()
{
	int mo=p[1],re=r[1];
	for (int i=2;i<=n;i++)
	{
		//x*mo+re=y*p[i]+r[i];
		int x,y;
		int gcd=egcd(mo,p[i],x,y);
		if ((r[i]-re)%gcd!=0) return -1;
		x*=(r[i]-re)/gcd;
		x=(x%(p[i]/gcd)+(p[i]/gcd))%(p[i]/gcd);  // Ä£ºóÄ£
		re=x*mo+re;
		mo=mo/gcd*p[i];
	}
	return re;
}