


inline double F(double y)
{
	
}

inline double simpson(double a,double b){
	double c=a+(b-a)/2;
	return (F(a)+4*F(c)+F(b))*(b-a)/6;
}

inline double asr(double a,double b,double eps,double A){
	double c=a+(b-a)/2;
	double L=simpson(a,c),R=simpson(c,b);
	if(fabs(L+R-A)<=15*eps) return L+R+(L+R-A)/15.0;
	return asr(a,c,eps/2,L)+asr(c,b,eps/2,R);
}

inline double asr(double a,double b,double eps){
	return asr(a,b,eps,simpson(a,b));
}

cout<<asr(1,2,1e-8)<<endl; //1到2关于F的积分，误差1e-8