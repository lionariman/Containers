

#include <iostream>
#include <vector>

using namespace std;


int main()
{
    vector<int> buffer;

    // add 10 numbers to buffer
    for (size_t i = 0; i < 10; i++)
        buffer.push_back(i);

    // vector<int>::iterator it;
    // vector<int>::const_iterator it;
    // vector<int>::reverse_iterator it;
    vector<int>::const_reverse_iterator it;
    // vector<int>::reference ref;

    for (it = buffer.crbegin(); it != buffer.crend(); it++)
        cout << "nunmber: [ " << *it << " ]\n";

    return (0);
}