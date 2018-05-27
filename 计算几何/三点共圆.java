x0 = ((y2-y1)*(y3*y3-y1*y1+x3*x3-x1*x1)-(y3-y1)*(y2*y2-y1*y1+x2*x2-x1*x1))/(2.0*((x3-x1)*(y2-y1)-(x2-x1)*(y3-y1)));

y0 = ((x2-x1)*(x3*x3-x1*x1+y3*y3-y1*y1)-(x3-x1)*(x2*x2-x1*x1+y2*y2-y1*y1))/(2.0*((y3-y1)*(x2-x1)-(y2-y1)*(x3-x1)));

r^2= (x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);


import java.math.*;  
import java.util.*;  

public class Main {
	public static BigDecimal dis(BigDecimal x, BigDecimal y, BigDecimal x0, BigDecimal y0){
		BigDecimal dx=(x.subtract(x0)).pow(2);
		BigDecimal dy=(y.subtract(y0)).pow(2);
		return dx.add(dy);
	}
	public static void main(String[] args) {
		Scanner cin= new Scanner(System.in);  
		int t=cin.nextInt();
        while(t>0)
        {
        	t--;
        	BigDecimal x1,y1,x2,y2,x3,y3,x,y,x0,y0,a,b,c,d,e,f,g,h;
        	x1=cin.nextBigDecimal();
        	y1=cin.nextBigDecimal();
        	x2=cin.nextBigDecimal();
        	y2=cin.nextBigDecimal();
        	x3=cin.nextBigDecimal();
        	y3=cin.nextBigDecimal();
        	x=cin.nextBigDecimal();
        	y=cin.nextBigDecimal();
        	
        	a=y2.subtract(y1);
        	b=y3.pow(2).subtract(y1.pow(2)).add(x3.pow(2)).subtract(x1.pow(2));
        	c=y3.subtract(y1);
        	d=y2.pow(2).subtract(y1.pow(2)).add(x2.pow(2)).subtract(x1.pow(2));
        	e=x3.subtract(x1);
        	f=y2.subtract(y1);
        	g=x2.subtract(x1);
        	h=y3.subtract(y1);
        	x0= (a.multiply(b).subtract(c.multiply(d))).divide(BigDecimal.valueOf(2.0).multiply((e.multiply(f).subtract(g.multiply(h)))));

        	a=x2.subtract(x1);
        	b=x3.pow(2).subtract(x1.pow(2)).add(y3.pow(2)).subtract(y1.pow(2));
        	c=x3.subtract(x1);
        	d=x2.pow(2).subtract(x1.pow(2)).add(y2.pow(2)).subtract(y1.pow(2));
        	e=y3.subtract(y1);
        	f=x2.subtract(x1);
        	g=y2.subtract(y1);
        	h=x3.subtract(x1);
        	y0= (a.multiply(b).subtract(c.multiply(d))).divide(BigDecimal.valueOf(2.0).multiply((e.multiply(f).subtract(g.multiply(h)))));
    	
        	if (dis(x, y, x0, y0).compareTo(dis(x1, y1, x0, y0))>0) 
        		System.out.println("Accepted");
        	else
        		System.out.println("Rejected");
        	
        	
        }

	}

}
