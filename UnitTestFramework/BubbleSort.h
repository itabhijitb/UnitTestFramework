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
#include <iostream>
#include <iterator>
#include "UnitTest.h"
namespace BSortTest {
    template <typename RandomAccessIterator>
    void bubble_sort(RandomAccessIterator begin, RandomAccessIterator end) {
        bool swapped = true;
        while (begin != end-- && swapped) {
            swapped = false;
            for (auto i = begin; i != end; ++i) {
                if (*(i + 1) < *i) {
                    std::iter_swap(i, i + 1);
                    swapped = true;
                }
            }
        }
    }
    GENTESTS(bubble_sort);
}