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
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <stack>
#include <set>
#include <sstream>
#include <type_traits>
#include "c11_type_traits.h"
#ifndef __PPRINTSTL_H__
#define __PPRINTSTL_H__

namespace pprint
{

	template<
		typename Ty, 
		bool as_type = std_c11::is_associative<Ty>::value,
		bool it_type = std_c11::is_iterable<Ty>::value,
		bool pr_type = std_c11::is_pair<Ty>::value
	>
	struct brackets
	{
		// Any other case is an Error
	};
	template<typename Ty>
	struct brackets<
		Ty,
		true,  //Associative
		true,  //Iterable
		false  //But not a Pair
	>
	{
		static const char open = '{';
		static const char close = '}';
	};
	template<typename Ty>
	struct brackets<
		Ty, 
		false, //Not Associative
		true,  //But Iterable
		false  //But not a Pair
	>
	{
		static const char open = '[';
		static const char close = ']';
	};
	template<typename Ty>
	struct brackets<
		Ty,
		false, //Neither Associative
		false, //Nor Iterable
		false  //Nor a Pair
	>
	{
		static const char open = '<';
		static const char close = '>';
	};
	template<typename Ty>
	struct brackets<
		Ty,
		false, //Neither Associative (actually don't care)
		false, //Nor Iterable
		true   //But a Pair
	>
	{
		static const char open = '(';
		static const char close = ')';
	};
	template<
		typename Ty, 
		bool is_iterable = std_c11::is_iterable<typename std::remove_cv<typename std::remove_reference<Ty>::type>::type>::value,
		bool is_fundamental = std_c11::is_fundamental<typename std::remove_cv<typename std::remove_reference<Ty>::type>::type>::value,
		bool is_string = std::is_convertible<Ty, std::string>::value
	>
	struct pprint {
		std::string   operator()(const Ty& data, size_t depth = 0)
		{
			std::string strm;
			strm += "\n";
			strm += std::string(depth , ' ');
			strm += std::string(1, brackets<Ty>::open);
			for (typename Ty::const_iterator it = data.begin();
				it != data.end();
				it++)
			{
				strm += pprint<typename Ty::value_type>()(*it, depth + 1);
				if (std::distance(it, data.end()) > 1)
				{
					strm += ",";
					
				}
			}
			strm += std::string(1, brackets<Ty>::close);
			return strm;
		}
	};
	//Smart Pointer
	template<typename Ty>
	struct pprint<
		Ty, 
		false,	//Is Neither Iterable 
		false,  //Nor Fundamental
		false   //Nor a String Convetable
	> {
		std::string   operator()(const Ty& data, size_t depth = 0)
		{
			std::string strm;
			strm = std::string(1, brackets<Ty>::open)
			     + pprint<typename Ty::element_type>()(*data, depth + 1)
			     + std::string(1, brackets<Ty>::close);
			return strm;
		}
	};
	//std::string / C Type String
	template<typename Ty>
	struct pprint<
		Ty, 
		true, //Is Iterable 
		false, //But not Fundamental
		true   //Yet a String Convetable
	> {
		const std::string   operator()(const std::string& data, size_t depth = 0)
		{
			std::string strm = "\"" + data + "\"";				
			return strm;
		}
	};
	// Fundamental Data Types
	template<typename Ty>
	struct pprint<
		Ty, 
		false,   //Is Neither Iterable 
		true,    //But Fundamental
		false    //But Not a String Convetable
	> {
		std::string  operator()(const Ty& data, size_t depth = 0)
		{
			std::stringstream st;
			st << data;
			return st.str();
		}
	};
	template<
		typename TyK, 
		typename TyV>
	struct pprint<
		std::pair<TyK, TyV>,  
		false, 
		false, 
		false> {
		std::string   operator()(const std::pair<TyK, TyV>& data, size_t depth = 0)
		{
			std::string strm = std::string("\n");
			strm += std::string(depth, ' ')
				+ std::string("(")
				+ pprint<TyK>()(data.first, depth)
				+ " :"
				+ "\n";
			strm += pprint<TyV>()(data.second, strm.size())
				  + ")";
			return strm;
		}
	};
	template<typename Ty, int size>
	struct pprint<Ty[size], false,  false, false> {
		std::string   operator()(const Ty data[size], size_t depth = 0)
		{
			std::string strm;
			strm += "\n";
			strm += std::string(depth, ' ');
			strm += std::string(1, brackets<Ty>::open);
			for (size_t i = 0; i < size; i++)
			{
				strm += std::string(depth + 1, ' ');
				strm += pprint<Ty>()(data[i], depth + 1);
				if ((size - i) > 1)
				{
					strm += ", ";

				}
			}
			strm += std::string(1, brackets<Ty>::close);
			return strm;
		}
	};

};
#endif
