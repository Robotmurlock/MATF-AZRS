#ifndef __HELLO__
#define __HELLO__

class Hello {
public:
    Hello(int val)
        : m_val(val)
        {}
    void hey() const;
private:
    int m_val;
};

#endif