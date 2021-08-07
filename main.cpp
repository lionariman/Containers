#include <vector>
#include <string>

#include "vector.hpp"

template < typename T >
void push_back_new_numbers(T &numbers, int numSize = int())
{
    for (int i(0); i < numSize; i++)
        numbers.push_back(i);
}

template < typename T1, typename T2 >
void print_each_element_and_size(T1 &std_numbers, T2 &my_numbers, int how = int())
{
    size_t i(0);

    std::cout << "\n[ ... Print each element and size ... ]\n\n";

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

    std::cout << "\n[ ... Print size and capacity ... ]\n\n";

    std::cout << "    std size: " << std_numbers.size() << '\n'
              << "     my size: " << my_numbers.size() << '\n'
              << "std capacity: " << std_numbers.capacity() << '\n'
              << " my capacity: " << my_numbers.capacity() << "\n\n";
}

void constructor_test()
{
        std::cout << ">> EMPTY VECTOR OF INTS <<\n";

        std::vector<int> std_numbers;
        ft::vector<int> my_numbers;

        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << "[ RESIZE ]\n";

        std_numbers.resize(10, 1);
        my_numbers.resize(10, 1);

        print_each_element_and_size(std_numbers, my_numbers);

        print_size_and_capacity(std_numbers, my_numbers);

        // std::cout << ">> FOUR INTS WITH VALUE 100 <<\n";

        // std::vector<int> std_numbers;
        // ft::vector<int> my_numbers;

        // print_size_and_capacity(std_numbers, my_numbers);

        // std::cout << "[ RESIZE ]\n";

        // std_numbers.resize(10, 1);
        // my_numbers.resize(10, 1);

        // print_each_element_and_size(std_numbers, my_numbers);

        // print_size_and_capacity(std_numbers, my_numbers);
}

int main()
{

    try
    {
        std::cout << "\n<========== START ==========>\n\n";
        constructor_test();
    }
    catch(std::exception const &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return (0);
}