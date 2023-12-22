cmake_minimum_required(VERSION 3.20)
project(c_dd_mine C)

set(CMAKE_C_STANDARD 99)

#add_executable(c_dd_mine main.c)
#add_executable(c main.c)

#add_executable(greedy main_no_active_point.c)
#add_executable(greedy_r main_no_active_point.c)
#add_executable(lex lexmin.c)
#add_executable(l  lexmin.c)
#add_executable(l inter_initial_basis.c)
#add_executable(g inter_initial_basis.c)
#add_executable(r test_rank_fuck.c)
#add_executable(rr random_initial.c)

#add_executable(r multi_practice_1.c)
#add_executable(r multi_practice_mutex.c)

#add_executable(r random_initial.c)
#add_executable(r multi_mutex.c)


#add_executable(r rank_only.c)
#add_executable(r rank_only_NC2.c)
#add_executable(r rank_only_NC2_r_pos.c)

#add_executable(r teset_argv.c)

#add_executable(r trun.c)
#add_executable(r array_in.c)
add_executable(r array_in_multi.c)
#target_link_libraries(r Threads::Threads)
#target_link_libraries(r winmm.lib)#呵呵播放用

#add_executable(r tell_me_array_dim.c)
#add_executable(tell tell_me_array_dim.c)



MATH(EXPR stack_size "30 * 1024 * 1024 * 1024") #  30GB
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

find_package(Threads REQUIRED)
