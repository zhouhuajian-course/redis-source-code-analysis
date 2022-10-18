# 这是啰嗦版的 Makefile
hello_world: hello_world.o
	gcc hello_world.o -o hello_world
hello_world.o: hello_world.c hello_world.h
	gcc -c hello_world.c
# install: hello_world
install:
    # 注释可以一行开头用#，如果注释不在一行开头，需要使用空格缩进，不能是 Table 制表符，
    # 如果是制表符缩进会被当成是一条命令
    # 如果是Linux，则命令为 install ./hello_world ../bin 或 cp ...
	copy  .\hello_world.exe ..\bin
clean:
    # 如果是Linux，则命令是 rm -f hello_world.o ../bin/hello_world
	del hello_world.o hello_world.exe ..\bin\hello_world.exe