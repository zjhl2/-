void build() {
	int top=0;
	rep(i,1,n+1) l[i]=0,r[i]=0,vis[i]=0;
	rep(i,1,n+1) {
		int k=top;
		while (k>0&&a[stk[k-1]]>a[i]) --k;
		if (k) r[stk[k-1]]=i;
		if (k<top) l[i]=stk[k];
		stk[k++]=i;
		top=k;
	}
	rep(i,1,n+1) vis[l[i]]=vis[r[i]]=1;
	int rt=0;
	rep(i,1,n+1) if (vis[i]==0) rt=i;
	dfs(rt);
}