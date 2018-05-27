#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <bitset>
using namespace std;
const int maxn=1e6+50;
char str[5*maxn];
bitset<1000> s[20];
bitset<1000> ans;

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<20;i++)
        s[i].reset();
        ans.reset();
        for(int i=0;i<n;i++)
        {
            int N,temp;
            scanf("%d",&N);
            for(int j=0;j<N;j++)
            {
                scanf("%d",&temp);
                s[temp].set(i);
            }
        }
        getchar();
        gets(str);
        int len=strlen(str);
        for(int i=0;i<len;i++)
        {
            ans=ans<<1;
            ans[0]=1;
            ans&=s[str[i]-'0'];
            if(ans[n-1]==1)
            {
                char temp=str[i+1];
                str[i+1]='\0';
                puts(str+i-n+1);
                str[i+1]=temp;
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}
/*
4
3 0 9 7
2 5 7
2 2 5
2 4 5
09755420524

*/