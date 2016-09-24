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
#ifndef __UNIT_TEST__
#define __UNIT_TEST__
#include <vector>
#include "OOTest/OOtest.h"
struct TestSortSample: public OOTestNS::Pledge
{

    TestSortSample()
    {
        int a[] = {100, 2, 56, 200, -52, 3, 99, 33, 177, -199};
        std::copy(a, a + OOTestNS::countof(a), std::back_inserter(data));
    }
    virtual void Honour() = 0;
    bool IsCommitted()
    {
        return true;
    }
    std::vector<int> data;
};
struct TestSortSmall: public OOTestNS::Pledge
{

    TestSortSmall()
    {
        data.resize(100);
        std::generate(data.begin(), data.end(), std::rand);
    }
    virtual void Honour() = 0;
    bool IsCommitted()
    {
        return true;
    }
    std::vector<int> data;
};
struct TestSortLarge: public OOTestNS::Pledge
{

    TestSortLarge()
    {
        data.resize(1000);
        std::generate(data.begin(), data.end(), std::rand);
    }
    virtual void Honour() = 0;
    bool IsCommitted()
    {
        return true;
    }
    std::vector<int> data;
};
struct TestSortDesc: public OOTestNS::Pledge
{

    TestSortDesc()
    {
        data.resize(1000);
        std::generate(data.begin(), data.end(), std::rand);
        std::sort(data.begin(), data.end(), std::greater<int>());
    }
    virtual void Honour() = 0;
    bool IsCommitted()
    {
        return true;
    }
    std::vector<int> data;
};
#define GENTEST(test, func) \
struct SortTest ## test : public TestSort ## test {  \
        void Honour() {                              \
            func(data.begin(), data.end());          \
        }                                            \
    };                                               
#define GENTESTS(func)                               \
    GENTEST(Sample, func);                           \
    GENTEST(Small, func);                            \
    GENTEST(Large, func);                            \
    GENTEST(Desc, func);                               
#endif