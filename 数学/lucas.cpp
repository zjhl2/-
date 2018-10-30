int C(int n,int m){
	if (m>n) return 0;
	return 1ll*fac[n]*inv(fac[m])%mo*inv(fac[n-m])%mo;
}
int lucas(int n,int m){
	if (m==0) return 1;
	return 1ll*C(n%mo,m%mo)*lucas(n/mo,m/mo)%mo;
}