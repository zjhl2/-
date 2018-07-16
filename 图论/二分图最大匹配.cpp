const int N=505;
vector<int>link[N];
bool vis[N];
int g[N];
int n; 
void init(){
    for (int i=1;i<=n;i++) link[i].clear();
}
bool find(int u){
    for (int v:link[u])
        if (!vis[v]){
            vis[v]=1;
            if (!g[v]||find(g[v])){
                g[v]=u;
                return 1;
            }
        }
    return 0;
}
int HA(){
    int all=0;
    for (int i=1;i<=n;i++) g[i]=0;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++) vis[j]=0;
        if (find(i)) all++;
    }
    return all;
}


/*
5
3 3
1 1
1 2
2 2
2 3
3 3
���ƥ���������ƥ���ƥ��ߵ���Ŀ

��С�㸲������ѡȡ���ٵĵ㣬ʹ����һ����������һ���˵㱻ѡ��

����������ѡȡ���ĵ㣬ʹ������ѡ�����������

��С·��������������һ�� DAG�������޻�ͼ����ѡȡ������·����ʹ��ÿ�����������ҽ�����һ��·����·��������Ϊ 0���������㣩��

����1�����ƥ���� = ��С�㸲���������� Konig ����

����2�����ƥ���� = ��������

����3����С·�������� = ������ - ���ƥ����
*/
