
for (int i=0;i<=m;i++) cnt[i]=0;
for (int i=1;i<=n;i++) cnt[rk[nxt[i]]]++;
for (int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
for (int i=n;i>=1;i--) sa2[cnt[rk[nxt[i]]]--]=i;

for (int i=0;i<=m;i++) cnt[i]=0;
for (int i=1;i<=n;i++) cnt[rk[sa2[i]]]++;
for (int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
for (int i=n;i>=1;i--) sa[cnt[rk[sa2[i]]]--]=sa2[i];
