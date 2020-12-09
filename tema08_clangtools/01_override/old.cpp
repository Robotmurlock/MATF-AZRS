struct Base {
    virtual void reimplementMe(int a) {}
};
struct Derived : public Base  {
    void reimplementMe(int a) {}
};

int main()
{
    Base* object = new Derived;
    return 0;
}
