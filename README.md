# UnitTestFramework
C++ Unit Testing Framework

## Why another Unit Testing Library?
The current implementation is an Object Oriented based Test framework. This enables to organize test cases properly, taking full support for inheritence and polymorphism. 
Moreover, the library has full support to recover from crash/exceptions/signals and records and displays in a well organized tabular form the result of execution

```
|                || BSortTest || CPPSortTest || CountSort || MSortTest || QSort |
|----------------||-----------||-------------||-----------||-----------||-------|
|  SortTestDesc  ||  CRASHED  ||    PASS     ||   PASS    ||   PASS    || PASS  |
|----------------||-----------||-------------||-----------||-----------||-------|
| SortTestLarge  ||   PASS    ||    PASS     ||   PASS    ||   PASS    || PASS  |
|----------------||-----------||-------------||-----------||-----------||-------|
| SortTestSample ||  CRASHED  ||    PASS     ||   PASS    ||   PASS    || PASS  |
|----------------||-----------||-------------||-----------||-----------||-------|
| SortTestSmall  ||   PASS    ||    PASS     ||   PASS    ||   PASS    || PASS  |
|________________||___________||_____________||___________||___________||_______|
```

Nevertheless, the library captures performance, memory and CPU utilization of each test case.

```
 __________________________________________________________________________
|                         Performance Benchmarking                         |
|__________________________________________________________________________|
______________________________________________________________________________
|                || CPPSortTest  || CountSort  ||  MSortTest  ||    QSort    |
|----------------||--------------||------------||-------------||-------------|
|  SortTestDesc  ||  0.477867ms  || 9.16708ms  ||  3.17753ms  ||  4.64725ms  |
|----------------||--------------||------------||-------------||-------------|
| SortTestLarge  ||  0.897991ms  ||  9.5798ms  ||  3.52853ms  ||  4.41429ms  |
|----------------||--------------||------------||-------------||-------------|
| SortTestSample || 0.00426667ms || 0.134258ms || 0.0355556ms || 0.0327111ms |
|----------------||--------------||------------||-------------||-------------|
| SortTestSmall  || 0.0594489ms  ||  8.1536ms  || 0.410738ms  || 0.405333ms  |
|________________||______________||____________||_____________||_____________|

 ________________________________________________________________________________
|                  Memory Benchmarking (Works with Debug Build)                  |
|________________________________________________________________________________|
_____________________________________________________________________________________
|                || BSortTest || CPPSortTest || CountSort || MSortTest ||   QSort   |
|----------------||-----------||-------------||-----------||-----------||-----------|
|  SortTestDesc  || 0.00bytes ||  0.00bytes  || 127.79KB  || 0.00bytes || 0.00bytes |
|----------------||-----------||-------------||-----------||-----------||-----------|
| SortTestLarge  || 0.00bytes ||  0.00bytes  || 127.62KB  || 0.00bytes || 0.00bytes |
|----------------||-----------||-------------||-----------||-----------||-----------|
| SortTestSample || 0.00bytes ||  0.00bytes  ||  1.57KB   || 0.00bytes || 0.00bytes |
|----------------||-----------||-------------||-----------||-----------||-----------|
| SortTestSmall  || 0.00bytes ||  0.00bytes  || 124.39KB  || 0.00bytes || 0.00bytes |
|________________||___________||_____________||___________||___________||___________|
 ______________________________________________________________________________
|                            Process Benchmarking                              |
|______________________________________________________________________________|
___________________________________________________________________________________
|                || BSortTest || CPPSortTest || CountSort || MSortTest ||  QSort  |
|----------------||-----------||-------------||-----------||-----------||---------|
|  SortTestDesc  ||  11.19MB  ||   11.22MB   ||  11.34MB  ||  11.34MB  || 11.34MB |
|----------------||-----------||-------------||-----------||-----------||---------|
| SortTestLarge  ||  11.20MB  ||   11.22MB   ||  11.34MB  ||  11.34MB  || 11.34MB |
|----------------||-----------||-------------||-----------||-----------||---------|
| SortTestSample ||  11.22MB  ||   11.22MB   ||  11.34MB  ||  11.34MB  || 11.34MB |
|----------------||-----------||-------------||-----------||-----------||---------|
| SortTestSmall  ||  11.22MB  ||   11.22MB   ||  11.34MB  ||  11.34MB  || 11.34MB |
|________________||___________||_____________||___________||___________||_________|
```

Another important aspect is, providing a quick compartion of various implementation providing a good mechanism, in case you need to compare competing algorithms and would want to choose the best optimized solution.

Other features like saving and loading last execution, running failed tests are supported out of the box.

Finally, the library has been tested to work on Windows, Darwin, HP-UX, Solaris, Linux, AIX and Cygwin


## How to use it

1. The function you would want to test, you write it within a namespace
```
namespace CPPSortTest {
    template <typename RandomAccessIterator>
    void CPPSort(RandomAccessIterator begin, RandomAccessIterator end) {
        std::sort(begin, end);
    }

    ## <TO-DO Unit Test>
}
```

2. You then take a pledge by inherting from `public OOTestNS::Pledge` and replacing the <TO-DO Unit Test> with the unit test

```
struct TestSortSample: public OOTestNS::Pledge
{

	TestSortSample() {}
    virtual void Honour() {
		CPPSort(data.begin(), data.end());
	}
    bool IsCommitted()
    {
		std::array<int, 10> sorted_data{ -199, -52, 2, 3, 33, 56, 99, 100, 177, 200 };
        return data == sorted_data;
    }
	std::array<int, 10> data{ 100, 2, 56, 200, -52, 3, 99, 33, 177, -199 };
};
```
Things to note
    1. Any initialization goes in the constructor `TestSortSample`
	2. Call to the routine to be tested goes in `Honor`. Any code that is within `Honor` is tested, so be careful what goes where
	3. IsCommitted checks if the test meets the success criteria. 
	
3. Finally, invoke your unit tests aspect
```
BEGIN_TEST("test_cases.csv")    
    ADD_TEST(CPPSortTest, SortTestSample);
END_TEST(ALL, FORMATTED, std::cout)
```


**Note** Refer `Source.cpp` to understand the full capabilities of the library