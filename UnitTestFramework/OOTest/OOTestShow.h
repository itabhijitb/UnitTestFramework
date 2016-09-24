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
/*****************************************************************************/
/*                              CRT Libraries                                */
/*****************************************************************************/
/*****************************************************************************/
/*                              STL Libraries                                */
/*****************************************************************************/
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <string>
#include <iomanip>
#include <set>
/*****************************************************************************/
/*                               C Libraries                                 */
/*****************************************************************************/
#include <cstdlib>
/*****************************************************************************/
/*                            WINDOWS Libraries                              */
/*****************************************************************************/
/*****************************************************************************/
/*                            PROJECT Libraries                              */
/*****************************************************************************/
#include "ptable.h"
#include "OOTestException.h"
#include "Timer.h"
#include "MemorySnap.h"
#include "Process.h"
#include "Utility.h"
#ifndef __PROFILER_SHOW_H__
#define __PROFILER_SHOW_H__
namespace OOTestNS {
	/*************************************************************************/
	/*                       Forward Declaratios                             */
	/*************************************************************************/
	struct IActor;
	template<typename U> class Actor;
	class Stage;
	class ScreenPlay;
	/*************************************************************************/
	/*                             Typedefs                                  */
	/*************************************************************************/
	typedef std::map<std::string, std::map<std::string, std::string> > TyResult;
	typedef std::map<std::string, std::unique_ptr<ScreenPlay > > TyPlay;
	/*
	Cutter: Every great magic trick consists of three parts or acts.
	The first part is called "The Pledge". The magician shows you something
	ordinary: a deck of cards, a bird or a man. He shows you this object.
	Perhaps he asks you to inspect it to see if it is indeed real,
	unaltered, normal. But of course... it probably isn't. The second act
	is called "The Turn". The magician takes the ordinary something and
	makes it do something extraordinary. Now you're looking for the
	secret... but you won't find it, because of course you're not really
	looking. You don't really want to know. You want to be fooled. But you
	wouldn't clap yet. Because making something disappear isn't enough; you
	have to bring it back. That's why every magic trick has a third act,
	the hardest part, the part we call "The Prestige"."
	*/
	struct IPledge
	{
		IPledge(){};
		virtual void Honour() = 0;
		virtual bool IsCommitted() = 0;
		virtual ~IPledge() {};
	};


	struct Pledge : public IPledge
	{
		friend struct IActor;
		template<typename U> friend class Actor;
		enum AssertCandidate {MEMORY, CPU, TEST, PROCESS};
		enum AssertType {LE, GE, LT, GT, EQ};
		template<AssertCandidate candidate, AssertType type >	bool Assert(double threshold) {}
		struct IResult
		{
			static const int fields_count = 4;
			enum Commitment { Committed, Uncommitted, Foresaken, Hoozah };
		};
	private:
		struct Result : public IResult
		{
			Commitment  m_committed;
			double m_executionTime;
			double m_memoryUse;
            size_t m_peakworkingsetsize;
			Result() : m_committed(Committed), m_executionTime(0.0), m_memoryUse(0), m_peakworkingsetsize(0) {};
		};
		static void* Honour_Helper(void *context)
		{
			(static_cast<Pledge *>(context))->Honour();
			return NULL;
		}
		Result m_result;
	};
	template <> bool Pledge::Assert<Pledge::MEMORY, Pledge::LE>(double threshold)  { return m_result.m_memoryUse <= threshold; };
	template <> bool Pledge::Assert<Pledge::MEMORY, Pledge::LT>(double threshold)  { return m_result.m_memoryUse < threshold; };
	template <> bool Pledge::Assert<Pledge::MEMORY, Pledge::GE>(double threshold)  { return m_result.m_memoryUse >= threshold; };
	template <> bool Pledge::Assert<Pledge::MEMORY, Pledge::GT>(double threshold)  { return m_result.m_memoryUse > threshold; };
	template <> bool Pledge::Assert<Pledge::MEMORY, Pledge::EQ>(double threshold)  { return m_result.m_memoryUse == threshold; };
	template <> bool Pledge::Assert<Pledge::CPU, Pledge::LE>(double threshold)  { return m_result.m_executionTime <= threshold; };
	template <> bool Pledge::Assert<Pledge::CPU, Pledge::LT>(double threshold)  { return m_result.m_executionTime < threshold; };
	template <> bool Pledge::Assert<Pledge::CPU, Pledge::GE>(double threshold)  { return m_result.m_executionTime >= threshold; };
	template <> bool Pledge::Assert<Pledge::CPU, Pledge::GT>(double threshold)  { return m_result.m_executionTime > threshold; };
	template <> bool Pledge::Assert<Pledge::CPU, Pledge::EQ>(double threshold)  { return m_result.m_executionTime == threshold; };
	struct IActor
	{

		virtual void Turn(bool skip = false) = 0;
		virtual Pledge::Result& Prestige() = 0;
		virtual ~IActor() = 0;
	};
	IActor::~IActor() {};
	template <typename Ty>
	class Actor : public IActor
	{
	private:
		std::unique_ptr<Pledge> m_pPledge;

	public:
		Actor() :m_pPledge(new Ty()) { }//"The Pledge"
		void Turn(bool skip = false)   //"The Turn"
		{
			if (skip == true)
			{
				m_pPledge->m_result.m_committed = Pledge::Result::Foresaken;
				return;
			}
			if (m_pPledge == NULL)
			{
				throw ProfilerException("You cannot take a turn without a pledge.");
			}
			Timer timer;
			MemoryProfile::Instance().StartMemorySnap();
			if (!SandBox(m_pPledge->Honour_Helper, m_pPledge.get(), NULL))
			{
				m_pPledge->m_result.m_committed = Pledge::Result::Hoozah;
			}
			m_pPledge->m_result.m_memoryUse = static_cast<double>(MemoryProfile::Instance().StopMemorySnap());
			m_pPledge->m_result.m_executionTime = timer.End();
            m_pPledge->m_result.m_peakworkingsetsize = getPeakRSS();
		}
		Pledge::Result& Prestige()             // "The Prestige"
		{
			if (m_pPledge->m_result.m_committed == Pledge::Result::Committed)
			{
				m_pPledge->m_result.m_committed = m_pPledge->IsCommitted() ? Pledge::Result::Committed : Pledge::Result::Uncommitted;
			}
			return m_pPledge->m_result;
		}
		~Actor()
		{
			//delete m_pPledge;
		}
	};

	class ScreenPlay
	{
	public:
        typedef std::map<std::string, std::unique_ptr<IActor > > TyActors;
		typedef std::set<std::string> TySkipList;
	private:
		std::stringstream &m_console;
		TyActors m_actors;
		TySkipList m_skiplist;
	public:
		ScreenPlay(std::stringstream& console) :m_console(console) {}
		const TyActors& Actors()  { return m_actors; }
		template<typename Ty>
		void Pledge(const std::string& name)
		{
			m_actors[name] = std::unique_ptr<OOTestNS::Actor<Ty> > (new OOTestNS::Actor<Ty>());
		}
		template<typename Ty, int size>
		ScreenPlay& SkipActors(){}
		template<typename Ty>
		ScreenPlay& SkipActors(const std::string& actor)
		{
			m_skiplist.insert(actor);
			return *this;

		}
		template<typename Ty>
		ScreenPlay& SkipActors(const std::vector<std::string>& actors)
		{
			for (std::vector<std::string>::const_iterator it = actors.begin();
				it != actors.end();
				it++)
			{
				m_skiplist.insert(*it);
			}
			return *this;
		}
		template<typename Iter>
		ScreenPlay& SkipActors(Iter begin, Iter end)
		{
			for (Iter it = begin;
				it != end;
				it++)
			{
				m_skiplist.insert(*it);
			}
			return *this;
		}
		template<int size>
		ScreenPlay& SkipActors(const std::string(&actors)[size])
		{
			for (int i = 0; i < size; i++)
			{
				m_skiplist.insert(actors[i]);
			}
			return *this;
		}
		void Perform()
		{
			for (std::map<std::string, std::unique_ptr<IActor > >::iterator it = m_actors.begin();
				it != m_actors.end();
				it++)
			{
				m_console << std::string(80, '-') << std::endl;
				m_console << "Test Name: " << it->first  << std::endl;
				m_console << std::string(80, '-') << std::endl;
				it->second->Turn(m_skiplist.count(it->first) > 0);
			}

		}
		~ScreenPlay()
		{
		}
		// Getters
		const TyActors& Actors() const
		{
			return m_actors;
		}
		const TySkipList& SkipList() const
		{
			return m_skiplist;
		}

	};

	class Stage
	{
		friend std::ostream& operator<<(std::ostream& os, const Stage& stage);
	public:


	private:
		TyPlay m_play;
		std::map<std::string, std::map<std::string, std::string> > m_lastPlay;
		std::stringstream &m_console;
	public:
		Stage(std::stringstream& console):m_console(console){};
		Stage(std::string last_result, std::stringstream& console):m_console(console)
		{
			std::vector<std::string> rows = OOTestNS::Utility::split(last_result, "\n");
			for (std::vector<std::string>::const_iterator it = rows.begin();
				it != rows.end();
				it++)
			{
				std::vector<std::string> elems = OOTestNS::Utility::split(*it, ",");
				if (elems.size() != Pledge::IResult::fields_count + 2)
				{
					throw ProfilerException("Invalid Result data");
				}
				m_lastPlay[elems[0]][elems[1]] = elems[2];

			}
		}
		ScreenPlay& operator[](const std::string& name)
		{
			if (m_play.count(name) == 0)
			{
				m_play.insert(std::make_pair(name, std::unique_ptr<ScreenPlay>(new ScreenPlay(m_console))));
			}
			return *m_play.find(name)->second;
		}
		enum Performance {ALL, FAILED, SKIPPED, SUCCESS, CRASHED};
		void Perform(Performance type = ALL)
		{
			for (std::map<std::string, std::unique_ptr<ScreenPlay>>::iterator it = m_play.begin();
				it != m_play.end();
				it++)
			{
				std::vector<std::string> skipList;
				m_console << std::string(80, '=') << std::endl;
				m_console << "Test Group: " << it->first <<std::endl;
				m_console << std::string(80, '=') << std::endl;
				if (m_lastPlay.count(it->first) > 0)
				{
					for (std::map<std::string, std::string>::const_iterator it_actor = m_lastPlay[it->first].begin();
						it_actor != m_lastPlay[it->first].end();
						it_actor++)
						switch (type)
					{
						case CRASHED:
							{
								if (std::atoi(it_actor->second.c_str()) != Pledge::IResult::Hoozah)
								{
									skipList.push_back(it_actor->first);
								}
								break;
							}
						case FAILED:
							{
								if (std::atoi(it_actor->second.c_str()) != Pledge::IResult::Uncommitted)
								{
									skipList.push_back(it_actor->first);
								}
								break;
							}
						case SKIPPED:
							{
								if (std::atoi(it_actor->second.c_str()) != Pledge::IResult::Foresaken)
								{
									skipList.push_back(it_actor->first);
								}
								break;
							}
						case SUCCESS:
							{
								if (std::atoi(it_actor->second.c_str()) != Pledge::IResult::Committed)
								{
									skipList.push_back(it_actor->first);
								}
								break;
							}
						default: break;
					}
					it->second->SkipActors<std::vector<std::string> >(skipList);
				}
				it->second->Perform();
			}

		}

		const TyPlay& Play() const
		{
			return m_play;
		}


	};



}

#endif
