
const int BUF=40000000;
char Buf[BUF],*buf=Buf;

inline void read(int&a){for(a=0;*buf<48;buf++);while(*buf>47)a=a*10+*buf++-48;}

int main()
{
    fread(Buf,1,BUF,stdin);
    read(t);
