#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <iterator>

# include "utils/allocator.hpp"
# include "utils/utils.hpp"

# define nl std::cout<<'\n'

# define check0 std::cout<< "< CHECK 0 >\n"
# define check1 std::cout<< "< CHECK 1 >\n"
# define check2 std::cout<< "< CHECK 2 >\n"
# define check3 std::cout<< "< CHECK 3 >\n"
# define check4 std::cout<< "< CHECK 4 >\n"
# define check5 std::cout<< "< CHECK 5 >\n"
# define check6 std::cout<< "< CHECK 6 >\n"
# define check7 std::cout<< "< CHECK 7 >\n"
# define check8 std::cout<< "< CHECK 8 >\n"
# define check9 std::cout<< "< CHECK 9 >\n"

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

        Node() :
            parent(nullptr),
            right(nullptr),
            left(nullptr),
            height(0) {}

        Node(const U &val) :
            data(ft::make_pair(val.first, val.second)),
            parent(nullptr),
            right(nullptr),
            left(nullptr),
            height(1) {}
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
            map_iterator(pointer ptr = nullptr) : _ptr(ptr) {}
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
            map_reverse_iterator(pointer ptr = nullptr) : _ptr(ptr) {}
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

            _node_pointer createNode(const value_type &val, _node_pointer parent, _node_pointer left, _node_pointer right)
            {
                _node_pointer newNode = _alloc_node.allocate(1); // allocate memory for a new node with a new value
                newNode->parent = parent;
                newNode->left = left;
                newNode->right = right;
                newNode->data = _alloc.allocate(1);
                _alloc.construct(newNode->data, val);
                return newNode;
            }

            // void deleteNode(_node_pointer nd)
            // {
            //     _alloc.destroy(nd->data, 1);
            //     _alloc.deallocate(nd, 1);
            //     _alloc_node.deallocate(nd, 1);
            //     nd = nullptr;
            // }

            // int getSize(_node_pointer nd)
            // {
            //     if (!nd) return 0;
            //     return nd->height;
            // }

            // void correctHeight(_node_pointer nd)
            // {
            //     int heightLeft = getSize(nd->left);
            //     int heightRight = getSize(nd->right);
            //     nd->height = ((heightLeft > heightRight) ? heightLeft : heightRight) + 1;
            // }

            // int balanceFactor(_node_pointer nd)
            // {
            //     return getSize(nd->right) - getSize(nd->left);
            // }

            // int keyCompare(const key_type &x, const key_type &y) const
            // {
            //     return _comp(x, y) + _comp(y, x) * 2;
            // }

            // int valueCompare(const value_type &x, const value_type &y) const
            // {
            //     return keyCompare(x.first, y.first);
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

            std::pair<iterator, bool> initTop(const value_type &val)
            {
                _begin = _alloc_node.allocate(1);
                _end = _alloc_node.allocate(1);

                //                [val] [parent] [left] [right]
                _root = createNode(val, nullptr, _begin, _end);


                _begin->parent = _root;
                _end->parent = _root;

                _begin->data = _alloc.allocate(1);
                _end->data = _alloc.allocate(1);

                // _begin->data = nullptr;
                // _end->data = nullptr;

                _begin->left = nullptr;
                _begin->right = nullptr;
                _end->left = nullptr;
                _end->right = nullptr;

                _root->height = 0;

                _size = 1;

                return std::pair<iterator, bool>(_root, true);
            }

        public:
            // empty constructor
            explicit map(const key_compare &comp = key_compare(),
                         const allocator_type &alloc = allocator_type()) :
                _root(nullptr),
                _begin(nullptr),
                _end(nullptr),
                _comp(comp),
                _size(0),
                _alloc(alloc) {}

            ~map()
            {
                if (_root == nullptr) return ;
                deleteTree(_root);
                _size = 0;
                _root->height = 0;
            }

            iterator begin() { return iterator(_begin->parent); }
            const_iterator cbegin() { return const_iterator(_begin->parent); }
            // reverse_iterator rbegin() { return reverse_iterator(_end); }
            // const_reverse_iterator crbegin() { return const_reverse_iterator(_end); }

            iterator end() { return iterator(_end); }
            const_iterator cend() { return const_iterator(_end); }
            // reverse_iterator rend() { return reverse_iterator(_begin); }
            // const_reverse_iterator crend() { return const_reverse_iterator(_begin); }

            bool empty() const { return _size; }
            size_type size() const { return _size; }
            size_type max_size() const { return _alloc.max_size() / 5; }

        private:

            void deleteTree(_node_pointer nd)
            {
                if (nd == nullptr) return ;
                else if (nd == _begin or nd == _end)
                {
                    _alloc.deallocate(nd->data, 1);
                    _alloc_node.deallocate(nd, 1);
                    return ;
                }
                deleteTree(nd->left);
                deleteTree(nd->right);
                _alloc.destroy(nd->data);
                _alloc.deallocate(nd->data, 1);
                _alloc_node.deallocate(nd, 1);
                nd = nullptr;
            }

            int getHeight(_node_pointer nd)
            {
                return nd ? nd->height : 0;
            }

            int max(int a, int b)
            {
                return (a > b) ? a : b;
            }

            int bfactor(_node_pointer nd)
            {
                return getHeight(nd->right) - getHeight(nd->left);
            }

            void fixHeight(_node_pointer nd)
            {
                int hl = getHeight(nd->left);
                int hr = getHeight(nd->right);
                nd->height = (hl > hr ? hl : hr) + 1;
            }

            _node_pointer balance(_node_pointer p)
            {
                fixHeight(p);
                if (bfactor(p) == 2)
                {
                    if (bfactor(p->right) < 0)
                        p->right = rightRotate(p->right);
                    return leftRotate(p);
                }
                else if (bfactor(p) == -2)
                {
                    if (bfactor(p->left) > 0)
                        p->left = leftRotate(p->left);
                    return rightRotate(p);
                }
                return p;
            }

            _node_pointer rightRotate(_node_pointer p)
            {
                _node_pointer q = p->left;
                p->left = q->right;
                q->right = p;
                q->parent = p->parent;
                p->parent = q;
                fixHeight(p);
                fixHeight(q);
                return q;
            }

            _node_pointer leftRotate(_node_pointer q)
            {
                _node_pointer p = q->right;
                q->right = p->left;
                p->left = q;
                p->parent = q->parent;
                q->parent = p;
                fixHeight(q);
                fixHeight(p);
                return p;
            }


            _node_pointer putNode(_node_pointer nd, _node_pointer parent, const value_type &val) // recursion insert
            {
                if (nd == nullptr)
                {
                    nd = createNode(val, parent, nullptr, nullptr);
                }
                else if (nd == _begin)
                {
                    nd = createNode(val, parent, _begin, nullptr);
                    _begin->parent = nd;
                }
                else if (nd == _end)
                {
                    nd = createNode(val, parent, nullptr, _end);
                    _end->parent = nd;
                }
                else
                {
                    if (_comp(nd->data->first, val.first) == true)
                    {
                        nd->right = putNode(nd->right, nd, val);
                    }
                    else if (_comp(nd->data->first, val.first) == false and _comp(val.first, nd->data->first) == false)
                    {
                        _size--;
                        return nd;
                    }
                    else
                    {
                        nd->left = putNode(nd->left, nd, val);
                    }
                }
                return balance(nd);
            }

            // RECURSIVE ALGORITHM TO PRINT ELEMENTS IN THE BINARY TREE
            void inOrder(_node_pointer nd)
            {
                if (nd == nullptr) return ;
                inOrder(nd->left);
                std::cout << "\n--------------------------< l >------------------------\n";
                if (nd->parent)
                    std::cout << " ^ nd parent: " << nd->parent->data->first << '\n';
                else
                    std::cout << "root\n";
                if (nd->data)
                    std::cout << " . nd data: " << nd->data->first << '\n';
                else
                    std::cout << "...\n";
                if (nd->left)
                    std::cout << " <- nd left: " << nd->left->data->first << '\n';
                else
                    std::cout << "...\n";
                if (nd->right)
                    std::cout << " -> nd right: " << nd->right->data->first << '\n';
                else
                    std::cout << "...\n";
                std::cout << "--------------------------< r >------------------------\n\n";
                inOrder(nd->right);
            }

        public:

            // PRE-ORDER CALL
            void callInOrder() { inOrder(_root); }

            //========================================================================================================
            //========================================================================================================

            size_type keycmp(const key_type &k1, const key_type &k2)
            {
                if (_comp(k1, k2) == true)                              return 1; // k1 < k2
                if (_comp(k1, k2) == false)                             return 2; // k1 > k2
                if (_comp(k1, k2) == false and _comp(k2, k1) == false)  return 0; // k1 == k2
                return 3;
            }

            _node_pointer findNode(_node_pointer node, const key_type &k)
            {
                _node_pointer found = nullptr;
                if (node and node != _begin and node != _end)
                {
                    if (keycmp(node->data->first, k) == 0)
                    {
                        std::cout << "FOUND NUBER: " << node->data->first << '\n';
                        return found;
                    }
                    else if (keycmp(node->data->first, k) == 1)
                    {
                        if (node->right != nullptr)
                            std::cout << "RIGHT SIDE NUMBER: " << node->right->data->first << '\n';
                        found = findNode(node->right, k);
                    }
                    else if (keycmp(node->data->first, k) == 2)
                    {
                        if (node->left != nullptr)
                            std::cout << "LEFT SIDE NUMBER: " << node->left->data->first << '\n';
                        found = findNode(node->left, k);
                    }
                }
                // std::cout << "< <<>> >\n";
                return node;
            }

            void testFindNodeMethod(const key_type &k)
            {
                _node_pointer found;

                std::cout << "ROOT >> " << _root->data->first << '\n';
                found = findNode(_root, k);
                if (found != nullptr)
                    std::cout << "found Node has: " << found->data->first << '\n';
                else
                    std::cout << "found Node is empty" << '\n';
            }

            //========================================================================================================
            //========================================================================================================

            iterator find(const key_type &k)
            {
                for (iterator it = _begin; it != _end; it++)
                    if (_comp(it->first, k) == false and _comp(k, it->first) == false)
                        return it;
                return _end;
            }

            const_iterator find(const key_type &k) const
            {
                for (iterator it = _begin; it != _end; it++)
                    if (_comp(it->first, k) == false and _comp(k, it->first) == false)
                        return const_iterator(*it);
                return cend();
            }

            std::pair<iterator, bool> insert(const value_type &val)
            {
                if (_size == 0) return initTop(val);
                iterator it = find(val.first);
                if (it != _end) return std::pair<iterator, bool>(it, false);
                _root = putNode(_root, nullptr, val);
                _size++;
                return std::pair<iterator, bool>(iterator(_root), true);
            }

            iterator insert(iterator position, const value_type &val)
            {
                (void)position;
                insert(val);
                return find(val.first);
            }

            template < class InputIterator >
            void insert(InputIterator first, InputIterator last)
            {
                for (; first != last; first++)
                    insert(*first);
            }

            mapped_type& operator[](const key_type &k)
            {
                return insert(_begin, std::make_pair(k, mapped_type()))->second;
            }

            mapped_type& at(const key_type &k)
            {
                iterator it = find(k);
                if (it != _end)
                    return it->second;
                throw std::out_of_range("map::at: key not found");
            }

            size_type count(const key_type &k) const
            {
                return ((find(k) != _end) ? 1 : 0);
            }

            // 1. use recursive algorithm to find a node insdead of find method
            // 2. implement erase method

    };

    // ============================================================================
}

#endif