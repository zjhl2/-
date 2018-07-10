
const int N=100005;
const int step=18;

int n; 
int fa[N][step];
int deep[N];
int getlca(int x,int y) {
	if (deep[x]<deep[y]) swap(x,y);
	if (deep[x]>deep[y])
	{
		for (int j=step-1;j>=0;j--)
			if (deep[fa[x][j]]>deep[y]) x=fa[x][j];
		x=fa[x][0];
	}
	if (x==y) return x;
	for (int j=step-1;j>=0;j--)
		if (fa[x][j]!=fa[y][j]) x=fa[x][j],y=fa[y][j];
	return fa[x][0];
}
void prelca(int n) {
	for (int j=1;j<step;j++)
		for (int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
}