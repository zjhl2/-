struct ST
{
	static const int step=18; //2^step>N
    int f[N][step]; //10w
    void make(int *a,int n)
    {
        for (int i=1;i<=n;i++) f[i][0]=a[i];
        for (int j=1;j<step;j++)
            for (int i=1;i<=n+1-(1<<j);i++)
                f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
    }
    int get(int l,int r)
    {
        int k=log(r-l+1)/log(2);
        return max(f[l][k],f[r+1-(1<<k)][k]);
    }
}MAX;
