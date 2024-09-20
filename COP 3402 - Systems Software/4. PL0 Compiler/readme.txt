//Alex Reyes
//Jesus Molina

How To Compile and Run the hw4compiler.c:
1. Head to the directory in terminal where the lex source code is stored
2. run command gcc parsercodegen.c -o <insert name for file>
3. run command ./<choosen file name>.out(or ./<choosen file name>.exe if your system created .exe file) <name of input file> or Run BASH script
4. Output will appear on terminal screen

Example:
C:\Users\student>cd HW4
C:\Users\student\HW2>gcc hw4compiler.c -o hw4compiler
C:\Users\student\HW2>hw4compiler input.txt

OR

Example:
C:\Users\student>cd hw4compiler
C:\Users\student\HW2>gcc hw4compiler.c -o hw4compiler
C:\Users\student\HW2>./hw4compiler.out input.txt

Output If Done Correctly:
var x,y,z,v,w;
procedure a;
  var x,y,u,v;
  procedure b;
    var y,z,v;
    procedure c;
      var y,z;
      begin
        z:=1;
        x:=y+z+w
      end;
    begin
      y:=x+u+w;
      call c
    end;
  begin
    z:=2;
    u:=z+w;
    call b
  end;
begin
  x:=1; y:=2; z:=3; v:=4; w:=5;
  x:=v+w;
  write z;
  call a;
end.  

No errors, program is syntactically correct

Assembly Code:

LINE    OP    L   M
0       JMP   0   18
1       JMP   0   6
2       INC   0   5
3       LIT   0   1
4       STO   0   3
5       RTN   0   0
6       INC   0   5
7       LIT   0   2
8       STO   0   3
9       SYS   0   3