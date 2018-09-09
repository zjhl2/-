int Merge(int A,int B)
{
    if (!A||!B) return A+B;
    if (C[A]<C[B]) swap(A,B);
    rs[A]=Merge(rs[A],B);
    if (dis[ls[A]]<dis[rs[A]]) swap(ls[A],rs[A]);
    dis[A]=dis[rs[A]]+1;
    return A;
}
int Delete(int A)
{
    return Merge(ls[A],rs[A]);
}