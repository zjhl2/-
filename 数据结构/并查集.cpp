struct Union_find{
    static const int mxN=6;
    int fa[mxN];
    void init(){
        for (int i=0;i<mxN;i++) fa[i]=i;
    }
    int find(int x){
        if (x==fa[x]) return x;
        return fa[x]=find(fa[x]);
    }
    void merge(int x,int y){
        x=find(x); y=find(y);
        if (x!=y) fa[x]=y;
    }
}