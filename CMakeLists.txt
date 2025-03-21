cmake_minimum_required(VERSION 3.30)
project(DoublyLinkedList)

set(CMAKE_CXX_STANDARD 20)

add_library(DoublyLinkedList STATIC
        src/main.cpp
        include/DoublyLinkedList.h
)

add_executable(DLLExe
    src/main.cpp
)

