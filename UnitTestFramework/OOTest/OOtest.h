#include "OOTestShow.h"
#include "Result.h"
#include <fstream>
#ifndef __PROFILER_PROFILER_H
#define __PROFILER_PROFILER_H
#define BEGIN_TEST(fname)                                                               \
struct UnitTest : public OOTest {                                                       \
		UnitTest() : OOTest(fname)  {                                                         
#define END_TEST(what, type, strm)                                                      \
		Test().Perform(Test().what);                                                    \
		strm << OOTestNS::Result::Format<OOTestNS::Result::type>(Test());               \
		strm << std::endl;                                                              \
	}                                                                                   \
};                                                                                      \
UnitTest();
#define END_TEST_LOG(what, type, strm, log)                                             \
		Test().Perform(Test().what);                                                    \
	    log << LOG().str();                                                             \
		strm << OOTestNS::Result::Format<OOTestNS::Result::type>(Test());               \
		strm << std::endl;                                                              \
	}                                                                                   \
};                                                                                      \
UnitTest();


#define ADD_TEST(GRP, NAME) Test()[#GRP].Pledge<GRP::NAME>(#NAME)

class OOTest 
{
	OOTestNS::Stage m_stage;
	static std::stringstream m_console;
	std::string m_fname;
	std::string FetchData(const std::string& fname)
	{
		std::ifstream fin(fname.c_str());
		std::string data;
		if (fin)
		{
			data = std::string((std::istreambuf_iterator<char>(fin)),
				std::istreambuf_iterator<char>());
		}
		return data;
	}
public:
	OOTest():m_stage(m_console){}
	OOTest(const std::string& fname) 
		: m_fname(fname), m_stage(FetchData(fname), m_console){}
	OOTestNS::Stage& Test() { return m_stage;  }
	static std::stringstream& LOG()
	{
		return m_console;
	}
	virtual ~OOTest()
	{
		if (m_fname.size())
		{
			std::ofstream fout(m_fname.c_str());
			if (fout)
			{
				std::string data = OOTestNS::Result::Format<OOTestNS::Result::CSV>(m_stage);
				fout.write(data.c_str(), data.size());
			}
		}
	}
};
std::stringstream OOTest::m_console;
#endif
