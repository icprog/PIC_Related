echo off
echo Building libpic30.a ...

rem save crt0.s and crt1.s to temp files before cleaning
rename crt0.s crt0.sav
rename crt1.s crt1.sav

for %%f in ( *.lst) do del %%f
for %%f in ( *.o) do del %%f
for %%f in ( *.s) do del %%f
if exist libpic30.a del libpic30.a

rem rename crt0.sav and crt1.sav to their original names crt0.s and crt1.s
rename crt0.sav crt0.s
rename crt1.sav crt1.s

%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer _exit.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer read.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer open.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer lseek.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer close.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer write.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer remove.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer rename.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer brk.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer sbrk.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer setjmp.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer system.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer time.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer mulsi3.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer umulsi3.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer muldi3.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer divmodsi3.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer divmoddi3.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer ashldi3.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer ashrdi3.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer lshrdi3.c
%1\bin\pic30-gcc -S -g -Os -nostdinc -I%1\include -I../support/h -mconst-in-data -msmall-code -msmall-data -mtext=.libtext -fomit-frame-pointer negdi2.c

%1\bin\pic30-as -o crt0.o -I%1\include -I../support/inc --defsym ARGV=1 -ahldi=crt0.lst crt0.s
%1\bin\pic30-as -o crt1.o -I%1\include -I../support/inc --defsym ARGV=1 -ahldi=crt1.lst crt1.s
%1\bin\pic30-as -o _exit.o -ahldi=_exit.lst _exit.s
%1\bin\pic30-as -o read.o -ahldi=read.lst read.s
%1\bin\pic30-as -o open.o -ahldi=open.lst open.s
%1\bin\pic30-as -o lseek.o -ahldi=lseek.lst lseek.s
%1\bin\pic30-as -o close.o -ahldi=close.lst close.s
%1\bin\pic30-as -o write.o -ahldi=write.lst write.s
%1\bin\pic30-as -o remove.o -ahldi=remove.lst remove.s
%1\bin\pic30-as -o rename.o -ahldi=rename.lst rename.s
%1\bin\pic30-as -o brk.o -ahldi=brk.lst brk.s
%1\bin\pic30-as -o sbrk.o -ahldi=sbrk.lst sbrk.s
%1\bin\pic30-as -o setjmp.o -ahldi=setjmp.lst setjmp.s
%1\bin\pic30-as -o system.o -ahldi=system.lst system.s
%1\bin\pic30-as -o time.o -ahldi=time.lst time.s
%1\bin\pic30-as -o mulsi3.o -ahldi=mulsi3.lst mulsi3.s
%1\bin\pic30-as -o umulsi3.o -ahldi=umulsi3.lst umulsi3.s
%1\bin\pic30-as -o muldi3.o -ahldi=muldi3.lst muldi3.s
%1\bin\pic30-as -o divmodsi3.o -ahldi=divmodsi3.lst divmodsi3.s
%1\bin\pic30-as -o divmoddi3.o -ahldi=divmoddi3.lst divmoddi3.s
%1\bin\pic30-as -o ashldi3.o -ahldi=ashldi3.lst ashldi3.s
%1\bin\pic30-as -o ashrdi3.o -ahldi=ashrdi3.lst ashrdi3.s
%1\bin\pic30-as -o lshrdi3.o -ahldi=lshrdi3.lst lshrdi3.s
%1\bin\pic30-as -o negdi2.o -ahldi=negdi2.lst negdi2.s

%1\bin\pic30-ar -r libpic30.a crt0.o crt1.o _exit.o read.o open.o lseek.o close.o write.o remove.o rename.o brk.o sbrk.o setjmp.o system.o time.o mulsi3.o umulsi3.o muldi3.o divmodsi3.o divmoddi3.o ashldi3.o ashrdi3.o lshrdi3.o negdi2.o 

echo libpic30.a contains the following members ...
%1\bin\pic30-ar -t libpic30.a
echo Library build complete
echo Installing files
copy libpic30.a %1\lib
copy *.c %1\src
copy *.h %1\src
copy crt0.s %1\src
copy crt1.s %1\src
copy makelib.bat %1\src
