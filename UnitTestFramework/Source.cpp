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
//#include <crtdbg.h>
#include "OOTest/OOtest.h"
#include "BubbleSort.h"
#include "CPPSort.h"
#include "MergeSort.h"
#include "QSort.h"
#include "CountSort.h"
#include <map>
#include <vector>
#include <memory>
#include <string>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main() {
    //_CrtSetBreakAlloc(1056);
    BEGIN_TEST("test_cases.csv")    
    ADD_TEST(CPPSortTest, SortTestSample);
    ADD_TEST(CPPSortTest, SortTestLarge);
    ADD_TEST(CPPSortTest, SortTestSmall);
    ADD_TEST(CPPSortTest, SortTestDesc);
    ADD_TEST(BSortTest, SortTestSample);
    ADD_TEST(BSortTest, SortTestLarge);
    ADD_TEST(BSortTest, SortTestSmall);
    ADD_TEST(BSortTest, SortTestDesc);
    ADD_TEST(MSortTest, SortTestSample);
    ADD_TEST(MSortTest, SortTestLarge);
    ADD_TEST(MSortTest, SortTestSmall);
    ADD_TEST(MSortTest, SortTestDesc);
    ADD_TEST(QSort, SortTestSample);
    ADD_TEST(QSort, SortTestLarge);
    ADD_TEST(QSort, SortTestSmall);
    ADD_TEST(QSort, SortTestDesc);
    ADD_TEST(CountSort, SortTestSample);
    ADD_TEST(CountSort, SortTestSmall);
    ADD_TEST(CountSort, SortTestLarge);
    ADD_TEST(CountSort, SortTestDesc);
    END_TEST(ALL, FORMATTED, std::cout)
    //_CrtDumpMemoryLeaks();
}
