#include <iostream>

int main(void)
{
    unsigned int buf1[sizeof(int) * 2];
    unsigned int buf2[2];


    // write items to buf1 and print them out
    for (int i(0); i < 2; ++i)
    {
        buf1[i] = i;
        std::cout << buf1[i] << std::endl;
    }

    // write items to buf2 and print them out
    for (int i(0); i < 2; ++i)
    {
        buf2[i] = i;
        std::cout << buf2[i] << std::endl;
    }
}