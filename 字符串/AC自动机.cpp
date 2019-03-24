const int N=1005;
int tot,root;
int ch[N][26],fail[N],cnt[N];
int newnode(){
	tot++;
	for (int i=0;i<26;i++) ch[tot][i]=0;
	fail[tot]=0; cnt[tot]=0;
	return tot;
}
void init(){
	tot=0;
	root=newnode();
}
void insert(char *s){
	int now=root;
	for (int i=0;s[i];i++){
		int w=s[i]-'a';
		if (!ch[now][w]) ch[now][w]=newnode();
		now=ch[now][w];
	}	
	cnt[now]=1;
}
void build(){
	queue<int>Q;
	fail[root]=root;
	for (int i=0;i<26;i++){
		if (!ch[root][i]) ch[root][i]=root;
		else{
			int v=ch[root][i];
			fail[v]=root;
			Q.push(v);
		}
	}
	while(!Q.empty()){
		int u=Q.front(); Q.pop();
		for (int i=0;i<26;i++){
			int v=ch[u][i];
			if (v){
				fail[v]=ch[fail[u]][i];
				Q.push(v);
			}
			else ch[u][i]=ch[fail[u]][i];
		}
	}
}