#ifndef __PROFILER_EXCEPTION_H__
#define __PROFILER_EXCEPTION_H__
/*****************************************************************************/
/*                              STL Libraries                                */
/*****************************************************************************/
#include <exception>

namespace OOTestNS
{
	class ProfilerException : public std::exception
	{
	public:
		ProfilerException(std::string msg) :m_msg(msg) {}
		~ProfilerException() noexcept {}
	private:
		std::string m_msg;
	};
}
#endif
