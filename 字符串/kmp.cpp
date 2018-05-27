#include<cstdio>
#include<cstring>
char sl[2000],s[2000];
int p[2000],lensl,l,i,j,ans;
int main()
{
    while(~scanf("%s",sl)&&sl[0]!='#')
    {
        scanf("%s",s);
        ans=0;
        l=strlen(s);
        for (i=l;i>=1;i--) s[i]=s[i-1];
        j=0;
        for (i=2;i<=l;i++)
        {
            while(j>0&&s[j+1]!=s[i]) j=p[j];
            if (s[j+1]==s[i]) j++;
            p[i]=j;
        }
        lensl=strlen(sl);
        for (i=lensl;i>=1;i--) sl[i]=sl[i-1];
        j=0;
        for (i=1;i<=lensl;i++)
        {
            while(j>0&&s[j+1]!=sl[i]) j=p[j];
            if (s[j+1]==sl[i]) j++;
            if (j==l) ans++,j=0;
        }
        printf("%d\n",ans);
    }
}
