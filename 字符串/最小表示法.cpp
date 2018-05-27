char s[20005];
int mcp(char *s)
{
	int len=strlen(s);
	for (int i=len;i<2*len;i++) s[i]=s[i-len];
	int i=0,j=1;
	while(i<len&&j<len)
	{
		int p=0;
		while(p<len&&s[i+p]==s[j+p]) p++;
		if (p==len) break;
		if (s[i+p]<s[j+p]) j=j+p+1;
		else i=i+p+1;
		if (i==j) j++;
	}
	return i<j?i:j;
}
int main()
{
	int t; scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s);
		printf("%d\n",mcp(s)+1);
	}
}