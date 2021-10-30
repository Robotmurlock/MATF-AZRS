struct Base {
    virtual void reimplementMe(int a) {}
};
struct Derived : public Base  {
    void reimplementMe(int a) override {}
};

auto main() -> int
{
    Base* object = new Derived;
    object->reimplementMe(1);
    delete object;
    return 0;
}
