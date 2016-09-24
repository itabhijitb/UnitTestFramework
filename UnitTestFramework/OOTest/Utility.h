/*****************************************************************************/
/*                        WINDOWS/POSIX Libraries                            */
/*****************************************************************************/
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif
/*****************************************************************************/
/*                              STL Libraries                                */
/*****************************************************************************/
#include <vector>
#include <sstream>
#include <string>
/*****************************************************************************/
/*                               C Libraries                                 */
/*****************************************************************************/
#include <cstdlib>

#ifndef __UTILITY_H__
#define __UTILITY_H__
namespace OOTestNS {
    namespace Utility {
        std::vector<std::string> split(const std::string &st, const std::string &delims) {
            //std::stringstream ss(st);
            //std::string item;
            std::vector<std::string> result;
            for (size_t start = 0, end = st.find_first_of(delims);
                end != std::string::npos;
                start = end + 1, end = st.find_first_of(delims, start))
            {
                result.push_back(st.substr(start, end - start));
            }
            return result;
        }
    }
    template < typename T, size_t N >
    size_t countof( T ( & arr )[ N ] )
    {
        return std::extent< T[ N ] >::value;
    }
}
bool SandBox(void *(*fn)(void *), void *arg, void *rc)
{
#ifdef WIN32
    __try
    {
        if (rc)
            rc = fn(arg);
        else
            fn(arg);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }

#else
	int child_pid = fork();
    int status;
    if (child_pid)
    {
        int wait_pid = waitpid(child_pid, &status, 0);
        if (wait_pid == -1) 
        {
            return false;
        }
        if (WIFEXITED(status))
        {
            if (rc)
                rc = fn(arg);
            else
                fn(arg);
            return true;
        } 
        else 
        {
            return false;
        }

    }
    else
    {
        if (rc)
            rc = fn(arg);
        else
            fn(arg);
        std::exit(0);

    }
    return true;
#endif

}
std::string DecoratedNametoSpaceSep(std::string name)
{
    std::string dest;
    for (std::string::const_iterator it = name.begin();
        it != name.end();
        ++it)
    {
        if (isupper(*it) || *it == '_')
        {
            if (dest != "")
            {
                dest += std::string(" ");
            }
            if (*it != '_')
            {
                dest += tolower(*it);
            }
        }
    }
    return dest;
}
#endif
