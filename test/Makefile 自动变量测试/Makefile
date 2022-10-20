
# &@是make的自动变量，表示目标名
.DEFAULT:
	echo $@

redis-server:
	echo "生成redis-server"

redis-sentinel:
	echo "生成redis-sentinel"

# $^ 是 make 的自动变量 表示所有依赖项，多个依赖项使用空格隔开
test: redis-server redis-sentinel
	echo $@
	echo $^

# > mingw32-make unknowed_target a=b
# echo unknowed_target
# unknowed_target

# > mingw32-make test
# echo "生成redis-server"
# "生成redis-server"
# echo "生成redis-sentinel"
# "生成redis-sentinel"
# echo test
# test
# echo redis-server redis-sentinel
# redis-server redis-sentinel

