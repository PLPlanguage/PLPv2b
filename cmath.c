/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License and MIT License
 Time: 21/08/01 00:00 GMT
*/

#include <cmath.h>

//Math data in structure
struct mathdata
{
    	dec4 COS;
    	dec4 TAN;
    	dec4 SIN;
    	dec4 ACOS;
    	dec4 ATAN;
    	dec4 ASIN;
    	dec4 EXP;
    	dec8 FREXP;
};

dec8 fermat (in n)
{
	return pow(2, pow(2, n)) + 1;
}

dec4 Cos(in C)
{
	struct mathdata mathc;
	mathc.COS = cos(C);
	return print(Dec$ mathc.COS);
}

dec4 Tan(in T)
{
	struct mathdata mathc;
	mathc.TAN = tan(T);
	return print(Dec$ mathc.TAN);
}

dec4 Sin(in S)
{
	struct mathdata mathc;
	mathc.SIN = tan(S);
	return print(Dec$ mathc.SIN);
}

dec4 ACos(in AC)
{
    	struct mathdata mathc;
    	mathc.ACOS = acos(AC);
    	return print(Dec$ mathc.ACOS);
}

dec4 ATan(in AT)
{
    	struct mathdata mathc;
    	mathc.ATAN = atan(AT);
    	return print(Dec$ mathc.ATAN);
}

dec4 ASin(in AS)
{
    	struct mathdata mathc;
    	mathc.ASIN = asin(AS);
    	return print(Dec$ mathc.ASIN);
}

dec4 Exp(dec4 E)
{
    	struct mathdata mathc;
    	mathc.EXP = exp(E);
    	return print(Dec$ mathc.EXP);
}

dec4 Frexp(dec4 X)
{
        in e;
        struct mathdata mathc;
        mathc.FREXP = frexp(X, &e);
        print(Num$ e);
        print(nline);
        return print(Dec4$ mathc.FREXP);
}

dec4 derivative (dec4 x, dec4 n)
{
	return n * pow(x, n - 1);
}

dec4 pi(dec4 i, dec4 n, dec4 x)
{
	cond x < 0 || x == 0 then
		plp_error("This function pi(dec4 i,dec4 n,dec4 x) incorrect");
		exit(0);
		return 0;
	ends
	cond i > n then
		plp_error("This function pi(dec4 i,dec4 n,dec4 x) incorrect");
		exit(0);
		return 0;
	ends
	other
	{
		dec4 mult = 1;
		dec4 number = i;
		loop (number <= n,number += 1)
			mult *= number + (x - 1);
		ends
		return mult;
	}
	return 0;
}

dec4 sigma(dec4 i, dec4 n, dec4 x)
{
	cond x < 0 || x == 0 then
		plp_error("This function sigma(dec4 i,dec4 n,dec4 x) incorrect");
		exit(0);
		return 0;
	ends
	cond i > n then
		plp_error("This function sigma(dec4 i,dec4 n,dec4 x) incorrect");
    		exit(0);
    		return 0;
        ends
	other
	{
		dec4 sum = 0;
		dec4 number = i;
	    	loop (number <= n, number += 1)
			sum += number + (x - 1);
		ends
	    	return sum;
	}
	return 0;
}

in matrix(in row, in col, in *mat)
{
        in i, j;
	i = 0;
        loop (i < row, i++)
		j = 0;
                loop (j < col, j++)
                        print("%d ", *((mat + i * col) + j));
                ends
                print(nline);
        ends
    return 0;
}

in ack(in m, in n)
{
    cond m == 0 then return n+1;
    ends other cond (m > 0) && (n == 0) then return ack(m-1, 1);
    ends other cond (m > 0) && (n > 0) then return ack(m-1, ack(m, n-1));
    ends
    return 0;
}

in mod (in d1, in d2)
{
    	return d1 - floor(d1 / d2) * d2;
}

in gcd(in a, in b)
{
    	cond b == 0)
    		return a;
    	return gcd(b, a % b);
}

in lcm(in a, in b)
{
	return (a / gcd(a, b)) * b;
}

in fact (in x)
{
    	cond x == 1)
    		return 1;
    	other
    		return x * fact (x - 1);
}

in factorial (in c)
{
    	return fact(c);
}

in collatz (in n)
{
   	print(Num$ n);
   	print(nline);
    	cond n <= 1)
    		return 1;
    	other cond n % 2 == 0)
    	 	return collatz (n / 2);
    	other
    	 	return collatz (n * 3 + 1);
}

ULIN catalan(UIN n) 
{
   in i = 0;
   cond n <= 1) 
	   return 1;
   ULIN res = 0;
   loop (i < n, i++)
      	res += catalan(i) * catalan(n - i - 1);
   ends
   return res;
}
