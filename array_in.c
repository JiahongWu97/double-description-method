//
// Created by liu_property on 2022/11/6.
//

#include "useful_function_2.h"

int main(int argc, char *argv[]) {
    time_t time_whole = clock();
    time_t t;
    struct tm *lt;
    time(&t);
    lt = localtime(&t);
    printf("%d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);

    int m, n;
    read_array_m_n("6_0_result_maybe.txt", &m, &n);
    printf("# of row:%d, # of col:%d\n", m, n);
    int arr_2[m][n];
    txt_2_array("6_0_result_maybe.txt", m, n, arr_2);

    int m_2, n_2;
    read_array_m_n("o_1.txt", &m_2, &n_2);
    printf("# of row:%d, # of col:%d\n", m_2, n_2);
    int arr_1[m_2][n_2];
    txt_2_array("o_1.txt", m_2, n_2, arr_1);

    _Bool flag, flag_2;
    for (int i = 0; i < m_2; ++i) {
        flag = TRUE;
        for (int j = 0; j < m; ++j) {
            flag_2 = TRUE;
            for (int k = 0; k < n; ++k) {
                if (arr_2[j][k] != arr_1[i][k]) {
                    flag_2 = FALSE;
                    break;
                }
            }
            if (flag_2) {
                flag = FALSE;
                break;
            }
        }
        if (flag)
            printf("FAIL************\n");
//        printf("%d %d %d\n", i+1, m_2, flag);


    }

    printf("time to range: %.1f\n", (clock() - time_whole) * 1.0 / 1000);

}