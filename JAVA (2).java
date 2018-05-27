import java.lang.reflect.Array;
import java.math.*;  
import java.util.*;  
  
  
public class Main {  
    public static void main(String[] args) {  
        Scanner cin= new Scanner(System.in);  
        BigInteger Bx;
        Bx=BigInteger.valueOf(1);
        Bx=Bx.multiply(Bx);
        int intx=3;
        System.out.printf("%d !! %03d\n",intx,intx);
        
        double doublex=3.1249;
        System.out.printf("%.2f\n", doublex);
        String S="1_;";//=cin.nextLine();
        System.out.println(S);
        char c=S.charAt(1);
        S="424sj";
        System.out.println(S.startsWith("42"));
        String T=S.substring(2,5);
        S.length();
        System.out.println(T);
        
        int num=Integer.parseInt("101",2);
        System.out.println(num);
        String NS=Integer.toString(5,2);
        System.out.println(NS);
        BigInteger m=new BigInteger("10101",2);
        System.out.println(m);
        
        //m=cin.nextBigInteger(2);
        //System.out.println(m);
        NS=m.toString(2);
        System.out.println(NS);
        
        int [] a=new int[105];
        for (int i=0;i<5;i++) a[i]=5-i;
        Arrays.sort(a,0,2);
        for (int i=0;i<5;i++) 
        	System.out.print(a[i]+" ");
    }  
}  




import java.util.*;  
import java.math.*;

public class Main {
	static long a[][] = new long[105][105];
	static long c[][] = new long[105][105];			
	static long[] p=new long[105];
	static long[] r=new long[105];
	static long x,y;
	static long pow(long x,long y,long mo)
	{
		long ret=1;
		while(y>0)
		{
			if (y%2==1) ret=ret*x%mo;
			x=x*x%mo;
			y/=2;
		}
		return ret;
	}
	static long egcd(long a,long b)
	{
		if (b==0){x=1; y=0; return a;}
		long tmp=egcd(b,a%b);
		long t=x; x=y; y=t;
		y-=a/b*x;
		return tmp;
	}
	static long CNA(int n)
	{
		long mo=p[1],re=r[1];
		for (int i=2;i<=n;i++)
		{
			//x*mo+re=y*p[i]+r[i];
			long gcd=egcd(mo,p[i]);
			if ((r[i]-re)%gcd!=0) return -1;
			x*=(r[i]-re)/gcd;
			x=(x%(p[i]/gcd)+(p[i]/gcd))%(p[i]/gcd);  // 模后模
			re=x*mo+re;
			mo=mo/gcd*p[i];
		}
		return re;
	}
	static long gauss(int n,long mo)
	{
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) a[i][j]=c[i][j]%mo;
		boolean flag=false;
		for (int i=1;i<=n;i++)
		{
			int k=i;
			while(k<=n&&a[k][i]==0) k++;
			if (k>n) return 0;
			if (k!=i) 
			{
				flag=!flag;
				for (int j=1;j<=n;j++) 
				{
					long t=a[i][j];
					a[i][j]=a[k][j];
					a[k][j]=t;
				}
			}
			for (k=i+1;k<=n;k++)
			{
				long l=a[k][i]*pow(a[i][i],mo-2,mo)%mo;
				for (int j=i;j<=n;j++) a[k][j]=(a[k][j]-l*a[i][j])%mo;
			}
		}
		long ans=1;
		for (int i=1;i<=n;i++) ans=ans*a[i][i]%mo;
		if (flag) ans=-ans;
		return (ans%mo+mo)%mo;
	}
	public static void main(String[] args)
	{
		Scanner cin= new Scanner(System.in);  
		while(cin.hasNext())
		{
			int n=cin.nextInt();
			long m=cin.nextLong();
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++) c[i][j]=cin.nextLong();

			int top=0;
			for (long i=2;i*i<=m;i++)
				if (m%i==0)
				{
					p[++top]=i;
					while(m%i==0) m/=i;
				}
			if (m!=1) p[++top]=m;
			//System.out.println(top);
			for (int i=1;i<=top;i++) r[i]=gauss(n,p[i]);
			//for (int i=1;i<=top;i++) System.out.println(p[i]+" "+r[i]);
			System.out.println(CNA(top));
		}

	}

}

