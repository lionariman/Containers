#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>

namespace ft
{
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

    private:
        value_type *_box;
        size_type _size;
        size_type _capacity;

        allocator_type _alloc;

    public:

        // ==================== COPLIEN ====================

        // default
        explicit vector(allocator_type const &alloc = allocator_type()) :
            _box(0), _size(0), _capacity(0), _alloc(alloc) {}

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

        // =================================================

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
            if (n < this->_size)
            {
                for (; this->_size > n; this->_size--)
                    this->_alloc.destroy(this->_box + this->_size);
                return ;
            }
            if (n > this->_size)
            {
                if (n > this->_capacity)
                {
                    value_type *tmp;

                    this->_capacity = (this->_capacity ? this->_capacity * 2 : n);
                    tmp = this->_alloc.allocate(this->_capacity);
                    for (size_type i(0); i < this->_size; i++)
                    {
                        this->_alloc.construct(tmp + i, *(this->_box + i));
                        this->_alloc.destroy(this->_box + i);
                    }
                    this->_alloc.deallocate(this->_box, this->_capacity / 2);
                    this->_box = tmp;
                    for (; this->_size < n; this->_size++)
                        this->_alloc.construct(this->_box + this->_size, val);
                    return ;
                }
                this->_size = n;
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


    };
}

#endif