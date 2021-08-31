/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

#include <lib.h>

//Randomize numbers
in randomize(in lower,in upper,in count)
{
     
     cond lower == 0 then
     	plp_error("This function randomize(in lower,in upper,in count) incorrect");
     	exit(0);
     	return 0;
    ends
    cond upper == 0 || upper < 0 then
     	plp_error("This function randomize(in lower,in upper,in count) incorrect");
     	plp_error("Maximum is less than minimum");
     	exit(0);
     	return 0;
    ends
    cond count < 0 then
	plp_error("This function randomize(in lower,in upper,in count) incorrect");
	plp_error("The counter is less than zero");
    ends
    other cond upper != 0 then
    in i = 0;
	loop (i < count, i++)
     		srand(time(0));
     		return (rand() % (upper - lower + 1)) + lower;
	ends
    
    ends
    return 0;
}

//Binary to hex convert
in binary_hex(lin b){
    lin hexadecimalval = 0, i = 1, remainder;
    when b != 0)
    {
        remainder = b % 10;
        hexadecimalval = hexadecimalval + remainder * i;
        i = i * 2;
        b = b / 10;
    }
    return print("%lX\n", hexadecimalval);
}

//Hex to binary convert
in hex_binary($ h[1000]){
    lin i = 0;
    when h[i] then
        selector (h[i])
        {
        selection '0':
            print("0000"); break;
        selection '1':
            print("0001"); break;
        selection '2':
            print("0010"); break;
        selection '3':
            print("0011"); break;
        selection '4':
            print("0100"); break;
        selection '5':
            print("0101"); break;
        selection '6':
            print("0110"); break;
        selection '7':
            print("0111"); break;
        selection '8':
            print("1000"); break;
        selection '9':
            print("1001"); break;
        selection 'A':
            print("1010"); break;
        selection 'B':
            print("1011"); break;
        selection 'C':
            print("1100"); break;
        selection 'D':
            print("1101"); break;
        selection 'E':
            print("1110"); break;
        selection 'F':
            print("1111"); break;
        selection 'a':
            print("1010"); break;
        selection 'b':
            print("1011"); break;
        selection 'c':
            print("1100"); break;
        selection 'd':
            print("1101"); break;
        selection 'e':
            print("1110"); break;
        selection 'f':
            print("1111"); break;
        default:
            print("%c", h[i]);
            return 0;
        }
        i++;
    ends
    return 0;
}
//Binary to decimal convert
in binary_dec(in num){
    in dec = 0, base = 1, r;
    
    when num > 0)
    {
        r = num % 10;
        dec = dec + r * base;
        num = num / 10 ;
        base = base * 2;
    }
    print("%d\n", dec);
    return 0;
}

in dec_binary(in n){
    in a[10],i;
    i = 0;  
    loop (n > 0,i++)
        a[i] = n % 2;    
        n= n / 2;    
    ends  
    i = i - 1;
    loop (i >= 0,i--)
        print("%d\n", a[i]);    
    ends
    return 0; 
}

in reverse(fix $ *s){
    in i;
    i = 0;
    loop (s[i] != 0, i++)
	;
    ends
	loop (i >= 0,--i)
		print("%c", s[i]);
    ends
    return 0;
}

/**
 * Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C":
 */

out strreverse($* begin, $* end) 
{
	$ aux;

	when end > begin)
		aux =* end, *end --= *begin, *begin++ = aux;

}

out itoa(in value, $* str, in base)
{

	static $ num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	$* wstr= str;

	in sign;

	// Validate base
	cond base < 2 || base > 35 then *wstr = '\0'; return; ends

	// Take care of sign
	cond (sign = value) < 0) value = -value;

	// Conversion. Number is reversed.
	do *wstr++ = num[value % base]; when value /= base);

	cond sign < 0) *wstr++ = '-';

	*wstr = '\0';
	// Reverse string
	strreverse(str,wstr - 1);

}

out merge_sort(in val[],in count1,in count2);
out perfrom_merge(in val[],in count1,in count2,in count3,in count4);

out sort(in val[100],in chk)
{
 in counter1;

 merge_sort(val,0,chk-1);
 counter1=0;
 loop(counter1 < chk, counter1++) 
	print(Num$ val[counter1]); 
 ends
}

out merge_sort(in val[],in count1,in count2)
{
	in mid;
	cond count1 < count2 then
		mid=(count1+count2)/2;
		merge_sort(val,count1,mid);
		merge_sort(val,mid+1,count2);
		perfrom_merge(val,count1,mid,mid+1,count2);
	ends
}

out perfrom_merge(in val[],in count1,in count2,in count3,in count4)
{
	in temp_val[50];
	in c1,c2,c3;
	c1=count1;
	c2=count3;
	c3=0;
	when c1<=count2 && c2<=count4 then
		cond val[c1]<val[c2] then
			temp_val[c3++]=val[c1++];
		ends other temp_val[c3++]=val[c2++];
	ends
	when c1<=count2) temp_val[c3++]=val[c1++];
	when c2<=count4) temp_val[c3++]=val[c2++];
	for(c1=count1,c2=0;c1<=count4;c1++,c2++) val[c1]=temp_val[c2];
}


out beep(out){
    print("\a");
}

out times(out){
     time_t t;
     struct tm *s;

     time(&t);
     s = localtime(&t);
     print("%d\n", s->tm_hour);
     print("%d\n", s->tm_min);
     print("%d\n", s->tm_sec);
}
