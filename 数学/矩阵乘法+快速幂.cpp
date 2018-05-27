#include<cstdio>
const int N=2,mo=10000;
struct mat{
    int c[N][N];
    void init()
    {
        for (int i=0;i<N;i++)
            for (int j=0;j<N;j++) c[i][j]=0;
    }
    mat operator*(mat b)
    {
        mat M; M.init();
        for (int i=0;i<N;i++)
            for (int j=0;j<N;j++)
                for (int k=0;k<N;k++)
                    M.c[i][j]=(c[i][k]*b.c[k][j]+M.c[i][j])%mo;
        return M;
    }
}B,A[31];
int n,i;
int main()
{
    A[0].init();
	A[0].c[0][1]=A[0].c[1][0]=A[0].c[1][1]=1;
    for (i=1;i<=30;i++) A[i]=A[i-1]*A[i-1];
    while(~scanf("%d",&n)&&n!=-1)
    {
		if (n==0) printf("0\n");
		else
		{
			n--;
			B.init();
			for (i=0;i<N;i++) B.c[i][i]=1;
			for (i=0;i<=30&&n;i++,n>>=1)
				if (n&1) B=B*A[i];
            printf("%d\n",B.c[1][1]);
		}
    }
}
