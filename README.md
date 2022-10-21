# Redis 源码分析

## Makefile 分析

GNU Make 手册  
https://www.gnu.org/software/make/manual/

Makefile 默认目标  
https://www.gnu.org/software/make/manual/make.html#How-Make-Works

Makefile 特别目标  
https://www.gnu.org/software/make/manual/make.html#Special-Targets

Nakefile 递归展开和简单展开变量  
https://www.gnu.org/software/make/manual/make.html#Flavors

Makefile 自动变量  
https://www.gnu.org/software/make/manual/make.html#Automatic-Variables

Makefile 变量覆盖  
https://www.gnu.org/software/make/manual/make.html#Overriding

Makefile 注释  
https://www.gnu.org/software/make/manual/make.html#Makefile-Contents

# Redis 图形化客户端

https://github.com/uglide/RedisDesktopManager  
https://github.com/qishibo/AnotherRedisDesktopManager

# C语言

- GNU c 手册或参考  
  https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html
- GNU libc (aka glibc) 文档  
  https://www.gnu.org/software/libc/manual/
- Linux man-pages 项目  
  https://www.kernel.org/doc/man-pages/
- GNU libc 整数  
  https://www.gnu.org/software/libc/manual/html_node/Integers.html
  

查看预定义宏 `gcc -dM -E xxx.c`

# CLion

- 选中 函数名 双击Shift 进行全局查找 可以快速找到函数的声明和实现 
  Ctrl+鼠标左键 或 Ctrl + B 一般会定位到函数的声明 而不是 实现

# Redis 六个命令

- redis-server -> src/server.c
- redis-cli -> src/redis-cli.c
- redis-benchmark -> src/redis-benchmark.c
- redis-sentinel 是 redis-server 的软链接
- redis-check-rdb 是 redis-server 的软链接
- redis-check-aof 是 redis-server 的软连接


# Redis String 字符串

- 整型字符串 未超过 LONG_MAX 使用 int 直接存在 RedisObject的ptr成员变量位置
- 普通字符串 不超过44个字节 使用 embstr 直接存在 RedisObject的末尾 总共最大64个字节
- 普通字符串 超过44个字节 使用 raw 创建一个 SDS 结构体实例 使用ptr成员变量指向 新创建的SDS实例

内存消耗由低到高  
存储性能由高到低

```shell
127.0.0.1:6379> SET name tom
OK
127.0.0.1:6379> OBJECT ENCODING name
"embstr"
127.0.0.1:6379> SET age 123
OK
127.0.0.1:6379> OBJECT ENCODING age
"int"
127.0.0.1:6379> SET school aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
OK
127.0.0.1:6379> OBJECT ENCODING school
"embstr"
127.0.0.1:6379> SET school aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
OK
127.0.0.1:6379> OBJECT ENCODING school
"raw"
```

# Redis List 列表

QuickList = LinkedList + ZipList ???

```c
typedef struct quicklist {
    quicklistNode *head;  // 链表头
    quicklistNode *tail;  // 链表尾
    unsigned long count;        /* total count of all entries in all listpacks */
    unsigned long len;          /* number of quicklistNodes */
    signed int fill : QL_FILL_BITS;       /* fill factor for individual nodes */
    unsigned int compress : QL_COMP_BITS; /* depth of end nodes not to compress;0=off */
    unsigned int bookmark_count: QL_BM_BITS;
    quicklistBookmark bookmarks[];
} quicklist;

robj *createQuicklistObject(void) {
    // 创建快速列表
    quicklist *l = quicklistCreate();
    // 创建 redis object
    robj *o = createObject(OBJ_LIST,l);
    // 设置 redis object 的编码为 QUICKLIST
    o->encoding = OBJ_ENCODING_QUICKLIST;
    return o;
}
```

# CMD 编码

设置 CMD 编码为 UTF-8

```
> chcp
活动代码页: 936
> chcp 65001
Active code page: 65001
```