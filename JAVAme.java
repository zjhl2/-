import java.lang.reflect.Array;
import java.math.*;  
import java.util.*;  
  
static class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }
 
    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }
 
    public int nextInt() {
        return Integer.parseInt(next());
    } 
}

public class Main {  
	static long a[][] = new long[105][105];
	static long pow(long x,long y,long mo){
		long ret=1;
		while(y>0){
			if (y%2==1) ret=ret*x%mo;
			x=x*x%mo;
			y/=2;
		}
		return ret;
	}
    public static void main(String[] args){  
		boolean flag=false;

		InputReader fcin=new InputReader(System.in);
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

