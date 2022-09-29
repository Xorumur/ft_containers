#pragma once

namespace ft {
    template<typename T1, typename T2>
    class pair {
        public:
            typedef T1  first_type;
            typedef T2  second_type;
            first_type  first;
            second_type second;

            pair() : first(first_type()), second(second_type()) { }
            
            pair(const T1 & x, const T2 & y) : first(x), second(y) { }

            template<class U, class V>
	    	pair(const pair< U, V > & rhs) : first(rhs.first), second(rhs.second) { }

            pair& operator=(const pair & rhs) {
                first = rhs.first;
                second = rhs.second;
                return (*this);
            }
 


        friend bool operator==(pair const & lhs, pair const & rhs) { return ((lhs.first == rhs.first && lhs.second == rhs.second)); }
		friend bool operator!=(pair const & lhs, pair const & rhs) { return (!(lhs == rhs)); }
		friend bool operator<(pair const & lhs, pair const & rhs) { return (lhs.first == rhs.first) ? (lhs.second < rhs.second) : (lhs.first < rhs.first); }
		friend bool operator>(pair const & lhs, pair const & rhs) { return (rhs < lhs); }
		friend bool operator<=(pair const & lhs, pair const & rhs) { return (!(lhs > rhs)); }
		friend bool operator>=(pair const & lhs, pair const & rhs) { return (!(lhs < rhs)); }

    };

    template<class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 t, T2 u) { return (pair<T1, T2>(t, u)); }
}