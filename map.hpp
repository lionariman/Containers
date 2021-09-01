#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <iterator>

# include "allocator.hpp"
# include "class_pair_and_functors.hpp"

# define nl std::cout<<'\n'

namespace ft
{
    // ================================ ITERATORS =================================

    template < class U >
    struct Node
    {
        U *data;
        Node *parent;
        Node *right;
        Node *left;
        int height;
    };
    
    template < class T >
    class map_iterator
    {
        public:
            typedef Node<T> *pointer;
            typedef Node<T> &reference;
            typedef std::bidirectional_iterator_tag iterator_category;

        private:
            pointer _ptr;

        public:
            map_iterator(pointer ptr = pointer()) : _ptr(ptr) {}
            map_iterator(const map_iterator &other) {
                if (this == &other) return ;
                *this = other;
            }
            ~map_iterator() {}

            map_iterator &operator=(const map_iterator &other) {
                _ptr = other._ptr;
                return *this;
            }

            map_iterator &operator++() { getNext(); return *this; }
            map_iterator &operator--() { getPrev(); return *this; }
            map_iterator operator++(int) { map_iterator tmp(*this); operator++(); return tmp; }
            map_iterator operator--(int) { map_iterator tmp(*this); operator--(); return tmp; }

            bool operator==(const map_iterator &rhs) const { return _ptr == rhs._ptr; }
            bool operator!=(const map_iterator &rhs) const { return _ptr != rhs._ptr; }
            T &operator*() { return *_ptr; }
            T *operator->() { return _ptr; }

            pointer getNode() { return _ptr; }
        
        private:
            void getNext() {
                if (_ptr->right) {
                    for (_ptr = _ptr->right; _ptr->left; _ptr = _ptr->left);
                } else {
                    for (; _ptr->parent and _ptr->parent->right == _ptr; _ptr = _ptr->parent);
                    _ptr = _ptr->parent;
                }
            }

            void getPrev() {
                if (_ptr->left) {
                    for (_ptr = _ptr->left; _ptr->right; _ptr = _ptr->right);
                } else {
                    for (; _ptr->parent and _ptr->parent->left == _ptr; _ptr = _ptr->parent);
                    _ptr = _ptr->parent;
                }
            }
    };

    template < class U >
    class map_reverse_iterator
    {
        public:
            typedef Node<U> *pointer;
            typedef Node<U> &reference;
            typedef std::bidirectional_iterator_tag iterator_category;

        private:
            pointer _ptr;

        public:
            map_reverse_iterator(pointer ptr = pointer()) : _ptr(ptr) {}
            map_reverse_iterator(const map_reverse_iterator &other) {
                if (this == &other) return ;
                *this = other;
            }
            ~map_reverse_iterator() {}

            map_reverse_iterator &operator=(const map_reverse_iterator &other) {
                _ptr = other._ptr;
                return *this;
            }

            map_reverse_iterator &operator++() { getPrev(); return *this; }
            map_reverse_iterator &operator--() { getNext(); return *this; }
            map_reverse_iterator operator++(int) { map_reverse_iterator tmp(*this); operator++(); return tmp; }
            map_reverse_iterator operator--(int) { map_reverse_iterator tmp(*this); operator--(); return tmp; }

            bool operator==(const map_reverse_iterator &rhs) const { return _ptr == rhs._ptr; }
            bool operator!=(const map_reverse_iterator &rhs) const { return _ptr != rhs._ptr; }
            U &operator*() { return *_ptr; }
            U *operator->() { return _ptr; }

            pointer getNode() { return _ptr; }

        private:
            void getNext() {
                if (_ptr->right) {
                    for (_ptr = _ptr->right; _ptr->left; _ptr = _ptr->left);
                } else {
                    for (; _ptr->parent and _ptr->parent->right == _ptr; _ptr = _ptr->parent);
                    _ptr = _ptr->parent;
                }
            }

            void getPrev() {
                if (_ptr->left) {
                    for (_ptr = _ptr->left; _ptr->right; _ptr = _ptr->right);
                } else {
                    for (; _ptr->parent and _ptr->parent->left == _ptr; _ptr = _ptr->parent);
                    _ptr = _ptr->parent;
                }
            }
    };

    // ============================================================================




    // =================================== MAP ====================================

    template <
        class Key,
        class T,
        class Compare = ft::less< Key >,
        class Allocator = ft::allocator< std::pair< const Key, T > >
    >
    class map
    {
        public:
            typedef Key                                        key_type;
            typedef T                                          mapped_type;
            typedef std::pair<const key_type, mapped_type>     value_type;
            typedef std::size_t                                size_type;
            typedef std::ptrdiff_t                             difference_type;
            typedef Compare                                    key_compare;
            typedef Allocator                                  allocator_type;
            typedef typename allocator_type::pointer           pointer;
            typedef typename allocator_type::reference         reference;
            typedef typename allocator_type::const_pointer     const_pointer;
            typedef typename allocator_type::const_reference   const_reference;
            typedef ft::map_iterator<value_type>               iterator;
            typedef ft::map_iterator<const value_type>         const_iterator;
            typedef ft::map_reverse_iterator<value_type>       reverse_iterator;
            typedef ft::map_reverse_iterator<const value_type> const_reverse_iterator;

            class value_compare : public ft::binary_function<value_type, value_type, bool> {
                protected:
                    key_compare comp;
                public:
                    explicit value_compare(key_compare c) : comp(c) {}
                    bool operator()(const value_type &__x, const value_type &__y) const {
                        return comp(__x.first, __y.first);
                    }
            };

        private:
            typedef ft::Node<value_type> _node;
            typedef ft::Node<value_type>* _node_pointer;
            typedef ft::Node<value_type>& _node_reference;

            typedef typename allocator_type::template rebind<_node>::other node_allocator;

            _node_pointer     _box;
            _node_pointer     _begin;
            _node_pointer     _end;
            key_compare       _comp;
            size_type         _size;
            allocator_type    _alloc;
            node_allocator    _alloc_node;

            _node_pointer newNode(const value_type &val)
            {
                _node_pointer new_node = _alloc_node.allocate(1);
                new_node->data = &val;
                new_node->parent = nullptr;
                new_node->left = nullptr;
                new_node->right = nullptr;
                new_node->height = 1;
                return new_node;
            }


        public:
            // empty constructor
            explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
                _box(nullptr),
                _comp(comp),
                _size(0),
                _alloc(alloc)
            {
                _box = _alloc_node.allocate(0);
            }

            // range constructor
            // template < class InputIterator >
            // map(InputIterator first, InputIterator last,
            //     const key_compare &comp = key_compare(),
            //     const allocator_type &alloc = allocator_type())
            // {

            // }

            // copy constructor
            map(const map &x) { *this = x; }

            ~map()
            {
                if (_size)
                {
                    clear();
                    _alloc_node.deallocate(_box, _size);
                }
                _size = 0;
            }

            // assignation operator overload
            map &operator=(const map &x)
            {
                if (this == &x) return *this ;
                if (_size)
                {
                    clear();
                    _alloc_node.deallocate(_box, _size);
                }
                _size = x._size;
            }

            void clear()
            {
                _node_pointer tmp = _begin;
                for (; tmp != _end; tmp++)
                    _alloc_node.destroy(tmp);
            }

            iterator begin() { return _begin; }
            const_iterator cbegin() { return _begin; }
            reverse_iterator rbegin() { return _end; }
            const_reverse_iterator crbegin() { return _end; }

            iterator end() { return _end; }
            const_iterator cend() { return _end; }
            reverse_iterator rend() { return _begin; }
            const_reverse_iterator crend() { return _begin; }

            bool empty() const { return _size; }
            size_type size() const { return _size; }
            size_type max_size() const { return _alloc.max_size() / 5; }

            // // single element
            // ft::pair<iterator, bool> insert(const value_type &val)
            // {

            // }

            // // with hint
            // iterator inser(iterator position, const value_type &val)
            // {

            // }

            // // range
            // template < class InputIterator >
            // void insert(InputIterator first, InputIterator last)
            // {

            // }


    };

    // ============================================================================
}

#endif