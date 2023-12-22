//
// Created by liu_property on 2022/10/30.
//

#include "useful_function_2.h"

#define NUM_THREADS 10
#define m 35
#define n 68
_Bool rand_initial_greedy = 0;
//gcc -Wl,--stack,4294967296 -o ./cmake-build-debug/tell.exe tell_me_array_dim.c
//gcc -Wl,--stack,4294967296 -o ./cmake-build-debug/r.exe trun.c -pthread


int ineq[m][n], ineq_order[m], (*er)[n], ii, *birth_index, *random_pos;
_Bool (*active_ineq)[m];
struct er_new_info *head, *prev, *current;
int len_er, count_new, *inherit_adj;

pthread_mutex_t lock_x = PTHREAD_MUTEX_INITIALIZER;

void *Thread(void *id) {
    time_t time1 = clock();
    int threadid = (int) id;

    printf("%dth started.\n", threadid);
    int count_pos, count_zero, count_neg;
    count_pos = 0;
    count_zero = 0;
    count_neg = 0;
    int value[len_er];
    int sign[3][len_er];
    for (int i = 0; i < len_er; ++i) {
        value[i] = inner_produce(n, er[i], ineq[ineq_order[ii]]);
        if (value[i] > 0)
            sign[0][count_pos++] = i;
        else if (value[i] == 0)
            sign[1][count_zero++] = i;
        else
            sign[2][count_neg++] = i;
    }
//        print_mat_2_long(3, len_er, sign);

    int col_index[n], jj, col_temp;
//    srand((unsigned) time(NULL));//这样每次运行，初始的随机数确实不一样
    for (int i = 0; i < n; ++i) {
        col_index[i] = i;
    }
    for (int i = n - 1; i > 0; --i) {
        jj = rand() * (i + 1) / (RAND_MAX + 1);
        col_temp = col_index[i];
        col_index[i] = col_index[jj];
        col_index[jj] = col_temp;//为了高斯消除时及早退出
    }


    //对+切割
    int segment = count_pos / NUM_THREADS;
    int index_first[NUM_THREADS + 1];
    for (int i = 0; i < NUM_THREADS; ++i)
        index_first[i] = i * segment;
    index_first[NUM_THREADS] = count_pos;

//    for (int l = index_first[threadid]; l < index_first[threadid + 1]; ++l)

    int count_ineq, ineq_reg[m], max_birth;
    double ineq_copy[m][n];
    _Bool flag;
    for (int i = index_first[threadid]; i < index_first[threadid + 1]; ++i) {
        for (int j = 0; j < count_neg; ++j) {

            if (inherit_adj[sign[0][random_pos[i]]] == sign[2][j] || inherit_adj[sign[2][j]] == sign[0][random_pos[i]]) {
                pthread_mutex_lock(&lock_x);
                count_new++;
                current = (struct er_new_info *) malloc(sizeof(struct er_new_info));
                current->pos = random_pos[i];
                current->neg = sign[2][j];
                current->pos_v = value[sign[0][random_pos[i]]];
                current->neg_v = value[current->neg];
                current->next = NULL;
                if (head == NULL)
                    head = current;
                else
                    prev->next = current;
                prev = current;
                pthread_mutex_unlock(&lock_x);
            } else {
                if (birth_index[sign[0][random_pos[i]]] < birth_index[sign[2][j]])
                    max_birth = birth_index[sign[2][j]];
                else
                    max_birth = birth_index[sign[0][random_pos[i]]];
                flag = 0;
                for (int k = max_birth; k < ii; ++k) {
                    if (active_ineq[sign[0][random_pos[i]]][k] && active_ineq[sign[2][j]][k]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag) {
                    count_ineq = 0;
                    for (int k = 0; k < ii; ++k) {
                        if (active_ineq[sign[0][random_pos[i]]][k] && active_ineq[sign[2][j]][k]) {
                            ineq_reg[count_ineq++] = k;
                        }
                    }
                    if (count_ineq >= n - 2) {

                        for (int k = 0; k < count_ineq; ++k) {
                            for (int l = 0; l < n; ++l) {
//                        ineq_copy[k][l] = (double) ineq[ineq_order[ineq_reg[k]]][l];
                                ineq_copy[k][l] = (double) ineq[ineq_order[ineq_reg[k]]][col_index[l]];
                            }
                        }
                        if (rank_0_1_dedicated(count_ineq, n, ineq_copy) == n - 2) {
                            pthread_mutex_lock(&lock_x);
                            count_new++;
                            current = (struct er_new_info *) malloc(sizeof(struct er_new_info));
                            current->pos = random_pos[i];
                            current->neg = sign[2][j];
                            current->pos_v = value[sign[0][random_pos[i]]];
                            current->neg_v = value[current->neg];
                            current->next = NULL;
                            if (head == NULL)
                                head = current;
                            else
                                prev->next = current;
                            prev = current;
                            pthread_mutex_unlock(&lock_x);
                        }

                    }


                }
            }
        }
    }
    printf("%d th finished. Time passed:%f\n", threadid, (clock() - time1) * 1.0 / 1000);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    srand((unsigned) time(NULL));//这样每次运行，初始的随机数确实不一样

    if (argc < 2) {
        printf("no input\n");
        exit(1);
    }
    printf("# of row:%d, # of col:%d\n", m, n);
    txt_2_array(argv[1], m, n, ineq);

/*
    int txt_ineq_order[1][n];
    txt_2_array(argv[3], 1, n, txt_ineq_order);
//    print_mat_2(1, n, txt_ineq_order);
*/

    _Bool (*active_ineq_new)[m], flag;
    active_ineq = (_Bool (*)[m]) malloc(n * m * sizeof(_Bool));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            active_ineq[i][j] = 1;
        }
        active_ineq[i][i] = 0;
    }
//    print_mat_2_bool(n, m, active_ineq);

    birth_index = (int *) malloc(n * sizeof(int));
    inherit_adj = (int *) malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        birth_index[i] = 0;
        inherit_adj[i] = -1;//用-1来表示无！
    }

    int ineq_shuffle[m], jjj, ineq_temp, rank = 1;
    double ineq_copy[m][n];

    for (int i = 0; i < m; ++i) {
        ineq_order[i] = i;
//        ineq_shuffle[i] = m - i - 1;
        ineq_shuffle[i] = i;
    }

    if (rand_initial_greedy) {
        for (int i = m - 1; i > 0; --i) {
            jjj = rand() * (i + 1) / (RAND_MAX + 1);
            ineq_temp = ineq_shuffle[i];
            ineq_shuffle[i] = ineq_shuffle[jjj];//好像加不了速度
            ineq_shuffle[jjj] = ineq_temp;
        }
    }
//    print_mat_1(m, ineq_shuffle);

    int rank_new;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            ineq_copy[i][j] = (double) ineq[ineq_shuffle[i]][j];
        }
    }

    ineq_order[0] = ineq_shuffle[0];
    int order_offset = n;
    for (int i = 2; i < m + 1; ++i) {
        rank_new = rank_0_1(i, n, ineq_copy);
        if (rank_new - rank) {
            ineq_order[rank++] = ineq_shuffle[i - 1];
        }
        if (rank == n)
            break;
    }

/*
    //从txt来的order
    for (int i = 0; i <n; ++i) {
        ineq_order[i] = txt_ineq_order[0][i];
    }
*/

    printf("find initial basis %d %d\n", rank, n);
    printf("\n************************\n");
    print_mat_1(rank, ineq_order);

    for (int i = 0; i < m; ++i) {
        flag = 1;
        for (int j = 0; j < n; ++j) {
            if (ineq_order[j] == i) {
                flag = 0;
                break;
            }
        }
        if (flag)
            ineq_order[rank++] = i;//索引补回来
    }


    printf("\n************************\n");
    print_mat_1(m, ineq_order);
//    print_mat_2(m, n, ineq);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ineq_copy[i][j] = (double) ineq[ineq_order[i]][j];
        }
    }

    int (*er_new)[n];
    er = (int (*)[n]) malloc(n * n * sizeof(int));

    double er_double[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            er_double[i][j] = (double) 0;
        }
        er_double[i][i] = (double) 1;
    }

//    print_mat_2(n, n, ineq_copy);
    rank = inv_0_1(n, n, ineq_copy, er_double);
    printf("find initial basis %d %d\n", rank, n);
    if (rank != n)
        return 1;
    square_matrix_T(n, er_double);
//    print_mat_2_double(n, n, er_double);

    double tol = 1e-6, sum_v, er_reg[n];
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < 100; ++j) {
            sum_v = 0;
            for (int k = 0; k < n; ++k) {
                er_reg[k] = er_double[i][k] * j;
                sum_v += pow(er_reg[k] - round(er_reg[k]), 2);
            }
            if (sum_v < tol) {
                for (int k = 0; k < n; ++k) {
                    er[i][k] = (int) round(er_reg[k]);//毕竟有理数，修回整数
                    if (er[i][k] != 0 && j > 1)
//                    if (er[i][k] != 0)
                        printf("%5.3f %5d\n", er_double[i][k], er[i][k]);
                }
                if (j > 1) {
                    printf("\a");
                    Sleep(3000);//这样才能完整播放音乐
                    printf("\n************************\n");
                }
                break;
            }
        }
    }
/*
    printf("\n************************\n");
    print_mat_2(n, n, er);
    printf("\n************************\n");
    file_write(n, n, er, argv[2]);
*/


    int count_pos, count_zero, count_neg, count_er_all, point_temp, jj;
    time_t time_whole = clock(), time1;
    double offset, now;
    int value_reg, ineq_choose;
    len_er = n;
    ii = n;
    pthread_t threads[NUM_THREADS];

    int *birth_index_new, *inherit_adj_new, search_i_reg, father;

    while (ii < m) {
        if (rand_initial_greedy) {
//        if (1) {
            //max |pos|
            offset = 0.0;
            for (int i = ii; i < m; ++i) {
                count_pos = 0;
                for (int j = 0; j < len_er; ++j) {
                    value_reg = inner_produce(n, er[j], ineq[ineq_order[i]]);
                    if (value_reg > 0)
                        count_pos++;
                }
                now = (double) count_pos;
                if (now > offset) {
                    ineq_choose = i;
                    offset = now;
                }
            }
            value_reg = ineq_order[ineq_choose];
            ineq_order[ineq_choose] = ineq_order[ii];
            ineq_order[ii] = value_reg;
        }
/*
        if (rand_initial_greedy) {
            //do greedy choose
            offset = 1e20;
            for (int i = ii; i < m; ++i) {
                count_pos = 0;
                count_neg = 0;
                for (int j = 0; j < len_er; ++j) {
                    value_reg = inner_produce(n, er[j], ineq[ineq_order[i]]);
                    if (value_reg > 0)
                        count_pos++;
                    else if (value_reg < 0)
                        count_neg++;
                }
                now = (double) count_pos * count_neg;
                if (now < offset) {
                    ineq_choose = i;
                    offset = now;
                }
            }
            value_reg = ineq_order[ineq_choose];
            ineq_order[ineq_choose] = ineq_order[ii];
            ineq_order[ii] = value_reg;
        }
*/


        count_pos = 0;
        count_zero = 0;
        count_neg = 0;
        int value[len_er];
        int sign[3][len_er];
        for (int i = 0; i < len_er; ++i) {
            value[i] = inner_produce(n, er[i], ineq[ineq_order[ii]]);
            if (value[i] > 0)
                sign[0][count_pos++] = i;
            else if (value[i] == 0)
                sign[1][count_zero++] = i;
            else
                sign[2][count_neg++] = i;
        }
//        print_mat_2_long(3, len_er, sign);
        random_pos = (int *) malloc((unsigned long long) count_pos * sizeof(int));
        for (int i = 0; i < count_pos; ++i) {
            random_pos[i] = i;//shuffle了for循环
        }
//        print_mat_1(count_pos, random_pos);
        for (int i = count_pos - 1; i > 0; --i) {
            jjj = (int) ((double) rand() / RAND_MAX * i);//之前m n不会越界吧,这会 count_pos = e5，爆炸！
            ineq_temp = random_pos[i];
            random_pos[i] = random_pos[jjj];
            random_pos[jjj] = ineq_temp;
        }
//        print_mat_1(count_pos, random_pos);



        printf("%.1E %.1E %.1E \n", (double) count_pos, (double) count_zero, (double) count_neg);
        count_new = 0;
        head = NULL;
//        count_trick_1 = 0;
        time1 = clock();

        time_t t;
        struct tm *lt;
        time(&t);
        lt = localtime(&t);
        printf("%d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);


        for (int i = 0; i < NUM_THREADS; ++i) {
            pthread_create(&threads[i], NULL, Thread, (void *) i);
        }
        for (int i = 0; i < NUM_THREADS; ++i) {
            pthread_join(threads[i], NULL);
        }

        printf("time to range: %.1f\n", (clock() - time1) * 1.0 / 1000);
        time1 = clock();

        len_er = (count_pos + count_zero + count_new);
//        printf("%.1E now number\n", (double) (count_pos + count_zero + count_new));
        active_ineq_new = (_Bool (*)[m]) malloc((unsigned long long) len_er * m * sizeof(_Bool));
        er_new = (int (*)[n]) malloc((unsigned long long) len_er * n * sizeof(int));
        birth_index_new = (int *) malloc(len_er * sizeof(int));
        inherit_adj_new = (int *) malloc(len_er * sizeof(int));
        count_er_all = 0;
//        printf("%.1E finish initialization\n", (double) len_er);//执行到这一步并不代表着内存都分配好了！

        for (int i = 0; i < count_pos; ++i) {
            birth_index_new[count_er_all] = birth_index[sign[0][i]];
//            printf("pos binary: %d\n", inherit_adj[sign[0][i]]);
            father = inherit_adj[sign[0][i]];
            if (father > -1) {
                if (value[father] > 0) {
                    search_i_reg = binary_search(father, count_pos, sign[0]);
                    inherit_adj_new[count_er_all] = search_i_reg;
                } else if (value[father] == 0) {
                    search_i_reg = binary_search(father, count_zero, sign[1]);
                    inherit_adj_new[count_er_all] = search_i_reg + count_pos;
                } else {
                    inherit_adj_new[count_er_all] = -1;
                }
            } else
                inherit_adj_new[count_er_all] = -1;
            for (int j = 0; j < n; ++j) {
                er_new[count_er_all][j] = er[sign[0][i]][j];
            }
            for (int j = 0; j < ii; ++j) {
                active_ineq_new[count_er_all][j] = active_ineq[sign[0][i]][j];
            }
            active_ineq_new[count_er_all++][ii] = 0;
        }
//        printf("finish build pos\n");
        for (int i = 0; i < count_zero; ++i) {
            birth_index_new[count_er_all] = birth_index[sign[1][i]];
//            printf("zero binary: %d\n", inherit_adj[sign[1][i]]);
            father = inherit_adj[sign[1][i]];
            if (father > -1) {
                if (value[father] > 0) {
                    search_i_reg = binary_search(father, count_pos, sign[0]);
                    inherit_adj_new[count_er_all] = search_i_reg;
                } else if (value[father] == 0) {
                    search_i_reg = binary_search(father, count_zero, sign[1]);
                    inherit_adj_new[count_er_all] = search_i_reg + count_pos;
                } else {
                    inherit_adj_new[count_er_all] = -1;
                }
            } else
                inherit_adj_new[count_er_all] = -1;
            for (int j = 0; j < n; ++j) {
                er_new[count_er_all][j] = er[sign[1][i]][j];
            }
            for (int j = 0; j < ii; ++j) {
                active_ineq_new[count_er_all][j] = active_ineq[sign[1][i]][j];
            }
            active_ineq_new[count_er_all++][ii] = 1;
        }
//        printf("finish build zero\n");
        current = head;
        while (current != NULL) {
            birth_index_new[count_er_all] = ii;
            inherit_adj_new[count_er_all] = current->pos;//必出现

            for (int i = 0; i < n; ++i) {
                er_new[count_er_all][i] = (er[current->neg][i]) * (current->pos_v) - (er[sign[0][current->pos]][i]) * (current->neg_v);
            }
//            printf("before:");
//            print_mat_1(n, er_new[count_er_all]);
            reduce_gcd(n, er_new[count_er_all]);
//            printf("after   :");
//            print_mat_1(n, er_new[count_er_all]);
            for (int k = 0; k < ii; ++k) {
                active_ineq_new[count_er_all][k] = active_ineq[sign[0][current->pos]][k] && active_ineq[current->neg][k];
            }
            active_ineq_new[count_er_all++][ii] = 1;
//            free(current);//放这里好像会出事
            prev = current;
            current = current->next;//保险一点先读了
            free(prev);
        }

//        print_mat_1(len_er, birth_index_new);
//        print_mat_1(len_er, inherit_adj_new);
//        printf("finish build new\n");
        free(active_ineq);
        free(er);
        free(birth_index);
        free(inherit_adj);
        free(random_pos);
        printf("time to build: %.1f\n", (clock() - time1) * 1.0 / 1000);
        printf("%.1E success build\n", (double) count_new);
//        printf("(%d,%d),  # of iter: %.3E, # of trick_1: %.3E, time passed: %.1f, choosen ineq: %d\n", ii + 1, m, (double) count_pos * count_neg, (double) count_trick_1, (clock() - time_whole) * 1.0 / 1000, ineq_order[ii]);
        printf("(%d,%d),  # of iter: %.3E, time passed: %.1f, choosen ineq: %d\n", ii + 1, m, (double) count_pos * count_neg, (clock() - time_whole) * 1.0 / 1000, ineq_order[ii]);
        printf("\n************************\n");
        active_ineq = active_ineq_new;
        er = er_new;
        birth_index = birth_index_new;
        inherit_adj = inherit_adj_new;
        file_write(len_er, n, er, argv[2]);

        ii++;
    }


    printf("final length %d, time:%f", len_er, (clock() - time_whole) * 1.0 / 1000);

//    file_write(len_er, n, er, argv[2]);
    return 0;
}


