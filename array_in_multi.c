//
// Created by liu_property on 2022/11/6.
//
#include "useful_function_2.h"

#define NUM_THREADS 4


#define n 68
int (*arr_1)[n], (*arr_2)[n];
int m, n_1;
int m_2, n_2;
void *Thread(void *id) {
    time_t time1 = clock();
    int threadid = (int) id;
    printf("%dth started.\n", threadid);

    //对m_2切割
    int segment = m_2 / NUM_THREADS;
    int index_first[NUM_THREADS + 1];
    for (int i = 0; i < NUM_THREADS; ++i)
        index_first[i] = i * segment;
    index_first[NUM_THREADS] = m_2;
    _Bool flag, flag_2;
//    print_mat_1(NUM_THREADS + 1, index_first);
    for (int i = index_first[threadid]; i < index_first[threadid + 1]; ++i) {
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
        if (flag) {
            printf("FAIL************\n");

            printf("\a");
            Sleep(3000);//这样才能完整播放音乐
            exit(0);//终止程序

        }
//        printf("%d %d %d\n", i+1, m_2, flag);




    }
    printf("%d th finished. Time passed:%f\n", threadid, (clock() - time1) * 1.0 / 1000);
    pthread_exit(NULL);

}


int main(int argc, char *argv[]) {
    time_t time1 = clock();
    time_t t;
    struct tm *lt;
    time(&t);
    lt = localtime(&t);
    printf("%d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);

    read_array_m_n("6_0_result_maybe.txt", &m, &n_1);
    printf("# of row:%d, # of col:%d %d\n", m, n_1, n);
    arr_2 = (int (*)[n]) malloc(m * n * sizeof(int));
    txt_2_array("6_0_result_maybe.txt", m, n_1, arr_2);

    read_array_m_n("o_1.txt", &m_2, &n_2);
    printf("# of row:%d, # of col:%d %d\n", m_2, n_2, n);
    arr_1 = (int (*)[n]) malloc(m_2 * n * sizeof(int));
    txt_2_array("o_1.txt", m_2, n_2, arr_1);

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, Thread, (void *) i);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(arr_1);
    free(arr_2);
    printf("time to range: %.1f\n", (clock() - time1) * 1.0 / 1000);
    return 0;
}