#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b)    for (int i(a); i <= (b); ++i)
#define    dec(i, a, b)    for (int i(a); i >= (b); --i)
#define    fi        first
#define    se        second
const double PI = acos(-1.0);
const int N=200005;

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

Complex x1[N << 2], x2[N << 2];

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
        rep(i, 0, len - 1) y[i].x /= len;
    }
}

int mul(int p[], int dp, int q[], int dq){
    int len = 1;
    while (len <= dp + dq) len <<= 1;

    rep(i, 0, dp)
        x1[i] = Complex(p[i], 0);

    rep(i, dp + 1, len - 1)
        x1[i] = Complex(0, 0);

    rep(i, 0, dq)
        x2[i] = Complex(q[i], 0);

    rep(i, dq + 1, len - 1)
        x2[i] = Complex(0, 0);

    fft(x1, len, 1);
    fft(x2, len, 1);

    rep(i, 0, len - 1)
        x1[i] = x1[i] * x2[i];

    fft(x1, len, -1);

    rep(i, 0, dp + dq)
        p[i] = (int)(x1[i].x + 0.5);

    return len;
}
char s1[N],s2[N];
int a[N],b[N];
int main()
{
    while(~scanf("%s%s",s1,s2))
    {
        int n=strlen(s1),m=strlen(s2);
        for (int i=0;i<n;i++) a[i]=s1[n-1-i]-'0';
        for (int i=0;i<m;i++) b[i]=s2[m-1-i]-'0';
        n=mul(a,n,b,m);
        int top=0;
        for (int i=0;i<n;i++)
        {
            a[i+1]+=a[i]/10;
            a[i]%=10;
            if (a[i]>0) top=i;
        }
        for (int i=top;i>=0;i--) printf("%d",a[i]);
        printf("\n");
        for (int i=0;i<n;i++) a[i]=b[i]=0;
    }
}