# 目标 install
install:
	echo "执行install目标里面的命令1"
	echo "执行install目标里面的命令2"
# 如果目录里面有一个 install 文件，并且不修改 install 文件，那么命令1 命令2永远不会被执行
# > mingw32-make install
#   mingw32-make: 'install' is up to date.
# 解决方案：需要使用特殊目标 .PHONY，指明目标 install 是一个假目标
.PHONY: install

# 目标 clean 也可能有类似问题