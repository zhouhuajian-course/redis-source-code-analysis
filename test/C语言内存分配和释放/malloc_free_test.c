#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <limits.h>
// INT_MIN INT_MAX UINT_MAX
// LONG_MIN LONG_MAX ULONG_MAX
// LONG_LONG_MIN LONG_LONG_MAX ULONG_LONG_MAX

int main() {
    // 申请能存储10个整型的内存 10 * sizeof(int) = 40 个字节
    // size_t 在 GNU C库中，64位是 unsigned long int 32位是 unsigned int
    // 如果用来表示大小数据，推荐使用size_t
    // 大小类型 size type
    // https://www.gnu.org/software/libc/manual/html_node/Important-Data-Types.html#index-size_005ft
    // 即使不调用free 程序正常结束 也会释放malloc申请的内存
    // 如果这块内存不需要了，并且程序还一直在跑，没有free，则会导致内存泄漏
    // 申请成功返回内存开始地址，申请失败返回空指针，例如内存空间不足
    int *ptr = malloc(10 * sizeof(int));
    // int *ptr = malloc(LONG_LONG_MAX);
    // 64位Centos上输出 8 4 8 8
    // printf("%d\n", sizeof(size_t));  // 说明 size_t 在64位操作系统上是 unsigned long
    // printf("%d\n", sizeof(int));
    // printf("%d\n", sizeof(unsigned long));
    // printf("%d\n", sizeof(unsigned long long));
    int i;
    if (ptr == NULL) {
        // Not enough space
        printf("%s", strerror(errno));
    } else {
        printf("%s\n", "申请成功，数据不会进行初始化");
        // 遍历
        printf("%s\n", "====================");
        for (i = 0; i < 10; i++) {
            printf("%d ", *(ptr + i));
            // 12278848 0 12255568 0 1030059625 1308637763 1161973077 1179606866 1330794591 1397966147
        }
        printf("\n");
        printf("%s\n", "====================");
        // 0 ~ 9 赋值
        for (i = 0; i < 10; i++) {
            *(ptr + i) = i;
        }
        // 遍历
        for (i = 0; i < 10; i++) {
            printf("%d ", *(ptr + i));
        }
    }
    free(ptr);

    return 0;
}


/*
Data Type: size_t
This is an unsigned integer type used to represent the sizes of objects.
The result of the sizeof operator is of this type,
and functions such as malloc (see Unconstrained Allocation) and memcpy (see Copying Strings and Arrays) accept arguments of this type to specify object sizes.
On systems using the GNU C Library, this will be unsigned int or unsigned long int.

Usage Note: size_t is the preferred way to declare any arguments or variables that hold the size of an object.


> .\malloc_free_test.exe
申请成功，数据不会进行初始化
====================
11099200 0 11075920 0 1030059625 1308637763 1161973077 1179606866 1330794591 1397966147
====================
0 1 2 3 4 5 6 7 8 9

 */