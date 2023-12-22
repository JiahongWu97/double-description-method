//
// Created by liu_property on 2022/10/15.
//

#ifndef C_DD_MINE_USEFUL_FUNCTION_H
#define C_DD_MINE_USEFUL_FUNCTION_H

#endif //C_DD_MINE_USEFUL_FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <windows.h>

struct er_new_info {
    int pos_v, neg_v;
    unsigned long long pos, neg;
    struct er_new_info *next;
};


int inner_produce(int col, int *a, int *b) {
    int count = 0;
    for (int i = 0; i < col; ++i) {
        count += a[i] * b[i];
    }
    return count;
};

void file_write(unsigned long long row, int col, int a[row][col], const char *_Filename) {
    FILE *fp;
//    fp = fopen("D:\\p\\secure network coding bound 2\\right.txt", "w");
    fp = fopen(_Filename, "w");

    for (unsigned long long i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            fprintf(fp, "%d", a[i][j]);
            fprintf(fp, j == col - 1 ? "" : " ");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void read_array_m_n(const char *_Filename, int *m, int *n) {
    FILE *fp;
    fp = fopen(_Filename, "r");
    if (fp == NULL) {
        printf("not find %s", _Filename);
        exit(1);
    }
    int ch;
    ch = getc(fp);
    int count_n = 0, count_s = 0;
    while (ch != EOF) {
        switch (ch) {
            case ' ':
                count_s++;
                break;
            case '\n':
                count_n++;
                break;
        }
//        putc(ch, stdout);
        ch = getc(fp);
    }
    printf("\n************************\n");

    printf("%d %d\n", count_n, count_s);
    fclose(fp);
    *m = count_n;
    *n = count_s / count_n + 1;
    if (count_s % count_n == 0) {
        printf("read success\n");
    } else
        exit(1);
}

void txt_2_array(const char *_Filename, int m, int n, int ineq[m][n]) {
    //    rewind(fp);
    FILE *fp;
    fp = fopen(_Filename, "r");
    if (fp == NULL) {
        printf("not find %s", _Filename);
        exit(1);
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(fp, "%d", &ineq[i][j]);
//            printf("%d ", ineq[i][j]);
        }
//        printf("\n");
    }
    fclose(fp);
}


void print_mat_2(int row, int col, int a[row][col]) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%d", a[i][j]);
            printf(j == col - 1 ? "" : " ");
        }
        printf("\n");
    }
}

void print_mat_2_double(int row, int col, double a[row][col]) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%.3f", a[i][j]);
            printf(j == col - 1 ? "" : " ");
        }
        printf("\n");
    }
}


void print_mat_2_bool(int row, int col, _Bool a[row][col]) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%d", a[i][j]);
            printf(j == col - 1 ? "" : " ");
        }
        printf("\n");
    }
}

void print_mat_2_long(int row, int col, unsigned long long a[row][col]) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%d", a[i][j]);
            printf(j == col - 1 ? "" : " ");
        }
        printf("\n");
    }
}

void print_mat_1(int row, int a[row]) {
    for (int i = 0; i < row; ++i) {
        printf("%d", a[i]);
        printf(i == row - 1 ? "" : " ");
    }
    printf("\n");
}

void print_mat_1_long(unsigned long long row, unsigned long long a[row]) {
    for (unsigned long long i = 0; i < row; ++i) {
        printf("%d", a[i]);
        printf(i == row - 1 ? "" : " ");
    }
    printf("\n");
}

int gcd(int x, int y) {
    if (y == 0)
        return x;
    else
        return gcd(y, x % y);
//    int z = 0;
//    while (z == (x % y)) {
//        x = y;
//        y = z;
//    }
//    return y;
}

void reduce_gcd(int col, int a[]) {//针对大于等于0的
    int temp = 0;
    for (int i = 0; i < col; ++i) {
        temp = gcd(temp, abs(a[i]));//后来初始在内部了，需要用到绝对值
    }
    for (int i = 0; i < col; ++i) {
        a[i] = a[i] / temp;
    }
}

//int rref_0_1(int m, int n, int a[m][n]) {
////void rref_0_1(int m, int n, int (* a) [n]) {
//    int i = 0, j = 0, k = 0, temp, rank = 0;
//    _Bool flag;
//    while (i < m && j < n) {
////        printf("%d %d\n", i, j);
//        flag = 1;
//        for (k = i; k < m; k++) {
////                    printf("a[k,j]: %d\n", a[k][j]);
//
//            if (a[k][j] != 0) {
//                flag = 0;
//                break;
//            }
//        }
//
////        printf("%d \n", flag);
//
//        if (flag)
//            j++;
//        else {
//            rank++;
//            //i - > k
//            for (int l = j; l < n; ++l) {
//                temp = a[i][l];
//                a[i][l] = a[k][l];
//                a[k][l] = temp;
//            }
////            print_mat_2(m, n, a);
////            printf("before:");
////            print_mat_1(n, a[i]);
//            temp = a[i][j];//否则在变
//            for (int l = j; l < n; ++l) {
//                a[i][l] /= temp;
//            }
///*
//            printf("after   :");
//            print_mat_1(n, a[i]);
//*/
//            for (int l = 0; l < m; ++l) {
//                if ((l != i) && (a[l][j] != 0)) {
//                    temp = a[l][j];
//                    for (int i1 = j; i1 < n; ++i1) {
//                        a[l][i1] -= a[i][i1] * temp;
//                    }
//                }
//            }
//
//            i++;
//            j++;
////            print_mat_2(m, n, a);
//
//        }
////        print_mat_2(m, n, a);
//
//    }
//
//    return rank;
//}

int rank_0_1(int m, int n, double a[m][n]) {//模仿rref
    int i = 0, j = 0, k, rank = 0;
    double tol = 1e-6, max_v, temp;
//    double reg[m];
    while (i < m && j < n) {
/*
        for (int l = i; l < m; ++l) {
            if (a[l][j] >= 0) {
                reg[l] = a[l][j];
            } else
                reg[l] = - a[l][j];
        }
*/

        max_v = fabs(a[i][j]);
        k = i;
        for (int l = i + 1; l < m; ++l) {
            temp = fabs(a[l][j]);
            if (temp > max_v) {
                max_v = temp;
                k = l;
            }
        }

        if (max_v < tol) {
/*
            for (int l = i; l < m; ++l) {
                a[l][j] = 0;//只是想知道rank
            }
*/
            j++;
        } else {
            rank++;
            //i - > k
            for (int l = j; l < n; ++l) {
                temp = a[i][l];
                a[i][l] = a[k][l];
                a[k][l] = temp;
            }
/*
            temp = a[i][j];//否则在变
            for (int l = j; l < n; ++l) {
                a[i][l] /= temp;
            }
*/
            for (int l = i + 1; l < m; ++l) {//向下
                if (a[l][j] != 0) {
                    temp = a[l][j] / a[i][j];
                    for (int i1 = j; i1 < n; ++i1) {
                        a[l][i1] -= a[i][i1] * temp;
//                        a[l][i1] = a[l][i1] - a[i][i1] * a[l][j];//尼玛变成0了
                    }
                }
            }
            i++;
            j++;
        }
    }
    return rank;
}

int rank_0_1_dedicated(int m, int n, double a[m][n]) {//模仿rref
    int i = 0, j = 0, k, count = 0;
    double tol = 1e-6, max_v, temp;
    while (i < m && j < n) {

        max_v = fabs(a[i][j]);
        k = i;
        for (int l = i + 1; l < m; ++l) {
            temp = fabs(a[l][j]);
            if (temp > max_v) {
                max_v = temp;
                k = l;
            }
        }

        if (max_v < tol) {
            count++;
            if (count > 2) {
//                printf("exit: %d %d\n", i, m);
                return n - 3;
            }
            j++;

        } else {
//            rank++;
            //i - > k
            for (int l = j; l < n; ++l) {
                temp = a[i][l];
                a[i][l] = a[k][l];
                a[k][l] = temp;
            }
            for (int l = i + 1; l < m; ++l) {//向下
                if (a[l][j] != 0) {
                    temp = a[l][j] / a[i][j];
                    for (int i1 = j; i1 < n; ++i1) {
                        a[l][i1] -= a[i][i1] * temp;
                    }
                }
            }
            i++;
            j++;
        }
    }
    return n - 2;
}

void square_matrix_T(int n, double a[n][n]) {
    double temp;//呵呵，类型得对齐
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }
}


int inv_0_1(int m, int n, double a[m][n], double b[m][n]) {
    int i = 0, j = 0, k, rank = 0;
    double tol = 1e-6, max_v, temp;

    while (i < m && j < n) {
        max_v = fabs(a[i][j]);
        k = i;
        for (int l = i + 1; l < m; ++l) {
            temp = fabs(a[l][j]);
            if (temp > max_v) {
                max_v = temp;
                k = l;
            }
        }

        if (max_v < tol) {
            for (int l = i; l < m; ++l) {
                a[l][j] = 0;
            }
            j++;
        } else {
            rank++;
            //i - > k
            for (int l = j; l < n; ++l) {
                temp = a[i][l];
                a[i][l] = a[k][l];
                a[k][l] = temp;
            }
            for (int l = 0; l < n; ++l) {
                temp = b[i][l];
                b[i][l] = b[k][l];
                b[k][l] = temp;
            }

//            print_mat_2(m, n, a);
            temp = a[i][j];//否则在变
            for (int l = j; l < n; ++l) {
                a[i][l] /= temp;
            }
            for (int l = 0; l < n; ++l) {
                b[i][l] /= temp;
            }

            for (int l = 0; l < m; ++l) {
                if ((l != i) && (a[l][j] != 0)) {
                    temp = a[l][j];
                    for (int i1 = j; i1 < n; ++i1) {
                        a[l][i1] -= a[i][i1] * temp;
                    }
                    for (int i1 = 0; i1 < n; ++i1) {
                        b[l][i1] -= b[i][i1] * temp;
                    }
                }
            }

            i++;
            j++;
//        print_mat_2(m, n, a);
//            printf("\n************************\n");
        }

    }
    return rank;
}

//呵呵，用unsigned long long不会出现-1， 0<=-1为真
int binary_search(unsigned long long value, int n, unsigned long long a[]) {
    int left = 0, right = n - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
//        printf("%d %d %d judge: %d\n", left, right, mid, left <= right);
        if (a[mid] < value)
            left = mid + 1;
        else if (a[mid] == value)
            return mid;
        else
            right = mid - 1;
    }
    return -1;
}