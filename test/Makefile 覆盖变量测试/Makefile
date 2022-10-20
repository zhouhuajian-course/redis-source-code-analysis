# 9.5 Overriding Variables
# An argument that contains ‘=’ specifies the value of a variable: ‘v=x’ sets the value of the variable v to x.
# If you specify a value in this way,
# all ordinary assignments of the same variable in the makefile are ignored;
# we say they have been overridden by the command line argument.

PREFIX ?= /usr/local
# PREFIX = /usr/local 结果一样
INSTALL_BIN = ${PREFIX}/bin

all:
	echo ${PREFIX}
	echo $(INSTALL_BIN)

# 命令行变量 在目标前或目标后都可以

# > mingw32-make PREFIX=/redis all
# echo /redis
# /redis
# echo /redis/bin
# /redis/bin

# > mingw32-make all PREFIX=/redis
# echo /redis
# /redis
# echo /redis/bin
# /redis/bin