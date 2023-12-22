//
// Created by liu_property on 2022/10/17.
//

#include "useful_function.h"

int main(int argc, char *argv[]) {
//    int a[]={1,2,3}, b[]={1,2,3};
//    printf("Hello, World!%d\n", inner_produce(3, a, b));
    srand((unsigned) time(NULL));//这样每次运行，初始的随机数确实不一样


/*
    int a[3][3] = {{1,0,-1}, {1,0,-1}, {1,1,0}};
    printf("rank: %d\n", rank_0_1(3, 3, a));
    print_mat_2(3, 3, a);
*/

    if (argc < 2) {
        printf("no input\n");
        exit(1);
    }
    int m, n;
    read_array_m_n(argv[1], &m, &n);
//        printf("%d %d\n", -1, abs(-1));

    printf("# of row:%d, # of col:%d\n", m, n);
    int ineq[m][n];
    txt_2_array(argv[1], m, n, ineq);
//    print_mat_2(m, n, ineq);

    _Bool (*active_ineq)[m];
    _Bool (*active_ineq_new)[m], flag;
//    _Bool ii[2][m];
    active_ineq = (_Bool (*)[m]) malloc(n * m * sizeof(_Bool));
//    printf("%d ", sizeof(_Bool));
//    free(active_ineq);
//    active_ineq = ii;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            active_ineq[i][j] = 1;
        }
        active_ineq[i][i] = 0;
    }
//    print_mat_2_bool(n, m, active_ineq);

    int ineq_shuffle[m], jjj, ineq_temp, rank = 1;
    double ineq_copy[m][n];
    int ineq_order[m];
//    int ineq_order[] = {73,51,56,11,6,55,70,68,65,4,80,18,3,2,12,82,39,28,9,26,67,77,32,33,54,16,13,24,74,71,46,0,1,5,7,8,10,14,15,17,19,20,21,22,23,25,27,29,30,31,34,35,36,37,38,40,41,42,43,44,45,47,48,49,50,52,53,57,58,59,60,61,62,63,64,66,69,72,75,76,78,79,81,83,84};



    for (int i = 0; i < m; ++i) {
        ineq_order[i] = i;
//        ineq_shuffle[i] = m - i - 1;
        ineq_shuffle[i] = i;
    }

    for (int i = m - 1; i > 0; --i) {
        jjj = rand() * (i + 1) / (RAND_MAX + 1);
        ineq_temp = ineq_shuffle[i];
        ineq_shuffle[i] = ineq_shuffle[jjj];//好像加不了速度
        ineq_shuffle[jjj] = ineq_temp;
    }

//    print_mat_1(m, ineq_shuffle);

    int rank_new;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            ineq_copy[i][j] = (double) ineq[ineq_shuffle[i]][j];
        }
    }
//     printf("\n************************\n");
//   print_mat_2(m, n, ineq);
    ineq_order[0] = ineq_shuffle[0];
    int order_offset = n;
    for (int i = 2; i < m + 1; ++i) {
        rank_new = rank_0_1(i, n, ineq_copy);
        if (rank_new - rank) {
//            rank = rank_new;
            ineq_order[rank++] = ineq_shuffle[i - 1];
        }
//        else
//            ineq_order[order_offset++] = i-1;
        if (rank == n)
            break;
    }
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

    int (*er)[n];
    int (*er_new)[n];
    er = (int (*)[n]) malloc(n * n * sizeof(int));

    double er_double[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            er_double[i][j] = (double)0;
        }
        er_double[i][i] = (double)1;
    }

//    print_mat_2(n, n, ineq_copy);
    rank = inv_0_1(n, n, ineq_copy, er_double);
    printf("find initial basis %d %d\n", rank, n);
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
                    er[i][k] = (int) round(er_reg[k]);
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
//    printf("\n************************\n");
//    print_mat_2(n, n, er);



    int ii = n, count_ineq, ineq_reg[m];
    unsigned long long count_pos, count_zero, count_neg, len_er = n, count_new, count_er_all, count_trick_1, point_temp, jj;
//    printf("er length initial: %u\n", len_er);
//    _Bool flag;
    struct er_new_info *head, *prev, *current;
    time_t time_whole = clock(), time1;
    double offset, now;
    int value_reg, ineq_choose;

    while (ii < m) {
        //do greedy choose
        offset = 1e20;
        for (int i = ii; i < m; ++i) {
            count_pos = 0;
            count_neg = 0;
            for (unsigned long long j = 0; j < len_er; ++j) {
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


        time1 = clock();
        count_pos = 0;
        count_zero = 0;
        count_neg = 0;
        int value[len_er];
        unsigned long long sign[3][len_er], point_index[len_er];
        for (unsigned long long i = 0; i < len_er; ++i) {
            point_index[i] = i;
            value[i] = inner_produce(n, er[i], ineq[ineq_order[ii]]);
            if (value[i] > 0)
                sign[0][count_pos++] = i;
            else if (value[i] == 0)
                sign[1][count_zero++] = i;
            else
                sign[2][count_neg++] = i;
        }
//        print_mat_2_long(3, len_er, sign);

        for (unsigned long long i = len_er - 1; i > 0; --i) {
            jj = rand() * (i + 1) / (RAND_MAX + 1);
            point_temp = point_index[i];
            point_index[i] = point_index[jj];
            point_index[jj] = point_temp;
        }
//        print_mat_1_long(len_er, point_index);
        printf("%.1E %.1E %.1E \n", (double) count_pos, (double) count_zero, (double) count_neg);
        count_new = 0;
        head = NULL;
        count_trick_1 = 0;
        for (unsigned long long i = 0; i < count_pos; ++i) {
            for (unsigned long long j = 0; j < count_neg; ++j) {
                count_ineq = 0;
                for (int k = 0; k < ii; ++k) {
                    if (active_ineq[sign[0][i]][k] && active_ineq[sign[2][j]][k]) {
                        ineq_reg[count_ineq++] = k;
                    }
                }
                if (count_ineq >= n - 2) {
                    count_trick_1++;

/*
                    for (int k = 0; k < count_ineq; ++k) {
                        for (int l = 0; l < n; ++l) {
                            ineq_copy[k][l] = (double) ineq[ineq_order[ineq_reg[k]]][l];
                        }
                    }
                    if (rank_0_1(count_ineq, n, ineq_copy) == n - 2) {
*/

                    for (unsigned long long k = 0; k < len_er; ++k) {//有问题，不管了
                        if ((point_index[k] != sign[0][i]) && (point_index[k] != sign[2][j])) {//少遍历2次全，更快些
                            flag = 1;
                            for (int l = 0; l < count_ineq; ++l) {
                                if (active_ineq[point_index[k]][ineq_reg[l]] == 0) {
                                    flag = 0;
                                    break;
                                }
                            }
                            if (flag)//all 1
                                break;
                        }
                    }
                    if (flag == 0) {//果然是问题理解出了问题


                        count_new++;
                        current = (struct er_new_info *) malloc(sizeof(struct er_new_info));
                        current->pos = sign[0][i];
                        current->neg = sign[2][j];
                        current->pos_v = value[current->pos];
                        current->neg_v = value[current->neg];
                        current->next = NULL;
                        if (head == NULL)
                            head = current;
                        else
                            prev->next = current;
                        prev = current;
                    }
                }
            }
        }
        printf("time to range: %.1f\n", (clock() - time1) * 1.0 / 1000);
//        time1 = clock();
        len_er = (count_pos + count_zero + count_new);
        active_ineq_new = (_Bool (*)[m]) malloc(len_er * m * sizeof(_Bool));
        er_new = (int (*)[n]) malloc(len_er * n * sizeof(int));
        count_er_all = 0;
        for (unsigned long long i = 0; i < count_pos; ++i) {
            for (int j = 0; j < n; ++j) {
                er_new[count_er_all][j] = er[sign[0][i]][j];
            }
            for (int j = 0; j < ii; ++j) {
                active_ineq_new[count_er_all][j] = active_ineq[sign[0][i]][j];
            }
            active_ineq_new[count_er_all++][ii] = 0;
        }
        for (unsigned long long i = 0; i < count_zero; ++i) {
            for (int j = 0; j < n; ++j) {
                er_new[count_er_all][j] = er[sign[1][i]][j];
            }
            for (int j = 0; j < ii; ++j) {
                active_ineq_new[count_er_all][j] = active_ineq[sign[1][i]][j];
            }
            active_ineq_new[count_er_all++][ii] = 1;
        }

        current = head;
        while (current != NULL) {
            for (int i = 0; i < n; ++i) {
                er_new[count_er_all][i] = (er[current->neg][i]) * (current->pos_v) - (er[current->pos][i]) * (current->neg_v);
            }
//            printf("before:");
//            print_mat_1(n, er_new[count_er_all]);
            reduce_gcd(n, er_new[count_er_all]);
//            printf("after   :");
//            print_mat_1(n, er_new[count_er_all]);
            for (int k = 0; k < ii; ++k) {
                active_ineq_new[count_er_all][k] = active_ineq[current->pos][k] && active_ineq[current->neg][k];
            }
            active_ineq_new[count_er_all++][ii] = 1;
//            free(current);//放这里好像会出事
            prev = current;
            current = current->next;//保险一点先读了
            free(prev);
        }

        free(active_ineq);
        free(er);
        printf("%.1E success build\n", (double) count_new);
        printf("(%d,%d),  # of iter: %.3E, # of trick_1: %.3E, time passed: %.1f, choosen ineq: %d\n", ii + 1, m, (double) count_pos * count_neg, (double) count_trick_1, (clock() - time_whole) * 1.0 / 1000, ineq_order[ii]);
        printf("\n************************\n");
        active_ineq = active_ineq_new;
        er = er_new;

        ii++;
    }


    printf("final length %lld, time:%f", len_er, (clock() - time_whole) * 1.0 / 1000);

    file_write(len_er, n, er, argv[2]);
    return 0;
}


