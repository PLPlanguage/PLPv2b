/* The Project Programming Language - PLP
 The Second Release on PLP Language -> PLPv2b
 BSD and MIT License
 Time: 21/08/01 00:00 GMT
*/

#include <import>
#include <luasyntax.h>

// When user CTRL + C (signal 2) entered
out cpress(in sig){
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
 selector(i){
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
            print("\t-c Execute a PLP file\n");
            print("\t-l Execute a luaPLP file\n");
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
	other{
	    print("This argument does not exist -%c\n",shelloption);
	    return 0;
    }
                  break;
    default:
            abort();
 }
 in c =1;
 // default argument
 loop (c < argc, c++)
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
	print("Compiler PLP|> Project Programming Language\n");
	when 1 then
        print("PLP|>");
		interrupt(cpress);
		cond fgets(buffer,sizeof(buffer),stdin) == 0 then beep(); return 0; ends
        cond indexof(buffer,"compile\n",0) then
            gets(buffer);
            inout(buffer);
            print("Compiling.. [%s]\n",buffer);
            rename("/tmp/cplp","/tmp/cplp.c");
            cc();
            remove("/tmp/aout");
            remove("/tmp/cplp.c");
        ends
        other cond indexof(buffer,"compile c\n",0) then
            gets(buffer);
            print("Compiling.. [%s]\n",buffer);
            inout(buffer);
            rename("/tmp/cplp","/tmp/cplp.cpp");
                cpp();
            remove("/tmp/cplp.cpp");
            remove("/tmp/aout");
        ends
        other cond indexof(buffer,"lua\n",0) then
            $ s[256];
            print("This is hybrid PLP & lua language,\n Please filename function: luaPLP [namefunctionfile]\n");
            gets(s);
            lua_dofile(s);
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
        print("   [lua] \tCommand execute a LUA file\n");
        ends
        other{
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

