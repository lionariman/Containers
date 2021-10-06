#include <vector>
#include <string>
#include <stack>
#include <map>

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"

#define CHECK std::cout<< "< CHECK >\n"

#define MY_ALLOCATOR 0
#define STATE 0

template < typename T >
void push_back_numbers(T &numbers, int numSize = int())
{
    // std::cout << GREEN << "[ ... Push back numbers (" << numSize << ") ... ]\n" << NCLR;
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


// #if 0
//         std::cout << BLUE << "<================ RESIZE ================>\n" << NCLR;

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

//         nl;

//         std::cout << YELLOW << "[ my numbers ]\n" << NCLR;
//         for (myIterator = my_numbers.begin(); myIterator != my_numbers.end(); myIterator++)
//             std::cout << *myIterator << ' ';

//         std::cout << "\n\n";
// #endif

// #if 0
//         std::cout << BLUE << "<========== ASSIGN ==========>\n" << NCLR;

//         push_back_numbers(std_numbers, 17);
//         push_back_numbers(my_numbers, 17);
//         print_each_element_and_size(std_numbers, my_numbers);
//         print_size_and_capacity(std_numbers, my_numbers);

//         std::cout << PURPLE << "... current vertors ... \n" << NCLR;
//         print_each_element_and_size(std_numbers, my_numbers);
//         print_size_and_capacity(std_numbers, my_numbers);

//         std::vector<int> new_s;
//         ft::vector<int> new_m;

//         std::cout << PURPLE << "... new vertors ... \n" << NCLR;

//         new_s.assign(std_numbers.crbegin(), std_numbers.crend());
//         new_m.assign(my_numbers.crbegin(), my_numbers.crend());

//         print_each_element_and_size(new_s, new_m);
//         print_size_and_capacity(new_s, new_m);
// #endif

// #if 0
//         std::cout << BLUE << "<========== INSERT ==========>\n" << NCLR;

//         push_back_numbers(std_numbers, 10);
//         push_back_numbers(my_numbers, 10);
//         print_each_element_and_size(std_numbers, my_numbers);
//         print_size_and_capacity(std_numbers, my_numbers);

//         std::cout << PURPLE << " ... after insert ... \n" << NCLR;

//         //                 [    position    ]   [        first         ]  [         last          ]
//         std_numbers.insert(std_numbers.begin(), std_numbers.begin() + 2, std_numbers.begin() + 8);
//         my_numbers.insert(my_numbers.begin(), my_numbers.begin() + 2, my_numbers.begin() + 8);
        
//         print_each_element_and_size(std_numbers, my_numbers);
//         print_size_and_capacity(std_numbers, my_numbers);

// #endif

// #if 0
//         std::cout << BLUE << "<=========== ERASE ==========>\n" << NCLR;
//         push_back_numbers(std_numbers, 11);
//         push_back_numbers(my_numbers, 11);
//         print_each_element_and_size(std_numbers, my_numbers);
//         print_size_and_capacity(std_numbers, my_numbers);

//         // std_numbers.erase(std_numbers.begin(), std_numbers.begin() + 5);
//         // my_numbers.erase(my_numbers.begin(), my_numbers.begin() + 5);

//         // print_each_element_and_size(std_numbers, my_numbers);
//         // print_size_and_capacity(std_numbers, my_numbers);

//         std::cout << " ... vector comparison ...\n";

//         ft::vector<int> zzz;
//         std::vector<int> xxx;
//         push_back_numbers(zzz, 11);
//         push_back_numbers(xxx, 11);

//         print_each_element_and_size(xxx, zzz);
//         print_size_and_capacity(xxx, zzz);

//         std::cout << "zzz > my_numbers returns " << (zzz > zzz) << '\n';
//         std::cout << "xxx > std_numbers returns " << (xxx > xxx) << '\n';
// #endif
// }

// void test_two()
// {
// #if MY_ALLOCATOR
//         std::cout << B_PURPLE << "... USING MY OWN ALLOCATOR ...\n" << NCLR;

//         std::vector< std::string, ft::allocator<std::string> > std_strings;

//         ft::vector< std::string, ft::allocator<std::string> > my_strings;
//         ft::vector< std::string, ft::allocator<std::string> > my_strings2;
// #else
//         std::vector<std::string> std_strings;
//         ft::vector<std::string> my_strings;
//         ft::vector<std::string> my_strings2;
// #endif

//     for (size_t i(0); i < 10; i++)
//         std_strings.push_back("x");

//     for (size_t i(0); i < 10; i++)
//         my_strings.push_back("x");

//     for (size_t i(0); i < 10; i++)
//         my_strings2.push_back("x");

//     print_each_element_and_size(my_strings, my_strings2);
//     print_size_and_capacity(my_strings, my_strings2);

//     my_strings = my_strings2;

//     print_each_element_and_size(my_strings, my_strings2);
//     print_size_and_capacity(my_strings, my_strings2);
// }

// void test_three()
// {
//         std::cout << BLUE << "<=========== STACK ==========>\n" << NCLR;

//         std::stack<int> sst;
//         ft::stack<int> mst;
//         ft::stack<int> xst;

//         sst.push(22);
//         sst.push(22);
//         sst.push(55);
//         sst.push(77);

//         mst.push(33);
//         mst.push(33);
//         mst.push(33);
//         mst.push(44);

//         xst.push(33);
//         xst.push(33);
//         xst.push(33);
//         xst.push(44);

//         std::cout << "________sst________\n";
//         std::cout << "TOP: " << sst.top() << '\n';
//         std::cout << "________mst________\n";
//         std::cout << "TOP: " << mst.top() << '\n';

//         sst.pop();
//         mst.pop();
//         xst.pop();

//         std::cout << "________sst________\n";
//         std::cout << "TOP: " << sst.top() << '\n';
//         std::cout << "________mst________\n";
//         std::cout << "TOP: " << mst.top() << '\n';

//         std::cout << "mst == xst returns " << (mst == xst) << '\n';
// }

void test_four()
{
    std::cout << BLUE << "<============ MAP ===========>\n" << NCLR;

    std::map<int, int> smap;

    // std::map<int, int> xmap;
    ft::map<int, int> zmap;
    

    smap.insert(std::pair<int, int>(50, 33)); // 1
    smap.insert(std::pair<int, int>(60, 33)); // 3
    smap.insert(std::pair<int, int>(70, 33)); // 3
    smap.insert(std::pair<int, int>(10, 33));
    smap.insert(std::pair<int, int>(40, 33)); // 2
    smap.insert(std::pair<int, int>(30, 33));

    zmap.insert(std::pair<int, int>(50, 33)); // top
    zmap.insert(std::pair<int, int>(60, 33)); // top
    zmap.insert(std::pair<int, int>(70, 33)); // top
    zmap.insert(std::pair<int, int>(10, 33));
    zmap.insert(std::pair<int, int>(40, 33)); // top
    zmap.insert(std::pair<int, int>(30, 33)); // top

    // xmap.insert(smap.begin(), smap.end());
    // zmap.insert(smap.begin(), smap.end());

    // xmap.insert(std::pair<int, int>(50, 33));
    // xmap.insert(std::pair<int, int>(60, 33));
    // xmap.insert(std::pair<int, int>(70, 33));
    
    // zmap.insert(std::pair<int, int>(50, 33)); // top
    // zmap.insert(std::pair<int, int>(60, 33)); // check 2
    // zmap.insert(std::pair<int, int>(70, 33)); // check 2



    std::map<int, int>::iterator it = smap.begin();
    ft::map<int, int>::iterator zit = zmap.begin();

    std::cout << "\n___________BEGIN___________\n\n";
    std::cout << "smap begin first: " << it->first << '\n';
    std::cout << "smap begin second: " << it->second << '\n';

    std::cout << "zmap begin first: " << zit->first << '\n';
    std::cout << "zmap begin second: " << zit->second << '\n';

    zmap.callInOrder();

    std::cout << "size: " << zmap.size() << '\n';

    // std::cout << "\n____________END____________\n\n";

    // it = xmap.end();
    // zit = zmap.end();

    // --it;
    // --zit;

    // std::cout << "xmap end first: " << it->first << '\n';
    // std::cout << "xmap end second: " << it->second << '\n';

    // std::cout << "zmap end first: " << zit->first << '\n';
    // std::cout << "zmap end second: " << zit->second << '\n';
}

int main()
{

    try
    {
        // std::cout << B_BLUE << "\n################# START #################\n\n" << NCLR;
        // test_one();
        // test_two();
        // test_three();
        test_four();
    }
    catch(std::exception const &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return (0);
}