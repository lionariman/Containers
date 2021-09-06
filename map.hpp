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

        bool isBegin;
        bool isEnd;

        Node() :
            parent(nullptr),
            right(nullptr),
            left(nullptr),
            height(0),
            isBegin(0),
            isEnd(0) {}

        Node(const U &val) :
            data(ft::make_pair(val.first, val.second)),
            parent(nullptr),
            right(nullptr),
            left(nullptr),
            height(1),
            isBegin(0),
            isEnd(0) {}
    };
    
    template < class T >
    class map_iterator
    {
        public:
            // t - value_type
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
            T &operator*() { return *(_ptr->data); }
            T *operator->() { return _ptr->data; }

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
            U &operator*() { return *(_ptr->data); }
            U *operator->() { return _ptr->data; }

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

            // from STD to FT -> less, allocator, binary_function

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

            class value_compare : public std::binary_function<value_type, value_type, bool> {
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

            _node_pointer  _root;
            _node_pointer  _begin;
            _node_pointer  _end;
            key_compare    _comp;
            size_type      _size;
            allocator_type _alloc;
            node_allocator _alloc_node;

            _node_pointer createNode(const value_type &val)
            {
                _node_pointer newNode = _alloc_node.allocate(1);
                newNode->parent = nullptr;
                newNode->left = nullptr;
                newNode->right = nullptr;
                newNode->data = _alloc.allocate(1);
                _alloc.construct(newNode->data, val);
                return newNode;
            }

            void deleteNode(_node_pointer nd)
            {
                _alloc.destroy(nd->data, 1);
                _alloc.deallocate(nd, 1);
                _alloc_node.deallocate(nd, 1);
                nd = nullptr;
            }

            int getSize(_node_pointer nd)
            {
                if (!nd) return 0;
                return nd->height;
            }

            void correctHeight(_node_pointer nd)
            {
                int heightLeft = getSize(nd->left);
                int heightRight = getSize(nd->right);
                nd->height = ((heightLeft > heightRight) ? heightLeft : heightRight) + 1;
            }

            int balanceFactor(_node_pointer nd)
            {
                return getSize(nd->right) - getSize(nd->left);
            }

            _node_pointer rotateLeft(_node_pointer nd)
            {
                _node_pointer pivot = nd->right;
                pivot->parent = nd->parent;
                if (nd->parent != nullptr)
                {
                    if (nd->parent->left == nd)
                        nd->parent->left = pivot;
                    else
                        nd->parent->right = pivot;
                }
                nd->right = pivot->left;
                if (pivot->left != nullptr)
                    pivot->left->parent = nd;
                nd->parent = pivot;
                pivot->left = nd;
                return nd;
            }

            _node_pointer rotateRight(_node_pointer nd)
            {
                _node_pointer pivot = nd->left;
                pivot->parent = nd->parent;
                if (nd->parent != nullptr)
                {
                    if (nd->parent->left == nd)
                        nd->parent->left = pivot;
                    else
                        nd->parent->right = pivot;
                }
                nd->left = pivot->right;
                if (pivot->right != nullptr)
                    pivot->right->parent = nd;
                nd->parent = pivot;
                pivot->right = nd;
                return nd;
            }

            _node_pointer balance(_node_pointer nd)
            {
                correctHeight(nd);
                if (balanceFactor(nd) == 2)
                {
                    if (balanceFactor(nd->right) < 0)
                        nd->right = rotateRight(nd->right);
                    return rotateLeft(nd);
                }
                if (balanceFactor(nd) == -2)
                {
                    if (balanceFactor(nd->left) > 0)
                        nd->left = rotateLeft(nd->left);
                    return rotateRight(nd);
                }
                return nd;
            }

            // int keyCompare(const key_type &x, const key_type &y) const
            // {
            //     return _comp(x, y) + _comp(y, x) * 2;
            // }

            // _node_pointer findNode(_node_pointer nd, key_type k)
            // {
            //     int compare = keyCompare(k, nd->data->first);
            //     if (compare == 1)
            //     {
            //         if (nd->left and nd->left != _begin)
            //             return findNode(nd->left, k);
            //     }
            //     else if (compare == 2)
            //     {
            //         if (nd->right and nd->right != _end)
            //             return findNode(nd->right, k);
            //     }
            //     return nd;
            // }

            _node_pointer putNode(_node_pointer nd, _node_pointer parent, const value_type &val)
            {
                if (nd and nd->isBegin)
                {
                    _node_pointer newNode = createNode(val);
                    parent->left = newNode;
                    newNode->parent = parent;
                    newNode->left = nd;
                    newNode->right = nullptr;
                    nd->parent = newNode;
                    return balance(parent);
                }
                else if (nd and nd->isEnd)
                {
                    _node_pointer newNode = createNode(val);
                    parent->right = newNode;
                    newNode->parent = parent;
                    newNode->right = nd;
                    newNode->left = nullptr;
                    nd->parent = newNode;
                    return balance(parent);
                }
                else if (!nd)
                {
                    nd = createNode(val);
                    nd->parent = parent;
                    nd->left = nullptr;
                    nd->right = nullptr;
                }
                if (nd->data->first > val.first)
                    nd->left = putNode(nd->left, nd, val);
                else if (nd->data->first < val.first)
                    nd->right = putNode(nd->right, nd, val);
                else if (nd->data->first == val.first)
                    nd->data->second = val.second;
                nd->height = 1 + getSize(nd->left) + getSize(nd->right);
                return balance(nd);
            }

            // _node_pointer deleteMin(_node_pointer nd)
            // {
            //     if (nd->left == nullptr) return nd->right;
            //     nd->left = deleteMin(nd->left);
            //     nd->height = 1 + getSize(nd->left) + getSize(nd->right);
            //     return nd;
            // }

            // _node_pointer getMin(_node_pointer nd)
            // {
            //     if (!nd->left) return nd;
            //     return getMin(nd->left);
            // }

            // _node_pointer getMax(_node_pointer nd)
            // {
            //     if (!nd->right) return nd;
            //     return getMax(nd->right);
            // }

            // _node_pointer deleteNode(_node_pointer nd, value_type &val)
            // {
            //     if (!nd) return nullptr;
            //     if (nd->data->first > val.first) nd->left = deleteNode(nd->left, val);
            //     else if (nd->data->first < val.first) nd->right = deleteNode(nd->right, val);
            //     else
            //     {
            //         if (!nd->right) return nd->left;
            //         if (!nd->left) return nd->right;
            //         _node_pointer t = nd;
            //         nd = getMin(t->right);
            //         nd->right = deleteMin(t->right);
            //         nd->left = t->left;
            //         return balance(nd);
            //     }
            //     return balance(nd);
            // }

            // void deleteTree(_node_pointer nd)
            // {
            //     if (nd->left != nullptr)
            //         deleteTree(nd->left);
            //     if (nd->right != nullptr)
            //         deleteTree(nd->right);
            //     delete nd;
            // }

        public:
            // empty constructor
            explicit map(const key_compare &comp = key_compare(),
                         const allocator_type &alloc = allocator_type()) :
                _root(nullptr),
                _comp(comp),
                _size(0),
                _alloc(alloc)
            {
                // initMap();
            }

            iterator begin() { return ++iterator(_begin); }
            // const_iterator cbegin() { return const_iterator(_begin); }
            // reverse_iterator rbegin() { return reverse_iterator(_end); }
            // const_reverse_iterator crbegin() { return const_reverse_iterator(_end); }

            // iterator end() { return iterator(_begin); }
            // const_iterator cend() { return const_iterator(_begin); }
            // reverse_iterator rend() { return reverse_iterator(_end); }
            // const_reverse_iterator crend() { return const_reverse_iterator(_end); }

            bool empty() const { return _size; }
            size_type size() const { return _size; }
            size_type max_size() const { return _alloc.max_size() / 5; }

            std::pair<iterator, bool> insert(const value_type &val)
            {
                if (_size == 0)
                {
                    std::cout << "insert 1\n";
                    _root = createNode(val);

                    _begin = _alloc_node.allocate(1);
                    _end = _alloc_node.allocate(1);

                    _begin->data = _alloc.allocate(0);
                    _end->data = _alloc.allocate(0);

                    _root->left = _begin;
                    _root->right = _end;

                    _begin->parent = _root;
                    _end->parent = _root;

                    _begin->left = nullptr;
                    _begin->right = nullptr;
                    _end->left = nullptr;
                    _end->right = nullptr;

                    _begin->isBegin = true;
                    _end->isEnd = true;

                    _root->height++;
                    _size++;

                    return std::pair<iterator, bool>(_root, true);
                }
                // bool yesnot = false;
                if (_root->data->first > val.first)
                    _root = putNode(_root->left, _root, val);
                else if (_root->data->first < val.first)
                    _root = putNode(_root->right, _root, val);
                else if (_root->data->first == val.first)
                    return std::pair<iterator, bool>(_root, false);
                _size++;
                return std::pair<iterator, bool>(_root, true);
            }

            // =============== FOR TESTS ================
            
            void printMinNode()
            {
                std::cout << "min: " << getMin(_root)->data->first << '\n';
            }

            void printMaxNode()
            {
                std::cout << "max: " << getMax(_root)->data->first << '\n';
            }

            _node_pointer getMinNode() { return getMin(_root); }
            _node_pointer getMaxNode() { return getMax(_root); }


    };

    // ============================================================================
}

#endif