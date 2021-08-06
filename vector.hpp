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

        allocator_type alloc;

    public:

        // ==================== COPLIEN ====================
        vector() : _box(NULL), _size(0), _capacity(0) {}


        vector(vector const &other) { *this = other; }

        vector(size_t const newSize)
        {
            this->_box = alloc.allocate(newSize);
            this->_size = newSize;
            this->_capacity = newSize;
            for (size_t i(0); i < this->size(); i++)
                alloc.construct(this->_box + i, value_type());
        }

        ~vector()
        {
            if (this->_size)
            {
                for (size_t i(0); i < this->_size; i++)
                    if (this->_box)
                        alloc.destroy(this->_box + i);
                alloc.deallocate(this->_box, this->_size);
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
                        alloc.destroy(this->_box + i);
                alloc.deallocate(this->_box, this->_size);
            }

            this->_box = alloc.allocate(other._size());
            for (size_t i(0); i < other._size(); i++)
                alloc.construct(this->_box + i, other[i]);
            this->_size = other._size;
            this->_capacity = other._capacity;

            return *this;
        }

        // =================================================

        size_type size() { return this->_size; }

        reference &operator[](size_type n) { return this->_box[n]; }

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
            if (n > this->_size)
            {
                std::cout << val << std::endl;
            }
        }



    };
}

#endif