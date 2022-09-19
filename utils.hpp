#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

	template < class T, T v >
	struct integral_constant
	{
		static const T value = v;

		typedef T						value_type;
		typedef integral_constant<T,v>	type;

		inline operator T() { return v; }
	};

	typedef	integral_constant< bool, false >	false_type;
	typedef	integral_constant< bool, true >		true_type;

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <class T>
	struct is_integral : false_type {} ;
	template <>
	struct is_integral<bool> : true_type {} ;
	template <>
	struct is_integral<char> : true_type {} ;
	template <>
	struct is_integral<char16_t> : true_type {} ;
	template <>
	struct is_integral<char32_t> : true_type {} ;
	template <>
	struct is_integral<wchar_t> : true_type {} ;
	template <>
	struct is_integral<short> : true_type {} ;
	template <>
	struct is_integral<int> : true_type {} ;
	template <>
	struct is_integral<long> : true_type {} ;
	template <>
	struct is_integral<long long> : true_type {} ;
}

#endif