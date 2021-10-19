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
    // ================================== NODE ====================================

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

    // ================================ ITERATORS =================================
    
    template < class T >
    class map_iterator
    {
        public:
            // t - value_type
            typedef Node<T> *_node_pointer;
            typedef Node<T> &_node_reference;
            typedef std::bidirectional_iterator_tag iterator_category;

        private:
            _node_pointer _ptr;

        public:
            map_iterator() : _ptr(nullptr) {}
            map_iterator(_node_pointer ptr) : _ptr(ptr) {}
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

            _node_pointer getNode() { return _ptr; }
        
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
            typedef Node<U> *_node_pointer;
            typedef Node<U> &_node_reference;
            typedef std::bidirectional_iterator_tag iterator_category;

        private:
            _node_pointer _ptr;

        public:
            map_reverse_iterator() : _ptr(nullptr) {}
            map_reverse_iterator(_node_pointer ptr) : _ptr(ptr) {}
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

            _node_pointer getNode() { return _ptr; }

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

            int getSize(_node_pointer nd)
            {
                if (!nd) return 0;
                return nd->height;
            }

            int valcmp(const value_type &x, const value_type &y) const
            {
                return keyCompare(x.first, y.first);
            }

            _node_pointer deleteMin(_node_pointer nd)
            {
                if (nd->left == nullptr) return nd->right;
                nd->left = deleteMin(nd->left);
                nd->height = 1 + getSize(nd->left) + getSize(nd->right);
                return nd;
            }

            _node_pointer getMin(_node_pointer nd)
            {
                if (!nd->left) return nd;
                return getMin(nd->left);
            }

            _node_pointer getMax(_node_pointer nd)
            {
                if (!nd->right) return nd;
                return getMax(nd->right);
            }


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

            iterator begin() { return _size ? iterator(_begin->parent) : iterator(_begin); }
            const_iterator cbegin() const { return _size ? const_iterator(_begin->parent) : const_iterator(_begin); }
            reverse_iterator rbegin() { return reverse_iterator(_end); }
            const_reverse_iterator crbegin() const { return const_reverse_iterator(_end); }

            iterator end() { return iterator(_end); }
            const_iterator cend() const { return const_iterator(_end); }
            reverse_iterator rend() { return _size ? reverse_iterator(_begin->parent) : reverse_iterator(_begin); }
            const_reverse_iterator crend() const { return _size ? const_reverse_iterator(_begin->parent) : const_reverse_iterator(_begin); }

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

            void deleteNode(_node_pointer node)
            {
                _alloc.destroy(node->data);
                _alloc.deallocate(node->data, 1);
                _alloc_node.deallocate(node, 1);
                node = nullptr;
            }

            size_type keycmp(const key_type &k1, const key_type &k2) const
            {
                return _comp(k1, k2) + _comp(k2, k1) * 2;
            }

            _node_pointer findNode(_node_pointer node, const key_type &k) const
            {
                int res = keycmp(node->data->first, k);
                if (res == 1 and node->right and node != _end)
                    return findNode(node->right, k);
                else if (res == 2 and node->left and node != _begin)
                    return findNode(node->left, k);
                return node;
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
                    if (keycmp(nd->data->first, val.first) == 1)
                    {
                        nd->right = putNode(nd->right, nd, val);
                    }
                    else if (keycmp(nd->data->first, val.first) == 2)
                    {
                        nd->left = putNode(nd->left, nd, val);
                    }
                    else
                    {
                        _size--;
                        return nd;
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


            // ===============================================================================
            // ================== TESTS ======================================================
            // PRE-ORDER CALL
            void callInOrder() { inOrder(_root); }

            void testFindNodeMethod(const key_type &k)
            {
                _node_pointer found;

                found = findNode(_root, k);
                if (found != nullptr)
                    std::cout << "found Node has: " << found->data->first << '\n';
                else
                    std::cout << "found Node is empty" << '\n';
            }
            // ================== TESTS ======================================================
            // ===============================================================================

            iterator find(const key_type &k)
            {
                _node_pointer found = findNode(_root, k);
                return (keycmp(found->data->first, k) == 0) ? iterator(found) : end();
            }

            const_iterator find(const key_type &k) const
            {
                _node_pointer found = findNode(_root, k);
                return (keycmp(found->data->first, k) == 0) ? const_iterator(found) : cend();
            }

            std::pair<iterator, bool> insert(const value_type &val)
            {
                if (_size == 0) return initTop(val);
                _node_pointer node = findNode(_root, val.first);
                if (keycmp(node->data->first, val.first) == 0)
                    return std::pair<iterator, bool>(iterator(node), false);
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
                throw std::out_of_range("map::at:  key not found");
            }

            size_type count(const key_type &k) const
            {
                return (keycmp(findNode(_root, k)->data->first, k) == 0) ? 1 : 0;
            }

            // ============================== ERASE ===========================================

            _node_pointer destroyer(_node_pointer nd, value_type &val)
            {
                if (!nd) return nullptr;
                if (nd->data->first > val.first) nd->left = deleteNode(nd->left, val);
                else if (nd->data->first < val.first) nd->right = deleteNode(nd->right, val);
                else
                {
                    if (!nd->right) return nd->left;
                    if (!nd->left) return nd->right;
                    _node_pointer t = nd;
                    nd = getMin(t->right);
                    nd->right = deleteMin(t->right);
                    nd->left = t->left;
                    return balance(nd);
                }
                return balance(nd);
            }

            void exterminator(_node_pointer victim)
            {
                if (victim->left == nullptr and victim->right == nullptr)
                {
                    if (keycmp(victim->parent->left->data->first, victim->data->first) == 0)
                    {
                        victim->parent->left = nullptr;
                        deleteNode(victim);
                    }
                    else if (keycmp(victim->parent->right->data->first, victim->data->first) == 0)
                    {
                        victim->parent->right = nullptr;
                        deleteNode(victim);
                    }
                }
                else if (victim->left != _begin and victim->right != _end and victim->left != nullptr and victim->right != nullptr)
                {
                    
                }
                else if (victim->right != _end and (victim->left == nullptr or victim->left == _begin))
                {
                    if (victim->right != nullptr)
                    {
                        victim->parent->left = victim->right;
                        victim->right->parent = victim->parent;
                        victim->right->left = victim->left;
                        _begin->parent = victim->right;
                    }
                    else
                    {
                        victim->parent->left = _begin;
                        _begin->parent = victim->parent;
                    }
                }
                else if (victim->left != _begin and (victim->right == nullptr or victim->right == _end))
                {
                    if (victim->left != nullptr)
                    {
                        victim->parent->right = victim->left;
                        victim->left->parent = victim->parent;
                        victim->left->right = victim->right;
                        _end->parent = victim->parent;
                    }
                    else
                    {
                        victim->parent->right = _end;
                        _end->parent = victim->parent;
                    }
                }
                // _root = balance(victim->parent);
            }

            void erase(iterator position)
            {
                if (_size == 0)
                    return ;
                exterminator(position.getNode());
                _size--;
            }

            size_type erase(const key_type &k)
            {
                if (_size == 0)
                    return 0;
                _node_pointer node = findNode(_root, k);
                if (keycmp(node->data->first, k))
                    return 0;
                exterminator(node);
                _size--;
                return 1;
            }

            void erase(iterator first, iterator last)
            {
                for (; first != last; first++)
                    erase(first);
            }
    };

    // ============================================================================
}

#endif