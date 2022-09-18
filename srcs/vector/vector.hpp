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

			vector (const vector& x) {
				*this = x;
			}

			~vector () {
				std::cout << "iuci" << std::endl;
				for (size_type i = 0; i < this->size() ; i++) {
					this->_allocator.destroy(this->_start + i);
					std::cout << "Boucle" << std::endl;
				}
				this->_allocator.deallocate(this->_start, this->_capacity);
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

			template <class InputIterator>
			typename enable_if< !is_integral<InputIterator>::value, void>::type
			assign (InputIterator first, InputIterator last) {
				ft::vector<value_type>	v;
				size_type		dist = 0;
				InputIterator	tmp = first;
				/* Calcul distance between first and last iterator */
				for ( ; tmp != last; tmp++) {
					dist++;
				}
				if (this->_capacity >= dist) {
					// std::cout << "fb" << std::endl;
					for ( ; first != last ; first++) {
						// std::cout << "fd" << std::endl;
						this->push_back(*first);
					}
				} else {
					// std::cout << "fc" << std::endl;
					v.reserve(dist);
					v._end = v._start;
					for ( ; first != last ; first++) {
						// std::cout << "fd" << std::endl;
						v._allocator.construct(v._end, *first);
						v._end++;
						v._used++;
					}
					this->swap(v);
				}
				// std::cout << "test" << std::endl;
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

			// iterator insert (iterator position, const value_type& val) {
			// 	size_type	conserv = position - this->_start;
			// 	if (this->_start == NULL)
			// 			this->reserve(1);
			// 	if (this->_start != NULL && this->_capacity < size() + 1)
			// 		this->reserve(this->_capacity * 2);
			// 	if (position.base() != NULL && position.base() < this->_start)	// Si pos inferieur a start -> pos = start
			// 		position = this->_start;
			// 	else if (position.base() != NULL && position.base() > this->_end)	// Si pos superieur a end -> pos = end
			// 		position = this->_end;
			// 	else if (position.base() == NULL)	// cas ou position = NULL
			// 	{
			// 		reserve(1);
			// 		push_back(val);
			// 		return (this->_end - 1);
			// 	}
			// 	else if (position.base() == this->_end && position.base() != this->_start)
			// 	{
			// 		push_back(val);
			// 		return (this->_end - 1);
			// 	}
			// 	ft::vector<value_type>	v(this->_capacity);
			// 	pointer		pos = v._start + conserv;
			// 	pointer		save_start = this->_start;
			// 	v._end = v._start;
			// 	for ( ; v._end != pos ; ) {
			// 		v._allocator.construct(v._end, *(this->_start));
			// 		this->_start++;
			// 		v._end++;
			// 		v._used++;
			// 	}
			// 	v._allocator.construct(v._end, val);
			// 	v._end++;
			// 	v._used++;
			// 	for ( ; this->_start != this->_end ; ) {
			// 		v._allocator.construct(v._end, *(this->_start));
			// 		this->_start++;
			// 		v._end++;
			// 		v._used++;
			// 	}
			// 	this->_start = save_start;
			// 	// this->swap(v);
			// 	this->assign(v.begin(), v.end());
			// 	return (this->_start + conserv);
			// }

			iterator insert (iterator position, const value_type& val) {
				size_type	conserv = position - _startpointer;	// stockage de la position dans le cas d'une reallocation
					if (_startpointer == NULL)
						this->reserve(1);
					if (_startpointer != NULL && _capacity < size() + 1)
						this->reserve(_capacity * 2);
					if (position.base() != NULL && position.base() < _startpointer)	// Si pos inferieur a start -> pos = start
						position = _startpointer;
					else if (position.base() != NULL && position.base() > _endpointer)	// Si pos superieur a end -> pos = end
						position = _endpointer;
					else if (position.base() == NULL)	// cas ou position = NULL
					{
						reserve(1);
						push_back(val);
						return (_endpointer - 1);
					}
					else if (position.base() == _endpointer && position.base() != _startpointer)
					{
						push_back(val);
						return (_endpointer - 1);
					}

					ft::vector<value_type>		vector_temp;
					vector_temp._startpointer	= _allocator.allocate(this->_capacity);
					vector_temp._capacity		= _capacity;
					vector_temp._endpointer		= vector_temp._startpointer;

					pointer		pos = vector_temp._startpointer + conserv;	// on recup la nouvelle position en cas de reallocation

					pointer		save_start = _startpointer;	// conserver le _start pour permettre le swap a la fin

					for ( ; vector_temp._endpointer != pos ; ) {
						vector_temp._allocator.construct(vector_temp._endpointer, *_startpointer);
						vector_temp._endpointer++;
						_startpointer++;
					}
					vector_temp._allocator.construct(vector_temp._endpointer, val);
					vector_temp._endpointer++;
					for ( ; _startpointer != _endpointer ; ) {
						vector_temp._allocator.construct(vector_temp._endpointer, *_startpointer);
						_startpointer++;
						vector_temp._endpointer++;
					}
					_startpointer = save_start;
					this->swap(vector_temp);
					return (_startpointer + conserv);
			}
			
			void insert (iterator position, size_type n, const value_type& val) {
				size_type	conserv = position.base() - this->_start;
				if (this->_start == NULL)
						this->reserve(1);
				if (this->_start != NULL && this->_capacity < size() + 1)
					this->reserve(this->_capacity * 2);
				if (position.base() != NULL && position.base() < this->_start)	// Si pos inferieur a start -> pos = start
					position = this->_start;
				else if (position.base() != NULL && position.base() > this->_end)	// Si pos superieur a end -> pos = end
					position = this->_end;
				else if (position.base() == NULL)	// cas ou position = NULL
				{
					reserve(1);
					push_back(val);
					return ;
				}
				else if (position.base() == this->_end && position.base() != this->_start)
				{
					push_back(val);
					return ;
				}
				ft::vector<value_type>	v;

				/* Check if there is enough space in the vector to handle the n new element in coming */
				if (n + this->_used < this->_capacity) 
					v.reserve(this->_capacity);
				else
					v.reserve(n + 1 + this->_used);

				pointer		pos = v._start + conserv;
				// pointer		save_start = this->_start;
				v._end = v._start;
				for ( ; v._end != pos ; ) {
					v._allocator.construct(v._end, *(this->_start));
					this->_start++;
					v._used++;
					v._end++;
				}
				for (size_type i = 0; i < n; i++) {
					v._allocator.construct(v._end, val);
					v._end++;
					v._used++;
				}
				for ( ; this->_start != this->_end ; ) {
					v._allocator.construct(v._end, *(this->_start));
					this->_start++;
					v._end++;
					v._used++;
				}
				// this->_start = save_start;
				std::cout << "55" << std::endl;
				this->swap(v);
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
				ft::vector<value_type>	v(this->_capacity);
				// size_type				conserv = position.base() - this->_start;
				pointer					pos = first.base();

				v._end = v._start;
				size_type		dist = 0;
				iterator		tmp(this->_start);
				for ( ; tmp != last; tmp++)
					dist++;
				if (pos == this->_end - 1)
				{
					this->_allocator.destroy(pos);
					this->_end -= 1;
					return (pos);
				}
				for ( ; this->_start != pos ; ) {
					v._allocator.construct(v._end, *(this->_start));
					this->_start++;
					v._used++;
					v._end++;
				}
				pointer save(v._end);
				for (size_type i = 0; i < dist ; i++) {
					this->_start++;
				}
				for ( ; this->_start != this->_end ; ) {
					v._allocator.construct(v._end, *(this->_start));
					this->_start++;
					v._used++;
					v._end++;
				}
				this->assign(v.begin(), v.begin());
				return iterator(save);
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

	};

}

#endif