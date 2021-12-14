#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
    template < class T, class _Container = std::vector<T> >
    class stack
    {
        public:
            typedef _Container container_type;
			typedef typename _Container::value_type value_type;
            typedef typename std::size_t size_type;

            container_type _cont;

            explicit stack(const container_type &cont = container_type()) : _cont(cont) {}
            stack(const stack &x) : _cont(x._cont) {}

            stack &operator=(const stack &x)
            {
                if (this == &x)
                    return ;
                this->_cont = x._cont;
            }

            ~stack() {}

            bool empty() const { return this->_cont.empty(); }

            value_type &top() { return this->_cont.back(); }
            value_type const &top() const { return this->_cont.back(); }
            size_type size() const { return this->_cont.size(); }
            void push(value_type const &val) { this->_cont.push_back(val); }
            void pop() { this->_cont.pop_back(); }
    };

    template <class T, class _Container>
	bool operator==(ft::stack<T, _Container> &lhs, ft::stack<T, _Container> &rhs)
	{
		return lhs._cont == rhs._cont;
	}
	
	template <class T, class _Container>
	bool operator!=(ft::stack<T, _Container> &lhs, ft::stack<T, _Container> &rhs)
	{
		return !(lhs == rhs);
	}
	
	template <class T, class _Container>
	bool operator<(ft::stack<T, _Container> &lhs, ft::stack<T, _Container> &rhs)
	{
		return lhs._cont < rhs._cont;
	}
	
	template <class T, class _Container>
	bool operator<=(ft::stack<T, _Container> &lhs, ft::stack<T, _Container> &rhs)
	{
		return !(rhs < lhs);
	}
	
	template <class T, class _Container>
	bool operator>(ft::stack<T, _Container> &lhs, ft::stack<T, _Container> &rhs)
	{
		return rhs < lhs;
	}
	
	template <class T, class _Container>
	bool operator>=(ft::stack<T, _Container> &lhs, ft::stack<T, _Container> &rhs)
	{
		return !(lhs < rhs);
	}
}

#endif