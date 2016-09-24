#include <algorithm>
#include <iostream>
#include <iterator>
 
template <typename RandomAccessIterator>
void CSort(RandomAccessIterator begin, RandomAccessIterator end) {
  std::sort(begin, end);
}
 