cmake_minimum_required(VERSION 3.22)
project(ex5_noamt)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex5_noamt
        Movie.cpp
        Movie.h
        print_main.cpp
        RecommenderSystem.h
        RecommenderSystem.cpp
        RecommenderSystemLoader.h
        RecommenderSystemLoader.cpp
        RSUser.cpp
        RSUser.h
        RSUsersLoader.h
        RSUsersLoader.cpp
#        test.cpp
        tests.cpp
#        test_main.cpp
#        main_shaked.cpp
#        presubmit.cpp
        )
