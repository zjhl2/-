
const int M=3000005;
int tot;
int root[N];
int ls[M],rs[M],sum[M];

void update(int &x,int y,int l,int r,int pos){
    x=++tot;
    ls[x]=ls[y]; rs[x]=rs[y];
    sum[x]=sum[y]+1;
    if (l==r) return;
    int mid=(l+r)/2;
    if (pos<=mid) update(ls[x],ls[y],l,mid,pos);
    else update(rs[x],rs[y],mid+1,r,pos);
}

int query(int x,int y,int lca,int fal,int l,int r,int k){
    if (l==r) return l;
    int cntl=sum[ls[x]]+sum[ls[y]]-sum[ls[lca]]-sum[ls[fal]];
    int mid=(l+r)/2;
    if (cntl>=k) 
        return query(ls[x],ls[y],ls[lca],ls[fal],l,mid,k);
    else 
        return query(rs[x],rs[y],rs[lca],rs[fal],mid+1,r,k-cntl);
}