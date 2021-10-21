#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <cstdio>

// Apstraktna klasa jednog procesa koji se vrsi nad ucitanim podacima
class Process{
public:
    Process(std::vector<float>* data)
        : m_data(data) {}
    virtual void process() = 0; 
protected:
    std::vector<float>* m_data;
};

// Apstraktna klasa za "Sliding window"
// Primer: Prozor(gsize) je dimenzije 3, a koristi se agregator za sumu(AggregatorSum)
// 1 2 3 4 5
// 6 9 12
// Objasnjenje: 
// ! 6 = (1 + 2 + 3)
// ! 9 = (2 + 3 + 4)
// ! 12 = (3 + 4 + 5)

class Aggregator : public Process{
public:
    Aggregator(std::vector<float>* data, int gsize)
        : Process(data), m_gsize(gsize) {}
    virtual void process() {
        std::vector<float> new_data = std::vector<float>();
        for(int i=0; i+m_gsize<m_data->size(); i++)
            new_data.push_back(group_agg(i));
        delete m_data;
        m_data = &new_data;
    }
protected:
    virtual float group_agg(int index) = 0;
    int m_gsize;
};

class AggregatorSum : public Aggregator{
public:
    AggregatorSum(std::vector<float>* data, int gsize)
        : Aggregator(data, gsize)
    {}
private:
    virtual float group_agg(int index)
    {
        int result = 0;
        for(int i=index; i<index+m_gsize; i++)
            result += m_data->at(i);
        return result;
    }
};

class AggregatorMean : public Aggregator{
public:
    AggregatorMean(std::vector<float>* data, int gsize)
        : Aggregator(data, gsize)
    {}
private:
    virtual float group_agg(int index)
    {
        int result = 0;
        for(int i=index; i<index+m_gsize; i++)
            result += m_data->at(i) / m_gsize;
        return result;
    }
};

// Ucitava vektor iz datoteke
std::vector<float> load(const std::string& filename)
{
    std::ifstream input(filename);
    if(input.fail())
    {
        std::cout << "Failed to load vector from file :(" << std::endl;
        exit(1);
    }
    std::vector<float> result;
    float value;
    while(input >> value)
        result.push_back(value);
    return result;
}

// Sortira sve podatke
class Sorter : public Process{
public:
    Sorter(std::vector<float>* data)
        : Process(data)
    {}
    virtual void process()
    {
        *m_data = sorted(*m_data);
    }
private:
    std::vector<float> sorted(std::vector<float> data)
    {
        if(data.size() <= 1)
            return data;
        auto[data_left, data_right] = split(data);
        data_left  = sorted(data_left);
        data_right = sorted(data_right);
        return merge(data_left, data_right);
    }
    std::pair<std::vector<float>, std::vector<float> > split(std::vector<float> data)
    {
        int half_size = data.size() / 2;
        const std::vector<float>::iterator start  = data.begin();
        const std::vector<float>::iterator middle = data.begin() + half_size;
        const std::vector<float>::iterator end    = data.end();
        
        std::vector<float> left(start, middle);
        std::vector<float> right(middle, end);

        return {left, right};
    }
    std::vector<float> merge(std::vector<float> left, std::vector<float> right)
    {
        std::vector<float> result;
        std::vector<float>::iterator left_it = left.begin();
        std::vector<float>::iterator right_it = right.begin();

        while(left_it != left.end() && right_it != right.end())
        {
            if(*left_it < *right_it)
            {
                result.push_back(*left_it);
                left_it++;
            }
            else
            {
                result.push_back(*right_it);
                right_it++;
            }
        }
        while(left_it != left.end())
        {
            result.push_back(*left_it);
            left_it++;
        }
        while(right_it != right.end())
        {
            result.push_back(*right_it);
            right_it++;
        }

        return result;
    }
};

int main()
{
    std::vector<float> data = load(std::string("input.txt"));
    // Objasnjenje: (data_x su verzije, ne prave se novi vektori)
    // Prvo se agregira svakih uzastopnih 5 brojeva iz ucitanog vektora(data) 
    //     u sumu (dobija se novi vektor(data_1))
    // Onda se agregiraju svaka 3 broja iz prethodnog vektora(data_1) 
    //     u ar. sredinu (dobija se novi vektor(data_2)) 
    // Onda se sortira prethodni vektor(data_2) i dobija se novi vektor(data_final)
    std::vector<Process*> pipeline = {
        new AggregatorSum(&data, 5),
        new AggregatorMean(&data, 3),
        new Sorter(&data)
    };
    for(Process* p: pipeline)
        p->process();

    for(float value: data)
        std::cout << value << " ";
    std::cout << std::endl;

    return 0;
}
