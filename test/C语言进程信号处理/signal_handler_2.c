// 接收 处理 Ctrl+C SIGINT 信号进行软中断
// 程序执行自己的收尾操作
// 多线程

// 编译 gcc -pthread signal_handler_2.c

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

void *thread_1(void *no) {
    while (1) {
        printf("thread 1 is running.\n");
        sleep(5);
    }
}

void *thread_2(void *no) {
    while (1) {
        printf("thread 2 is running.\n");
        sleep(5);
    }
}

void sigint_handler(int signo) {
    printf("中断前先把内存中的数据写入到磁盘\n");
    // 需要自己退出进程，不然不会退出
    exit(0);
}

int main() {
    pthread_t t1, t2;
    signal(SIGINT, sigint_handler);
    // 创建两个线程 并开始运行
    pthread_create(&t1, NULL, thread_1, NULL);
    pthread_create(&t2, NULL, thread_2, NULL);
    // 等待两个线程结束
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}