#include <iostream>
using namespace std;

namespace ft
{
    struct Node
    {
        string data;
        Node *next;

        Node(string &x) : data(x), next(nullptr) {}
    };

    struct list
    {
        Node *first;
        Node *last;
        int size;

        list() : first(nullptr), last(nullptr), size(0) {}

        bool is_empty() { return first == nullptr; }

        void push_back(string x)
        {
            Node *p = new Node(x);
            size++;
            if (is_empty()) { first = p; last = p; return ; }
            last->next = p;
            last = p;
        }

        Node *find(string const &x)
        {
            Node *p = first;
            while (p && p->data != x) p = p->next;
                return (p && p->data == x) ? p : nullptr;
        }

        void remove_first()
        {
            if (is_empty()) return ;
            Node *p = first;
            first = first->next;
            delete p;
        }

        void remove_last()
        {
            if (is_empty()) return ;
            if (first == last) { remove_first(); return ; }
            Node *p = first;
            while (p->next != last) { p = p->next; }
            p->next = nullptr;
            delete last;
            last = p;
        }

        void remove(string const &x)
        {
            if (is_empty()) return ;
            if (first->data == x) { remove_first(); return ; }
            if (last->data == x) { remove_last(); return ; }
            Node *p = first;
            while (p->next && p->next->data != x) p = p->next;
            if (p->next == nullptr) { cout << "this element dose not exist!\n"; }
            Node *z = p->next;
            p->next = p->next->next;
            delete z;
        }

        Node *operator[](const int index)
        {
            if (is_empty()) return nullptr;
            Node *p = first;
            for (int i = 0; i < index; ++i) { p = p->next; if (!p) return nullptr; }
            return p;
        }

        void print()
        {
            if (is_empty()) return ;
            Node *p = first;
            while (p) { cout << p->data << '\n'; p = p->next; }
            cout << endl;
        }
    };
}

int main()
{
    ft::list l;
    string one("a");
    char c = 'a';
    for (int i = 0; i < 20; ++i) { l.push_back(one); one += ++c; }
    l.remove_first();
    l.remove_last();
    l.remove("abcdef");
    l.remove_first();
    l.remove("abc");
    l.remove("abcdefghijklmnopqrs");
    l.print();
    cout << "operator[] -> " << l[6]->data << '\n';
    cout << "      find -> " << l.find("abcdefghijk")->data << '\n';
}
