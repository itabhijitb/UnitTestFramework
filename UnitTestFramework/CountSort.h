#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include "UnitTest.h"
namespace CountSort
{
    template<typename ForwardIterator> void counting_sort(ForwardIterator begin,
        ForwardIterator end) {
            auto min_max = std::minmax_element(begin, end);
            if (min_max.first == min_max.second) {  // empty range
                return;
            }
            auto min = *min_max.first;
            auto max = *min_max.second;
            std::vector<size_t> count((max - min) + 1, 0u);
            for (auto i = begin; i != end; ++i) {
                ++count[*i - min];
            }
            for (auto i = min; i <= max; ++i) {
                for (auto j = 0U; j < count[i - min]; ++j) {
                    *begin++ = i;
                }
            }
    }
    GENTESTS(counting_sort);
}