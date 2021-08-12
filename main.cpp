#include <vector>
#include <string>

#include "vector.hpp"

#define MY_ALLOCATOR 0
#define STATE 0

template < typename T >
void push_back_numbers(T &numbers, int numSize = int())
{
    std::cout << GREEN << "[ ... Push back numbers (" << numSize << ") ... ]\n" << NCLR;
    for (int i(0); i < numSize; i++)
        numbers.push_back(i);
}

template < typename T >
void pop_back_numbers(T &numbers, int times = int())
{
    std::cout << GREEN << "[ ... Pop back numbers (" << times << ") ... ]\n" << NCLR;
    for (int i(0); i < times; i++)
        numbers.pop_back();
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

// void test_one()
// {
//         // std::cout << GREEN << ">> EMPTY VECTOR OF INTS <<\n" << NCLR;

// #if MY_ALLOCATOR
//         std::cout << B_PURPLE << "... USING MY OWN ALLOCATOR ...\n" << NCLR;
//         std::vector< int, ft::allocator<int> > std_numbers;
//         ft::vector< int, ft::allocator<int> > my_numbers;
// #else
//         std::vector<int> std_numbers;
//         ft::vector<int> my_numbers;
// #endif

//         std::cout << BLUE << "<================ RESIZE ================>\n" << NCLR;

// #if 1
//         std_numbers.resize(10, 1);
//         my_numbers.resize(10, 1);

//         print_each_element_and_size(std_numbers, my_numbers);
//         print_size_and_capacity(std_numbers, my_numbers);

//         std::cout << BLUE << "<================ RESERVE ================>\n" << NCLR;

//         std_numbers.reserve(16);
//         my_numbers.reserve(16);

//         print_each_element_and_size(std_numbers, my_numbers);
//         print_size_and_capacity(std_numbers, my_numbers);

//         std::cout << BLUE << "<================ ITERATOR ================>\n" << NCLR;

//         push_back_numbers(std_numbers, 10);
//         push_back_numbers(my_numbers, 10);

//         std::vector<int>::iterator stdIterator = std_numbers.begin();
//         ft::vector<int>::iterator myIterator = my_numbers.begin();

//         std::cout << YELLOW << "[ std numbers ]\n" << NCLR;
//         for (stdIterator = std_numbers.begin(); stdIterator != std_numbers.end(); stdIterator++)
//             std::cout << *stdIterator << ' ';

//         std::cout << '\n';

//         std::cout << YELLOW << "[ my numbers ]\n" << NCLR;
//         for (myIterator = my_numbers.begin(); myIterator != my_numbers.end(); myIterator++)
//             std::cout << *myIterator << ' ';

//         std::cout << "\n\n";
// #endif

// #if 1
//         std::cout << BLUE << "<========== ASSIGNATION OPERATOR ==========>\n" << NCLR;

//         push_back_numbers(std_numbers, 5);
//         pop_back_numbers(my_numbers, 5);

//         print_each_element_and_size(std_numbers, my_numbers);

//         // my_numbers = std_numbers;
//         // std_numbers = my_numbers;

//         // print_each_element_and_size(std_numbers, my_numbers);

// #endif

// }

void test_two()
{
#if MY_ALLOCATOR
        std::cout << B_PURPLE << "... USING MY OWN ALLOCATOR ...\n" << NCLR;
        std::vector< std::string, ft::allocator<std::string> > std_strings;
        ft::vector< std::string, ft::allocator<std::string> > my_strings;
        ft::vector< std::string, ft::allocator<std::string> > my_strings2;
#else
        std::vector<std::string> std_strings;
        ft::vector<std::string> my_strings;
        ft::vector<std::string> my_strings2;
#endif

    for (size_t i(0); i < 10; i++)
        std_strings.push_back("x");

    for (size_t i(0); i < 10; i++)
        my_strings.push_back("x");

    for (size_t i(0); i < 10; i++)
        my_strings2.push_back("x");

    // print_each_element_and_size(std_strings, my_strings);

    std::cout << '\n';

    my_strings.pop_back();
    my_strings.pop_back();
    my_strings.pop_back();
    my_strings.pop_back();

    print_each_element_and_size(my_strings, my_strings2);
    print_size_and_capacity(my_strings, my_strings2);

    my_strings = my_strings2;

    print_each_element_and_size(my_strings, my_strings2);
    print_size_and_capacity(my_strings, my_strings2);

}

int main()
{

    try
    {
        // std::cout << B_BLUE << "\n################# START #################\n\n" << NCLR;
        // test_one();
        test_two();
    }
    catch(std::exception const &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return (0);
}