#include<bits/stdc++.h>
using namespace std;

const int N=100005;
char s1[N],s2[N];


//ext1[i]表示 st[i...len]和st[1...len]的公共前缀长度
//ext2[i]表示 s[i..len2]和st[1...len]的公共前缀长度
int ext1[N];
void extend1(char *st,int len)
{
	ext1[1]=len;
	int j=0;
	while(j+2<=len&&st[2+j]==st[j+1]) j++;
	ext1[2]=j;
	int k=2;
	for (int i=3;i<=len;i++)
	{
		int p=k+ext1[k]-1;
		int j=ext1[i-k+1];
		if (i+j-1<p) ext1[i]=j;
		else
		{
			j=max(0,p-i+1);
			while(i+j<=len&&st[i+j]==st[j+1]) j++;
			ext1[i]=j;
			k=i;
		}
	}
}
int ext2[N];
void extend2(char *s,char *st,int len2,int len)
{
	int j=0;
	while(j+1<=len2&&j+1<=len&&s[j+1]==st[j+1]) j++;
	ext2[1]=j;
	int k=1;
	for (int i=2;i<=len2;i++)
	{
		int p=k+ext2[k]-1;
		int j=ext1[i-k+1];
		if (i+j-1<p) ext2[i]=j;
		else
		{
			j=max(0,p-i+1);
			while(i+j<=len2&&j+1<=len&&s[i+j]==st[j+1]) j++;
			ext2[i]=j;
			k=i;
		}
	}
}
bool vis[N];
int main()
{
	while(~scanf("%s",s1+1))
	{
		scanf("%s",s2+1);
		int len1=strlen(s1+1);
		int len2=strlen(s2+1);
		extend1(s1,len1);
		extend2(s2,s1,len2,len1);
		int ans=0;
		for (int i=1;i<=len2;i++)
			if (ext2[i]+i-1==len2)
			{
				ans=i;
				break;
			}
		if (ans==0) printf("0\n");
		else printf("%s %d\n",s2+ans,len2-ans+1);
	}
}
