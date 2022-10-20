# 递归展开变量 =
# 和大多数的编程语言规则不同
foo = $(bar)
bar = $(var)
var = abc

test1:
# foo 的值为 abc 递归展开
	echo ${foo}

# 简单展开 := ::= 效果一样 := 可能旧版本不支持
# 和大多数的编程语言规则类似
foo1 := bar
foo2 := $(foo1)
foo1 := abc

test2:
# foo2 的值是 bar 而不是 abc 简单展开
	echo $(foo2)

# 有条件的变量定义，没定义过才会定义
# Make 变量严格区分大小写 FOO和foo是不同变量
FOO ?= bar

test3:
# 如果命令行中添加弹出FOO=BAR那么，FOO的值为BAR，否则为bar
	echo ${FOO}

# > mingw32-make test3 FOO=BAR
# echo BAR
# BAR
#
# > mingw32-make test3
# echo bar
# bar