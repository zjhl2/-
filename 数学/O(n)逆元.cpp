
const int mo=1e9+7;
ll fac[N],inv[N],invfac[N];
ll C(int n,int m){
	if (m>n) return 0;
	return fac[n]*invfac[m]*invfac[n-m]%mo;
}
void init(int n){
	fac[0]=invfac[0]=fac[1]=inv[1]=invfac[1]=1;
	for (int i=2;i<N;i++){
		fac[i]=fac[i-1]*i%mo;
		inv[i]=(mo-mo/i)*inv[mo%i]%mo;
		invfac[i]=invfac[i-1]*inv[i]%mo;
	}
}