#include <stdio.h>

int global_value = 0;

void f() {
    for(int i=0; i<1000; i++)
        global_value++;
}

void g() {
    for(int i=0; i<2000; i++)
        global_value++;
}

void a() {
    f();
}

void b() {
    f(); f();
}

void c() {
    f(); g();
}

int main() {
    a(); a(); a(); b(); a(); c();
    return 0;
}