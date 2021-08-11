#include <vector>
#include <string>

#include "vector.hpp"

template < typename T >
void push_back_new_numbers(T &numbers, int numSize = int())
{
    // std::cout << GREEN << "\n[ ... Push back new numbers (" << numSize << ") ... ]\n" << NCLR;
    for (int i(0); i < numSize; i++)
        numbers.push_back(i);
}

template < typename T1, typename T2 >
void print_each_element_and_size(T1 &std_numbers, T2 &my_numbers, int how = int())
{
    size_t i(0);

    // std::cout << YELLOW << "\n[ ... Print each element size ... ]\n\n" << NCLR;

    if (how)
    {
        for (; i < std_numbers.size(); i++)
            std::cout << std_numbers.at(i) << '\n';
        std::cout << "[" << i << "]\n";
        i = 0;
        for (; i < my_numbers.size(); i++)
            std::cout << my_numbers.at(i) << '\n';
        std::cout << "[" << i << "]\n";
        return ;
    }
    for (; i < std_numbers.size(); i++)
        std::cout << std_numbers.at(i) << ' ';
    std::cout << " [" << i << "] \n";
    i = 0;
    for (; i < my_numbers.size(); i++)
        std::cout << my_numbers.at(i) << ' ';
    std::cout << " [" << i << "] \n";
}

template < typename T1, typename T2 >
void print_size_and_capacity(T1 &std_numbers, T2 &my_numbers)
{

    // std::cout << YELLOW << "\n[ ... Print size and capacity ... ]\n\n" << NCLR;

    std::cout << "    std size: " << std_numbers.size() << '\n'
              << "     my size: " << my_numbers.size() << '\n'
              << "std capacity: " << std_numbers.capacity() << '\n'
              << " my capacity: " << my_numbers.capacity() << "\n\n";
}

void constructor_test()
{
        // std::cout << GREEN << ">> EMPTY VECTOR OF INTS <<\n" << NCLR;

        std::vector<int> std_numbers;
        ft::vector<int> my_numbers;

        std::cout << BLUE << "<================ RESIZE ================>\n" << NCLR;

        std_numbers.resize(10, 1);
        my_numbers.resize(10, 1);

        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << BLUE << "<================ RESERVE ================>\n" << NCLR;

        std_numbers.reserve(16);
        my_numbers.reserve(16);

        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << BLUE << "<================ ITERATOR ================>\n" << NCLR;

        push_back_new_numbers(std_numbers, 10);
        push_back_new_numbers(my_numbers, 10);

        std::vector<int>::iterator stdIterator;
        ft::vector<int>::iterator myIterator;

        stdIterator = std_numbers.begin();
        myIterator = my_numbers.begin();

        std::cout << YELLOW << "[ std numbers ]\n" << NCLR;
        for (stdIterator = std_numbers.begin(); stdIterator != std_numbers.end(); stdIterator++)
            std::cout << *stdIterator << ' ';

        std::cout << '\n';

        std::cout << YELLOW << "[ my numbers ]\n" << NCLR;
        for (myIterator = my_numbers.begin(); myIterator != my_numbers.end(); myIterator++)
            std::cout << *myIterator << ' ';

        std::cout << "\n\n";

        std_numbers.pop_back();
        my_numbers.pop_back();

        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);
}

int main()
{

    try
    {
        // std::cout << B_BLUE << "\n################# START #################\n\n" << NCLR;
        constructor_test();
    }
    catch(std::exception const &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return (0);
}