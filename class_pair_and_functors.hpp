#ifndef CLASS_PAIR_AND_FUNCTORS_HPP
# define CLASS_PAIR_AND_FUNCTORS_HPP

namespace ft
{
    // =================================== PAIR ===================================

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
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
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

    // ============================================================================


    // =================== FUNCTORS: LESS, GREATER AND COMPARE ====================

    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };
    
    template <class T>
    struct less : ft::binary_function<T, T, bool>
    {
        bool operator()(const T &x, const T &y) const
        {
            return x < y;
        }
    };

    template <class T>
    struct greater : ft::binary_function<T, T, bool>
    {
        bool operator()(const T &x, const T &y) const
        {
            return x > y;
        }
    };

    struct Compare : ft::binary_function<int, int, bool>
    {
        bool operator()(int a, int b)
        {
            return (a == b);
        }
    };
    // ============================================================================
}

#endif