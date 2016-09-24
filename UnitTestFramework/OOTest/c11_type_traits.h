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
#ifndef __C11_TYPE_TRAITS_H__
#define __C11_TYPE_TRAITS_H__
namespace std_c11
{
	template<typename Ty>
	struct  is_fundamental
	{
		typedef char Yes[1];
		typedef char No[2];
		template <class U> static Yes &test(char);
		template <class U> static Yes &test(unsigned char);
		template <class U> static Yes &test(signed char);
		template <class U> static Yes &test(short int);
		template <class U> static Yes &test(unsigned short int);
		template <class U> static Yes &test(int);
		template <class U> static Yes &test(unsigned int);
		template <class U> static Yes &test(long int);
		template <class U> static Yes &test(unsigned long int);
		template <class U> static Yes &test(long long int);
		template <class U> static Yes &test(unsigned long long int);
		template <class U> static No  &test(...);
	public:
		typedef is_fundamental type;
		static bool const value = sizeof(test<Ty>(0)) == sizeof(Yes);
	};
	struct  _is_convertible
	{
		typedef char Yes[1];
		typedef char No[2];
		template <class Ty> static Yes &test1(const Ty&);
		template <class Ty> static No  &test1(...);
		template <class Ty> static Yes &test2(Ty);
		template <class Ty> static No  &test2(...);
		template <class Ty> static Ty  source();
	};

	template <class T1, class T2>
	struct is_convertible
	{
		static const bool value = sizeof(_is_convertible::test1<T2>(_is_convertible::source<T1>())) == 1;
	};

	template <class T>
	struct is_convertible<T, T>
	{
		static const bool value = sizeof(is_conv_imp::test2<T>(is_conv_imp::source<T>())) == 1;
	};
	template<class Ty>
	struct remove_reference
	{
		typedef Ty type;
	};

	template<class Ty>
	struct remove_reference<Ty&>
	{
		typedef Ty type;
	};
	template<class Ty>
	struct remove_const
	{
		typedef Ty type;
	};

	template<class Ty>
	struct remove_const<const Ty>
	{
		typedef Ty type;
	};

	template<class Ty>
	struct remove_const<const Ty[]>
	{
		typedef Ty type[];
	};

	template<class Ty, unsigned int size>
	struct remove_const<const Ty[size]>
	{
		typedef Ty type[size];
	};
	// TEMPLATE CLASS remove_const
	template<class Ty>
	struct remove_volatile
	{
		typedef Ty type;
	};

	template<class Ty>
	struct remove_volatile<volatile Ty>
	{
		typedef Ty type;
	};

	template<class Ty>
	struct remove_volatile<volatile Ty[]>
	{
		typedef Ty type[];
	};

	template<class Ty, unsigned int size>
	struct remove_volatile<volatile Ty[size]>
	{
		typedef Ty type[size];
	};
	template<class Ty>
	struct remove_cv
	{
		typedef typename remove_const<typename remove_volatile<Ty>::type>::type
			type;
	};
	template<typename T>
	class is_associative
	{

		typedef char Yes[1];
		typedef char No[2];

		template<typename U> static Yes  &func(typename U::key_type);
		template<typename> static No  &func(...);

	public:
		typedef is_associative type;
		static bool const value = sizeof(func<T>(0)) == sizeof(Yes);
	};
	template <typename T>
	class is_iterable
	{
		typedef char Yes[1];
		typedef char No[2];

		template<typename U> static Yes  &func(typename U::iterator*);
		template<typename> static No  &func(...);

	public:
		typedef is_iterable type;
		static bool const value = sizeof(func<T>(0)) == sizeof(Yes);
	};
	template <typename T>
	struct is_pair {
		static const bool value = false;
	};
	template <typename TyK, typename TyV>
	struct is_pair < std::pair<TyK, TyV> > {
		static const bool value = true;
	};
}

#endif
