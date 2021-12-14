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

            // default
            allocator() throw() {}

            allocator(allocator const &alloc) throw() { static_cast<void>(alloc); }

            ~allocator() throw() {}

            // copy
            template < class U >
            allocator(allocator<U> const &alloc) throw() { static_cast<void>(alloc); }

            // rebind allocator to type U
            template < class U >
            struct rebind { typedef allocator<U> other; };
            
            pointer address(reference value) const { return &value; }

            const_pointer address(const_reference value) const { return &value; }

            size_type max_size() const throw()
            {
                size_type const big(18446744073709551615U);
                return (big / sizeof(value_type));
            }

            pointer allocate(size_type n)
            {
                pointer ret;

                // allocate memory with global new
                ret = reinterpret_cast<pointer>(::operator new(n * sizeof(value_type)));
                return ret;
            }

            void deallocate(pointer p, size_type n)
            {
                static_cast<void>(n);

                // deallocate memory with global delete
                ::operator delete(static_cast<void *>(p));
            }

            void construct(pointer p, const_reference value)
            {
                static_cast<void>(value);
                new (reinterpret_cast<void *>(p)) value_type(value);
            }

            void destroy(pointer p)
            {
                // destroy objects by calling their destructor
                p->~value_type();
            }
    };
}

#endif