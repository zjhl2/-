#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct FFT{
    const static int L=20,mxN=(1<<L);
    const double two_pi=acos(-1)*2;
    struct Cpx{
        double x,y;
        Cpx operator+(const Cpx &b) const{
            return {x+b.x,y+b.y};
        }
        Cpx operator-(const Cpx &b) const{
            return {x-b.x,y-b.y};
        }
        Cpx operator*(const Cpx &b) const{
            return {x*b.x-y*b.y,x*b.y+y*b.x};
        }
        Cpx operator!() const{ 
            return {x,-y}; 
        }
    }nw[mxN+1],f[mxN],g[mxN],h[mxN],hh[mxN];
    int rev[mxN];
    void init(){
        rev[0]=0; nw[0]=nw[mxN]={1,0};
        for (int i=1;i<mxN;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
        for (int i=1;i<=(mxN>>1);i++) nw[i]={cos(i*two_pi/mxN),sin(i*two_pi/mxN)};
        for (int i=(mxN>>1)+1;i<mxN;i++) nw[i]=!nw[mxN-i];
    }
    void fft(Cpx *a,int n,int on){
        int j=__builtin_ctz(mxN/n);
        for (int i=0;i<n;i++) 
            if (i<(rev[i]>>j)) swap(a[i],a[rev[i]>>j]);
        for (int len=2;len<=n;len<<=1){
            int step=mxN/len*on; 
            for (int i=0;i<n;i+=len){
                Cpx *u=a+i,*v=a+(i+(len>>1)),*w=(on==1?nw:nw+mxN);
                for (int k=(len>>1);k--;){
                    Cpx tmp=(*v)*(*w);
                    *v=*u-tmp,*u=*u+tmp;
                    u++,v++,w+=step;
                }
            }
        }
        if (on==-1){
            for (int i=0;i<n;i++) a[i].x/=n,a[i].y/=n;
        }
    }
    //[0, n) * [0, m) = [0, n + m - 2]
    int getlen(int n,int m){
        int len=1;
        while(len<n+m-1) len<<=1;
        return len;
    }
    /// multiply two polynomial nlog(n) time modulo p
    void multiply(int *a,int *b,int *c,int lena,int lenb,int mo){
        int n=getlen(lena,lenb);
        for (int i=0;i<n;i++){
            f[i]=i<lena?Cpx{double(a[i]>>15),double(a[i]&32767)}:Cpx{0,0};
            g[i]=i<lenb?Cpx{double(b[i]>>15),double(b[i]&32767)}:Cpx{0,0};
        }
        fft(f,n,1); fft(g,n,1);
        for (int i=0;i<n;i++){
            int j=(i?n-i:0);
            hh[i]=((f[i]+!f[j])*(!g[j]-g[i])+(!f[j]-f[i])*(g[i]+!g[j]) )*Cpx{0,0.25};
            h[i]=(!f[j]-f[i])*(!g[j]-g[i])*Cpx{-0.25,0}+(f[i]+!f[j])*(g[i]+!g[j])*Cpx{0,0.25};
        }
        fft(h,n,-1); fft(hh,n,-1);
        for (int i=0;i<lena+lenb-1;i++)
            c[i]=((ll)(h[i].x+0.5)+((ll)(hh[i].x+0.5)%mo<<15)+((ll)(h[i].y+0.5)%mo<<30))%mo;
    }
    void mul(int *a,int *b,int *c,int lena,int lenb) {
        int n=getlen(lena,lenb);
        for (int i=0;i<n;i++){
            f[i]=i<lena?Cpx{double(a[i]),0}:Cpx{0,0};
            g[i]=i<lenb?Cpx{double(b[i]),0}:Cpx{0,0};
        }
        fft(f,n,1); fft(g,n,1);
        for (int i=0;i<n;i++) f[i]=f[i]*g[i];
        fft(f,n,-1);
        for (int i=0;i<lena+lenb-1;i++) c[i]=int(f[i].x+0.5);
    }
}FFT;