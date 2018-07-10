
int lca(int x,int y)
{
	if (deep[x]<deep[y]) swap(x,y);
	if (deep[x]>deep[y])
		{
			for (int j=20;j>=0;j--)
				if (deep[fa[x][j]]>deep[y]) x=fa[x][j];
			x=fa[x][0];
		}
	if (x==y) return x;
	for (int j=20;j>=0;j--)
		if (fa[x][j]!=fa[y][j]) x=fa[x][j],y=fa[y][j];
	return fa[x][0];
}

void prelca()
{
	for (int j=1;j<=20;j++)
		for (int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
}

int go(int x,int step)
{
	for (int i=20;i>=0;i--)
		if (step>=(1<<i)) x=fa[x][i],step-=(1<<i);
	return x;
}