#include <algorithm>
#include <iostream>
#include <iterator>
#include "UnitTest.h"
namespace CPPSortTest {
    template <typename RandomAccessIterator>
    void CPPSort(RandomAccessIterator begin, RandomAccessIterator end) {
        std::sort(begin, end);
    }

    GENTESTS(CPPSort);
}