#include<bits/stdc++.h>
using namespace std;

const int N=400005;
const double PI=acos(-1);
struct Complex{
    double x, y;
    Complex(double x = 0.0, double y = 0.0) : x(x), y(y){}
    Complex operator + (const Complex &b) const{
        return Complex(x + b.x, y + b.y);
    }
    Complex operator - (const Complex &b) const{
        return Complex(x - b.x, y - b.y);
    }
    Complex operator * (const Complex &b) const{
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};

Complex x1[N], x2[N];

void change(Complex y[], int len){
    for (int i = 1, j = len / 2; i < len - 1; i++){
        if (i < j) swap(y[i], y[j]);
        int k = len / 2;
        while (j >= k){
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}

void fft(Complex y[], int len, int on){
    change(y, len);
    for (int h = 2; h <= len; h <<= 1){
        Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
        for (int j = 0; j < len; j += h){
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k++){
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }

    if (on == -1){
        for (int i = 0; i< len; i++) y[i].x /= len;
    }
}

int mul(int p[], int dp, int q[], int dq){
    int len = 1;
    while (len < dp + dq - 1) len <<= 1;

    for (int i = 0; i < len; i++)
    {
        if (i < dp) x1[i] = Complex(p[i], 0);
        else x1[i] = Complex(0, 0);
        if (i < dq) x2[i] = Complex(q[i], 0);
        else x2[i] = Complex(0, 0);
    }

    fft(x1, len, 1);
    fft(x2, len, 1);

    for (int i = 0; i < len; i++)
        x1[i] = x1[i] * x2[i];

    fft(x1, len, -1);

    for (int i = 0 ;i < len; i++)
        p[i] = (int)(x1[i].x + 0.5);

    return len;
}
int arr1[N],arr2[N];



#include<bits/stdc++.h>
#define pi acos(-1)
using namespace std;
typedef complex<double> E;
const int N=400005;
int n,m;  //10w
E a[N],b[N];
int c[N];
void FFT(E *x,int n,int type)
{
    if(n==1)return;
    E l[n>>1],r[n>>1];
    for(int i=0;i<n;i+=2)
        l[i>>1]=x[i],r[i>>1]=x[i+1];
    FFT(l,n>>1,type);FFT(r,n>>1,type);
    E wn(cos(2*pi/n),sin(type*2*pi/n)),w(1,0);
    for(int i=0;i<n>>1;i++,w*=wn)
        x[i]=l[i]+w*r[i],x[i+(n>>1)]=l[i]-w*r[i];
}

char s1[N],s2[N];
int main()
{
    while(~scanf("%s%s",s1,s2))
    {
        int n=strlen(s1),m=strlen(s2);
        for (int i=0;i<n;i++) a[i]=s1[n-1-i]-'0';
        for (int i=0;i<m;i++) b[i]=s2[m-1-i]-'0';
        m+=n; for (n=1;n<m;n<<=1);
        FFT(a,n,1); FFT(b,n,1);
        for (int i=0;i<n;i++) a[i]*=b[i];
        FFT(a,n,-1);
        int top=0;
        for (int i=0;i<m;i++)
        {
            c[i]+=int(a[i].real()/n+0.5);
            c[i+1]+=c[i]/10;
            c[i]%=10;
            if (c[i]>0) top=i;
        }
        for (int i=top;i>=0;i--) printf("%d",c[i]);
        printf("\n");
        for (int i=0;i<n;i++) a[i]=b[i]=c[i]=0;
    }
}