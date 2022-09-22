#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include <memory>

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack {
		public:

			typedef	Container								container_type;
			typedef	typename Container::value_type			value_type;
			typedef	typename Container::size_type			size_type;
			typedef	typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;
	
		private:
			container_type	_c;
		public:
			explicit stack (const container_type& ctnr = container_type()) : _c(ctnr) { }

			bool empty() const { return _c.empty();}

			size_type size() const {return _c.size();}

			value_type& top() { return _c.back();}

			const value_type& top() const { return _c.back();}

			void push (const value_type& val) {_c.push_back(val);}

			void pop() { return _c.pop_back();}

			template <class Ts, class Containers>
			friend bool operator== (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

			template <class Ts, class Containers>
			friend bool operator!= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

			template <class Ts, class Containers>
			friend bool operator<  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

			template <class Ts, class Containers>
			friend bool operator<= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

			template <class Ts, class Containers>
			friend bool operator>  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

			template <class Ts, class Containers>
			friend bool operator>= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

	};

	template <class Ts, class Containers>
	bool operator== (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs._c == rhs._c);
	}

	template <class Ts, class Containers>
	bool operator!= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs._c != rhs._c);
	}

	template <class Ts, class Containers>
	bool operator<  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs._c < rhs._c);
	}

	template <class Ts, class Containers>
	bool operator<= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs._c <= rhs._c);
	}

	template <class Ts, class Containers>
	bool operator>  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs._c > rhs._c);
	}

	template <class Ts, class Containers>
	bool operator>= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs._c >= rhs._c);
	}
}

#endif