// #include "vector.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <exception>

namespace ft
{
    template<
        typename T,
        typename Allocator = std::allocator<T>
    > class vector
    {
    public:
        typedef T typeValue;
        typedef size_t size_type;

    private:
        T *_arr;
        Allocator _alloc;
        size_t _sz;
        size_t _cap;

    public:
        vector(Allocator const &al = Allocator()) : _arr(0), _alloc(al), _sz(0), _cap(0) {}
        ~vector() {}
        vector(vector const &other) { *this = other; }
        vector &operator = (vector const &other)
        {
            if (this == &other)
                return *this;
            this->_arr = other._arr;
            this->_alloc = other._alloc;
            this->_sz = other._sz;
            this->_cap = other._cap;
            return *this;
        }

        size_type max_size() const
        {
            // unsigned long bignum = 18446744073709551615U;
            // return bignum / sizeof(typeValue);
            return this->_alloc.max_size();
        }

        void reserve(size_type count)
        {
            std::cout << "max size: " << max_size() << '\n';
            if (count < this->_cap)
                return;
            else if (count > max_size())
                throw std::length_error("too big size than possible size of buffer");
            this->_arr = this->_alloc.allocate(count);
            this->_cap = count;
        }

/*

Resizes the container to contain count elements.
If the current size is greater than count, the container is reduced to its first count elements.
If the current size is less than count,
    1) additional default-inserted elements are appended
    2) additional copies of value are appended.

*/
        void resize(size_type count)
        {
            if (this->_cap > count)
            {
                typeValue *temp = this->_arr;
                reserve(count);
                for (size_t i(0); i < this->_sz; i++)
                    this->_alloc.construct(this->_arr + i, *(temp + i));
                for (size_t i(0); i < this->_sz; i++)
                    this->_alloc.destroy(temp + i);
                this->_alloc.deallocate(temp, this->_sz);
            }
            else
            {
                typeValue *temp = this->_arr;
                reserve(count);
                for (size_t i(0); i > count; i++)
                    this->_alloc.construct(this->_arr + i, *(temp + i));
                for (size_t i(0); i < count; i++)
                    this->_alloc.destroy(temp + i);
                this->_alloc.deallocate(temp, this->_sz);
                this->_sz = count;
            }
        }

    };
}


void foo(void)
{
    try
    {
        std::cout << "<====================>" << std::endl;
        ft::vector<std::string> box;
        // ft::vector<int> box2;
        std::vector<std::string> vec;

        // box.reserve(20);
        box.resize(10);
        

        // box2 = box;

        // box2.reserve(3);

        std::cout << "<====================>" << std::endl;

    }
    catch(const std::exception& e) { std::cerr << e.what() << '\n'; }

    return;
}

int main(void)
{
    foo();

    // while (1);

    return 0;
}
