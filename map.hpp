#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <iterator>

# define nl std::cout<<'\n'

namespace ft
{
    // =================================== PAIR ===================================

    template < class T1, class T2 > struct pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;

            first_type first;
            second_type second;

            pair() : first(0), second(0) {}

            template <class U, class V>
            pair(const pair<U, V> &pr) { *this = pr; }

            pair(const first_type &a, const second_type &b) : first(a), second(b) {}

            pair &operator=(const pair &x)
            {
                if (this == &x)
                    return *this;
                this->first = x.first;
                this->second = x.second;
            }
    };

    template < class T1, class T2 >
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template < class T1, class T2 >
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs == rhs);
    }

    template < class T1, class T2 >
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template < class T1, class T2 >
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(rhs < lhs);
    }

    template < class T1, class T2 >
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return rhs < lhs;
    }

    template < class T1, class T2 >
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }

    // ============================================================================


    // =================================== LESS ===================================

    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };
    
    template <class T>
    struct less : ft::binary_function<T, T, bool>
    {
        bool operator()(const T &x, const T &y) const
        {
            return x < y;
        }
    };

    template <class T>
    struct greater : ft::binary_function<T, T, bool>
    {
        bool operator()(const T &x, const T &y) const
        {
            return x > y;
        }
    };

    struct Compare : ft::binary_function<int, int, bool>
    {
        bool operator()(int a, int b)
        {
            return (a == b);
        }
    };
    

    // ============================================================================




    // ================================ ITERATOR ==================================

    template < class U >
    struct Node
    {
        U *data;
        Node *parent;
        Node *right;
        Node *left;
        int key;
        unsigned char height;
        Node(int k) {
            key = k;
            left = right = 0;
            height = 1;
        }
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
            int &operator*() { return *_ptr; }
            int *operator->() { return _ptr; }

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
        class Compare = std::less< Key >,
        class Allocator = std::allocator< std::pair< const Key, T > >
    >
    class map
    {
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef typename std::pair<const key_type, mapped_type> value_type;
            typedef typename std::size_t size_type;
            typedef typename std::ptrdiff_t difference_type;
            typedef Compare key_compare;
            typedef Allocator allocator_type;
            typedef value_type& reference;
            typedef value_type* pointer;
            typedef const value_type& const_reference;
            typedef const value_type* const_pointer;
            ft::map_iterator<value_type> iterator;
            ft::map_iterator<const value_type> const_iterator;
            // ft::map_reverse_iterator<value_type> reverse_iterator;
            // ft::map_reverse_iterator<const value_type> const_reverse_iterator;

            typedef Node<value_type> avlnode;
            typedef Node<value_type>* avlnode_pointer;
            typedef Node<value_type>& avlnode_reference;

        
            /*
            
            */
            typedef typename allocator_type::template rebind<alvnode>::other avlnode_allocator;


        private:
            avlnode_pointer _box;
            avlnode_allocator _allocNode;
            allocator_type _allocVal;
            key_compare _comp;
            size_type _size;
            avlnode_pointer _begin;
            avlnode_pointer _end;

            // empty avl node initialisation
            void initMap() {
                _end = _allocNode.allocate(1);
                _end->parent = nullptr;
                _end->left = nullptr;
                _end->right = nullptr;
                _end->data = _allocVal.allocate(0);
                _begin = _allocNode.allocate(1);
                _begin->parent = nullptr;
                _begin->left = nullptr;
                _begin->right = nullptr;
                _begin->data = _allocVal.allocate(0);
            }

            void deleteNode(avlnode_pointer node) {
                _allocVal.destroy(node->data);
                _allocVal.deallocate(node->data, 1);
                _allocNode.deallocate(node, 1);
                _size--;
            }

        public:
            // explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
            // {
            // }

    };

    // ============================================================================
}

#endif