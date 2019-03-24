//求行列式
ll gauss(int n){
    ll ret=1;
    for (int i=1;i<=n;i++){
		int k=i;
		for (int j=i+1;j<=n;j++)
			if (abs(a[j][i])>abs(a[k][i])) k=j;
        if (k!=i){
            ret*=-1;
            for (int j=1;j<=n;j++) swap(a[i][j],a[k][j]);
        }
        if (a[i][i]==0) return 0;
		for (k=i+1;k<=n;k++){
			ll l=a[k][i]*inv(a[i][i])%mo;
			for (int j=i;j<=n;j++) a[k][j]=(a[k][j]-l*a[i][j]%mo+mo)%mo;
		}
    }
    for (int i=1;i<=n;i++) ret=ret*a[i][i]%mo;
    if (ret<0) ret+=mo;
    return ret;
}
