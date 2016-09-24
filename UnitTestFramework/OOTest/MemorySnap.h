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
#ifndef __PROFILER_MEMORY_SNAP_H__
#define __PROFILER_MEMORY_SNAP_H__
/*****************************************************************************/
/*                               C Libraries                                 */
/*****************************************************************************/
#include <cstdlib>
#include <iostream>
#ifdef WIN32
/*****************************************************************************/
/*                            WINDOWS Libraries                              */
/*****************************************************************************/
#include <crtdbg.h>


namespace OOTestNS {
    static size_t gAllocSize;
    int __cdecl MyAllocHook(
        int      ,
        void   * ,
        size_t   nSize,
        int      ,
        long     ,
        const unsigned char * ,
        int      
        )
    {
        gAllocSize += nSize;
        return(true);         // Allow the memory operation to proceed
    }
    class MemoryProfile
    {
        /* The Following Code Snippet Creates a Monoid Pattern*/
    public:
        static MemoryProfile& Instance()
        {
            if (!m_destroyed && !m_pInstance)
            {
                m_pInstance = std::unique_ptr<MemoryProfile>(new MemoryProfile());
                std::atexit(&CleanUp);
            }
            return *m_pInstance;
        }


    private:
        static std::unique_ptr<MemoryProfile> m_pInstance;
        static bool m_destroyed;
        static void CleanUp()
        {
            //delete m_pInstance;
			m_pInstance.release();
            m_pInstance = 0;
            m_destroyed = true;
        }
        /* Monoid Pattern Relevent Code Ends Here*/
    public:
        void StartMemorySnap()
        {
            gAllocSize = 0;
            m_prevalloc = _CrtSetAllocHook(MyAllocHook);
        }
        size_t StopMemorySnap()
        {
            m_prevalloc = _CrtSetAllocHook(m_prevalloc);
            return gAllocSize;
        }
    private:
        _CRT_ALLOC_HOOK m_prevalloc;

    };
    std::unique_ptr<MemoryProfile> MemoryProfile::m_pInstance = 0;
    bool MemoryProfile::m_destroyed = false;
}
#else
#define __GNU_SOURCE
#include <dlfcn.h>
static size_t gAllocSize;
#ifndef  __CYGWIN__
extern "C" void* malloc(size_t nSize)
{
    static void* (*my_malloc)(size_t) = NULL;
    if (!my_malloc)
        my_malloc = reinterpret_cast<void* (*)(size_t)>(dlsym(RTLD_NEXT, "malloc"));
    void *p = my_malloc(nSize);              
    gAllocSize += nSize;
    return p;
}
#endif
namespace OOTestNS {


    class MemoryProfile
    {
        /* The Following Code Snippet Creates a Monoid Pattern*/
    public:
        static MemoryProfile& Instance()
        {
            if (!m_destroyed && !m_pInstance)
            {
                m_pInstance = std::unique_ptr<MemoryProfile>(new MemoryProfile());
                std::atexit(&CleanUp);
            }
            return *m_pInstance;
        }


    private:
        static std::unique_ptr<MemoryProfile> m_pInstance;
        static bool m_destroyed;
        static void CleanUp()
        {
            m_pInstance.release();
            m_pInstance = 0;
            m_destroyed = true;
        }
        /* Monoid Pattern Relevent Code Ends Here*/
    public:
        void StartMemorySnap()
        {
            gAllocSize = 0;
        }
        size_t StopMemorySnap()
        {
            return gAllocSize;
        }

    };
    std::unique_ptr<MemoryProfile> MemoryProfile::m_pInstance = 0;
    bool MemoryProfile::m_destroyed = false;
}
#endif //WIN32
#endif //Include Guard
