#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1600005,mo=1009;
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

vector<ll> mul(const vector<ll>& p,const vector<ll>& q){
    int len = 1;
    while (len < p.size() + q.size() + 1) len <<= 1;

    for (int i = 0; i < len; i++)
    {
        if (i < p.size() ) x1[i] = Complex(p[i], 0);
        else x1[i] = Complex(0, 0);
        if (i < q.size() ) x2[i] = Complex(q[i], 0);
        else x2[i] = Complex(0, 0);
    }

    fft(x1, len, 1);
    fft(x2, len, 1);

    for (int i = 0; i < len; i++)
        x1[i] = x1[i] * x2[i];

    fft(x1, len, -1);

    vector<ll> ret;
    for (int i = 0 ;i < p.size() + q.size()+1; i++)
        ret.emplace_back((ll)(x1[i].x + 0.5) % mo);

    return ret;
}

int cnt[N];
vector<ll> solve(int l,int r){
    if (l==r){
        vector<ll> ret(cnt[l]+1);
        for (int i=0;i<=cnt[l];i++) ret[i]=1;
        return ret;
    }
    int mid=(l+r)/2;
    return mul(solve(l,mid),solve(mid+1,r));
}
int main(){
    int n,m,k; scanf("%d%d%d",&n,&m,&k);
    for (int i=1;i<=n;i++){
        int x; scanf("%d",&x);
        cnt[x]++;
    }
    printf("%lld\n",solve(1,m)[k]);
}