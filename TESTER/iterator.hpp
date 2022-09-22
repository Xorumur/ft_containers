// #ifndef ITERATOR_HPP
// #define ITERATOR_HPP

#include <iostream>
#include <iterator> 
#include "iterator_traits.hpp" 
#include "reverse_iterator.hpp"

// namespace ft
// {
// 	template<typename T>
// 	class random_access_iterator {
// 		private:
// 			typedef	ft::iterator_traits<T>						Iter;

// 		public:
// 			/* a signed integer type that can be used to identify distance between iterator steps */
// 			typedef typename Iter::difference_type			difference_type;

// 			/* the type the iterator iterates over */
// 			typedef typename Iter::value_type				value_type;

// 			/* defines a pointer to the type iterated over */
// 			typedef typename Iter::pointer					pointer;

// 			/* defines a reference to the type iterated over */
// 			typedef typename Iter::reference				reference;

// 			/* one of the six iterator categories we have seen above */
// 			/* Here this will be random_access_iterator that englobs all the operators */
// 			typedef typename Iter::iterator_category		iterator_category;


// 		private:
// 			pointer	_ptr;


// 		public:
		
// 		    	// operator IterVector<const T>() const { return (this->ptr); }

// 			random_access_iterator(){
// 				this->_ptr = NULL;
// 			}

// 			random_access_iterator(pointer pointer) : _ptr(pointer) { }

// 			template <class It>
// 			random_access_iterator (const random_access_iterator<It> & rhs) : _ptr(rhs.base()) { }

// 			// template <class It>
// 			// random_access_iterator (const random_access_iterator<It> & rhs) { _ptr = const_cast<const T>rhs.base();}

// 			// operator random_access_iterator<const T>() const   // cast iterator -> const iterator
// 			// {   return _ptr;    }

// 			pointer base(void) const {
// 				return(this->_ptr);
// 			}

// 				/* OPERATORS */
// 			// template <class Iterator>
// 			// random_access_iterator& operator=(const random_access_iterator<Iterator>& rhs) {
// 			// 	this->_ptr = rhs.base();
// 			// 	return (*this);
// 			// }

// 			reference operator*() const { return *this->_ptr; }

// 			pointer operator->() { return this->_ptr; }

// 			random_access_iterator& operator++() {
// 					/* Prefix increment */
// 					this->_ptr++; 
// 					return *this; 
// 				}

// 			random_access_iterator operator++(int) {
// 				/* Postfix increment */
// 				random_access_iterator tmp = *this; 
// 				++(*this);
// 				return tmp;
// 			}

// 			random_access_iterator& operator--() {
// 					/* Prefix increment */
// 					this->_ptr--; 
// 					return *this; 
// 				}

// 			random_access_iterator operator--(int) {
// 				/* Postfix increment */
// 				random_access_iterator tmp = *this; 
// 				--(*this);
// 				return tmp;
// 			}

// 			random_access_iterator operator+ (difference_type n) const { 
// 				return random_access_iterator(this->_ptr + n);
// 			}

// 			difference_type operator+ (const random_access_iterator & rhs) const { 
// 				return (this->_ptr + rhs._ptr);
// 			}

// 			random_access_iterator operator- (difference_type n) const { 
// 				return random_access_iterator(this->_ptr - n);
// 			}

// 			difference_type operator- (const random_access_iterator & rhs) const { 
// 				return (this->_ptr - rhs._ptr);
// 			}

// 			random_access_iterator& operator-= (difference_type n) { 
// 				this->_ptr -= n;
// 				return (*this);
// 			}

// 			random_access_iterator& operator+= (difference_type n) { 
// 				this->_ptr += n;
// 				return (*this);
// 			}

// 			reference operator[] (difference_type n) {
// 				return *(this->_ptr + n);
// 			}

// 			reference operator[] (difference_type n) const{
// 				return *(this->_ptr + n);
// 			}
// 	};
	
// 	/* OUT OF CLASS OPERATORS */
// 	template <class Iterator>
// 	ft::random_access_iterator<Iterator> operator+ ( typename ft::random_access_iterator<Iterator>::difference_type n, 
// 											const ft::random_access_iterator<Iterator>& it) {
// 		return (it + n);
// 	}
// 	/* OUT OF CLASS COMPARAISONS */

// 	template<class Iterator1, class Iterator2>
// 	bool operator== (const Iterator1& a, const Iterator2& b) {
// 		/* EQUAL COMPARAISON */
// 		/* So we ask if the pointer in each Iterator's classes are the same 
// 			which means if the iterators are the same */ 
// 		return (a.base() == b.base()); 
// 	};

// 	template<class Iterator1, class Iterator2>
// 	bool operator!= (const Iterator1& a, const Iterator2& b) {
// 		/* INEQUAL COMPARAISON */
// 		/* Same goes here */ 
// 		return (a.base() != b.base()); 
// 	};

// 	template<class Iterator1, class Iterator2>
// 	bool operator< (const Iterator1& a, const Iterator2& b) {
// 		/* INEQUAL COMPARAISON */
// 		/* Same goes here */ 
// 		return (a.base() < b.base()); 
// 	};

// 	template<class Iterator1, class Iterator2>
// 	bool operator> (const Iterator1& a, const Iterator2& b) {
// 		/* INEQUAL COMPARAISON */
// 		/* Same goes here */ 
// 		return (a.base() > b.base()); 
// 	};

// 	template<class Iterator1, class Iterator2>
// 	bool operator<= (const Iterator1& a, const Iterator2& b) {
// 		/* INEQUAL COMPARAISON */
// 		/* Same goes here */ 
// 		return (a.base() <= b.base());
// 	};

// 	template<class Iterator1, class Iterator2>
// 	bool operator>= (const Iterator1& a, const Iterator2& b) {
// 		/* INEQUAL COMPARAISON */
// 		/* Same goes here */ 
// 		return (a.base() >= b.base()); 
// 	};
// }


// #endif

#ifndef	ITERATOR_HPP
# define ITERATOR_HPP

// # include <iostream>
// # include "iterator_traits.hpp"
// # include "bidirectional_iterator.hpp"

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