all: myshell

myshell: myshell.c execx
	gcc -o myshell myshell.c
execx : execx.c writef
	gcc -o execx execx.c
writefde : writef.c 
	gcc -o writef writef.c	
