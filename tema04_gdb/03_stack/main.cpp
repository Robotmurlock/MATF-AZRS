void A();
void B();
void C() {}
void D();
void E() {}
void F();
void G() {}

void F(){
    D();
}
void D() {
    G();
}
void B(){
    C();
    D();
}
void A(){
    B();
    E();
    F();
}
int main(){
    A();
    return 0;
}