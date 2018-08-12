for (int i=1;i<=n;i++) vis[i]=0,on[i]=0;
int root=dfs1(1,1);
r[l[root]]=root; on[root]=1;
for (int i=l[root];i!=root;i=l[i])  r[l[i]]=i,on[i]=1;