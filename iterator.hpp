#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <iterator> 
#include "iterator_traits.hpp" 

namespace ft
{
	template<typename T>
	class random_access_iterator	{
		private:
			typedef	std::iterator_traits<T>						Iter;

		public:
			/* a signed integer type that can be used to identify distance between iterator steps */
			typedef typename Iter::difference_type			difference_type;

			/* the type the iterator iterates over */
			typedef typename Iter::value_type				value_type;

			/* defines a pointer to the type iterated over */
			typedef typename Iter::pointer					pointer;

			/* defines a reference to the type iterated over */
			typedef typename Iter::reference				reference;

			/* one of the six iterator categories we have seen above */
			/* Here this will be random_access_iterator that englobs all the operators */
			typedef typename Iter::iterator_category		iterator_category;


		private:
			pointer	_ptr;


		public:
			random_access_iterator(){
				this->_ptr = NULL;
			}

			random_access_iterator(pointer pointer) {
				this->_ptr = pointer;
			}

			template <class It>
			random_access_iterator (const random_access_iterator<It> & rhs) : _ptr(rhs.base()) { }

			pointer base(void) const {
				return(this->_ptr);
			}

				/* OPERATORS */
			// template <class Iterator>
			random_access_iterator& operator=(const random_access_iterator& rhs) {
				this->_ptr = rhs.base();
				return (*this);
			}

			reference operator*() const { return *this->_ptr; }

			pointer operator->() { return this->_ptr; }

			random_access_iterator& operator++() {
					/* Prefix increment */
					this->_ptr++; 
					return *this; 
				}

			random_access_iterator operator++(int) {
				/* Postfix increment */
				random_access_iterator tmp = *this; 
				++(*this);
				return tmp;
			}

			random_access_iterator& operator--() {
					/* Prefix increment */
					this->_ptr--; 
					return *this; 
				}

			random_access_iterator operator--(int) {
				/* Postfix increment */
				random_access_iterator tmp = *this; 
				--(*this);
				return tmp;
			}

			random_access_iterator& operator+ (difference_type n) { 
				return random_access_iterator(this->_ptr + n);
			}

			// random_access_iterator& operator+(size_t n) {
			// 	this->_ptr = n + this->_ptr;
			// 	return (*this);
			// }

			difference_type operator+ (const random_access_iterator & rhs) { 
				return (this->_ptr + rhs._ptr);
			}

			random_access_iterator& operator- (difference_type n) { 
				this->_ptr -= n;
				return (*this);
			}

			difference_type operator- (const random_access_iterator & rhs) const { 
				return (this->_ptr - rhs._ptr);
			}

			random_access_iterator& operator-= (difference_type n) { 
				this->_ptr -= n;
				return (*this);
			}

			random_access_iterator& operator+= (difference_type n) { 
				this->_ptr += n;
				return (*this);
			}

			reference operator[] (difference_type n) {
				return *(this->_ptr + n);
			}

			reference operator[] (difference_type n) const{
				return *(this->_ptr + n);
			}
	};
	
	/* OUT OF CLASS OPERATORS */

	template <class Iterator>
	ft::random_access_iterator<Iterator> operator+ ( typename ft::random_access_iterator<Iterator>::difference_type n, 
											const ft::random_access_iterator<Iterator>& it) {
		return (it + n);
	}


	/* OUT OF CLASS COMPARAISONS */

	template<class Iterator1, class Iterator2>
	bool operator== (const Iterator1& a, const Iterator2& b) {
		/* EQUAL COMPARAISON */
		/* So we ask if the pointer in each Iterator's classes are the same 
			which means if the iterators are the same */ 
		return (a.base() == b.base()); 
	};

	template<class Iterator1, class Iterator2>
	bool operator!= (const Iterator1& a, const Iterator2& b) {
		/* INEQUAL COMPARAISON */
		/* Same goes here */ 
		return (a.base() != b.base()); 
	};

	template<class Iterator1, class Iterator2>
	bool operator< (const Iterator1& a, const Iterator2& b) {
		/* INEQUAL COMPARAISON */
		/* Same goes here */ 
		return (a.base() < b.base()); 
	};

	template<class Iterator1, class Iterator2>
	bool operator> (const Iterator1& a, const Iterator2& b) {
		/* INEQUAL COMPARAISON */
		/* Same goes here */ 
		return (a.base() > b.base()); 
	};

	template<class Iterator1, class Iterator2>
	bool operator<= (const Iterator1& a, const Iterator2& b) {
		/* INEQUAL COMPARAISON */
		/* Same goes here */ 
		return (a.base() <= b.base());
	};

	template<class Iterator1, class Iterator2>
	bool operator>= (const Iterator1& a, const Iterator2& b) {
		/* INEQUAL COMPARAISON */
		/* Same goes here */ 
		return (a.base() >= b.base()); 
	};
}


#endif