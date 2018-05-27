ACM中java的使用

 

这里指的java速成，只限于java语法，包括输入输出，运算处理，字符串和高精度的处理，进制之间的转换等，能解决OJ上的一些高精度题目。

1. 输入：

格式为：Scanner cin = new Scanner (new BufferedInputStream(System.in));

例程：

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

        a = cin.nextInt(); b = cin.nextDouble(); c = cin.nextBigInteger(); d = cin.nextLine(); // 每种类型都有相应的输入函数.

    }

}

 

2. 输出

函数：System.out.print(); System.out.println(); System.out.printf();

System.out.print(); // cout << …;

System.out.println(); // cout << … << endl;

System.out.printf(); // 与C中的printf用法类似.

例程：

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

        System.out.printf("%d %10.5f\n", a, b); // 输入b为字宽为10，右对齐，保留小数点后5位，四舍五入.

    }

}

规格化的输出：

函数：

// 这里0指一位数字，#指除0以外的数字(如果是0，则不显示),四舍五入.

    DecimalFormat fd = new DecimalFormat("#.00#");

    DecimalFormat gd = new DecimalFormat("0.000");

    System.out.println("x =" + fd.format(x));

    System.out.println("x =" + gd.format(x));

 

3. 字符串处理

java中字符串String是不可以修改的，要修改只能转换为字符数组.

例程：

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

        System.out.println(st.charAt(0)); // st.charAt(i)就相当于st[i].

        char [] ch;

        ch = st.toCharArray(); // 字符串转换为字符数组.

        for (i = 0; i < ch.length; i++) ch[i] += 1;

        System.out.println(ch); // 输入为“bcdefgh”.

if (st.startsWith("a")) // 如果字符串以'0'开头.

        {

            st = st.substring(1); // 则从第1位开始copy(开头为第0位).

        }

    }

}

 

4. 高精度

BigInteger和BigDecimal可以说是acmer选择java的首要原因。

函数：add, subtract, divide, mod, compareTo等，其中加减乘除模都要求是BigInteger(BigDecimal)和BigInteger(BigDecimal)之间的运算，所以需要把int(double)类型转换为BigInteger(BigDecimal)，用函数BigInteger.valueOf().

例程：

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

 

5. 进制转换

java很强大的一个功能。

函数：

String st = Integer.toString(num, base); // 把num当做10进制的数转成base进制的st(base <= 35).

int num = Integer.parseInt(st, base); // 把st当做base进制，转成10进制的int(parseInt有两个参数,第一个为要转的字符串,第二个为说明是什么进制).  

BigInter m = new BigInteger(st, base); // st是字符串，base是st的进制.

//Added by abilitytao

1.如果要将一个大数以2进制形式读入 可以使用cin.nextBigInteger(2);

当然也可以使用其他进制方式读入；

2.如果要将一个大数转换成其他进制形式的字符串 使用cin.toString(2);//将它转换成2进制表示的字符串

例程：POJ 2305

 

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

 

6. 排序

函数：Arrays.sort();至于怎么排序结构体，像C++里写个cmp的方法，在java还不太清楚，希望有人指点下～～

例程：

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

 

7. POJ高精度题目汇总：

POJ 1131 1205 1220 1405 1503 1604 1894 2084 2305 2325 2389 2413 3101 3199

 

转自：http://hi.baidu.com/czyuan_acm/blog/item/d0bf7a439d90d21b72f05d69.html

 

acm中Java的应用

Chapter I.

Java的优缺点各种书上都有，这里只说说用Java做ACM-ICPC的特点：

(1) 最明显的好处是，学会Java，可以参加Java Challenge    :)

(2) 对于熟悉C/C++的程序员来说，Java 并不难学，找本书，一两周业余时间就可以搞定了。当然，这里只是指一般编程，想熟悉所有的Java库还是需要些时间的。

      事实上，Java 只相当于C++的一个改进版，所有的语法都几乎是C++的，很少有变动。

(3) 在一般比赛中，Java程序会有额外的时间和空间，而实际上经过实验，在执行计算密集任务的时候Java并不比C/C++慢多少，只是IO操作较慢而已。

(4) Java 简单而功能强大，有些东西用Java实现起来更为方便，比如高精度。

(5) 用Java不易犯细微的错误，比如C/C++中的指针， “if (n = m) ... ” 等

(6) 目前来看Eclipse已成基本配置，写Java程序反而比C/C++更方便调试。在具体竞赛时也算多一种选择。

(7) 学会Java对以后工作有好处。现在国外很多地方会Java的人比会C/C++的人多。

(8) 会Java可以使你看起来更像偶蹄类动物（牛）      hoho~

 

Chapter II.

下面说一下ACM-ICPC队员初用Java编程所遇到的一些问题：

1. 基本输入输出：

(1)

JDK1.5.0新增的Scanner类为输入提供了良好的基础，简直就是为ACM-ICPC而设的。

一般用法为：

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

当然也可以直接 Scanner cin = new Scanner(System.in);

只是加Buffer可能会快一些

(2)

读一个整数：    int n = cin.nextInt();          相当于    scanf("%d", &n);    或 cin >> n;

读一个字符串：String s = cin.next();          相当于    scanf("%s", s);      或 cin >> s;

读一个浮点数：double t = cin.nextDouble();    相当于    scanf("%lf", &t); 或 cin >> t;

读一整行：      String s = cin.nextLine();      相当于    gets(s);            或 cin.getline(...);

判断是否有下一个输入可以用 cin.hasNext() 或 cin.hasNextInt() 或 cin.hasNextDouble() 等，具体见 TOJ 1001 例程。

(3)

输出一般可以直接用 System.out.print() 和 System.out.println()，前者不输出换行，而后者输出。

比如：System.out.println(n);    // n 为 int 型

同一行输出多个整数可以用

      System.out.println(new Integer(n).toString() + " " + new Integer(m).toString());

也可重新定义：

static PrintWriter cout = new PrintWriter(new BufferedOutputStream(System.out));

cout.println(n);

(4)

对于输出浮点数保留几位小数的问题，可以使用DecimalFormat类，

import java.text.*;

DecimalFormat f = new DecimalFormat("#.00#");

DecimalFormat g = new DecimalFormat("0.000");

double a = 123.45678, b = 0.12;

System.out.println(f.format(a));

System.out.println(f.format(b));

System.out.println(g.format(b));

这里0指一位数字，#指除0以外的数字。

 

2. 大数字

BigInteger 和 BigDecimal 是在java.math包中已有的类，前者表示整数，后者表示浮点数

用法：

不能直接用符号如+、-来使用大数字，例如：

(import java.math.*)    // 需要引入 java.math 包

BigInteger a = BigInteger.valueOf(100);

BigInteger b = BigInteger.valueOf(50);

BigInteger c = a.add(b)    // c = a + b;

主要有以下方法可以使用：

BigInteger add(BigInteger other)

BigInteger subtract(BigInteger other)

BigInteger multiply(BigInteger other)

BigInteger divide(BigInteger other)

BigInteger mod(BigInteger other)

int compareTo(BigInteger other)

static BigInteger valueOf(long x)

输出大数字时直接使用 System.out.println(a) 即可。

 

3. 字符串

String 类用来存储字符串，可以用charAt方法来取出其中某一字节，计数从0开始：

String a = "Hello";      // a.charAt(1) = ’e’

用substring方法可得到子串，如上例

System.out.println(a.substring(0, 4))      // output "Hell"

注意第2个参数位置上的字符不包括进来。这样做使得 s.substring(a, b) 总是有 b-a个字符。

字符串连接可以直接用 + 号，如

String a = "Hello";

String b = "world";

System.out.println(a + ", " + b + "!");      // output "Hello, world!"

如想直接将字符串中的某字节改变，可以使用另外的StringBuffer类。

 

4. 调用递归（或其他动态方法）

在主类中 main 方法必须是 public static void 的，在 main 中调用非static类时会有警告信息，

可以先建立对象，然后通过对象调用方法：

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

5. 其他注意的事项

(1) Java 是面向对象的语言，思考方法需要变换一下，里面的函数统称为方法，不要搞错。

(2) Java 里的数组有些变动，多维数组的内部其实都是指针，所以Java不支持fill多维数组。

      数组定义后必须初始化，如 int[] a = new int[100];

(3) 布尔类型为 boolean，只有true和false二值，在 if (...) / while (...) 等语句的条件中必须为boolean类型。

      在C/C++中的 if (n % 2) ... 在Java中无法编译通过。

(4) 下面在java.util包里Arrays类的几个方法可替代C/C++里的memset、qsort/sort 和 bsearch:

Arrays.fill()

Arrays.sort()

Arrays.binarySearch() 

转自：http://hi.baidu.com/oak_wesley/blog/item/35839200fd9dc10e1d9583de.html