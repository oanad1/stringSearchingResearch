#!/bin/bash

NR_TESTS=20
NR_ROT_TESTS=5
NR_PS_TESTS=5

make

for((i=1; i<=NR_TESTS; i++)) do
    ./test "test"$i
done

for((i=1; i<=NR_ROT_TESTS; i++)) do
    ./test "rotation_test"$i
done

for((i=1; i<=NR_PS_TESTS; i++)) do
    ./test "suffix_test"$i
done
make clean
