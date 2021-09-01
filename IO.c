/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License
 Time: 21/08/01 00:00 GMT
*/

#include <IO.h>

// When Error in PLP Language
in plp_error($ *s){
    return fprintf(stderr,red "Error PLP|>" set "%s;\n",s);
    exit(0);
}

// Input and Ouput PLP Compiler
in inout($ * a){
    FILE * fp = fopen(a,"r");
    FILE * fp2 = fopen("/tmp/cplp","wr");
    cond fp == NULL || fp2 == NULL then
    	lua_error("NILL");
    	remove("/tmp/cplp");
    	exit(0);
    ends
     $ c[256];
    fputs("#include \"import\"\n",fp2);
     in cs;
     $ ch[2] = "//";
     in i = atoi(ch);
    when !feof(fp) then
    	cs= getc(fp);
    	cond cs == EOF) break;
    	 cond cs == ':' then ungetc(';',fp); cs++; ends;
          cond cs == ' ' || cs == '\t') ungetc(';',fp);
           cond cs == '.' then ungetc(')',fp); continue; ends
            cond cs == '|') ungetc('#',fp);
             cond cs == '-') ungetc(i,fp);
           	 other ungetc(cs,fp);
             cond fgets(c,256,fp) != NULL) fputs(c,fp2);
            	other break;
    }
    fclose(fp);
    fclose(fp2);
    return 0;
}

in argvinout($ * s){
    FILE * fp2 = fopen("/tmp/cplp","wr");
        fputs("#include \"import\"\n _ ",fp2);
        fputs(s,fp2);
     	fputs("\nDone",fp2);
        fclose(fp2);
        print(nline);
	return 0;
}

in defkey($ * i){
	FILE * fp = fopen("Define","a");
	fputs("#define ",fp);
	fprintf(fp,Str$ i);
	fprintf(fp,nline);
	fclose(fp);
	print(nline);
	return 0;
}

in cc(out){
     $ str2[512];
    strcpy(str2,"cc ");
    strcat(str2,"/tmp/cplp");
    strcat(str2,".c -O2 -I. -c");
    strcat(str2," -o /tmp/aout");
    system(str2);
     $ str3[512]; 
    strcpy(str3,"c++ ");
    FILE * aout = fopen("/tmp/aout","r");
    cond aout != NULL)
    strcat(str3,"/tmp/aout cmath.o IO.o luasyntax.o lib.o cs50.o lua/hash.o lua/inout.o lua/lex_yy.o lua/opcode.o lua/table.o lua/y_tab.o lua/iolib.o lua/mathlib.o lua/strlib.o -lm");
    other {
    plp_error("NULL");
    remove("/tmp/cplp.c");
    exit(0);
    }
    return system(str3);
}

in cpp(out){
     $ str4[512];
    strcpy(str4,"c++ ");
    strcat(str4,"/tmp/cplp");
    strcat(str4,".cpp -O2 -I. -c");
    strcat(str4," -o /tmp/aout");
    system(str4);
     $ str5[512]; 
    strcpy(str5,"c++ ");
    FILE * aout = fopen("/tmp/aout","r");
    cond aout != NULL)
    strcat(str5,"/tmp/aout cmath.o IO.o luasyntax.o lib.o cs50.o lua/hash.o lua/inout.o lua/lex_yy.o lua/opcode.o lua/table.o lua/y_tab.o lua/iolib.o lua/mathlib.o lua/strlib.o -lm");
    other {
    plp_error("NULL");
    remove("/tmp/cplp.cpp");
    exit(0);
    }
    return system(str5);
}
