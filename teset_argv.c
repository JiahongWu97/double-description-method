//
// Created by liu_property on 2023/1/16.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[]) {//argv[0]是程序名，1才是后续
//    printf("%d %d\n", *argv[0], *argv[0]);
    printf("%d %d\n", atoi(argv[1]), atoi(argv[2]));
//    printf("%c %c\n", *argv[1], *argv[2]);
//    printf("%s %s\n", argv[1], argv[2]);//有问题，先不用
}