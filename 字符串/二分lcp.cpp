#include<bits/stdc++.h>
typedef long long ll;

const int N=20010,P=31,D=1000173169,M=262143;
ll base[N];
ll hs[N];
char s[N];
ll hash(int l,int r) {
	return (hs[r]−hs[l−1]*base[r−l+1]%D+D)%D;
}
int main(){
    int n; scanf("%d%s",s+1);
    base[0]=1;
	for(int i=1;i<=n;i++) base[i]=base[i−1]*P%D;
	for(int i=1;i<=n;i++) hs[i]=(hs[i−1]*P+s[i])%D;
}
int getlcp(int p,int q,int n) {
    int l=1,r=n-max(p,q)+1;
    while(l<r) {
        int mid=(l+r)/2;
        if (hash(p,p+mid)==hash(q,q+mid)) l=mid+1;
        else r=mid;
    }
    return l-1;
}