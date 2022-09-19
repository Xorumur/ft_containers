#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include "../iterator/iterator.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include "../utils.hpp"
/*		TO DO LIST	
Insert quelques securites
						*/


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

			typedef typename ft::random_access_iterator<pointer>			iterator;	
			typedef ft::random_access_iterator<const_pointer>				const_iterator;	
			typedef size_t													size_type;


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
				}
			}

			vector (vector const & x) {
				*this = x;
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
				if (n > this->_capacity) {
					this->reserve(n);
					// this->clear();
					for (size_type i = 0; i < n; i++) {
						this->push_back(val);
					}
				} else {
					this->clear();
					for (size_type i = 0; i < n; i++) {
						this->push_back(val);
					}
				}
			}

			// template <class InputIterator>
			// typename enable_if< !is_integral<InputIterator>::value, void>::type
			// assign (InputIterator first, InputIterator last) {
			// 	ft::vector<value_type>	v;
			// 	size_type		dist = std::distance(first, last);
			// 	// InputIterator	tmp = first;
			// 	// /* Calcul distance between first and last iterator */
			// 	// for ( ; tmp != last; tmp++) {
			// 	// 	dist++;
			// 	// }
			// 	if (this->_capacity > dist) {
			// 		// std::cout << "fb" << std::endl;
			// 		for ( ; first != last ; first++) {
			// 			std::cout << "fd1" << std::endl;
			// 			this->push_back(*first);
			// 		}
			// 	} else {
			// 		// std::cout << "fc" << std::endl;
			// 		v.reserve(dist);
			// 		v._end = v._start;
			// 		for ( ; first != last ; first++) {
			// 			std::cout << "fd2" << std::endl;
			// 			v._allocator.construct(v._end, *first);
			// 			v._end++;
			// 			v._used++;
			// 		}
			// 		this->swap(v);
			// 	}
			// 	std::cout << "test" << std::endl;
			// }

			template <class InputIterator>
			typename enable_if< !is_integral<InputIterator>::value, void>::type
			assign (InputIterator first, InputIterator last) {
				clear();
				size_type		dist = std::distance(first, last);
				pointer			tmp(this->_start);
				for (size_type i = 0; i < dist ; i++) {
					this->_allocator.construct(tmp + i, *first);
					first++;
					this->_used++;
					this->_end++;
				}
			}

			void push_back (const value_type& val) {
				if (this->_used == this->_capacity) {
					/* realloc */
					// std::cout << "1" << std::endl;
					this->reserve(this->_capacity + 2);
					this->_allocator.construct(this->_end, val);
					this->_end++;
					this->_used++;
				} else {
					/* Add an element at the end */
					// std::cout << this->_capacity << " " << this->_used << " 2" << std::endl;
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
				x._start = this->_end;
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
				for ( ; this->_start != this->_end ; ) {
					this->_allocator.destroy(this->_end - 1);
					this->_end--;
				}
				this->_used = 0;
			}

			iterator insert (iterator position, const value_type& val) {
				size_type dist = this->getDistance(this->begin(), position);
				if (this->_used == this->_capacity)
					reserve(this->_used + 1);
				for (iterator it = this->end(); it != this->begin() + dist; it--)
					*it = *(it - 1);
				*(this->begin() + dist) = val;
				this->_used++;
				return (this->begin() + dist);
			}
			
			void insert (iterator position, size_type n, const value_type& val) {
				if (!n)
					return ;
				size_type dist = this->getDistance(this->begin(), position);
				if (this->_used + n > this->_capacity)
					reserve(this->_used + n);
				for (iterator it = this->end() + n; it != this->begin() + dist + n - 1; it--)
					*it = *(it - n);
				for (size_type i = 0; i < n; i++)
					*(this->_start + dist + i) = val;
				this->_used += n;
				return ;
			}

			template <class InputIterator>
    		typename enable_if<!is_integral<InputIterator>::value, void>::type 
			insert (iterator position, InputIterator first, InputIterator last) {
				size_type	conserv = position.base() - this->_start;
				// size_type	dist = std::distance(first, last);
				ft::vector<value_type>	v;

				/* Calcul distance between first and last iterator */
				
				InputIterator	tmp = first;
				size_type		dist = 0;
				for ( ; tmp != last; tmp++)
					dist++;
				/* Check if there is enough space in the vector to handle the n new element in coming */
				if (dist + this->_used < this->_capacity) 
					v.reserve(this->_capacity);
				else
					v.reserve(dist + 1 + this->_used);

				pointer		pos = v._start + conserv;

				v._end = v._start;
				for ( ; v._end != pos ; ) {
					v._allocator.construct(v._end, *(this->_start));
					this->_start++;
					v._used++;
					v._end++;
				}
				for (size_type i = 0; i < dist; i++) {
					v._allocator.construct(v._end, *(first++));
					v._end++;
					v._used++;
				}
				for ( ; this->_start != this->_end ; ) {
					v._allocator.construct(v._end, *(this->_start));
					this->_start++;
					v._end++;
					v._used++;
				}
				this->swap(v);
			}

			iterator erase (iterator position) {
				ft::vector<value_type>	v(this->_capacity);
				size_type				conserv = position.base() - this->_start;
				pointer					pos = v._start + conserv;

				v._end = v._start;
				// if (pos == this->_end - 1)
				// {
				// 	this->_allocator.destroy(pos);
				// 	this->_end -= 1;
				// 	return (pos);
				// }
				if (position == this->end()) {
					this->_allocator.destroy(this->_end);

					iterator	save(this->_end);
					this->_end--;
					return save;
				}
				for ( ; v._end != pos ; ) {
					v._allocator.construct(v._end, *(this->_start));
					this->_start++;
					v._used++;
					v._end++;
				}
				this->_start++;
				pointer save(v._end);
				for ( ; this->_start != this->_end ; ) {
					v._allocator.construct(v._end, *(this->_start));
					this->_start++;
					v._used++;
					v._end++;
				}
				this->swap(v);
				return iterator(save);
			}

			iterator erase (iterator first, iterator last) {
				pointer	pos	= first.base();
					_allocator.destroy(first.base());
					size_type	diff = std::distance(first, last);
					if (pos == _end - 1)
					{
						_allocator.destroy(pos);
						_end -= 1;
						return (pos);
					}
					else if (pos != _end)
					{
						for (size_type i = 0 ; pos + i + diff < _end ; i++ ) {
							std::cout << "ici" << std::endl;
							_allocator.construct(pos + i, *(pos + i + diff));
							_allocator.destroy(pos + i + diff);
						}
						_end -= diff;
					}
					return (pos);
			}

				/* ITERATORS */

			iterator begin() {
				return iterator(this->_start);
			}

			const_iterator begin() const {
				return iterator(this->_start);
			}

			iterator end() {
				return iterator(this->_end);
			}

			const_iterator end() const {
				return iterator(this->_end);
			}
				/* Capacity */

			void reserve (size_type n) {
				/* Add n space to the vector */
				if (n > this->_capacity) {
					pointer		oldstart = this->_start;
					size_type	oldcapacity = this->_capacity;

					this->_start = this->_allocator.allocate(n);
					this->_end = this->_start;
					this->_capacity = n;
					for (size_type i = 0; i < oldcapacity; i++) {
						this->_allocator.construct(this->_start + i, *(oldstart + i));
						this->_end++;
					}
					for (size_type i = 0; i < n; i++)
						this->_allocator.destroy(oldstart + i);
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
					this->reserve(n);
					for (size_type i = this->_used; i < n; i++) {
						this->push_back(val);
					}
					return ;
				} else if (n == this->_used) {return ;}
			}

			size_type size() const {
				return (this->_used);
			}

			size_type max_size() const {
				return (this->_capacity);
			}

			bool empty() const {
				return (!(this->_used) ? true : false);
			}

			size_type capacity() const {
				return (this->_capacity);
			}

				/* Element access */

			reference at (size_type n) {
				if (n >= size() || n < 0)
					throw std::out_of_range("vector");
				return (*(this->_start + n));
			}

			const_reference at (size_type n) const {
				if (n >= size() || n < 0)
					throw std::out_of_range("vector");
				return (*(this->_start + n));
			}

			reference back() {
				return (*(this->_end));
			}

			const_reference back() const {
				return (*(this->_end));
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
				if ( this != &x)
					this->assign(x.begin(), x.end());
				return (*this);
			}

			reference operator[] (size_type n) {
				return (this->_start[n]);
			}

			const_reference operator[] (size_type n) const {
				return (this->_start[n]);
			}

			template <typename Iter>

			size_type getDistance(Iter first, Iter last) {
				size_type res = 0;
				for (Iter it = first; it != last; it++)
					res++;
				return (res);
			}

	};

}

#endif