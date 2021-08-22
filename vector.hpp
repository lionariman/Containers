#ifndef VECTOR_HPP
# define VECTOR_HPP

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

# include <iostream>
# include <memory>

# include "allocator.hpp"

namespace ft
{
    template < bool B, class T = void >
    struct enable_if {};

    template < class T >
    struct enable_if < true, T > { typedef T type; };

    template < class T >
    class vector_iterator
    {
        public:
            typedef T value_type;
            typedef size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef T* pointer;
            typedef T& reference;
            typedef std::random_access_iterator_tag iterator_category;

            typedef vector_iterator<value_type> iterator;
        private:
            pointer _ptr;
        
        public:
            vector_iterator() : _ptr(NULL) {}
            vector_iterator(vector_iterator const &other) { *this = other; }
            vector_iterator(pointer ptr) : _ptr(ptr) {}
            ~vector_iterator() { this->_ptr = NULL; }

            iterator &operator=(iterator const &other) { this->_ptr = other._ptr; return *this; }

            reference       operator*() const                   { return *this->_ptr; }
            pointer         operator->() const                  { return this->_ptr; }
            reference       operator[](difference_type &n)      { return this->_ptr[n]; }
            
            iterator        &operator++()                       { this->_ptr++; return *this; }
            iterator        &operator--()                       { this->_ptr--; return *this; }
            iterator        operator++(int)                     { return this->_ptr++; }
            iterator        operator--(int)                     { return this->_ptr--; }
            iterator        operator+(int v) const              { return this->_ptr + v; }
            iterator        operator+(size_type v) const        { return this->_ptr + v; }
            iterator        operator+(difference_type v) const  { return this->_ptr + v; }
            difference_type operator+(iterator &other) const    { return this->_ptr + other._ptr; }
            iterator        operator-(int v) const              { return this->_ptr - v; }
            iterator        operator-(size_type v) const        { return this->_ptr - v; }
            iterator        operator-(difference_type v) const  { return this->_ptr - v; }
            difference_type operator-(iterator &other) const    { return this->_ptr - other._ptr; }
            iterator        &operator+=(difference_type &ptr)   { this->_ptr += ptr; return *this; }
            iterator        &operator-=(difference_type &ptr)   { this->_ptr -= ptr; return *this; }

            bool            operator==(iterator const &v) const { return this->_ptr == v._ptr; }
            bool            operator!=(iterator const &v) const { return this->_ptr != v._ptr; }
            bool            operator<(iterator const &v) const  { return this->_ptr < v._ptr; }
            bool            operator>(iterator const &v) const  { return this->_ptr > v._ptr; }
            bool            operator<=(iterator const &v) const { return this->_ptr <= v._ptr; }
            bool            operator>=(iterator const &v) const { return this->_ptr >= v._ptr; }
    };

    template< class T >
    class vector_reverse_iterator
    {
        public:
            typedef T value_type;
            typedef size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef T* pointer;
            typedef T& reference;
            typedef std::random_access_iterator_tag iterator_category;

            typedef vector_reverse_iterator<value_type> iterator;

        private:
            pointer _ptr;

        public:
            vector_reverse_iterator() : _ptr(NULL) {}
            vector_reverse_iterator(vector_reverse_iterator const &other) { *this = other; }
            vector_reverse_iterator(pointer ptr) : _ptr(ptr) {}
            ~vector_reverse_iterator() { this->_ptr = NULL; }
            
            iterator        &operator=(iterator const &other) { this->_ptr = other._ptr; return *this; }

            reference       operator*() const { return *this->_ptr; }
            pointer         operator->() const { return this->_ptr; }
            reference       operator[](difference_type &n) { return this->_ptr[n]; }

            iterator        &operator++()                       { this->_ptr--; return *this; }
            iterator        &operator--()                       { this->_ptr++; return *this; }
            iterator        operator++(int)                     { return this->_ptr--; }
            iterator        operator--(int)                     { return this->_ptr++; }
            iterator        operator+(int v) const              { return this->_ptr - v; }
            iterator        operator+(size_type v) const        { return this->_ptr - v; }
            iterator        operator+(difference_type v) const  { return this->_ptr - v; }
            difference_type operator+(iterator &other) const    { return this->_ptr - other._ptr; }
            iterator        operator-(int v) const              { return this->_ptr + v; }
            iterator        operator-(size_type v) const        { return this->_ptr + v; }
            iterator        operator-(difference_type v) const  { return this->_ptr + v; }
            difference_type operator-(iterator &other) const    { return this->_ptr + other._ptr; }
            iterator        &operator+=(difference_type &ptr)   { this->_ptr -= ptr; return *this; }
            iterator        &operator-=(difference_type &ptr)   { this->_ptr += ptr; return *this; }

            bool            operator==(iterator const &v) const { return this->_ptr == v._ptr; }
            bool            operator!=(iterator const &v) const { return this->_ptr != v._ptr; }
            bool            operator<(iterator const &v) const  { return this->_ptr < v._ptr; }
            bool            operator>(iterator const &v) const  { return this->_ptr > v._ptr; }
            bool            operator<=(iterator const &v) const { return this->_ptr <= v._ptr; }
            bool            operator>=(iterator const &v) const { return this->_ptr >= v._ptr; }
    };

    template <
        class T,
        class Allocator = std::allocator<T>
    >
    class vector
    {
    public:
        typedef typename std::size_t size_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::vector_iterator<value_type> iterator;
        typedef ft::vector_iterator<const value_type> const_iterator;
        typedef ft::vector_reverse_iterator<value_type> reverse_iterator;
        typedef ft::vector_reverse_iterator<const value_type> const_reverse_iterator;
        

    private:
        difference_type distance(iterator first, iterator last)
        {
            difference_type i = 0;
            if (*first == 0 && *last == 0)
                return 0;
            for (; first != last; first++, i++) ;
            return i;
        }

    private:
        value_type *_box;
        size_type _size, _capacity;
        allocator_type _alloc;

    public:
        // default
        explicit vector(allocator_type const &alloc = allocator_type()) :
            _box(0), _size(0), _capacity(0), _alloc(alloc) {}

        // fill
        explicit vector(size_type n, value_type const &val = value_type(),
                        allocator_type const &alloc = allocator_type()) :
            _box(0), _size(0), _capacity(0), _alloc(alloc)
        {
            this->_box = this->_alloc.allocate(n);
            this->_size = n;
            this->_capacity = n;
            for (size_t i(0); i < this->size(); i++)
                this->_alloc.construct(this->_box + i, val);
        }

        // range
        template < class InputIterator >
        vector(InputIterator first, InputIterator last,
               allocator_type const &alloc = allocator_type()) :
            _box(0), _size(0), _capacity(0), _alloc(alloc)
        {
            difference_type p = last - first;
            if (p < 0)
                throw std::out_of_range("vector");
            this->_capacity = static_cast<size_type>(p);
            this->_box = this->_alloc.allocate(this->_capacity);
            for (; first != last; first++, this->_size++)
                this->_alloc.construct(this->_box + this->_size, *first);
        }

        // copy
        vector(vector const &x) { *this = x; }

        ~vector()
        {
            if (this->_box)
                clear();
            this->_alloc.deallocate(this->_box, this->_size);
            this->_capacity = 0;
            this->_size = 0;
        }

        vector &operator=(vector const &x)
        {
            if (this == &x)
                return *this;
            if (this->_size)
            {
                clear();
                this->_alloc.deallocate(this->_box, this->_capacity);
            }
            this->_box = this->_alloc.allocate(x.size());
            for (size_t i(0); i < x.size(); i++)
                this->_alloc.construct(this->_box + i, x.at(i));
            this->_size = x.size();
            this->_capacity = x.capacity();

            return *this;
        }

        size_type size() const { return this->_size; }
        size_type capacity() const { return this->_capacity; }
        reference &operator[](size_type n) { return *(this->_box + n); }

        reference front() { return *this->_box; }
        reference back() { return *(this->_box + this->_size - 1); }
        const_reference front() const { return *this->_box; }
        const_reference back() const { return *(this->_box + this->_size - 1); }

        iterator begin() { return this->_box; }
        iterator end() { return this->_box + this->_size; }
        reverse_iterator rbegin() { return this->_box + this->_size - 1; }
        reverse_iterator rend() { return this->_box - 1; }

        const_iterator cbegin() const { return this->_box; }
        const_iterator cend() const { return this->_box + this->_size; }

        bool empty() const { return this->_size; }

        void clear()
        {
            if (this->_size == 0)
                return ;
            for (; this->_size != 0; this->_size--)
                this->_alloc.destroy(this->_box + this->_size);
        }

        reference at(size_type n)
        {
            if (n >= this->_size)
                throw std::out_of_range("\nIndex out of range\nFunction: at");
            return this->_box[n];
        }

        const_reference at(size_type n) const
        {
            if (n >= this->_size)
                throw std::out_of_range("\nIndex out of range\nFunction: at");
            return this->_box[n];
        }

        size_type max_size() const
        {
            size_type const big(18446744073709551615U);
            return big / sizeof(value_type);
        }

        void reserve(size_type n)
        {
            if (n <= this->_capacity)
                return ;

            value_type *tmp = this->_alloc.allocate(n);
            for (size_type i(0); i < this->_size; i++)
            {
                this->_alloc.construct(tmp + i, *(this->_box + i));
                this->_alloc.destroy(this->_box + i);
            }
            this->_alloc.deallocate(this->_box, this->_capacity);
            this->_box = tmp;
            this->_capacity = n;
        }

        void resize(size_type n, value_type val = value_type())
        {
            if (this->_capacity == 0)
            {
                reserve(n);
                this->_capacity = n;
            }
            if (n > this->_capacity)
                reserve(this->_capacity * 2);
            for (; this->_size < n; this->_size++)
                this->_alloc.construct(this->_box + this->_size, val);
            if (n < this->_size)
            {
                for (; this->_size > n; this->_size--)
                    this->_alloc.destroy(this->_box + this->_size);
            }
        }

        void push_back(value_type const &val)
        {
            if (this->_capacity == 0 && this->_size == 0)
            {
                reserve(1);
                this->_alloc.construct(this->_box, val);
                this->_size++;
                return ;
            }
            if (this->_capacity == this->_size)
                reserve(2 * this->_capacity);
            this->_alloc.construct(this->_box + this->_size, val);
            this->_size++;
        }

        void pop_back()
        {
            if (this->_size == 0)
                return ;
            this->_alloc.destroy(this->_box + this->_size);
            this->_size--;
        }

        void assign(size_type n, value_type const &val)
        {
            clear();
            if (n < this->_capacity)
            {
                for (; this->_size < n; this->_size++)
                    this->_alloc.construct(this->_box + this->_size, val);
                return ;
            }
            resize(n, val);
        }

        template < class InputIterator >
        void assign(InputIterator first, InputIterator last,
        typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0)
        {
            difference_type n = distance(first, last);
            if (n == 0)
                return ;
            if (n < 0)
                throw std::out_of_range("vector");
            clear();
            if (static_cast<size_type>(n) > this->_capacity)
            {
                this->_alloc.deallocate(this->_box, this->_capacity);
                this->_box = this->_alloc.allocate(static_cast<size_type>(n));
                this->_capacity = static_cast<size_type>(n);
            }
            for (; first != last; first++, this->_size++)
                this->_alloc.construct(this->_box + this->_size, *first);
        }

        iterator insert(iterator position, value_type const &val)
        {
            if (this->_size + 1 > this->_capacity)
            {
                value_type *tmp = this->_alloc.allocate(this->_capacity * 2);
                for (size_type i(0); i < this->_size; i++)
                {
                    this->_alloc.construct(tmp + i, *(this->_box + i));
                    this->_alloc.destroy(this->_box + i);
                }
                this->_alloc.deallocate(this->_box, this->_capacity);
                this->_box = tmp;
                this->_capacity *= 2;
            }
            difference_type p = position - begin();
            for (size_type i = this->_size - 1; i != static_cast<size_type>(p) - 1; i--)
            {
                this->_alloc.construct(this->_box + i + 1, *(this->_box + i));
                this->_alloc.destroy(this->_box + i);
            }
            this->_alloc.construct(this->_box + static_cast<size_type>(p), val);
            this->_size++;
            return this->_box + static_cast<size_type>(p);
        }

        void insert(iterator position, size_type n, value_type const &val)
        {
            if (this->_size + n > this->_capacity)
            {
                value_type *tmp = this->_alloc.allocate(this->_size + n);
                for (size_type i(0); i < this->_size; i++)
                {
                    this->_alloc.construct(tmp + i, *(this->_box + i));
                    this->_alloc.destroy(this->_box + i);
                }
                this->_alloc.deallocate(this->_box, this->_capacity);
                this->_box = tmp;
                this->_capacity = this->_size + n;
            }
            difference_type p = distance(begin(), position);
            for (size_type i = this->_size - 1; i != static_cast<size_type>(p) - 1; i--)
            {
                this->_alloc.construct(this->_box + i + n, *(this->_box + i));
                this->_alloc.destroy(this->_box + i);
            }
            for (size_type i = static_cast<size_type>(p); i < static_cast<value_type>(p) + n; i++)
                this->_alloc.construct(this->_box + i, val);
            this->_size += n;
        }

        template < class InputIterator >
        void insert(iterator position, InputIterator first, InputIterator last,
        typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0)
        {
            difference_type p = last - first;
            if (p == 0 || p < 0)
                return ;
            if (this->_size + static_cast<size_type>(p) > this->_capacity)
            {
                value_type *tmp = this->_alloc.allocate(this->_capacity * 2);
                for (size_type i(0); i < this->_size; i++)
                {
                    this->_alloc.construct(tmp + i, *(this->_box + i));
                    this->_alloc.destroy(this->_box + i);
                }
                this->_alloc.deallocate(this->_box, this->_capacity);
                this->_box = tmp;
                this->_capacity *= 2;
            }
            difference_type pos = distance(begin(), position);
            for (size_type i = this->_size - 1; i != static_cast<size_type>(pos) - 1; i--)
            {
                this->_alloc.construct(this->_box + i + static_cast<size_type>(p), *(this->_box + i));
                this->_alloc.destroy(this->_box + i);
            }
            for (size_type i = static_cast<size_type>(pos);
            first != last && i != this->_capacity + 1; first++, i++)
                this->_alloc.construct(this->_box + i, *first);
            this->_size += static_cast<size_type>(p);
        }

        iterator erase(iterator position)
        {
            difference_type p = distance(begin(), position);
            if (p < 0) p = 0;
            this->_alloc.destroy(this->_box + static_cast<size_type>(p));
            for (size_type i = static_cast<size_type>(p); i < this->_size; i++)
            {
                this->_alloc.construct(this->_box + i, *(this->_box + i + 1));
                this->_alloc.destroy(this->_box + i + 1);
            }
            this->_size--;
            return this->_box + static_cast<size_type>(p);
        }

        iterator erase(iterator first, iterator last)
        {
            difference_type ps = distance(begin(), first);
            difference_type ds = distance(first, last);
            if (ps < 0) ps = 0;
            for (size_type i = static_cast<size_type>(ps); first != last; first++, i++)
                this->_alloc.destroy(this->_box + i);
            for (size_type i = static_cast<size_type>(ps); i < this->_size; i++)
            {
                this->_alloc.construct(this->_box + i, *(this->_box + i + static_cast<size_type>(ds)));
                this->_alloc.destroy(this->_box + i + static_cast<size_type>(ds));
            }
            this->_size -= static_cast<size_type>(ds);
            return this->_box + static_cast<size_type>(ps);
        }

        void swap(vector &x)
        {
            value_type *tmp_box = this->_box;
            size_type tmp_size = this->_size;
            size_type tmp_capacity = this->_capacity;
            this->_box = x._box;
            this->_size = x._size;
            this->_capacity = x._capacity;
            x._box = tmp_box;
            x._size = tmp_size;
            x._capacity = tmp_capacity;
        }
    };

    template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T, Alloc>::const_iterator it1 = lhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite1 = lhs.cend();
		typename ft::vector<T, Alloc>::const_iterator it2 = rhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite2 = rhs.cend();
		while (it1 != ite1)
		{
			if (*it1 != *it2)
				return (false);
			++it1;
			++it2;
		}
		return (true);
	}

    template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() == rhs.size())
			return (false);
		typename ft::vector<T, Alloc>::const_iterator it1 = lhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite1 = lhs.cend();
		typename ft::vector<T, Alloc>::const_iterator it2 = rhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite2 = rhs.cend();
		while (it1 != ite1)
		{
			if (*it1 == *it2)
				return (false);
			++it1;
			++it2;
		}
		return (true);
	}

    template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T, Alloc>::const_iterator it1 = lhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite1 = lhs.cend();
		typename ft::vector<T, Alloc>::const_iterator it2 = rhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite2 = rhs.cend();
		while (it1 != ite1)
		{
			if (*it1 >= *it2)
				return (false);
			++it1;
			++it2;
		}
		return (true);
	}

    template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T, Alloc>::const_iterator it1 = lhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite1 = lhs.cend();
		typename ft::vector<T, Alloc>::const_iterator it2 = rhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite2 = rhs.cend();
		while (it1 != ite1)
		{
			if (*it1 <= *it2)
				return (false);
			++it1;
			++it2;
		}
		return (true);
	}

    template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T, Alloc>::const_iterator it1 = lhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite1 = lhs.cend();
		typename ft::vector<T, Alloc>::const_iterator it2 = rhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite2 = rhs.cend();
		while (it1 != ite1)
		{
			if (*it1 > *it2)
				return (false);
			++it1;
			++it2;
		}
		return (true);
	}

    template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T, Alloc>::const_iterator it1 = lhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite1 = lhs.cend();
		typename ft::vector<T, Alloc>::const_iterator it2 = rhs.cbegin();
		typename ft::vector<T, Alloc>::const_iterator ite2 = rhs.cend();
		while (it1 != ite1)
		{
			if (*it1 < *it2)
				return (false);
			++it1;
			++it2;
		}
		return (true);
	}

    template < class T, class Alloc >
    void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y) { x.swap(y); }
}

#endif