#pragma once

#include "pair.hpp"
#include <memory>
#include <iostream>
#include "utils.hpp"

namespace ft {

    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
    class map {
        public:
            typedef Key                     Key_type;
            typedef ft::pair<const Key, T>  value_type;
            typedef T                       mapped_type;
            typedef size_t                  size_type;
            typedef Alloc                   allocator_type;
            typedef Compare                 Key_compare;
        private:

        public:
            map();
    };
}