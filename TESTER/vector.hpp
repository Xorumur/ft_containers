#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
// #include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include "utils.hpp"
// #include "bidirectional_iterator.hpp"

namespace ft {

	template<typename T, class Alloc = std::allocator<T> > 
	class vector {

		public : /* Definition of somes Member types */

			typedef Alloc													allocator_type;
			typedef typename allocator_type::value_type						value_type;

			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer  				const_pointer;
			typedef	typename allocator_type::reference						reference;
			typedef	typename allocator_type::const_reference				const_reference;
			typedef size_t													size_type;

			typedef ft::random_access_iterator<pointer>						iterator;	
			typedef ft::random_access_iterator<const_pointer>				const_iterator;	
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;// = reverse_iterator;


		private:
			pointer			_start;
			pointer			_end;
			allocator_type	_allocator;
			size_type		_capacity;
			size_type		_used;

		public:
			explicit
			vector (const allocator_type& alloc = allocator_type()) {
				this->_allocator = alloc;
				this->_capacity = 0;
				this->_start = NULL;
				this->_end = NULL;
				this->_used = 0;
			}

			explicit
			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
				this->_allocator = alloc;
				this->_capacity = n;
				this->_start = _allocator.allocate(_capacity);
				this->_end = this->_start;
				this->_used = 0;
				for (int i = 0; i < (int)n; i++) {
					this->_allocator.construct(this->_end, val);
					this->_end++;
					this->_used++;
				}
				//this->_end = this->_start + this->_used;
			}

			template <class InputIterator>	
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename enable_if< !is_integral<InputIterator>::value, int>::type = 0 )
			{
				size_type dist		= std::distance(first, last);
				_allocator			= alloc;
				_start				= _allocator.allocate(dist);
				_end				= _start + dist;
				_capacity			= dist;
				// _used				= dist;
				this->assign(first, last);
			}

			vector (vector const & other) {
				this->_allocator = other._allocator;
				this->_start = this->_allocator.allocate(other._used);
				for (size_type i = 0; i < other._used; i++)
					this->_allocator.construct(_start + i, *(other._start + i));
				this->_used = other._used;
				this->_capacity = other._capacity;
				// this->_end = other._end;
			}

			~vector () {
				// std::cout << "iuci" << std::endl;
				for (size_type i = 0; i < this->size() ; i++) {
					this->_allocator.destroy(this->_start + i);
					// std::cout << "Boucle" << std::endl;
				}
				// std::cout << "s" << std::endl;
				this->_allocator.deallocate(this->_start, --this->_capacity);
			}
				/* Modifiers */
			
			void assign (size_type n, const value_type& val) {
				
				// std::cout << " -1 " << std::endl;
				// this->clear();
				// std::cout << " 0 " << std::endl;
				if (n > this->_capacity) {
					// std::cout << " 1 " << std::endl;
					this->reserve(n);
					this->clear();
					// std::cout << " 2 " << std::endl;
					for (size_type i = 0; i < n; i++) {
						this->_allocator.construct(this->_start + i, val);
						this->_used++;
						this->_end++;
					}
					// std::cout << " 3 " << std::endl;
					// this->_used = i;
				} else {
					this->clear();
					// std::cout << " 4 " << std::endl;
					for (size_type i = 0; i < n; i++) {
						this->push_back(val);
					}
					// std::cout << " 5 " << std::endl;
				}
			}

			template <class InputIt>
			typename enable_if< !is_integral<InputIt>::value, void>::type
			assign( InputIt first, InputIt last ) {
				this->clear();
				size_type	dist = std::distance(first, last);
				if (this->_capacity >= dist)
				{
					for ( ; first != last ; first++)
						this->push_back(*first);
				}
				else
				{
					_allocator.deallocate(_start, _capacity);
					_start = _allocator.allocate(dist);
					_end = _start;
					_capacity = dist;
					for ( ; first != last ; first++)
						this->push_back(*first);
				}
			}

			void push_back (const value_type& val) {
				if (this->_used == this->_capacity) {
					/* realloc */
					// std::cout << "here" << std::endl;
					this->reserve(this->_capacity + 2);
					// std::cout << "guy" << std::endl;
					this->_allocator.construct(this->_end, val);
					this->_end++;
					this->_used++;
				} else {
					/* Add an element at the end */
					this->_allocator.construct(this->_end, val);
					this->_end++;
					this->_used++;
				}
			}

			void pop_back() {
				/* Delete the last element, I did not deallocate to gain efficiency */
				if (this->_used == 0)
					return ;
				this->_allocator.destroy(this->_end);
				this->_used--;
				this->_end--;
			}

			void swap (vector& x) {
				/* Swap Fill mode */
				pointer 		tmp_s = x._start;
				pointer			tmp_e = x._end;
				allocator_type tmp_alloc = x._allocator;
				size_type		tmp_capacity = x._capacity;
				size_type		tmp_used = x._used;

				x._start = this->_start;
				x._end = this->_end;
				x._allocator = this->_allocator;
				x._capacity = this->_capacity;
				x._used = this->_used;

				this->_start = tmp_s;
				this->_end = tmp_e;
				this->_allocator = tmp_alloc;
				this->_capacity = tmp_capacity;
				this->_used = tmp_used;
			}

			void clear() {
				// std::cout << "before clear() 1 & size() = " << size() << std::endl;
				// for (size_type i = 0, max = size(); i < max ; i++) {
				// 	std::cout << "I'm cleaning : " << i << std::endl;
				// 	this->_allocator.destroy(this->_start + i);
				// }
				// std::cout << "after clear() 1" << std::endl;
				for ( ; _start != _end ; ) {
						_allocator.destroy(_end - 1);
						_end--;
				}
				this->_used = 0;
				// this->_end = this->_start;
			}
			
			iterator insert (iterator position, const value_type& val) {
				size_type dist = std::distance(begin(), position);
				this->insert(position, 1, val);
				return iterator(this->_start + dist);
			}

			void insert (iterator position, size_type n, const value_type& val) {
				if (!n)
					return ;
				size_type dist = std::distance(this->begin(), position);
				if (this->_used + n > this->_capacity)
					reserve(this->_used + n);
				pointer p = this->_start + this->_used + n - 1;
				for ( ; p != this->_start + dist + n - 1; p--)
					*p = *(p - n);
				for (size_type i = 0; i < n; i++) {
					*(this->_start + dist + i) = val;
					this->_end++;
				}
				this->_used += n;
				return ;

			}

			template <class InputIterator>
    		typename enable_if<!is_integral<InputIterator>::value, void>::type 
			insert (iterator position, InputIterator first, InputIterator last) {
				if (first == last)
					return ;
				size_type dist = std::distance(this->begin(), position);
				size_type itSize = std::distance(first, last);
				if (this->_used + itSize > this->_capacity)
					reserve(this->_used + itSize);
				pointer p = this->_start + this->_used + itSize - 1;
				for (; p != this->_start + dist + itSize - 1; p--)
					*p = *(p - itSize);
				for (size_type i = 0; i < itSize; i++)
					*(this->_start + dist + i) = *first++;
				this->_used += itSize;
				this->_end += itSize;
				return ;
			}

			iterator erase(iterator pos) {
				if (_start == _end) 
					return NULL;
				iterator	tmp = begin();
				size_type	diff = std::distance(begin(), pos);
				this->_allocator.destroy(pos.base());
				for (size_type i = 0 ; tmp + diff + i < end() ; i++) {
					this->_allocator.construct(this->_start + diff + i, *(this->_start + diff + i + 1));
				}
				this->_used--;
				this->_end--;
				return iterator(this->_start + diff);
			}

			iterator erase (iterator first, iterator last) {
				pointer	pos	= first.base();
				size_type	diff = std::distance(first, last);
				// std::cout << diff << std::endl;
				_allocator.destroy(first.base());
				if (pos == _end - 1)
				{
					_allocator.destroy(pos);
					_end -= 1;
					return (pos);
				}
				else if (pos != _end)
				{
					for (size_type i = 0 ; pos + i + diff < _end ; i++ ) {
						_allocator.construct(pos + i, *(pos + i + diff));
						_allocator.destroy(pos + i + diff);
						// this->_used++;
					}
					_end -= diff;
					_used -= diff;
				}
				return (pos);
			}

				/* ITERATORS */

			iterator begin() {
				return iterator(this->_start);
			}

			const_iterator begin() const {
				return const_iterator(this->_start);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end());
			}

			reverse_iterator rend( void ) {
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend( void ) const {
				return const_reverse_iterator(begin());
			}

			iterator end() {
				//return iterator(this->_end);
				return iterator(this->_start + _used);
			}

			const_iterator end() const {
				return const_iterator(this->_start + _used);
				//return iterator(this->_end);
			}
				/* Capacity */

			void reserve (size_type n) {
				/* Add n space to the vector */
				if (n > this->_capacity) {
					pointer		oldstart = this->_start;
					size_type	oldcapacity = this->_used;

					this->_start = this->_allocator.allocate(n);
					this->_end = this->_start;
					this->_capacity = n;
					for (size_type i = 0; i < oldcapacity; i++) {
						this->_allocator.construct(this->_start + i, *(oldstart + i));
						this->_end++;
					}
					if (oldcapacity > 0) {
						for (size_type i = 0; i < n; i++)
							this->_allocator.destroy(oldstart + i);
					}
					this->_allocator.deallocate(oldstart, oldcapacity);
					
				} else {return;}
			}

			void resize (size_type n, value_type val = value_type()) {
				if (n < this->_used) {
					/* Reduced to its first n elements */
					for (pointer it = this->_start + n ; it != this->_end ; it++)
							this->_allocator.destroy(it);
					this->_end		= this->_start + n;
					this->_used = n;
					return ;
				} else if (n > this->_used) {
					/* Increase the capacity and fill the vector with val value */
					// this->reserve(n);
					// this->clear();
					// _allocator = allocate()
					// std::cout << capacity() << std::endl;
					for (size_type i = this->_used; i < n; i++) {
						// std::cout << "ptr" << std::endl;
						this->push_back(val);
					}
					return ;
				} else if (n == this->_used) {return ;}
			}

			size_type size() const {
				return (this->_used);
			}

			size_type max_size() const {
				return (_allocator.max_size());
			}

			bool empty() const {
				// std::cout << "Here test" << size() << std::endl;
				return ((this->_used) ? false : true);
			}

			size_type capacity() const {
				return (this->_capacity);
			}

				/* Element access */

			reference at (size_type n) {
				// std::cout << size() << std::endl;
				if (n >= size() || n < 0)
					throw std::out_of_range("vector");
				return (*(this->_start + n));
			}

			const_reference at (size_type n) const {
				// std::cout << "Here size() : " << size() << " && the n : " << n << std::endl;
				if (n >= size() || n < 0)
					throw std::out_of_range("vector");
				return (*(this->_start + n));
			}

			reference back() {
				return *(this->_start + this->_used - 1);
			}

			const_reference back() const {
				// std::cout << _used << std::endl;
				return *(this->_start + this->_used - 1);
			}

			reference front() {
				return (*(this->_start));
			}

			const_reference front() const {
				return (*(this->_start));
			}

			allocator_type get_allocator() const {
				return (this->_allocator);
			}


				/* Operators */
			
			vector& operator= (const vector& x) {
				if ( this != &x) {
					// for (size_type i = 0; x.begin() + i != x.end() ; i++) {
					// 	push_back(*(x.begin() + i));
					// }
					this->assign(x.begin(), x.end());
				}
				// std::cout << "op = " << std::endl;
				return (*this);
				// return vector(x.begin(), x.end());
			}

			reference operator[] (size_type n) {
				return (this->_start[n]);
			}

			const_reference operator[] (size_type n) const {
				return (this->_start[n]);
			}
	};

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

	// ====================
	// NON MEMBER OPERATORS
	// ====================
	
	// ==
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	// !=
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	// < et >
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) );
	}
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( rhs < lhs );
	}

	// <= et >=
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( !(rhs < lhs) );
	}
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( !(lhs < rhs) );
	}

}

#endif