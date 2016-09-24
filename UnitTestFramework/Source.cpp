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
//#include <crtdbg.h>
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
