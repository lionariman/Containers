#ifndef CLASS_PAIR_AND_FUNCTORS_HPP
# define CLASS_PAIR_AND_FUNCTORS_HPP

# define NCLR        "\033[0m"
# define BLACK       "\033[0;30m"
# define WHITE       "\033[0;37m"
# define YELLOW      "\033[0;33m"
# define RED         "\033[0;31m"
# define GREEN       "\033[0;32m"
# define CYAN        "\033[0;36m"
# define BLUE        "\033[0;34m"
# define PURPLE      "\033[0;35m"
# define B_GRAY      "\033[1;30m"
# define B_WHITE     "\033[1;37m"
# define B_RED       "\033[1;31m"
# define B_YELLOW    "\033[1;33m"
# define B_GREEN     "\033[1;32m"
# define B_CYAN      "\033[1;36m"
# define B_BLUE      "\033[1;34m"
# define B_PURPLE    "\033[1;35m"

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

    template < class T1, class T2 >
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return ft::pair<T1, T2>(x, y);
    }
    // ============================================================================


    // =============================== ENABLE IF ==================================

    template < bool B, class T = void >
    struct enable_if {};

    template < class T >
    struct enable_if < true, T > { typedef T type; };

    // ============================================================================


    // ================================== EQUAL ===================================
    template <class InputT1, class InputT2>
    bool equal(InputT1 first1, InputT1 last1, InputT2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
            if (*first1 != *first2)
                return false;
        return true;
    }
    // ============================================================================


    // ======================== LEXICOGRAPHICAL COMPARE ===========================
    template <class InputT1, class InputT2>
    bool lexicographical_compare(InputT1 first1, InputT1 last1, InputT2 first2, InputT2 last2)
    {
        for (; first1 != last1 and first2 != last2; ++first1, ++last2)
        {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) and (first2 != last2);
    }

    template <class InputT1, class InputT2, class Compare>
    bool lexicographical_compare(InputT1 first1, InputT1 last1, InputT2 first2, InputT2 last2, Compare comp)
    {
        for (; first1 != last1 and first2 != last2; ++first1, ++last2)
        {
            if (comp(*first1, *first2)) return true;
            if (comp(*first2, *first1)) return false;
        }
        return (first1 == last1) and (first2 != last2);
    }
    // ============================================================================
}

#endif