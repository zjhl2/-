struct Link_Cut_Tree{
    const static int N=100005;
    int top,ch[N][2],fa[N],sz[N],q[N],rev[N];
    int _sz[N]; //虚边sz和
    void init(int n){
        for (int i=1;i<=n;i++){
            ch[i][0]=ch[i][1]=0;
            fa[i]=0; sz[i]=1; 
            _sz[i]=0; //
            rev[i]=0;
        }
    }
    inline void pushup(int x){
        sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
        sz[x]+=_sz[x]; //
    }
    inline void pushdown(int x){
        int l=ch[x][0],r=ch[x][1];
        if(rev[x]){
            rev[l]^=1; rev[r]^=1; rev[x]^=1;
            swap(ch[x][0],ch[x][1]);
        }
    }
    inline bool isroot(int x){
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void rotate(int x){
        int y=fa[x],z=fa[y],l,r;
        if (ch[y][0]==x) l=0; 
        else l=1; 
        r=l^1;
        if (!isroot(y)){
            if(ch[z][0]==y) ch[z][0]=x;
            else ch[z][1]=x;
        }
        fa[x]=z; fa[y]=x; fa[ch[x][r]]=y;
        ch[y][l]=ch[x][r]; ch[x][r]=y;
        pushup(y); pushup(x);
    }
    void splay(int x){
        top=1; q[top]=x;
        for(int i=x;!isroot(i);i=fa[i]) q[++top]=fa[i];
        for(int i=top;i;i--) pushdown(q[i]);
        while(!isroot(x)){
            int y=fa[x],z=fa[y];
            if(!isroot(y)){
                if((ch[y][0]==x)^(ch[z][0]==y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
    void access(int x){
        for(int t=0;x;t=x,x=fa[x]){
            splay(x);
            _sz[x]+=sz[ch[x][1]]; //
            ch[x][1]=t;
            _sz[x]-=sz[ch[x][1]]; //
            pushup(x);
        }
    }
    void makeroot(int x){
        access(x); splay(x); rev[x]^=1;
    }
    int find(int x){
        access(x); splay(x); 
        while(ch[x][0]) x=ch[x][0];
        return x;
    }
    void split(int x,int y){
        makeroot(x); access(y); splay(y);
    }
    void cut(int x,int y){
        split(x,y);
        assert(ch[y][0]==x);
        ch[y][0]=0,fa[x]=0;
        pushup(y);
    }
    void link(int x,int y){
        split(x,y); fa[x]=y; 
        _sz[y]+=sz[x]; //
        pushup(y);
    }
    int get_fa(int x,int y){
        split(x,y);
        pushdown(y);
        x=ch[y][0];
        while(pushdown(x),ch[x][1]) x=ch[x][1];
        return x;
    }
}T;