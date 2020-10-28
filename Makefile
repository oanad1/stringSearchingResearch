CC = g++
CFLAGS = -Wall -Wextra -O2
LDLIBS = -lm

build: algo_test.o

algo.o: algo.cpp
	g++ algo.cpp algo1.cpp algo2.cpp -c $(CFLAGS)

algo_test.o: algo_test.cpp algo.o
	g++ algo_test.cpp algo.cpp algo1.cpp algo2.cpp algo3.cpp -o test $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o test
