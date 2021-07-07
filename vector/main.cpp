// #include "vector.hpp"

#include <iostream>
#include <vector>

template<typename T>
class Vector
{
public:
    typedef T typeValue;

private:
    T *_arr;
    size_t _sz;
    size_t _cap;

public:

    // ------------------------------------------
    // Vector() : _arr(nullptr), _sz(0), _cap(0) {}

    // virtual ~Vector() {}

    // Vector &operator = (const Vector &other)
    // {
    //     if (this == &other)
    //         return *this;
    //     this->_arr = other._arr;
    //     this->_sz = other._sz;
    //     this->_cap = other._cap;
    //     return *this;
    // }

    Vector() : _sz(0), _cap(0) { this->_arr = new T[0]; }

    virtual ~Vector() { delete[] this->_arr; }

    Vector(Vector const &other) { *this = other; }

    Vector &operator = (Vector const &other)
    {
        if (this == &other)
            return *this;
        delete[] this->_arr;
        this->_arr = other._arr;
        this->_sz = other._sz;
        this->_cap = other._cap;
        return *this;
    }
    // ------------------------------------------

    size_t size() const { return this->_sz; }
    size_t capacity() const { return this->_cap; }

    void assign(size_t count, typeValue const &value = typeValue())
    {
        this->_sz = count;
        this->_cap = count * 2;
        delete[] this->_arr;
        this->_arr = new typeValue[this->_cap];
        for (size_t i(0); i < count; i++)
            this->_arr[i] = value;
    }

    typeValue &operator [] (size_t const count) { return this->_arr[count]; }

    typeValue &at(size_t const count) const
    {
        if (count < this->_sz)
            return this->_arr[count];
        throw std::runtime_error("wrong indexing");
    }

    void resize(size_t count, typeValue const &value = typeValue())
    {
        this->_cap = count * 2;
        typeValue *newArr = new typeValue[this->_cap];
        if (count < this->_sz)
        {
            for (size_t i(0); i < count; i++)
                newArr[i] = this->_arr[i];
        }
        else
        {
            for (size_t i(0); i < this->_sz; i++)
                newArr[i] = this->_arr[i];
            for (size_t i(this->_sz); i < count; i++)
                newArr[i] = value;
        }
        delete[] this->_arr;
        this->_arr = newArr;
        this->_sz = count;
    }

    void reserve(size_t newCap)
    {
        if (newCap < this->_cap) return;
        typeValue *newArr = new typeValue[newCap];
        for (size_t i(0); i < this->_sz; i++)
            newArr[i] = this->_arr[i];
        delete[] this->_arr;
        this->_arr = newArr;
        this->_cap = newCap;
    }

    void push_back(const T &value)
    {
        if (value == NULL) return;
        if (this->_sz == this->_cap)
            reserve(this->_cap * 2);
        this->_arr[this->_sz] = value;
        this->_sz++;
    }

    // ----------------- iterators -----------------

    class iterator
    {
        private:
            typeValue *_ptr;
        
        public:
            iterator() : _ptr(NULL) {}
            ~iterator() { this->_ptr = NULL; }
            iterator(iterator const &other) { *this = other; }
            iterator(typeValue *value) { this->_ptr = value; }

            iterator &operator = (iterator const &other) { this->_ptr = other._ptr; return *this; }
            iterator &operator ++ () { return iterator(++this->_ptr); }
            iterator &operator -- () { return iterator(--this->_ptr); }
            bool operator == (iterator const &other) { return this->_ptr == other._ptr; }
            bool operator <= (iterator const &other) { return this->_ptr <= other._ptr; }
            bool operator >= (iterator const &other) { return this->_ptr >= other._ptr; }
            bool operator > (iterator const &other) { return this->_ptr > other._ptr; }
            bool operator < (iterator const &other) { return this->_ptr < other._ptr; }
            bool operator != (iterator const &other) { return this->_ptr != other._ptr; }
            typeValue &operator * () { return *this->_ptr; }
    };

    iterator begin() { return iterator(&this->_arr[0]); }
    iterator end() { return iterator(&this->_arr[this->_sz + 1]); }

};

void foo(void)
{
    try
    {
        // std::vector<int> vec;

        // vec.push_back(1);
        // vec.push_back(1);
        // vec.push_back(1);
        // vec.push_back(1);
        // vec.push_back(1);
        // vec.push_back(1);

        // std::cout << vec.at(0) << std::endl;

        // vec.clear();

        // my vector
        Vector<std::string> box;
        Vector<std::string>::iterator iter;

        box.assign(3, "zzz...");

        box.resize(4, "> x <");
        box.reserve(10);

        iter = box.begin();
        iter++;
        iter++;
        iter++;
        std::cout << (iter != box.end()) << std::endl;
        // while (iter != box.end())
        //     std::cout << *iter << std::endl;

        // box.push_back("world");
        // std::cout << box.at(3) << std::endl;
        // for (size_t i(0); i < box.size(); ++i)
        //     std::cout << box[i] << std::endl;
        std::cout << box.size() << ' ' << box.capacity() << std::endl;

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
