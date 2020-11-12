#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cctype>
#include <utility>

void error(const std::string& msg)
{
    std::cerr << "Error: " << msg << "!" << std::endl;
    exit(EXIT_FAILURE);
}

#define STOP 0
#define FMUL 1
#define FSUM 2
#define BOPEN 3
#define BCLOSE 4
#define COMMA 5
#define NUM 6

class Parser{
public:
    Parser(const std::string& file_name, int modul = 1000)
        : m_input(file_name), m_modul(modul)
        {}

    int calculate()
    {
        int token_id = next();
        if(token_id == FMUL)
            return fmul();
        if(token_id == FSUM)
            return fsum();
        if(token_id == NUM)
            return m_value;

        fail();
        return 0;
    }
private:
    inline void fail() const
    {
        error("Failed to parse");
    }

    int exp()
    {
        // Greska 1: U svakom if-u se poziva f-ja next() i tako
        // se ucitava sledeci token za svaki. Potrebno je da se 
        // ucita sledeci token, pa tek onda da se vrsi provera
        /*
            if(next() == NUM)
                return m_value;
            if(next() == FSUM)
                return fsum();
            if(next() == FMUL)
                return fmul();
        */
        int n = next();
        if(n == NUM)
            return m_value;
        if(n == FSUM)
            return fsum();
        if(n == FMUL)
            return fmul();

        fail();
        return 0;
    }

    std::pair<int, int> args()
    {
        if(next() != BOPEN)
            fail();
        int lhs = exp();
        if(next() != COMMA)
            fail();
        int rhs = exp();
        if(next() != BCLOSE)
            fail();
        return {lhs, rhs};
    }

    int fmul()
    {
        auto[lhs, rhs] = args();
        return (lhs * rhs) % m_modul;
    }

    int fsum()
    {
        auto[lhs, rhs] = args();
        return (lhs + rhs) % m_modul;
    }

    int next()
    {
        char c;
        if(!m_input.get(c))
            return STOP;
        c = tolower(c);
        switch (c)
        {
        case ' ':
        case '\n':
        case '\t':
            return next();
        case 'm':
            if(m_state == 2)
            {
                m_state = 0;
                return FSUM;
            }
            // Greska 2: Ne vrsi se provera za nulto stanje
            // i upada se u case 's'. Ova greska omogucava
            // da sa "SUL(2, 3)" parsira kao "MUL(2, 3)" i
            // nije toliko nezgodna u smislu da ce program
            // da radi u vecini slucajeva
            if(m_state == 0)
            {
                m_state++;
                return next();
            }
            fail();
        case 's':
            if(m_state != 0)
                fail();
            m_state++;
            return next();
        case 'u':
            if(m_state != 1)
                fail();
            m_state++;
            return next();
        // Greska 3: 'L' umesto 'l', gde je c malo slovo (ako je slovo)
        case 'l':
            if(m_state != 2)
                fail();
            m_state = 0;
            return FMUL;
        case '(':
            return BOPEN;
        case ')':
            return BCLOSE;
        case ',':
            return COMMA;
        case EOF:
            return STOP;
        default:
            if(isdigit(c))
            {
                std::string num;
                while(isdigit(c))
                {
                    // Greska 4: Pogresan redosled komandi, zbog cega se prva
                    // cifra uvek preskoci.
                    num.push_back(c);
                    if(!m_input.get(c))
                        fail();
                }
                m_input.unget();
                m_value = atoi(num.c_str());
                return NUM;
            }
            fail();
        }

        return 0;
    }

    std::ifstream m_input;
    const int m_modul;
    int m_state = 0;
    int m_value = 0;
};

int main(int argc, char** argv)
{
    if(argc < 2)
        error("Wrong number of arguments");
    std::string file_name(argv[1]);
    Parser parser(file_name);
    std::cout << parser.calculate() << std::endl;
    return 0;
}