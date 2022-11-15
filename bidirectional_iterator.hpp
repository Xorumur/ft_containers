#pragma once

# include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft {

	template <class T>
	class bidirectional_iterator {

	private:
		typedef	std::iterator_traits<T>						Iter;

	public:
		typedef T											value_type;
		typedef value_type*									pointer;
		typedef value_type&									reference;
		typedef size_t										difference_type;
		typedef std::bidirectional_iterator_tag				iterator_category;

		// typedef typename Iter::difference_type			difference_type;

		// /* the type the iterator iterates over */
		// typedef typename Iter::value_type				value_type;

		// /* defines a pointer to the type iterated over */
		// typedef typename Iter::pointer					pointer;

		// /* defines a reference to the type iterated over */
		// typedef typename Iter::reference				reference;

		// /* one of the six iterator categories we have seen above */
		// /* Here this will be random_access_iterator that englobs all the operators */
		// typedef typename Iter::iterator_category		iterator_category;

	protected:
		pointer _current;

	public:

		// Default constructor
		bidirectional_iterator() {this->_current = NULL;}

		bidirectional_iterator(pointer _ptr) : _current(_current){ this->_current = _ptr;};

		// Copy and cast constructor
		bidirectional_iterator(const bidirectional_iterator& other) : _current(other._current){};

		template <typename TT>
		bidirectional_iterator(const bidirectional_iterator<TT>& other) : _current(other.base()) {}

		reference operator*() const { return *_current; };

		pointer operator->() const { return &(operator*()); };

		pointer const& base() const { return _current; }

		bool operator==(const bidirectional_iterator<T>& other) {
			return (this->_current == other._current);
		};

		bool operator!=(const bidirectional_iterator<T>& other) {
			return (this->_current != other._current);
		};

		bidirectional_iterator& operator++() {
			++_current;
			return *this;
		};

		bidirectional_iterator operator++(int) {
			bidirectional_iterator tmp = *this;
			++(*this);
			return tmp;
		};

		bidirectional_iterator& operator--() {
			--_current;
			return *this;
		};

		bidirectional_iterator operator--(int) {
			bidirectional_iterator tmp = *this;
			--(*this);
			return tmp;
		};

	};

}
