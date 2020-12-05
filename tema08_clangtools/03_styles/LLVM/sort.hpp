#ifndef __SORTY__
#define __SORTY__

#include <functional>
#include <vector>

class AbstractSort {
public:
  AbstractSort(std::function<bool(int, int)> cmp) : m_cmp(cmp) {}
  virtual ~AbstractSort() = default;
  virtual void sort(std::vector<int> &vec) = 0;

protected:
  std::function<bool(int, int)> m_cmp;
};

class SelectionSort : public AbstractSort {
public:
  SelectionSort(std::function<bool(int, int)> cmp) : AbstractSort(cmp) {}
  void sort(std::vector<int> &vec);
};

class QuickSort : public AbstractSort {
public:
  QuickSort(std::function<bool(int, int)> cmp) : AbstractSort(cmp) {}
  void sort(std::vector<int> &vec);
};

#endif // __SORTY__
