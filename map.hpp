#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>


namespace ft
{
    // template < class T >
    // class map_iterator
    // {
    //     private:



    //     public:
    // }

    template < class T1, class T2 > struct pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;

            first_type first;
            second_type second;

            pair() : first(0), second(0) {}

            template <class U, class V>
            pair(const pair<U, V> &pr) { *this = pr; }

            pair(const first_type &a, const second_type &b) : first(a), second(b) {}

            pair &operator=(const pair &x)
            {
                if (this == &x)
                    return *this;
                this->first = x.first;
                this->second = x.second;
            }
    };

    template < class T1, class T2 >
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template < class T1, class T2 >
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs == rhs);
    }

    template < class T1, class T2 >
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return lhs.first < rhs.first || (!(lhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template < class T1, class T2 >
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(rhs < lhs);
    }

    template < class T1, class T2 >
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return rhs < lhs;
    }

    template < class T1, class T2 >
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }

    template <
        class Key,
        class T,
        class Compare = std::less< Key >,
        class Allocator = std::allocator< std::pair< const Key, T > >
    >
    class map
    {
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef typename std::pair<const key_type, mapped_type> value_type;
            typedef Compare key_compare;
            typedef typename std::size_t size_type;
            typedef Allocator allocator_type;
            
            // template < class Key, class T, class Compare, class Alloc >
            // class map

        private:
            key_type *_key;
            mapped_type *_val;
            size_type _size, _capacity;
            allocator_type _alloc;
            key_compare _comp;

        public:
            // empty
            explicit map(const key_compare &comp = key_compare(),
                         const allocator_type &alloc = allocator_type()) :
                         _key(0), _val(0), _size(0), _capacity(0), _alloc(alloc), _comp(comp) {}
            
            // range
            // template < class InputIterator >
            // map(InputIterator first, InputIterator last,
            //     const key_compare &comp = key_compare(),
            //     const allocator_type &alloc = allocator_type())
            // {

            // }

            // copy
            map(const map &x) { *this = x; }

            // map &operator=(const map &x) {  }

    };
}

#endif