// #include "vector.hpp"

#include <iostream>
#include <vector>
#include <memory>

namespace ft
{
    template<
        typename T,
        typename Allocator = std::allocator<T>
    > class vector
    {
    public:
        typedef T typeValue;

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

        void reserve(size_t n)
        {
            this->_cap = n;
            this->_arr = this->_alloc.allocate(this->_cap);
            std::cout << ">> array has been alocated by allocator <<" << std::endl;
            this->_alloc.deallocate(this->_arr, this->_cap);
            std::cout << ">> array has been dealocated by allocator <<" << std::endl;
        }

    };
}


void foo(void)
{
    try
    {
        std::cout << "<====================>" << std::endl;
        ft::vector<std::string> box;
        ft::vector<std::string> box2;

        box.reserve(5);

        box2 = box;

        box2.reserve(3);

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
