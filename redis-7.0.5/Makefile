# Top level makefile, the real shit is at src/Makefile

# make 默认会找第一个定义的目标，所以这个Makefile默认目标是default
# 目标 default 依赖与 目标 all，所以实际执行的是 目标 all 里面的命令
default: all

# 特殊目标，没有找到明确的目标，就是执行这个特殊目标里面的命令
# $@表示目标名
.DEFAULT:
	cd src && $(MAKE) $@

# 目标 install
install:
	cd src && $(MAKE) $@

# 假目标 避免目录里面有个 install文件，导致目标install已经是最新的问题
.PHONY: install
