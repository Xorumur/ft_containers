#ifndef	REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"

namespace ft
{

	// =================================
	// ======= REVERSE_ITERATOR ========
	// =================================
	template< class Iterator >
	class reverse_iterator
	{
 		public:
				// typedef macro
				typedef Iterator								iterator_type;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::iterator_category	iterator_category;

				

		protected:
				iterator_type		_base_it;
		public:
				reverse_iterator() { _base_it = NULL; }													// default
				explicit reverse_iterator (iterator_type it) : _base_it(it) { }							// param
				template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base_it(rev_it.base()) { }

				// operator reverse_iterator<const Iterator>() const { return this->_base_it; }
				~reverse_iterator( void ) {  }

				iterator_type base() const {
					return (this->_base_it);
				}

				reference operator*() const {
					iterator_type	cpy = _base_it;
					return (*(--cpy));
				}
				
				pointer operator->() const {
					return &(operator*());
				}

				reverse_iterator operator=(const reverse_iterator & rhs) {
						_base_it = rhs.base();
						return *this;
				}

				// ++ et --
				reverse_iterator& operator++() {
					--_base_it;
					return (*this);
				}
				reverse_iterator operator++(int) {
					reverse_iterator temp = *this;
					operator++();
					return temp;
				}
				reverse_iterator& operator--() {
					++_base_it;
					return (*this);
				}
				reverse_iterator operator--(int) {
					reverse_iterator temp = *this;
					--(*this);
					return temp;
				}

				// + et -
				reverse_iterator operator+ (difference_type n) const {
					return reverse_iterator(_base_it - n);
				}
				reverse_iterator operator- (difference_type n) const {
					return reverse_iterator(_base_it + n);
				}

				// -= et +=
				reverse_iterator& operator-= (difference_type n) {
					this->_base_it += n;
					return (*this);
				}
				reverse_iterator& operator+= (difference_type n) {
					this->_base_it -= n;
					return (*this);
				}

				// []
				reference operator[] (difference_type n) const {
					return (base()[-n-1]);
				}
	};

	// OUT OF CLASS OPERATORS
	template <class Iterator>
	reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n,
												const reverse_iterator<Iterator>& rev_it) {
		return (rev_it + n);
	}
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator- (
					const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (rhs.base() - lhs.base());
	}

	// OUT OF CLASS COMPARISON
	template <class Iterator1, class Iterator2>
	bool operator== (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!= (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<  (const reverse_iterator<Iterator1>& lhs,
 						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>  (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<= (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>= (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() <= rhs.base());
	}
}

#endif