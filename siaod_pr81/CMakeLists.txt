cmake_minimum_required(VERSION 3.29)
project(siaod_pr81)

set(CMAKE_CXX_STANDARD 20)

add_executable(siaod_pr81
        1/main1.cpp
        2/main2.cpp
        main.cpp
        1/main1.h
        2/main2.h
        1/Fano1.h
        2/Fano2.h
        2/Huffman.h
)

target_sources(siaod_pr81 PRIVATE
        1/LZ77.cpp
        1/LZ78.cpp
        1/Fano.cpp
        2/Fano2.cpp
        2/Huffman.cpp
)
