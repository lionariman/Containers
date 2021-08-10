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
# include <iterator>

namespace ft
{

    // ============================== ITERATOR =================================

    template < class T >
    class vector_iterator
    {
        public:
            typedef T value_type;
            typedef size_t size_type;
            // typedef std::ptrdiff_t difference_type;
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

            vector_iterator &operator=(vector_iterator const &other)
            {
                this->_ptr = other._ptr;
                return *this;
            }

            iterator        operator++()                        { this->_ptr++; return *this; } //prefix
            iterator        operator--()                        { this->_ptr--; return *this; } //prefix
            iterator        operator++(int)                     { return this->_ptr++; } // postfix
            iterator        operator--(int)                     { return this->_ptr--; } // postfix

            reference       operator*() const                   { return *this->_ptr; }
            pointer         operator->() const                  { return this->_ptr; }

            iterator        operator+(size_type v) const        { return this->_ptr + v; }
            // iterator        operator+(difference_type v) const  { return this->_ptr + v; }
            // difference_type operator+(iterator &other) const    { return this->_ptr + other._ptr; }

            iterator        operator-(size_type v) const        { return this->_ptr - v; }
            // iterator        operator-(difference_type v) const  { return this->_ptr - v; }
            // difference_type operator-(iterator &other) const    { return this->_ptr - other._ptr; }

            bool            operator==(iterator const &v) const { return this->_ptr == v._ptr; }
            bool            operator!=(iterator const &v) const { return this->_ptr != v._ptr; }
            bool            operator<(iterator const &v) const  { return this->_ptr < v._ptr; }
            bool            operator>(iterator const &v) const  { return this->_ptr > v._ptr; }
            bool            operator<=(iterator const &v) const { return this->_ptr <= v._ptr; }
            bool            operator>=(iterator const &v) const { return this->_ptr >= v._ptr; }
    };

    // =========================================================================







    // =============================== VECTOR ==================================

    template <
        class T,
        class Allocator = std::allocator<T>
    >
    class vector
    {
    public:
        typedef size_t size_type;
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef vector_iterator<value_type> iterator;

    private:
        value_type *_box;
        size_type _size;
        size_type _capacity;
        size_type _count;

        allocator_type _alloc;


    public:

        // ==================== COPLIEN ====================

        // default
        explicit vector(allocator_type const &alloc = allocator_type()) :
            _box(0), _size(0), _capacity(0), _count(0), _alloc(alloc) {}

        // fill
        // explicit vector(size_type n,
        //                 value_type const &val = value_type(),
        //                 allocator_type const &alloc = allocator_type())
        // {
        //     this->_box = this->_alloc.allocate(n);
        //     this->_size = n;
        //     this->_capacity = n;
        //     for (size_t i(0); i < this->size(); i++)
        //         this->_alloc.construct(this->_box + i, val);
        // }

        // range
        // template < class InputIterator >
        // vector(InputIterator first,
        //        InputIterator last,
        //        allocator_type const &alloc = allocator_type()) {}

        // copy
        vector(vector const &other) { *this = other; }

        vector(size_type n)
        {
            this->_box = this->_alloc.allocate(n);
            this->_size = n;
            this->_capacity = n;
            for (size_t i(0); i < this->size(); i++)
                this->_alloc.construct(this->_box + i, value_type());
        }

        ~vector()
        {
            if (this->_capacity)
            {
                for (size_t i(0); i < this->_size; i++)
                    if (this->_box)
                        this->_alloc.destroy(this->_box + i);
                this->_alloc.deallocate(this->_box, this->_size);
            }
        }

        vector &operator=(vector const &other)
        {
            if (this == &other)
                return *this;

            if (this->_size)
            {
                for (size_t i(0); i < this->_size; i++)
                    if (this->_box)
                        this->_alloc.destroy(this->_box + i);
                this->_alloc.deallocate(this->_box, this->_size);
            }

            this->_box = this->_alloc.allocate(other._size());
            for (size_t i(0); i < other._size(); i++)
                this->_alloc.construct(this->_box + i, other[i]);
            this->_size = other._size;
            this->_capacity = other._capacity;

            return *this;
        }

        size_type size() { return this->_size; }

        size_type capacity() { return this->_capacity; }

        reference &operator[](size_type n) { return this->_box[n]; }
        
        reference front() { return this->_box[0]; }

        reference back() { return this->_box[this->_size]; }

        bool empty() const { return this->_size; }

        reference at(size_type n)
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

        void resize(size_type n, value_type val = value_type())
        {
            // if (this->_size == 0 && this->_capacity == 0)
            // {
            //     this->_box = this->_alloc.allocate(1);
            //     this->_alloc.construct(this->_box, val);
            //     this->_capacity++;
            //     this->_size++;
            // }
            if (n < this->_size)
            {
                for (; this->_size > n; this->_size--)
                    this->_alloc.destroy(this->_box + this->_size);
            }
            else if (n > this->_capacity)
            {
                value_type *temp;
                temp = this->_alloc.allocate(n);
                for (size_type i(0); i < this->_size; i++)
                {
                    this->_alloc.construct(temp + i, *(this->_box + i));
                    this->_alloc.destroy(this->_box + i);
                }
                this->_alloc.deallocate(this->_box, this->_capacity);
                this->_box = temp;
                for (; this->_size < n - 1; this->_size++)
                    this->_alloc.construct(this->_box + this->_size, val);
                this->_capacity = (this->_capacity ? this->_capacity * 2 : n);
                this->_size = (this->_size ? this->_size + 1 : n);
            }
            else if (n >= this->_size)
            {
                for (; this->_size < n; this->_size++)
                    this->_alloc.construct(this->_box + this->_size, val);
            }
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

        iterator begin() { return this->_box; }
        iterator end() { return this->_box + this->_size; }

        void push_back(value_type const &val)
        {
            resize(++this->_count, val);
            *(this->_box + this->_count - 1) = val;
            // this->_count++;
            // this->_size++
        }




    };

    // =========================================================================
}

#endif