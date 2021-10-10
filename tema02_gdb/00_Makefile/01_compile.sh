g++ -c -o vector_extension.o -g -std=c++17 -Wall -Wextra vector_extension.cpp
g++ -c -o test.o -g -std=c++17 -Wall -Wextra test.cpp
g++ -o test.out test.o vector_extension.o
