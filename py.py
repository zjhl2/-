import decimal
T = int(raw_input())
decimal.getcontext().prec = 3000
while (T > 0) :
    T -= 1
    n = decimal.Decimal(raw_input())
    print int(n.sqrt()) & 1
# 大数开根号
	
import sys    
for n in sys.stdin:
    print int(n)
#多组输入
	
import decimal
T = int(raw_input())
while (T > 0) :
    T -= 1
    s = raw_input()
    n = int(s)
    if (n < 2) :
        print n
        continue
    l = int((len(s)-1)/2)
    s = '1'
    if l != 0 :
        for i in range(1,l):
            s += '0'
    x = decimal.Decimal(s)
    last = 0
    eps = 1e-1
    while ( abs(x - last) > eps ) :
        y = x ** 2
        last = x
        x += ( n - y ) / ( 2 * x)
    x = int(x)
    print (x & 1)


s = '1'
for i in range(1,1) :
    s += '0'
n = int(s)
if (n < 2) :
    print n
else :
    l = int((len(s)-1)/2)
    s = '1'
    if l != 0 :
        for i in range(1,l):
            s += '0'
    x = decimal.Decimal(s)
    last = 0
    eps = 1e-1
    while ( abs(x - last) > eps ) :
        y = x ** 2
        last = x
        x += ( n - y ) / ( 2 * x)
    x = int(x)
    print (x & 1)
