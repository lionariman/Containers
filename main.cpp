#include <vector>
#include <string>

#include "vector.hpp"

enum Actions
{
    RESIZE,
    RESERVE,
    SHRINK_TO_FIT
};

template < typename T >
void push_back_new_numbers(T &numbers, int numSize = int())
{
    for (int i(0); i < numSize; i++)
        numbers.push_back(i);
}

template < typename T >
void capacity_tester(T &numbers)
{
    std::cout << "capacity: " << numbers.capacity() << '\n';
    std::cout << "    size: " << numbers.size() << '\n';

    if (!numbers.empty())
    {
        for (size_t i(0); i < numbers.size(); i++)
            std::cout << numbers[i] << ' ';
        std::cout << '\n';
    }
}

template < typename T >
void capacity_change(T &numbers, Actions action, int value = int(), int cnt = int())
{
    switch (action)
    {
        case RESIZE:
            if (cnt)
                numbers.resize(value, cnt);
            else
                numbers.resize(value);
            break;

        case RESERVE:
            numbers.reserve(value);
            break;

        case SHRINK_TO_FIT:
            numbers.shrink_to_fit();
            break;
        
        default:
            break;
    }
}

int main()
{

    try
    {
        std::vector<int> numbers(15);

        // ft::vector<int> my_numbers(10);

        // std::cout << "     my size: " << my_numbers.size() << '\n';
        // std::cout << "    std size: " << numbers.size() << '\n';
        // std::cout << " my max size: " << my_numbers.max_size() << '\n';
        // std::cout << "std max size: " << numbers.max_size() << '\n';

        // for (size_t i(0); i < my_numbers.size(); i++)
        //     std::cout << "> " << my_numbers.at(i) << '\n';

        push_back_new_numbers(numbers, 4);

        capacity_tester(numbers);

        // capacity_change(numbers, RESIZE, 11);

        // capacity_tester(numbers);

        // push_back_new_numbers(my_numbers);

        // push_back_new_numbers(numbers, 5);
        // capacity_tester(numbers);
    }
    catch(std::exception const &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }
    


    return (0);
}