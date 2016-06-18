#!/bin/bash

function build_gtest {
    mkdir -p temp
    pushd temp
    cmake ../external/googletest/googletest/
    make -j4
    popd
}

function build_lib {
	g++ src/*.cc -o temp/libcpputils.so -shared -fPIC -Iinclude -std=c++14 -lstdc++fs
}

function build_tests {
    g++ tests/*.cc -o temp/tests -Ltemp -Iinclude -Iexternal/googletest/googletest/include -lgtest_main -lgtest -lcpputils -pthread -std=c++14
}

function run_tests {
    LD_LIBRARY_PATH=temp ./temp/tests
}

build_lib
build_gtest
build_tests
run_tests
