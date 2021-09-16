#ifndef ALLOCATOR_HPP
# define ALLOCATOR_HPP

namespace ft
{
    template < class T >
    class allocator
    {
        public:
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef const T* const_pointer;
            typedef const T& const_reference;
            typedef size_t size_type;
            typedef std::ptrdiff_t difference_type;

            // default constructor
            allocator() throw() {}

            allocator(allocator const &alloc) throw() { (void)alloc; }

            ~allocator() throw() {}

            // copy constructor
            template < class U >
            allocator(allocator<U> const &alloc) throw() { (void)alloc; }

            // rebind allocator to type U
            template < class U >
            struct rebind { typedef allocator<U> other; };
            
            pointer address(reference value) const { return &value; }

            const_pointer address(const_reference value) const { return &value; }

            size_type max_size() const throw()
            {
                size_type const big(18446744073709551615U);
                return big / sizeof(value_type);
            }

            pointer allocate(size_type n)
            {
                pointer ret;

                // allocate memory with global new
                ret = (pointer)(::operator new(n * sizeof(value_type)));
                return ret;
            }

            void deallocate(pointer p, size_type n)
            {
                // deallocate memory with global delete
                (void)n;
                ::operator delete((void *)p);
            }

            void construct(pointer p, const_reference value)
            {
                // initialize memory with placement new
                (void)value;
                new ((void *)p) value_type(value);
            }

            void destroy(pointer p)
            {
                // destroy objects by calling their destructor
                p->~value_type();
            }

    };
}

#endif