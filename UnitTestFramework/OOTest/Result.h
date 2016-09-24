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
/*                              STL Libraries                                */
/*****************************************************************************/
#include <string>
#include <sstream>
/*****************************************************************************/
/*                            PROJECT Libraries                              */
/*****************************************************************************/
#include "OOTestShow.h"
//#include "c11_type_traits.h"


#ifndef __PROFILER_RESULT_H__
#define __PROFILER_RESULT_H__
namespace OOTestNS {
	namespace Result {
		struct XML {};
		struct CSV {};
		struct FORMATTED {};
		struct JSON {};
		template<typename Ty>
		std::string Format(const Stage& stage) {}
		template<>
		std::string Format<XML>(const Stage& stage)
		{
			std::stringstream elem;
			elem << "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>";
			elem << std::string("<unittest>");
			for (TyPlay::const_iterator it_screenplay = stage.Play().begin();
				it_screenplay != stage.Play().end();
				it_screenplay++)
			{
				std::string act = it_screenplay->first;

				elem << std::string("<testgrp name=") + "\"" + act + "\">";
				for (ScreenPlay::TyActors::const_iterator it_actors = it_screenplay->second->Actors().begin();
					it_actors != it_screenplay->second->Actors().end();
					it_actors++)
				{
					std::string actor = it_actors->first;
					elem << std::string("<test name=") + "\"" + actor + "\">";
					elem << std::string("<status>");
					switch (it_actors->second->Prestige().m_committed)
					{
					case Pledge::IResult::Committed:
						elem << "PASS"; break;
					case Pledge::IResult::Uncommitted:
						elem << "FAIL"; break;
					case Pledge::IResult::Hoozah:
						elem << "CRASHED"; break;
					case Pledge::IResult::Foresaken:
						elem << "SKIP"; break;
					}
					elem << std::string("</status>");
					elem << std::string("<time>");
					elem << it_actors->second->Prestige().m_executionTime;
					elem << std::string("</time>");
					elem << std::string("<memory>");
					elem << it_actors->second->Prestige().m_memoryUse;
					elem << std::string("</memory>");
					elem << std::string("<process>");
                    elem << it_actors->second->Prestige().m_peakworkingsetsize;
					elem << std::string("</process>");
					elem << std::string("</test");
				}
				elem << std::string("</testgrp>");
			}
			elem << std::string("</unittest>");
			return elem.str();
		}
		template<>
		std::string Format<CSV>(const Stage& stage)
		{
			std::stringstream result;
			for (TyPlay::const_iterator it_screenplay = stage.Play().begin();
				it_screenplay != stage.Play().end();
				it_screenplay++)
			{
				std::string act = it_screenplay->first;
				for (ScreenPlay::TyActors::const_iterator it_actors = it_screenplay->second->Actors().begin();
					it_actors != it_screenplay->second->Actors().end();
					it_actors++)
				{
					std::string actor = it_actors->first;
					result
						<< act << ","
						<< actor << ","
						<< it_actors->second->Prestige().m_committed << ","
						<< it_actors->second->Prestige().m_executionTime << ","
						<< it_actors->second->Prestige().m_memoryUse << ","
                        << it_actors->second->Prestige().m_peakworkingsetsize << ","
						<< std::endl;
				}
			}
			return result.str();
		}
		template<>
		std::string Format<FORMATTED>(const Stage& stage)
		{
			std::stringstream result;
			result << stage;
			return result.str();
		}
		enum FetchType { TEST, CPU, MEMORY, PROCESS };
		template<FetchType fetch>
		TyResult Fetch(const Stage& stage)
		{
			std::map<std::string, std::map<std::string, std::string> > result;
			for (TyPlay::const_iterator it_screenplay = stage.Play().begin();
				it_screenplay != stage.Play().end();
				it_screenplay++)
			{
				std::string act = it_screenplay->first;
				for (ScreenPlay::TyActors::const_iterator it_actors = it_screenplay->second->Actors().begin();
					it_actors != it_screenplay->second->Actors().end();
					it_actors++)
				{
					std::string actor = it_actors->first;
					std::stringstream st;
					switch (fetch)
					{
					case TEST:
					{
						switch (it_actors->second->Prestige().m_committed)
						{
						case Pledge::IResult::Hoozah:
							result[actor][act] = "CRASHED"; break;
						case Pledge::IResult::Committed:
							result[actor][act] = "PASS"; break;
						case Pledge::IResult::Uncommitted:
							result[actor][act] = "FAIL"; break;
						case Pledge::IResult::Foresaken:
							result[actor][act] = "SKIP"; break;
						default:break;
						}
						break;
					}
					case CPU:
					{
						st << it_actors->second->Prestige().m_executionTime
							<< "bytes";
						result[actor][act] = st.str();
						break;
					}
					case PROCESS:
					{
                        if (it_actors->second->Prestige().m_peakworkingsetsize > 1024 * 1024 * 1024) {
							st << std::fixed
								<< std::setprecision(2)
								<< static_cast<double>(it_actors->second->Prestige().m_peakworkingsetsize) / (1024 * 1024 * 1024)
								<< "GB";
						}
						else if (it_actors->second->Prestige().m_peakworkingsetsize > 1024 * 1024) {
							st << std::fixed
								<< std::setprecision(2)
								<< static_cast<double>(it_actors->second->Prestige().m_peakworkingsetsize) / (1024 * 1024)
								<< "MB";
						}
						else if (it_actors->second->Prestige().m_peakworkingsetsize > 1024) {
							st << std::fixed
								<< std::setprecision(2)
								<< static_cast<double>(it_actors->second->Prestige().m_peakworkingsetsize) / (1024)
								<< "KB";
						}
						else  {
							st << std::fixed
								<< std::setprecision(2)
								<< it_actors->second->Prestige().m_peakworkingsetsize
								<< "bytes";
						}
						result[actor][act] = st.str();
						break;
					}
					case MEMORY:
					{
						if (it_actors->second->Prestige().m_memoryUse > 1024 * 1024 * 1024) {
							st << std::fixed
								<< std::setprecision(2)
								<< static_cast<double>(it_actors->second->Prestige().m_memoryUse) / (1024 * 1024 * 1024)
								<< "GB";
						}
						else if (it_actors->second->Prestige().m_memoryUse > 1024 * 1024) {
							st << std::fixed
								<< std::setprecision(2)
								<< static_cast<double>(it_actors->second->Prestige().m_memoryUse) / (1024 * 1024)
								<< "MB";
						}
						else if (it_actors->second->Prestige().m_memoryUse > 1024) {
							st << std::fixed
								<< std::setprecision(2)
								<< static_cast<double>(it_actors->second->Prestige().m_memoryUse) / (1024)
								<< "KB";
						}
						else  {
							st << std::fixed
								<< std::setprecision(2)
								<< it_actors->second->Prestige().m_memoryUse
								<< "bytes";
						}
						result[actor][act] = st.str();
						break;
					}
					default:
						break;
					}
				}
			}
			return result;
		}
	}
	std::ostream& operator<<(std::ostream& os, const Stage& stage)
	{
		PTable::PTManip::Instance(OOTestNS::Result::Fetch<OOTestNS::Result::TEST>(stage));
		os << PTable::CenterAllign();
		os << PTable::Row<PTable::LINE>(PTable::PTManip::Instance().get_header_sep(), ' ');
		os << PTable::Row<PTable::TITLE>("Unit Testing Result");
		os << PTable::Row<PTable::LINE>(PTable::PTManip::Instance().get_footer_sep());
		os << PTable::Table<TyResult>(OOTestNS::Result::Fetch<OOTestNS::Result::TEST>(stage));

		PTable::PTManip::Instance(OOTestNS::Result::Fetch<OOTestNS::Result::CPU>(stage));
		os << PTable::CenterAllign();
		os << PTable::Row<PTable::LINE>(PTable::PTManip::Instance().get_header_sep(), ' ');
		os << PTable::Row<PTable::TITLE>("Performance Benchmarking");
		os << PTable::Row<PTable::LINE>(PTable::PTManip::Instance().get_footer_sep());
		os << PTable::Table<TyResult>(OOTestNS::Result::Fetch<OOTestNS::Result::CPU>(stage));
		
		PTable::PTManip::Instance(OOTestNS::Result::Fetch<OOTestNS::Result::MEMORY>(stage));
		os << PTable::CenterAllign();
		os << PTable::Row<PTable::LINE>(PTable::PTManip::Instance().get_header_sep(), ' ');
		os << PTable::Row<PTable::TITLE>("Memory Benchmarking (Works with Debug Build)");
		os << PTable::Row<PTable::LINE>(PTable::PTManip::Instance().get_footer_sep());
		os << PTable::Table<TyResult>(OOTestNS::Result::Fetch<OOTestNS::Result::MEMORY>(stage));

        PTable::PTManip::Instance(OOTestNS::Result::Fetch<OOTestNS::Result::PROCESS>(stage));
		os << PTable::CenterAllign();
		os << PTable::Row<PTable::LINE>(PTable::PTManip::Instance().get_header_sep(), ' ');
		os << PTable::Row<PTable::TITLE>("Process Benchmarking ");
		os << PTable::Row<PTable::LINE>(PTable::PTManip::Instance().get_footer_sep());
        os << PTable::Table<TyResult>(OOTestNS::Result::Fetch<OOTestNS::Result::PROCESS>(stage));
		return os;
	}
}
#endif
