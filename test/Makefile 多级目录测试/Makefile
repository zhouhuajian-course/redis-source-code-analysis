# 真正的Makefile在src目录里面
hello_world:
	cd src && ${MAKE} $@
.DEFAULT:
	cd src && ${MAKE} $@

# > mingw32-make
# cd src && mingw32-make hello_world
# mingw32-make[1]: Entering directory 'C:/Users/zhouhuajian/Desktop/redis-source-code-analysis/test/Makefile 多级目录测试/src'
# gcc -c hello_world.c
# gcc hello_world.o -o hello_world
# mingw32-make[1]: Leaving directory 'C:/Users/zhouhuajian/Desktop/redis-source-code-analysis/test/Makefile 多级目录测试/src'

# > mingw32-make install
# cd src && mingw32-make install
# mingw32-make[1]: Entering directory 'C:/Users/zhouhuajian/Desktop/redis-source-code-analysis/test/Makefile 多级目录测试/src'
# copy  .\hello_world.exe ..\bin
# 已复制         1 个文件。
# mingw32-make[1]: Leaving directory 'C:/Users/zhouhuajian/Desktop/redis-source-code-analysis/test/Makefile 多级目录测试/src'

# > mingw32-make clean
# cd src && mingw32-make clean
# mingw32-make[1]: Entering directory 'C:/Users/zhouhuajian/Desktop/redis-source-code-analysis/test/Makefile 多级目录测试/src'
# del hello_world.o hello_world.exe ..\bin\hello_world.exe
# mingw32-make[1]: Leaving directory 'C:/Users/zhouhuajian/Desktop/redis-source-code-analysis/test/Makefile 多级目录测试/src'

