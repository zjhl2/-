#include<cstdio>
const int maxn=1000005;
int m[maxn],phi[maxn],p[maxn],pt,t,n;

int main()
{
    phi[1]=1;
    int N=maxn;
    int k;
    phi[1]=1;
    for(int i=2;i<N;i++)
    {
        if(!m[i])
            p[pt++]=m[i]=i,phi[i]=i-1;
        for(int j=0;j<pt&&(k=p[j]*i)<N;j++)
        {
            m[k]=p[j];
            if(m[i]==p[j])
            {
                phi[k]=phi[i]*p[j]; break;
            }
            else
                phi[k]=phi[i]*(p[j]-1);
        }
    }
}


long long phi(long long n)
{
	long long ans = n;
	for(int i = 2;i*i <= n;i++)
	{
		if(n % i == 0)
		{
			ans -= ans/i;
			while(n % i == 0)
				n /= i;
		}
	}
	if(n > 1)ans -= ans/n;
	return ans;
}
