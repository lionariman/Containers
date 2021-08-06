#include <iostream>

/*

Excploration of new cpp features

*/

template < class T > class A
{
    static const int i = 5;
    int n1[i]; // i refers to a member of the current instantiation
    int n2[A::i]; // A::i refers to a member of the current instantiation
    int n3[A<T>::i]; // A<T> i refers to a member of the current instantiation

public:
    int f();

    int *getArr(int const &numofarr);
};

template < class T >
int A<T>::f()
{
    return this->i; // i refers to a member of the current instantiation  
}

template < class T >
int *A<T>::getArr(int const &numofarr)
{
    switch (numofarr)
    {
        case 1:
            return this->n1;
            break;

        case 2:
            return this->n2;
            break;

        case 3:
            return this->n3;
            break;

        default:
            break;
    }
    return (NULL);
}

int main()
{
    A<int> a;

    std::cout << "I: " << a.f() << std::endl;

    for (int i(0); i < 5; i++) {
        a.getArr(3)[i] = 0;
        std::cout << "ARR: " << a.getArr(3)[i] << std::endl;
    }

    return (0);
}