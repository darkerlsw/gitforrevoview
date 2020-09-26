#include "stdio.h"
#include "stdlib.h"

//可以返回指向字符串常量的局部指针
char *returnStr() {
    char *p = "hello world";
    return p;
}

int returnStr2() {
    char *p;
    p = returnStr();
    printf("%s\n", p);
    return 0;
}

//可以返回局部变量的值
int func() {
    int a;
    a = 3;
    return a;
}

int *func1() {
    int a;
    a = 3;
    //return &a;
    return 0;
}

//可以返回static变量修饰的类型
char *staticStr() {
    static char p[] = "hello world";
    return p;
}

int staticStr1() {
    char *p;
    p = staticStr();
    printf("%s\n", p);
    return 0;
}

char *arry() {
    static char a[6] = {0};
    return &a[0];
}

char *arry2() {
    static char a[2][3] = {0};
    char *p = (char *)malloc(sizeof(char) * 2 * 3);
    p = &a;
    return p;
}

//函数可以返回局部变量的值，但不能返回非静态局部变量的指针
//函数可以返回static修饰的指针，但想要返回局部变量数组的指针，不但数组要被static修饰，还需要将指针指向堆内存
