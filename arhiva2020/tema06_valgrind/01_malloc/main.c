#include <stdlib.h>

int main() {
    char* string = malloc(5 * sizeof(char)); //LEAK: not freed!
    return 0;
}