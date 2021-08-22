#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
    template < class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type;

        protected:
            container_type _cont;

        public:
            explicit stack(container_type const &cont = container_type()) : _cont(cont) {}
            stack(const stack<value_type, container_type> &x) : _cont(x._cont) {}
            stack &operator=(const stack<value_type, container_type> &x)
            {
                if (this == &x)
                    return ;
                this->_cont = x._cont;
            }
            virtual ~stack() {}
            bool empty() const { return this->_cont.empty(); }
            value_type &top() { return this->_cont.back(); }
            value_type const &top() const { return this->_cont.back(); }
            size_type size() const { return this->_cont.size(); }
            void push(value_type const &val) { this->_cont.push_back(val); }
            void pop() { this->_cont.pop_back(); }
    };

    template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._cont == rhs._cont;
	}
	
	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}
	
	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._cont < rhs._cont;
	}
	
	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(rhs < lhs);
	}
	
	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return rhs < lhs;
	}
	
	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}

    // template <class T, class Container>
	// bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	// {
	// 	if (lhs.size() != rhs.size())
	// 		return (false);
	// 	typename ft::stack<T, Container>::const_iterator it1 = lhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite1 = lhs.cend();
	// 	typename ft::stack<T, Container>::const_iterator it2 = rhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite2 = rhs.cend();
	// 	while (it1 != ite1)
	// 	{
	// 		if (*it1 != *it2)
	// 			return (false);
	// 		++it1;
	// 		++it2;
	// 	}
	// 	return (true);
	// }

    // template <class T, class Container>
	// bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	// {
	// 	if (lhs.size() == rhs.size())
	// 		return (false);
	// 	typename ft::stack<T, Container>::const_iterator it1 = lhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite1 = lhs.cend();
	// 	typename ft::stack<T, Container>::const_iterator it2 = rhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite2 = rhs.cend();
	// 	while (it1 != ite1)
	// 	{
	// 		if (*it1 == *it2)
	// 			return (false);
	// 		++it1;
	// 		++it2;
	// 	}
	// 	return (true);
	// }

    // template <class T, class Container>
	// bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	// {
	// 	if (lhs.size() != rhs.size())
	// 		return (false);
	// 	typename ft::stack<T, Container>::const_iterator it1 = lhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite1 = lhs.cend();
	// 	typename ft::stack<T, Container>::const_iterator it2 = rhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite2 = rhs.cend();
	// 	while (it1 != ite1)
	// 	{
	// 		if (*it1 >= *it2)
	// 			return (false);
	// 		++it1;
	// 		++it2;
	// 	}
	// 	return (true);
	// }

    // template <class T, class Container>
	// bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	// {
	// 	if (lhs.size() != rhs.size())
	// 		return (false);
	// 	typename ft::stack<T, Container>::const_iterator it1 = lhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite1 = lhs.cend();
	// 	typename ft::stack<T, Container>::const_iterator it2 = rhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite2 = rhs.cend();
	// 	while (it1 != ite1)
	// 	{
	// 		if (*it1 <= *it2)
	// 			return (false);
	// 		++it1;
	// 		++it2;
	// 	}
	// 	return (true);
	// }

    // template <class T, class Container>
	// bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	// {
	// 	if (lhs.size() != rhs.size())
	// 		return (false);
	// 	typename ft::stack<T, Container>::const_iterator it1 = lhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite1 = lhs.cend();
	// 	typename ft::stack<T, Container>::const_iterator it2 = rhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite2 = rhs.cend();
	// 	while (it1 != ite1)
	// 	{
	// 		if (*it1 > *it2)
	// 			return (false);
	// 		++it1;
	// 		++it2;
	// 	}
	// 	return (true);
	// }

    // template <class T, class Container>
	// bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	// {
	// 	if (lhs.size() != rhs.size())
	// 		return (false);
	// 	typename ft::stack<T, Container>::const_iterator it1 = lhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite1 = lhs.cend();
	// 	typename ft::stack<T, Container>::const_iterator it2 = rhs.cbegin();
	// 	typename ft::stack<T, Container>::const_iterator ite2 = rhs.cend();
	// 	while (it1 != ite1)
	// 	{
	// 		if (*it1 < *it2)
	// 			return (false);
	// 		++it1;
	// 		++it2;
	// 	}
	// 	return (true);
	// }
}


#endif