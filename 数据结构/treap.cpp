const int mxN=1000005;
int root;
int tot;
struct node {
    int val,pri,sz,ls,rs;
}T[mxN];

void push(int u){
}

void up(int u){
    T[u].sz=T[T[u].ls].sz+T[T[u].rs].sz+1;
}

int merge(int a,int b){
    if(a==0||b==0) return a+b;
    if(T[a].pri<T[b].pri){
        push(a);
        T[a].rs=merge(T[a].rs,b);
        up(a);
        return a;
    }
    else{
        push(b);
        T[b].ls=merge(a,T[b].ls);
        up(b);
        return b;
    }
}

void split(int u,int k,int &x,int &y){
    if (!u) x=0,y=0;
    else{
        push(u);
        int lsz=T[T[u].ls].sz;
        if (lsz>=k) y=u,split(T[u].ls,k,x,T[u].ls),up(y);
        else x=u,split(T[u].rs,k-lsz-1,T[u].rs,y),up(x);
    }
}

int find(int u,int k){
    assert(k>=1&&k<=T[u].sz);
    int lsz=T[T[u].ls].sz;
    if (lsz+1==k) return u;
    if (lsz>=k) return find(T[u].ls,k);
    else return find(T[u].rs,k-lsz-1);
}