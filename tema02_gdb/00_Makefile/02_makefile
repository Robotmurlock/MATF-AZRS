test.out: test.o vector_extension.o
	g++ -o test.out test.o vector_extension.o

test.o: test.cpp
	g++ -c -o test.o -g -std=c++17 -Wall -Wextra test.cpp

vector_extension.o: vector_extension.cpp vector_extension.hpp
	g++ -c -o vector_extension.o -g -std=c++17 -Wall -Wextra vector_extension.cpp

