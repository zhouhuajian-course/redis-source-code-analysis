// 接收 处理 Ctrl+C SIGINT 信号进行软中断
// 程序执行自己的收尾操作
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int signo) {
    printf("中断前先把内存中的数据写入到磁盘\n");
    // 需要自己退出进程，不然不会退出
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1) {}
    return 0;
}