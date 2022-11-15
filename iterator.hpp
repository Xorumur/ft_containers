// #ifndef ITERATOR_HPP
// #define ITERATOR_HPP

#include <iostream>
#include <iterator> 
#include "iterator_traits.hpp" 
#include "reverse_iterator.hpp"

#ifndef	ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{

	// =======================================
	// ======= RANDOM_ACCESS_ITERATOR ========
	// =======================================
	template< typename T >
	class random_access_iterator
	{
		private:
				// recup traits macro
				typedef iterator_traits<T> it;
		public:
				// typedef macro
				typedef typename it::value_type				value_type;
				typedef typename it::pointer				pointer;
				typedef typename it::reference				reference;
				typedef typename it::difference_type		difference_type;
				typedef typename it::iterator_category		iterator_category;
		protected:
				pointer	_pointer;
		public:
				random_access_iterator( void ) { _pointer = NULL; }											 // default
				random_access_iterator( pointer pointer ) { _pointer = pointer; }							 // param
				template <class Iter>
				random_access_iterator (const random_access_iterator<Iter> & rhs) : _pointer(rhs.base()) { } // copy
				~random_access_iterator( void ) {  }														 // destruct

				// recup le pointer de l'iterator (conversion plus simple que &(*(iterator)))
				pointer base(void) const
				{
					return this->_pointer;
				}

				// assignation
				template <class Iterator>
				random_access_iterator& operator= (const random_access_iterator<Iterator>& rhs) {
					this->_pointer = rhs.base();
					return (*this);
				}

				// *
				reference operator* () {
					return (*_pointer);
				}
				reference operator* () const {
					return (*_pointer);
				}

				// []
				reference operator[] (difference_type n) {
					return (*(_pointer + n));
				}
				reference operator[] (difference_type n) const {
					return (*(_pointer + n));
				}

				// ->
				pointer operator->() const {
					return &(operator*());
				}
				// +=
				random_access_iterator operator+=(difference_type n) {
					return (this->_pointer = this->_pointer + n);
				}
				// -=
				random_access_iterator operator-=(difference_type n) {
					return (this->_pointer = this->_pointer - n);
				}

				// ++
				random_access_iterator&	operator++() {
					_pointer++;
					return (*this);
				}
				random_access_iterator	operator++(int) {
					random_access_iterator temp(*this);
					_pointer++;
					return (temp);
				}

				// --
				random_access_iterator&	operator--() {
					_pointer--;
					return (*this);
				}
				random_access_iterator	operator--(int) {
					random_access_iterator temp(*this);
					_pointer--;
					return (temp);
				}

				// -
				difference_type operator-(const random_access_iterator & rhs) const {
					return (_pointer - rhs._pointer);
				}
				random_access_iterator operator-(difference_type n) const {
					return random_access_iterator(_pointer - n);
				}

				// +
				difference_type operator+(const random_access_iterator & rhs) const {
					return (_pointer + rhs._pointer);
				}
				random_access_iterator operator+(difference_type n) const {
					return random_access_iterator(_pointer + n);
				}
	};

	// OUT OF CLASS OPERATORS
	template <class Iterator1, class Iterator2>
	typename ft::random_access_iterator<Iterator1>::difference_type operator- ( const ft::random_access_iterator<Iterator1>& lhs, 
											const ft::random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() - rhs.base());
	}
	template <class Iterator>
	ft::random_access_iterator<Iterator> operator+ ( typename ft::random_access_iterator<Iterator>::difference_type n, 
											const ft::random_access_iterator<Iterator>& it) {
		return (it + n);
	}

	// OUT OF CLASS COMPARISON
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::random_access_iterator<Iterator1>& lhs,	
				const ft::random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<  (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() < rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<= (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs){
		return (lhs.base() <= rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>  (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs){
		return (lhs.base() > rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>= (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs){
		return (lhs.base() >= rhs.base());
	}
}

#endif