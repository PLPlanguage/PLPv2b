/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD License and MIT License
 Time: 21/08/01 00:00 GMT
*/

#include <import>
#include <luasyntax.h>

#define keywords bold magenta "keyword:" set
#define functions  bold green "function:" set
#define variables bold cyan "variable:" set
#define luaPLP bold yellow "luaPLP interpreter\n" set

#define mathlibs yellow "math library->" set 
#define libio yellow "IO library->" set
#define keys yellow "Key Define->" set
#define shelloption_s bold black "shell library->" set 
// When user CTRL + C (signal 2) entered
out cpress(in sig)
{
	fprint(stdout,"\nCTRL+C Pressed.\n");
	beep();
	exit(0);
}

_ 
 // first argument for PLP Compiler
 cond argv[1])
    print("PLP|>");
 in i;
 $ * a = NULL;
// PLP Compiler Arguments
Shell(i,"l:c:o:d:i:h")
 selector i then
    selection 'l':
       a = getshell;
            iolib_open();
            mathlib_open();
            strlib_open();
            return dofile(argv[2]);
	exit(0);
	return 0;
                  break;
    selection 'c':  
            a = getshell;
            print("Compiling.. [%s]\n",a);
            inout(a);
            rename("/tmp/cplp","/tmp/cplp.cpp");
                cpp();
            remove("/tmp/cplp.cpp");
            remove("/tmp/aout");
            exit(0);
            return 0;
                  break;
    selection 'o':
       a = getshell;
	        print("Output: %s\n",a);
	    #ifndef __CYGWIN__
            rename("a.out",a);
	    #endif
	    #ifdef __CYGWIN__
	    rename("a.exe",a);
	    #endif
            exit(0);
	    return 0;
		 break;
     selection 'd':
        a = getshell;
      // Detect codes and execute it.
	    argvinout(argv[2]);
        rename("/tmp/cplp","/tmp/cplp.cpp");
         cpp();
        remove("/tmp/cplp.cpp");
        remove("/tmp/aout");
        #ifdef __CYGWIN__
        system("./a.exe");
	print(nline);
	return remove("a.exe");
        #endif
	#ifndef __CYGWIN__
	executel("./a.out");
	print(nline);
	return remove("a.out");
	#endif
                  break;
    selection 'i':
	a = getshell;
  //get user defined variables
	defkey(a);
	print(nline);
	return 0;
		  break;
    selection 'h':
            print(" Project Programming Language \n");
            print(" Help");
	    print("\tPLP [function filename]\n");
	    print("\tPLP help [command]  Commands you don't know what they are.\n");
            print("\t-c Execute a PLP file\n");
            print("\t-l Execute a interpreter file\n");
	    print("\t-d Print a script with the argument\n"); 
            print("\t-o Rename the executed PLP file\n");
	    print("\t-i Writing definitions, for example [-i 'Radian 1']\n");
	    exit(0);
	    return 0;
                  break;
    selection '?':
        cond shelloption == 'l' then
            print("This is hybrid PLP & lua language,\n Please filename function: luaPLP [namefunctionfile]\n");
            return 0;
    ends
	cond shelloption == 'd' then
	    print("Please print a script -%c [argument]\n",shelloption);
	    return 0;
    ends
	cond shelloption == 'o' then
	    print("Please Rename the executed PLP file -%c [file]\n",shelloption);
	    return 0;
    ends
	cond shelloption == 'i' then
	    print("Please Writing definitions, for example [-%c pi 3.14]\n",shelloption);
	    return 0;
    ends
        cond shelloption == 'c' then
            print("Compile file with -%c [file]\n",shelloption);
	    return 0;
    ends
	other
	{
	    print("This argument does not exist -%c\n",shelloption);
	    return 0;
	}
                  break;
    default:
            abort();
  ends
 in c =1;
 // default argument
 loop (c < argc, c++)
 in ic = 1;
    // Help for basic developer  
    loop (ic < argc, ic++)
      cond strstr(argv[ic], "help") then
        in d = 2;
        loop(d < argc, ++d)
        print(" \n");
          cond indexof(argv[d], "_", 0) then
            print(bold white "Main response:" set "\tIt is a type of keyword that can be used to call commands\n");
            print("You must end your commands with the operator ( . ) after you write them inside\n");
            return 0;
          ends
	  cond indexof(argv[d], "executel", 0) then
	    print(libio bold " in executel (fix $ * s)\n" set);
	    print(luaPLP functions "\texecute of system commands\n");
	    return 0;
	  ends 
	  cond indexof(argv[d], "printl", 0) then
	    print(libio bold " out printl ($ *str)\n" set);
	    print(luaPLP functions "\tprint with lua language\n");
	    return 0;
	  ends
	  cond indexof(argv[d], "writel", 0) then
	    print(libio bold " out writel ($ *str)\n" set);
	    print(luaPLP functions "\twrite the command in lua language\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "sigma", 0) then
	    print(mathlibs bold " dec4 sigma(dec4 i, dec4 n, dec4 x)\n" set);
	    print(functions "\tsummation start and end and command\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "fermat", 0) then
	    print(mathlibs bold " out writel ($ *str)\n" set);
	    print(functions "\tfermat numbers in PLP language\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "matrix", 0) then
	    print(mathlibs bold " in matrix(in row, in col, in *mat)\n" set);
	    print(functions "\tmatrics or matrix mathematic in PLP language\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "ack", 0) then
	    print(mathlibs bold " in ack(in m, in n)\n" set);
	    print(functions "\tackermann function in PLP\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "mod", 0) then
	    print(mathlibs bold " in mod (in d1, in d2)\n" set);
	    print(functions "\tmode of mathematics\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "fib", 0) then
	    print(mathlibs bold " in fib (in n)\n" set);
	    print(functions "\tfibonacci numbers in mathematics\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "factorial", 0) then
	    print(mathlibs bold " in factorial (in c)\n" set);
	    print(functions "\tfactorial numbers in mathematics\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "collatz", 0) then
	    print(mathlibs bold " in collatz (in n)\n" set);
	    print(functions "\tcollatz conjecture in mathematics\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "catalan", 0) then
	    print(mathlibs bold " ULIN catalan(UIN n)\n" set);
	    print(functions "\tcatalan numbers in mathematics\n");
	    return 0;
	  ends
          other cond indexof(argv[d], "lambda", 0) then
            print(functions "\tthis is a anonymous function (" yellow "advanced" set ")\n");
            print(bold yellow "Note: in gcc compiler has work\n" set );
            return 0;
          ends
          other cond indexof(argv[d], "range", 0) then
            print(keys bold white " range" set "(" bold green "string" set ", " bold yellow "start" set ", " bold yellow "end" set ", " bold blue "range_start" set " ... " bold blue "range_end" set ")" nline);
            print(functions "function:" set "\trange of numbers\n");
            return 0;
          ends
          other cond indexof(argv[d], "interrupt", 0) then
            print(functions "\tinterruption of program and progress\n");
            return 0;
          ends
          other cond indexof(argv[d], "print", 0) then
            print(keys bold white " print" set "(" bold yellow "varstr" set "," bold yellow " arg..." set ")" nline);
            print(functions "\tPrints and displays strings and variables \n");
            return 0;
          ends
          other cond indexof(argv[d], "loop", 0) then
            print(keys bold white " loop" set "(" bold yellow "prevar" set ", " bold cyan "step" set ")" nline);
            print(functions "\tIt works like the when loop, but you can also specify the variable jump\n");
            return 0;
          ends
          other cond indexof(argv[d], "typeof", 0) then
            print(functions "\tCalculates the size of the variables data  that is stored.\n");
            return 0;
          ends
          cond indexof(argv[d], "function", 0) then
            print(keys bold white " function" set "(" set bold magenta "type" set bold yellow  " namevar" set "," bold yellow "arg..." set ") " nline);
            print(functions "\tThe function command is a type of function that contains a set of function " yellow "(variable)" set " arguments\n");
            return 0;
          ends
          other cond indexof(argv[d], "eulers", 0) then
            print(functions "\tThe Euler analysis in mathematics");
            return 0;
          ends
          other cond indexof(argv[d], "when", 0) then
            print(keys bold white " when" set bold yellow " variable " set bold white "then\n" set);
            print(keywords "\tCodes will continue when a condition is met\n");
            return 0;
          ends
          other cond indexof(argv[d], "other", 0) then
            print(keywords "\tThis command works like " yellow "else" set ", but its text is like this\n");
            return 0;
          ends
          other cond indexof(argv[d], "bp", 0) then
            print(keywords "\tIt specifies a breakpoint in the code and breaks the execution of the code\n");
            return 0;
          ends
          other cond indexof(argv[d], "str$", 0) or indexof(argv[d], "Str$", 0) then
            print(keywords "\tIt prints string variables like " yellow "num$" set " and " yellow "dec$" set " commands\n");
            return 0;
          ends
          other cond indexof(argv[d], "nline", 0) then
            print(keywords "\tGo to the next line, Of course this command works mostly with print \n");
            return 0;
          ends
          other cond indexof(argv[d], "cond", 0) then
            print(keys bold white " cond" set bold yellow " variable " set bold white "then\n" set);
            print(keywords " Like the if command is operating. It means " yellow "condition" set ", Of course should be (then) command after it, because the codes can be write after that\n");
            return 0;
          ends
          other cond indexof(argv[d], "selector", 0) then
            print(keys bold white " selector" set bold yellow " variable " set bold white "then\n" set);
            print(keywords "\tLike the switch command is operating.\n");
            return 0;
          ends
          other cond indexof(argv[d], "selection", 0) then
            print(keys bold white " selection " set bold cyan "str|int|dec|" set ":\n");
            print(keywords "\tLike the case command is operating.\n");
            return 0;
          ends
	  other cond indexof(argv[d], "dec8", 0) or indexof(argv[d], "DEC8", 0) then
	    print(variables "\tIt's a type of 8 decimal variable\n");
	    return 0;
	  ends
	  other cond indexof(argv[d], "dec4", 0) or indexof(argv[d], "DEC4", 0) then
	    print(variables "\tIt's a type of 4 decimal variable\n");
	    return 0;
	  ends
          other cond indexof(argv[d], "in", 0) or indexof(argv[d], "IN", 0) then
            print(variables "\tIt is a type of integer variable\n");
            return 0;
          ends
          other cond indexof(argv[d], "$", 0) or indexof(argv[d], "text", 0) then
            print(variables "\tIt is a type of character or string variable\n");
            return 0;
          ends
          other{ print(" Not find keyword or function\n"); return 0;}
        ends
        print("Help in functions and keywords in PLP language \n");
          print("please command PLP help [command]\n");  
      ends
    ends
                print("Compiling.. [%s]\n",argv[c]);
                inout(argv[c]);
                rename("/tmp/cplp","/tmp/cplp.c");
                cc();
                remove("/tmp/cplp.c");
                remove("/tmp/aout");
                exit(0);
                return 0;
ends
 cond argc < 2 then
	 $ buffer[256];
     text hi;
	print("Compiler PLP|> Project Programming Language\n");
	when 1 then
        print("PLP|>");
		interrupt(cpress);
		cond fgets(buffer,sizeof(buffer),stdin) == 0 then beep(); return 0; ends
        cond indexof(buffer,"compile\n",0) then
            hi = get_text("File:");
            inout(hi);
            print("Compiling.. [%s]\n",hi);
            rename("/tmp/cplp","/tmp/cplp.c");
            cc();
            remove("/tmp/aout");
            remove("/tmp/cplp.c");
        ends
        other cond indexof(buffer,"compile c\n",0) then
            hi = get_text("File:");
            print("Compiling.. [%s]\n",buffer);
            inout(buffer);
            rename("/tmp/cplp","/tmp/cplp.cpp");
            cpp();
            remove("/tmp/cplp.cpp");
            remove("/tmp/aout");
        ends
        other cond indexof(buffer,"interpreter\n",0) then
            print("This is hybrid PLP & lua language,\n Please filename function: luaPLP [namefunctionfile]\n");
            hi = get_text("");
            lua_dofile(hi);
        ends
        other cond indexof(buffer,"exit\n",0) then
            beep();
            return 0;
        ends
        other cond indexof(buffer,"help\n",0) then
        print(" Lua scripts in PLP language\n");
        print("  Example:");
        print(" \tPLP|>execute('echo Hello World')\n");
        print("   [compile] \tCommand execute a PLP file\n");
        print("   [compile c] \tCommand execute a PLP file (advanced)\n");
        print("   [interpreter] \tCommand execute a interpreter file\n");
        ends
        other
	{
                iolib_open ();
                strlib_open ();
                mathlib_open ();
                lua_dostring(buffer);
        }
    ends
   #ifdef __cplusplus
	free(buffer);
  #endif
ends
Done
