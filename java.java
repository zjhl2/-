ACM��java��ʹ��

 

����ָ��java�ٳɣ�ֻ����java�﷨������������������㴦���ַ����͸߾��ȵĴ�������֮���ת���ȣ��ܽ��OJ�ϵ�һЩ�߾�����Ŀ��

1. ���룺

��ʽΪ��Scanner cin = new Scanner (new BufferedInputStream(System.in));

���̣�

import java.io.*;

import java.math.*;

import java.util.*;

import java.text.*;

public classMain

{

    public static void main(String[] args)

    {

        Scanner cin = new Scanner (new BufferedInputStream(System.in));

        int a; double b; BigInteger c; String st;

        a = cin.nextInt(); b = cin.nextDouble(); c = cin.nextBigInteger(); d = cin.nextLine(); // ÿ�����Ͷ�����Ӧ�����뺯��.

    }

}

 

2. ���

������System.out.print(); System.out.println(); System.out.printf();

System.out.print(); // cout << ��;

System.out.println(); // cout << �� << endl;

System.out.printf(); // ��C�е�printf�÷�����.

���̣�

import java.io.*;

import java.math.*;

import java.util.*;

import java.text.*;

public classMain

{

    public static void main(String[] args)

    {

        Scanner cin = new Scanner (new BufferedInputStream(System.in));

        int a; double b;

        a = 12345; b = 1.234567;

        System.out.println(a + " " + b);

        System.out.printf("%d %10.5f\n", a, b); // ����bΪ�ֿ�Ϊ10���Ҷ��룬����С�����5λ����������.

    }

}

��񻯵������

������

// ����0ָһλ���֣�#ָ��0���������(�����0������ʾ),��������.

    DecimalFormat fd = new DecimalFormat("#.00#");

    DecimalFormat gd = new DecimalFormat("0.000");

    System.out.println("x =" + fd.format(x));

    System.out.println("x =" + gd.format(x));

 

3. �ַ�������

java���ַ���String�ǲ������޸ĵģ�Ҫ�޸�ֻ��ת��Ϊ�ַ�����.

���̣�

import java.io.*;

import java.math.*;

import java.util.*;

import java.text.*;

public classMain

{

    public static void main(String[] args)

    {

        int i;

        Scanner cin = new Scanner (new BufferedInputStream(System.in));

        String st = "abcdefg";

        System.out.println(st.charAt(0)); // st.charAt(i)���൱��st[i].

        char [] ch;

        ch = st.toCharArray(); // �ַ���ת��Ϊ�ַ�����.

        for (i = 0; i < ch.length; i++) ch[i] += 1;

        System.out.println(ch); // ����Ϊ��bcdefgh��.

if (st.startsWith("a")) // ����ַ�����'0'��ͷ.

        {

            st = st.substring(1); // ��ӵ�1λ��ʼcopy(��ͷΪ��0λ).

        }

    }

}

 

4. �߾���

BigInteger��BigDecimal����˵��acmerѡ��java����Ҫԭ��

������add, subtract, divide, mod, compareTo�ȣ����мӼ��˳�ģ��Ҫ����BigInteger(BigDecimal)��BigInteger(BigDecimal)֮������㣬������Ҫ��int(double)����ת��ΪBigInteger(BigDecimal)���ú���BigInteger.valueOf().

���̣�

import java.io.*;

import java.math.*;

import java.util.*;

import java.text.*;

public classMain

{

    public static void main(String[] args)

    {

        Scanner cin = new Scanner (new BufferedInputStream(System.in));

        int a = 123, b = 456, c = 7890;

        BigInteger x, y, z, ans;

        x = BigInteger.valueOf(a); y = BigInteger.valueOf(b); z = BigInteger.valueOf(c);

        ans = x.add(y); System.out.println(ans);

        ans = z.divide(y); System.out.println(ans);

        ans = x.mod(z); System.out.println(ans);

        if (ans.compareTo(x) == 0) System.out.println("1");

    }

}

 

5. ����ת��

java��ǿ���һ�����ܡ�

������

String st = Integer.toString(num, base); // ��num����10���Ƶ���ת��base���Ƶ�st(base <= 35).

int num = Integer.parseInt(st, base); // ��st����base���ƣ�ת��10���Ƶ�int(parseInt����������,��һ��ΪҪת���ַ���,�ڶ���Ϊ˵����ʲô����).  

BigInter m = new BigInteger(st, base); // st���ַ�����base��st�Ľ���.

//Added by abilitytao

1.���Ҫ��һ��������2������ʽ���� ����ʹ��cin.nextBigInteger(2);

��ȻҲ����ʹ���������Ʒ�ʽ���룻

2.���Ҫ��һ������ת��������������ʽ���ַ��� ʹ��cin.toString(2);//����ת����2���Ʊ�ʾ���ַ���

���̣�POJ 2305

 

import java.io.*;

import java.util.*;

import java.math.*;

public classMain

{

    public static void main(String[] args)

    {

        int b;

        BigInteger p,m,ans;

        String str ;

        Scanner cin = new Scanner (new BufferedInputStream(System.in));

        while(cin.hasNext())

        {

            b=cin.nextInt();

            if(b==0)

                break;

            p=cin.nextBigInteger(b);

            m=cin.nextBigInteger(b);

            ans=p.mod(m);

            str=ans.toString(b);

            System.out.println(str);

        }

    }

}

//End by abilitytao

 

6. ����

������Arrays.sort();������ô����ṹ�壬��C++��д��cmp�ķ�������java����̫�����ϣ������ָ���¡���

���̣�

import java.io.*;

import java.math.*;

import java.util.*;

import java.text.*;

public classMain

{

    public static void main(String[] args)

    {

        Scanner cin = new Scanner (new BufferedInputStream(System.in));

        int n = cin.nextInt();

        int a[] = new int [n];

        for (int i = 0; i < n; i++) a[i] = cin.nextInt();

        Arrays.sort(a);

        for (int i = 0; i < n; i++) System.out.print(a[i] + " ");

    }

}

 

7. POJ�߾�����Ŀ���ܣ�

POJ 1131 1205 1220 1405 1503 1604 1894 2084 2305 2325 2389 2413 3101 3199

 

ת�ԣ�http://hi.baidu.com/czyuan_acm/blog/item/d0bf7a439d90d21b72f05d69.html

 

acm��Java��Ӧ��

Chapter I.

Java����ȱ��������϶��У�����ֻ˵˵��Java��ACM-ICPC���ص㣺

(1) �����Եĺô��ǣ�ѧ��Java�����Բμ�Java Challenge    :)

(2) ������ϤC/C++�ĳ���Ա��˵��Java ������ѧ���ұ��飬һ����ҵ��ʱ��Ϳ��Ը㶨�ˡ���Ȼ������ֻ��ָһ���̣�����Ϥ���е�Java�⻹����ҪЩʱ��ġ�

      ��ʵ�ϣ�Java ֻ�൱��C++��һ���Ľ��棬���е��﷨��������C++�ģ������б䶯��

(3) ��һ������У�Java������ж����ʱ��Ϳռ䣬��ʵ���Ͼ���ʵ�飬��ִ�м����ܼ������ʱ��Java������C/C++�����٣�ֻ��IO�����������ѡ�

(4) Java �򵥶�����ǿ����Щ������Javaʵ��������Ϊ���㣬����߾��ȡ�

(5) ��Java���׷�ϸ΢�Ĵ��󣬱���C/C++�е�ָ�룬 ��if (n = m) ... �� ��

(6) Ŀǰ����Eclipse�ѳɻ������ã�дJava���򷴶���C/C++��������ԡ��ھ��徺��ʱҲ���һ��ѡ��

(7) ѧ��Java���Ժ����кô������ڹ���ܶ�ط���Java���˱Ȼ�C/C++���˶ࡣ

(8) ��Java����ʹ�㿴��������ż���ද�ţ��      hoho~

 

Chapter II.

����˵һ��ACM-ICPC��Ա����Java�����������һЩ���⣺

1. �������������

(1)

JDK1.5.0������Scanner��Ϊ�����ṩ�����õĻ�������ֱ����ΪACM-ICPC����ġ�

һ���÷�Ϊ��

import java.io.*

import java.util.*

public classMain

{

      public static void main(String args[])

      {

          Scanner cin = new Scanner(new BufferedInputStream(System.in));

          ...

      }

}

��ȻҲ����ֱ�� Scanner cin = new Scanner(System.in);

ֻ�Ǽ�Buffer���ܻ��һЩ

(2)

��һ��������    int n = cin.nextInt();          �൱��    scanf("%d", &n);    �� cin >> n;

��һ���ַ�����String s = cin.next();          �൱��    scanf("%s", s);      �� cin >> s;

��һ����������double t = cin.nextDouble();    �൱��    scanf("%lf", &t); �� cin >> t;

��һ���У�      String s = cin.nextLine();      �൱��    gets(s);            �� cin.getline(...);

�ж��Ƿ�����һ����������� cin.hasNext() �� cin.hasNextInt() �� cin.hasNextDouble() �ȣ������ TOJ 1001 ���̡�

(3)

���һ�����ֱ���� System.out.print() �� System.out.println()��ǰ�߲�������У������������

���磺System.out.println(n);    // n Ϊ int ��

ͬһ������������������

      System.out.println(new Integer(n).toString() + " " + new Integer(m).toString());

Ҳ�����¶��壺

static PrintWriter cout = new PrintWriter(new BufferedOutputStream(System.out));

cout.println(n);

(4)

�������������������λС�������⣬����ʹ��DecimalFormat�࣬

import java.text.*;

DecimalFormat f = new DecimalFormat("#.00#");

DecimalFormat g = new DecimalFormat("0.000");

double a = 123.45678, b = 0.12;

System.out.println(f.format(a));

System.out.println(f.format(b));

System.out.println(g.format(b));

����0ָһλ���֣�#ָ��0��������֡�

 

2. ������

BigInteger �� BigDecimal ����java.math�������е��࣬ǰ�߱�ʾ���������߱�ʾ������

�÷���

����ֱ���÷�����+��-��ʹ�ô����֣����磺

(import java.math.*)    // ��Ҫ���� java.math ��

BigInteger a = BigInteger.valueOf(100);

BigInteger b = BigInteger.valueOf(50);

BigInteger c = a.add(b)    // c = a + b;

��Ҫ�����·�������ʹ�ã�

BigInteger add(BigInteger other)

BigInteger subtract(BigInteger other)

BigInteger multiply(BigInteger other)

BigInteger divide(BigInteger other)

BigInteger mod(BigInteger other)

int compareTo(BigInteger other)

static BigInteger valueOf(long x)

���������ʱֱ��ʹ�� System.out.println(a) ���ɡ�

 

3. �ַ���

String �������洢�ַ�����������charAt������ȡ������ĳһ�ֽڣ�������0��ʼ��

String a = "Hello";      // a.charAt(1) = ��e��

��substring�����ɵõ��Ӵ���������

System.out.println(a.substring(0, 4))      // output "Hell"

ע���2������λ���ϵ��ַ�������������������ʹ�� s.substring(a, b) ������ b-a���ַ���

�ַ������ӿ���ֱ���� + �ţ���

String a = "Hello";

String b = "world";

System.out.println(a + ", " + b + "!");      // output "Hello, world!"

����ֱ�ӽ��ַ����е�ĳ�ֽڸı䣬����ʹ�������StringBuffer�ࡣ

 

4. ���õݹ飨��������̬������

�������� main ���������� public static void �ģ��� main �е��÷�static��ʱ���о�����Ϣ��

�����Ƚ�������Ȼ��ͨ��������÷�����

public classMain

{

      ...

      void dfs(int a)

      {

          if (...) return;

          ...

          dfs(a+1);

      }

    

      public static void main(String args[])

      {

          ...

          Main e = newMain();

          e.dfs(0);

          ...

      }

}

5. ����ע�������

(1) Java �������������ԣ�˼��������Ҫ�任һ�£�����ĺ���ͳ��Ϊ��������Ҫ���

(2) Java ���������Щ�䶯����ά������ڲ���ʵ����ָ�룬����Java��֧��fill��ά���顣

      ���鶨�������ʼ������ int[] a = new int[100];

(3) ��������Ϊ boolean��ֻ��true��false��ֵ���� if (...) / while (...) �����������б���Ϊboolean���͡�

      ��C/C++�е� if (n % 2) ... ��Java���޷�����ͨ����

(4) ������java.util����Arrays��ļ������������C/C++���memset��qsort/sort �� bsearch:

Arrays.fill()

Arrays.sort()

Arrays.binarySearch() 

ת�ԣ�http://hi.baidu.com/oak_wesley/blog/item/35839200fd9dc10e1d9583de.html