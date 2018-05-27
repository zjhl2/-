int getlcp(int p,int p2)
{
    int l=0,r=min(p,p2)+1;
    while(l<r)
    {
        int mid=(l+r)/2;
        if (get(p,mid)==get(p2,mid)) l=mid+1;
        else r=mid;
    }
    return l-1;
}