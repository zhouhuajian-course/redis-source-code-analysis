# 如果设置了特殊变量.DEFAULT_GOAL，那么执行make没有制定目标的情况下，使用.DEFAULT_GOAL指定的目标
# 如果没有设置.DEFAULT_GOAL特殊标量，那么默认使用Makefile文件中第一个目标
# target: prerequisites ...
# 目标: 依赖项 ...
# 	命令 command
#   ...

# .DEFAULT_GOAL=redis-server

# target:
# 	echo "这是制作测试target要执行的命令"

# 目标 default的目标依赖项是 all
default: all

# 目标 all，目标依赖项是 redis-server redis-cli
all: redis-server redis-cli

redis-server:
	echo "这是制作目标redis-server要执行的命令"
	echo "这里需要生产redis-server文件"

redis-cli:
	echo "这是制作目标redis-cli要执行的命令"
	echo "这里需要生产redis-cli文件"

clean:
	echo "这是制作目标clean要执行的命令"

# .DEFAULT是特殊目标，其他目标都会走执行.DEFAULT特殊目标里面的命令
.DEFAULT:
	echo "这是制作其他目标要执行的命令"

# > mingw32-make
# echo "这是制作目标redis-server要执行的命令"
# "这是制作目标redis-server要执行的命令"
# echo "这里需要生产redis-server文件"
# "这里需要生产redis-server文件"
# echo "这是制作目标redis-cli要执行的命令"
# "这是制作目标redis-cli要执行的命令"
# echo "这里需要生产redis-cli文件"
# "这里需要生产redis-cli文件"


# > mingw32-make install
# echo "这是制作其他目标要执行的命令"
# "这是制作其他目标要执行的命令"