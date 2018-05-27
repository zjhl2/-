bool vis[N];
int p[N],mu[N],tot;

int main()
{
    mu[1]=1;
    for (int i=2;i<N;i++)
    {
        if (!vis[i])
        {
            p[++tot]=i;
            mu[i]=-1;
        }
        for (int j=1;j<=tot&&i*p[j]<N;j++)
        {
            vis[i*p[j]]=1;
            if (i%p[j]) mu[i*p[j]]=-mu[i];
            else
            {
                mu[i*p[j]]=0;
                break;
            }
        }
    }