//
// Created by liu_property on 2022/10/17.
//
//gcc -Wl,--stack,4294967296 -o ./cmake-build-debug/tell.exe tell_me_array_dim.c

#include "useful_function_2.h"

#define F 3
struct aa{
    int a[F];
};
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("no input\n");
        exit(1);
    }
    int m, n;
    read_array_m_n(argv[1], &m, &n);

    printf("# of row:  %5d\n # of col:%5d\n", m, n);

    struct aa asd;
    asd.a[0]=42;

    time_t time1 = clock();
    for (int i = 0; i < (int) 1e6; ++i) {
        for (int j = 0; j < (int) 1e6; ++j) {

        }
    }


    printf("Time passed:%f\n", (clock() - time1) * 1.0 / 1000);



/*
    double a=1, b=2;
    printf("%f %f\n", a/b, b/a);
*/

/*
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    for (int i =-3; i < 14; ++i) {
        printf("%d %d\n", i, binary_search(i, 10, a));
    }
*/
//    a[-1] = 23;
//    printf("%d\n", a[132]);
//    printf("%d\n", binary_search(0, 10, a));

/*
    int ii = 2147483647;
    unsigned int jj = 4294967295;
    printf("test int: %d %d %d\n", ii, ii + 1, ii + 2);
    printf("test int: %u %u %u\n", jj, jj + 1, jj + 2);
*/

/*
    int *a, len = 6, jjj, ineq_temp, r;
    a = (int *) malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i) {
        a[i] = i;
    }
//    print_mat_1(len, a);
    srand((unsigned) time(NULL));//在测试shuffule，针对数值较大的情况
    for (int i = len - 1; i > 0; --i) {
        r = rand();
        jjj = (int) ((double) r * i /RAND_MAX );//之前m n不会越界吧
//        jjj = rand() * i /RAND_MAX;//之前m n不会越界吧
        printf("%d %d %d %f\n", jjj, r, RAND_MAX, (double )r / RAND_MAX);
        ineq_temp = a[i];
        a[i] = a[jjj];
        a[jjj] = ineq_temp;
    }
    print_mat_1(len, a);
    free(a);
*/

/*
    int len_er = (int) 1e7;
    int mm = 100, nn = 63;
    _Bool active_ineq_new[len_er][mm];
    int er_new[len_er][nn];


//    _Bool a[100000];
//    int a[100000];
    printf("%lld\n", sizeof(active_ineq_new));
    printf("%lld\n", sizeof(er_new));
    //总和也就3G内存

        printf("\a");
    Sleep(4000);
*/


/*
    int mm = 246;
    _Bool (*active_ineq_new)[m], flag;
    int len_er = (int) 1.2e7;
    active_ineq_new = (_Bool (*)[m]) malloc((long long)len_er * m * sizeof(_Bool));
    _Bool a[len_er][mm];
//    _Bool *b;
//    b = (_Bool *) malloc(len_er * m * sizeof(_Bool));

    int *b;
    b = (int *) malloc(len_er * m * sizeof(int));

//    int d[(int)1e9][64];
//    boolean b;
//    printf("%d", sizeof(b));
    printf("%lld %d %d %d\n", sizeof(a), active_ineq_new == NULL, a==NULL, b==NULL);
    active_ineq_new[0][0] = 0;
//    a[0][0] = 0;
//    Sleep(30000);

    printf("%d\n", (long long) 2*2);
*/


/*
    //x学下memcopY
*/
/*
    int a[4] = {1,2,3,4};
    int * b;
    b = (int *) malloc(4 * sizeof (int));
    memcpy(b, a, 4 * sizeof(int));
    print_mat_1(4, b);
*//*

    struct er_new_info a;
    a.pos=332;
    a.neg=-234;

    struct er_new_info *b= malloc(sizeof(struct er_new_info));
    memcpy(b, &a, sizeof(struct er_new_info));
    printf("%d %d", b->pos, b->neg);
*/
/*
    struct er_new_info b;
    memcpy(&b, &a, sizeof(struct er_new_info));
    printf("%d %d", b.pos, b.neg);
*/





    return 0;
}


