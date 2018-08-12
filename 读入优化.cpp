
const int BUF=40000000;
char Buf[BUF],*buf=Buf;

inline void read(int&a){for(a=0;*buf<48;buf++);while(*buf>47)a=a*10+*buf++-48;}

int main()
{
    fread(Buf,1,BUF,stdin);
    read(t);
}

void read(int &x){
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
void print(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
// 读入100w个int scanf需要0.5s， 优化后需要0.1s
// 输出100w个int printf需要1.8s, 优化后需要0.1s