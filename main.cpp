#include <vector>
#include <string>
#include <stack>
#include <map>

#include "utils/utils.hpp"
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

void test_one()
{
        // std::cout << GREEN << ">> EMPTY VECTOR OF INTS <<\n" << NCLR;

#if MY_ALLOCATOR
        std::cout << B_PURPLE << "... USING MY OWN ALLOCATOR ...\n" << NCLR;
        std::vector< int, ft::allocator<int> > std_numbers;
        ft::vector< int, ft::allocator<int> > my_numbers;
#else
        std::vector<int> std_numbers;
        ft::vector<int> my_numbers;
#endif


#if 1
        std::cout << BLUE << "<================ RESIZE ================>\n" << NCLR;

        std::cout << PURPLE << "... before ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << PURPLE << "... numbers.resize(10, 1) ... \n" << NCLR;
        std_numbers.resize(10, 1);
        my_numbers.resize(10, 1);

        std::cout << PURPLE << "... after ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << BLUE << "<================ RESERVE ================>\n" << NCLR;

        std::cout << PURPLE << "... before ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << PURPLE << "... numbers.reserve(16) ... \n" << NCLR;
        std_numbers.reserve(16);
        my_numbers.reserve(16);

        std::cout << PURPLE << "... after ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << BLUE << "<================ ITERATOR ================>\n" << NCLR;

        push_back_numbers(std_numbers, 10);
        push_back_numbers(my_numbers, 10);

        std::vector<int>::iterator stdIterator = std_numbers.begin();
        ft::vector<int>::iterator myIterator = my_numbers.begin();

        std::cout << YELLOW << "[ std numbers ]\n" << NCLR;
        for (stdIterator = std_numbers.begin(); stdIterator != std_numbers.end(); stdIterator++)
            std::cout << *stdIterator << ' ';

        nl;

        std::cout << YELLOW << "[ my numbers ]\n" << NCLR;
        for (myIterator = my_numbers.begin(); myIterator != my_numbers.end(); myIterator++)
            std::cout << *myIterator << ' ';

        std::cout << "\n\n";
#endif

#if 1
        std::cout << BLUE << "<================ ASSIGN ================>\n" << NCLR;

        push_back_numbers(std_numbers, 17);
        push_back_numbers(my_numbers, 17);
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << PURPLE << "... current vertors ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::vector<int> new_s;
        ft::vector<int> new_m;

        std::cout << PURPLE << "... assign all values from current vectors to new vectors ... \n" << NCLR;
        std::cout << PURPLE << "... new_numbers.assign(crbegin, crend) ... \n" << NCLR;
        new_s.assign(std_numbers.crbegin(), std_numbers.crend());
        new_m.assign(my_numbers.crbegin(), my_numbers.crend());

        std::cout << PURPLE << "... new vertors ... \n" << NCLR;
        print_each_element_and_size(new_s, new_m);
        print_size_and_capacity(new_s, new_m);
#endif

#if 1
        std::cout << BLUE << "<================ INSERT ================>\n" << NCLR;

        push_back_numbers(std_numbers, 10);
        push_back_numbers(my_numbers, 10);
        std::cout << PURPLE << " ... before ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);


        std::cout << PURPLE << " ... numbers.insert(begin, begin + 2, begin + 8) ... \n" << NCLR;
        //                 [    position    ]   [        first         ]  [         last          ]
        std_numbers.insert(std_numbers.begin(), std_numbers.begin() + 2, std_numbers.begin() + 8);
        my_numbers.insert(my_numbers.begin(), my_numbers.begin() + 2, my_numbers.begin() + 8);
        
        std::cout << PURPLE << " ... after ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

#endif

#if 1
        std::cout << BLUE << "<================ ERASE ================>\n" << NCLR;
        push_back_numbers(std_numbers, 11);
        push_back_numbers(my_numbers, 11);

        std::cout << PURPLE << " ... before ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << PURPLE << " ... numbers.erase(begin, begin + 5) ... \n" << NCLR;
        std_numbers.erase(std_numbers.begin(), std_numbers.begin() + 5);
        my_numbers.erase(my_numbers.begin(), my_numbers.begin() + 5);

        std::cout << PURPLE << " ... after ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << " ... vector comparison ...\n";

        ft::vector<int> zzz;
        std::vector<int> xxx;
        push_back_numbers(zzz, 11);
        push_back_numbers(xxx, 11);

        print_each_element_and_size(xxx, zzz);
        print_size_and_capacity(xxx, zzz);

        std::cout << "(zzz > my_numbers) ---> " << (zzz > my_numbers) << '\n';
        std::cout << "(xxx > std_numbers) ---> " << (xxx > std_numbers) << '\n';
        std::cout << "(zzz < my_numbers) ---> " << (zzz < my_numbers) << '\n';
        std::cout << "(xxx < std_numbers) ---> " << (xxx < std_numbers) << '\n';
        std::cout << "(zzz <= my_numbers) ---> " << (zzz <= my_numbers) << '\n';
        std::cout << "(xxx <= std_numbers) ---> " << (xxx <= std_numbers) << '\n';
        std::cout << "(zzz >= my_numbers) ---> " << (zzz >= my_numbers) << '\n';
        std::cout << "(xxx >= std_numbers) ---> " << (xxx >= std_numbers) << '\n';
        std::cout << "(zzz == my_numbers) ---> " << (zzz == my_numbers) << '\n';
        std::cout << "(xxx == std_numbers) ---> " << (xxx == std_numbers) << '\n';

        
#if 1
        std::cout << BLUE << "<================ SWAP ================>\n" << NCLR;

        std::cout << PURPLE << " ... BEFORE ... \n" << NCLR;
        std::cout << PURPLE << " ... first vectors ... \n" << NCLR;
        push_back_numbers(std_numbers, 10);
        push_back_numbers(my_numbers, 10);
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std::cout << PURPLE << " ... second vectors ... \n" << NCLR;
        push_back_numbers(xxx, 10);
        push_back_numbers(zzz, 10);
        print_each_element_and_size(xxx, zzz);
        print_size_and_capacity(xxx, zzz);

        std_numbers.swap(xxx);
        my_numbers.swap(zzz);

        std::cout << PURPLE << " ... AFTER ... \n" << NCLR;
        std::cout << PURPLE << " ... first vectors ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);
        std::cout << PURPLE << " ... second vectors ... \n" << NCLR;
        print_each_element_and_size(xxx, zzz);
        print_size_and_capacity(xxx, zzz);

#endif

#if 1
        std::cout << BLUE << "<================ CLEAR ================>\n" << NCLR;

        std::cout << PURPLE << " ... BEFORE ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

        std_numbers.clear();
        my_numbers.clear();
        new_s.clear();
        new_m.clear();
        xxx.clear();
        zzz.clear();

        std::cout << PURPLE << " ... AFTER ... \n" << NCLR;
        print_each_element_and_size(std_numbers, my_numbers);
        print_size_and_capacity(std_numbers, my_numbers);

#endif

#endif
}

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

    print_each_element_and_size(my_strings, my_strings2);
    print_size_and_capacity(my_strings, my_strings2);

    my_strings = my_strings2;

    print_each_element_and_size(my_strings, my_strings2);
    print_size_and_capacity(my_strings, my_strings2);
}

void test_three()
{
        std::stack<int> sst;
        ft::stack<int> mst;
        ft::stack<int> xst;

        std::cout << "sst push: 22, 22, 55, 77\n";

        sst.push(22);
        sst.push(22);
        sst.push(55);
        sst.push(77);

        std::cout << "mst push: 33, 33, 33, 44\n";

        mst.push(33);
        mst.push(33);
        mst.push(33);
        mst.push(44);

        std::cout << "xst push: 33, 33, 33, 44\n";

        nl;

        std::cout << "sst size: "; sst.size(); nl ;
        std::cout << "mst size: "; mst.size(); nl ;
        std::cout << "xst size: "; xst.size(); nl ;

        xst.push(33);
        xst.push(33);
        xst.push(33);
        xst.push(44);

        std::cout << "________sst________\n";
        std::cout << "TOP: " << sst.top() << '\n';
        std::cout << "________mst________\n";
        std::cout << "TOP: " << mst.top() << '\n';
        std::cout << "________xst________\n";
        std::cout << "TOP: " << xst.top() << '\n';

        nl;

        std::cout << "sst pop\n";
        sst.pop();
        std::cout << "mst pop\n";
        mst.pop();
        std::cout << "xst pop\n";
        xst.pop();

        std::cout << "________sst________\n";
        std::cout << "TOP: " << sst.top() << '\n';
        std::cout << "________mst________\n";
        std::cout << "TOP: " << mst.top() << '\n';
        std::cout << "________xst________\n";
        std::cout << "TOP: " << xst.top() << '\n';

        nl;

        std::cout << "(mst == xst) ---> " << (mst == xst) << '\n';
        std::cout << "(mst < xst) ---> " << (mst < xst) << '\n';
        std::cout << "(mst > xst) ---> " << (mst > xst) << '\n';
        std::cout << "(mst <= xst) ---> " << (mst <= xst) << '\n';
        std::cout << "(mst >= xst) ---> " << (mst >= xst) << '\n';
        std::cout << "(mst != xst) ---> " << (mst != xst) << '\n';

        nl;

}

void test_four()
{
    std::map<int, int> smap;
    std::map<int, int> smap_copy;
    ft::map<int, int> zmap;
    ft::map<int, int> zmap_copy;

    smap.insert(std::pair<int, int>(50, 50));
    smap.insert(std::pair<int, int>(60, 60));
    smap.insert(std::pair<int, int>(70, 70));
    smap.insert(std::pair<int, int>(10, 10));
    smap.insert(std::pair<int, int>(20, 20));
    smap.insert(std::pair<int, int>(40, 40));
    smap.insert(std::pair<int, int>(30, 30));
    smap.insert(std::pair<int, int>(65, 65));
    smap.insert(std::pair<int, int>(100, 100));
    smap.insert(std::pair<int, int>(5, 5));
    smap.insert(std::pair<int, int>(120, 120));
    smap.insert(std::pair<int, int>(34, 34));

    zmap.insert(std::pair<int, int>(50, 50));
    zmap.insert(std::pair<int, int>(60, 60));
    zmap.insert(std::pair<int, int>(70, 70));
    zmap.insert(std::pair<int, int>(10, 10));
    zmap.insert(std::pair<int, int>(20, 20));
    zmap.insert(std::pair<int, int>(40, 40));
    zmap.insert(std::pair<int, int>(30, 30));
    zmap.insert(std::pair<int, int>(65, 65));
    zmap.insert(std::pair<int, int>(100, 100));
    zmap.insert(std::pair<int, int>(5, 5));
    zmap.insert(std::pair<int, int>(120, 120));
    zmap.insert(std::pair<int, int>(34, 34));

    std::cout << "smap size: " << smap.size() << '\n';
    std::cout << "zmap size: " << zmap.size() << '\n';

    std::map<int, int>::iterator it = smap.begin();
    ft::map<int, int>::iterator zit = zmap.begin();


    it = smap.begin();
    zit = zmap.begin();

    std::cout << "\n_______ALL ELEMENTS________\n\n";

    std::cout << "smap: ";
    while (it != smap.end())
    {
        std::cout << it->first << ' ';
        it++;
    }

    nl;

    std::cout << "zmap: ";
    while (zit != zmap.end())
    {
        std::cout << zit->first << ' ';
        zit++;
    }

    nl;

    std::cout << "\n___________BEGIN___________\n\n";
    std::cout << "smap begin first: " << it->first << '\n';
    std::cout << "smap begin second: " << it->second << '\n';

    std::cout << "zmap begin first: " << zit->first << '\n';
    std::cout << "zmap begin second: " << zit->second << '\n';


    std::cout << "\n____________END____________\n\n";

    it = smap.end();
    zit = zmap.end();

    --it;
    --zit;

    std::cout << "smap end first: " << it->first << '\n';
    std::cout << "smap end second: " << it->second << '\n';

    std::cout << "zmap end first: " << zit->first << '\n';
    std::cout << "zmap end second: " << zit->second << '\n';

    std::cout << "\n____________FIND___________\n\n";

    std::cout << "if the node exists\n\n";
    std::cout << "smap find 40: " << (*smap.find(40)).second << '\n';
    std::cout << "zmap find 40: " << (*zmap.find(40)).second << '\n';
    std::cout << "\nif the node doesn't exist\n\n";
    std::cout << "smap find 40: " << (*smap.find(200)).second << '\n';
    std::cout << "zmap find 40: " << (*zmap.find(200)).second << '\n';

    std::cout << "\n____________COPY___________\n\n";

    std::cout << "copy from SMAP to SMAP_COPY up to number 40\n";
    std::cout << "copy from ZMAP to ZMAP_COPY up to number 40\n\n";

    smap_copy.insert(smap.begin(), smap.find(40));
    zmap_copy.insert(zmap.begin(), zmap.find(40));

    it = smap_copy.begin();
    zit = zmap_copy.begin();

    std::cout << "print all items from SMAP_COPY and ZMAP_COPY\n\n";

    std::cout << "smap_copy: ";
    while (it != smap_copy.end())
    {
        std::cout << it->first << ' ';
        it++;
    }

    nl;

    std::cout << "zmap_copy: ";
    while (zit != zmap_copy.end())
    {
        std::cout << zit->first << ' ';
        zit++;
    }

    std::cout << "\n_____________[]____________\n\n";

    std::cout << "smap [50]: " << smap[50] << '\n';

    it = smap.begin();
    zit = zmap.begin();

    while (it != smap.end())
    {
        std::cout << it->first << ' ';
        it++;
    }

    nl;

    std::cout << "zmap [50]: " << zmap[50] << '\n';

    while (zit != zmap.end())
    {
        std::cout << zit->first << ' ';
        zit++;
    }

    std::cout << "\n_____________AT____________\n\n";

    try
    {
        std::cout << "smap at 30: " << smap.at(30) << '\n';
        std::cout << "smap at 90: " << smap.at(90) << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    nl;

    try
    {
        std::cout << "zmap at 30: " << zmap.at(30) << '\n';
        std::cout << "zmap at 90: " << zmap.at(90) << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\n___________COUNT___________\n\n";

    std::cout << "smap count 30: " << smap.count(30) << '\n';
    std::cout << "smap count 90: " << smap.count(90) << '\n';
    std::cout << "zmap count 30: " << zmap.count(30) << '\n';
    std::cout << "zmap count 90: " << zmap.count(90) << '\n';

    std::cout << "\n___________ERASE___________\n\n";

    it = smap.begin();
    zit = zmap.begin();

    std::cout << "\n____ALL ELEMENTS BEFORE____\n\n";

    std::cout << "smap: ";
    while (it != smap.end())
    {
        std::cout << it->first << ' ';
        it++;
    }

    nl;

    std::cout << "zmap: ";
    while (zit != zmap.end())
    {
        std::cout << zit->first << ' ';
        zit++;
    }

    nl;

    std::cout << "\nerase: 5, 30, 65";

    smap.erase(5);
    zmap.erase(5);
    smap.erase(30);
    zmap.erase(30);
    smap.erase(65);
    zmap.erase(65);

    it = smap.begin();
    zit = zmap.begin();

    std::cout << "\n\n_____ALL ELEMENTS AFTER____\n\n";

    std::cout << "smap: ";
    while (it != smap.end())
    {
        std::cout << it->first << ' ';
        it++;
    }

    nl;

    std::cout << "zmap: ";
    while (zit != zmap.end())
    {
        std::cout << zit->first << ' ';
        zit++;
    }

    nl;
    nl;

    std::cout << "smap size: " << smap.size() << '\n';
    std::cout << "zmap size: " << zmap.size() << '\n';
    
    std::cout << "\n_______ALL ELEMENTS________\n\n";

    it = smap.begin();
    zit = zmap.begin();

    std::cout << "smap: ";
    while (it != smap.end())
    {
        std::cout << it->first << ' ';
        it++;
    }

    nl;

    std::cout << "zmap: ";
    while (zit != zmap.end())
    {
        std::cout << zit->first << ' ';
        zit++;
    }

    nl;

    std::cout << "\n____________SWAP___________\n\n";

    zmap_copy.insert(std::pair<int, int>(51, 51));
    zmap_copy.insert(std::pair<int, int>(61, 61));
    zmap_copy.insert(std::pair<int, int>(71, 71));
    zmap_copy.insert(std::pair<int, int>(11, 11));
    zmap_copy.insert(std::pair<int, int>(21, 21));
    zmap_copy.insert(std::pair<int, int>(41, 41));
    zmap_copy.insert(std::pair<int, int>(31, 31));

    std::cout << "\n____ALL ELEMENTS BEFORE____\n\n";

    zit = zmap.begin();
    ft::map<int, int>::iterator zit_copy = zmap_copy.begin();

    std::cout << "zmap copy: ";
    while (zit_copy != zmap_copy.end())
    {
        std::cout << zit_copy->first << ' ';
        zit_copy++;
    }

    nl;

    std::cout << "zmap:      ";
    while (zit != zmap.end())
    {
        std::cout << zit->first << ' ';
        zit++;
    }

    zmap.swap(zmap_copy);

    std::cout << "\n\n_____ALL ELEMENTS AFTER____\n\n";

    zit = zmap.begin();
    zit_copy = zmap_copy.begin();

    std::cout << "zmap copy: ";
    while (zit_copy != zmap_copy.end())
    {
        std::cout << zit_copy->first << ' ';
        zit_copy++;
    }

    nl;

    std::cout << "zmap:      ";
    while (zit != zmap.end())
    {
        std::cout << zit->first << ' ';
        zit++;
    }

    zmap.swap(zmap_copy);

    std::cout << "\n\n____LOWER / UPPER BOUND____\n\n";
    
    std::cout << "smap lower bound: " << smap.lower_bound(12)->second << '\n';
    std::cout << "zmap lower bound: " << zmap.lower_bound(12)->second << '\n';

    nl;

    std::cout << "smap upper bound: " << smap.upper_bound(20)->second << '\n';
    std::cout << "zmap upper bound: " << zmap.upper_bound(20)->second << '\n';

    std::cout << "\n_______ALL ELEMENTS________\n\n";

    it = smap.begin();
    zit = zmap.begin();

    std::cout << "smap: ";
    while (it != smap.end())
    {
        std::cout << it->first << ' ';
        it++;
    }
    nl;
    std::cout << "zmap: ";
    while (zit != zmap.end())
    {
        std::cout << zit->first << ' ';
        zit++;
    }

    std::cout << "\n\n________EQUAL RANGE________\n\n";

    typedef std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> stdDoubleIntPair;
    typedef std::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> ftDoubleIntPair;

    stdDoubleIntPair std_ret = smap.equal_range(11);
    ftDoubleIntPair ft_ret = zmap.equal_range(11);

    std::cout << std_ret.first->first << " std => " << std_ret.first->second << '\n';
    std::cout << std_ret.second->first << " std => " << std_ret.second->second << '\n';

    nl;

    std::cout << ft_ret.first->first << " ft => " << ft_ret.first->second << '\n';
    std::cout << ft_ret.second->first << " ft => " << ft_ret.second->second << '\n';

    std::map<int, int> new_smap(smap);
    ft::map<int, int> new_zmap(zmap);

    it = smap.begin();
    zit = zmap.begin();

    ft::map<int, int>::iterator new_iter = new_zmap.begin();

    std::cout << "\n_______ALL ELEMENTS________\n\n";

    std::cout << "smap: ";
    while (it != smap.end())
    {
        std::cout << it->first << ' ';
        it++;
    }

    nl;

    std::cout << "zmap: ";
    while (new_iter != new_zmap.end())
    {
        std::cout << new_iter->first << ' ';
        new_iter++;
    }

    nl;

    // zmap.callInOrder();
}

int main()
{

    try
    {
        std::cout << B_BLUE << "\n################# START #################\n\n" << NCLR;
        std::cout << GREEN << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        std::cout << "\t\t\t\tVECTOR\t\t\t\t\n";
        std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << NCLR << '\n';
        test_one();
        // test_two();
        std::cout << GREEN << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        std::cout << "\t\t\t\tSTACK\t\t\t\t\n";
        std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << NCLR << '\n';
        test_three();
        std::cout << GREEN << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        std::cout << "\t\t\t\tMAP\t\t\t\t\n";
        std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << NCLR << '\n';
        test_four();
    }
    catch(std::exception const &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return (0);
}