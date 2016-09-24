/*****************************************************************************
*  Copyright{ 2016 } {Abhijit Bhattacharjee(itabhijitb@gmail.com)}           *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
******************************************************************************/
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
                for (auto j = 0; j < count[i - min]; ++j) {
                    *begin++ = i;
                }
            }
    }
    GENTESTS(counting_sort);
}