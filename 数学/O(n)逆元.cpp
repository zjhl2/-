
inv[1]=1;
for (int i=2;i<N;i++) inv[i]=(mo-mo/i)*inv[mo%i]%mo;