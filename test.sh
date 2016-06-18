#!/bin/bash

function build_gtest {
    mkdir -p temp
    pushd temp
    cmake ../external/googletest/googletest/
    make -j4
    popd
}

function build_tests {
    g++ tests/*.cc -o temp/tests -Ltemp -Iinclude -Iexternal/googletest/googletest/include -lgtest_main -lgtest -pthread
}

function run_tests {
    temp/tests
}

build_gtest
build_tests
run_tests
