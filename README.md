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

## Redis 处理命令调用栈

```shell
(gdb) backtrace
#0  processCommand (c=c@entry=0x8de6c0) at server.c:3612
#1  0x000000000045a1ac in processCommandAndResetClient (c=c@entry=0x8de6c0) at networking.c:2444
#2  0x000000000045cc31 in processInputBuffer (c=c@entry=0x8de6c0) at networking.c:2548
#3  0x000000000045fe69 in readQueryFromClient (conn=<optimized out>) at networking.c:2684
#4  0x00000000004f6c33 in callHandler (handler=<optimized out>, conn=0x8de670) at connhelpers.h:79
#5  connSocketEventHandler (el=<optimized out>, fd=<optimized out>, clientData=0x8de670, mask=<optimized out>) at connection.c:310
#6  0x000000000043aa45 in aeProcessEvents (eventLoop=eventLoop@entry=0x88d190, flags=flags@entry=27) at ae.c:436
#7  0x000000000043ad8d in aeMain (eventLoop=0x88d190) at ae.c:496
#8  0x0000000000437011 in main (argc=1, argv=0x7fffffffe498) at server.c:7075
```

## Redis 主从复制 

在 server.c processCommand 里面，打印 主节点 Redis 执行的命令

```c
#include <stdio.h>
int processCommand(client *c) {
    int i = 0;
    printf("命令参数数量 c->argc = %d\n", c->argc);
    for(i = 0; i < c->argc; i++) {
        char *str = c->argv[i]->ptr;
        printf("%s ", str);
    }
    printf("\n");
    // ...
}
```

### 从节点启动服务

4869:S 24 Oct 2022 14:44:29.217 * Ready to accept connections
4869:S 24 Oct 2022 14:44:29.218 * Connecting to MASTER 127.0.0.1:6379
4869:S 24 Oct 2022 14:44:29.218 * MASTER <-> REPLICA sync started
4869:S 24 Oct 2022 14:44:29.218 * Non blocking connect for SYNC fired the event.

### 然后，从节点发送给主节点命令

1. PING 命令，检查是否能和Master沟通；
2. REPLCONF 命令，
   The REPLCONF command is an internal command. 
   It is used by a Redis master to configure a connected replica.
   让Master记录从节点的信息
3. PSYNC partial sync
   部分同步/增量同步，
   如果第一次同步，那么使用全量同步
   ----
   SYNC是2.8版本以前的同步命令，每次都是全量同步
4. REPLCONF 每隔一秒发这个命令

大概每一秒钟会去主节点请求同步数据
可以从从节点的日志中看出