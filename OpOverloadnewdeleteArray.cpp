#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;
class loc {
    int longitude, latitude;
    public:
    loc() {longitude = latitude = 0;}
    loc(int lg, int lt) {
        longitude = lg;
        latitude = lt;
    }
    void show() {
        cout << longitude << " ";
        cout << latitude << "\n";
    }
    void *operator new(size_t size);
    void operator delete(void *p);
    void *operator new[](size_t size);
    void operator delete[](void *p);
};

// new overloaded relative to loc.
void *loc::operator new(size_t size)
{
    void *p;
    cout << "In overloaded new.\n";
    p = malloc(size);
    if(!p) {
        bad_alloc ba;
        throw ba;
    }
    return p;
}

// delete overloaded relative to loc.
void loc::operator delete(void *p)
{
    cout << "In overloaded delete.\n";
    free(p);
}
// new overloaded for loc arrays.
void *loc::operator new[](size_t size)
{
    void *p;
    cout << "Using overload new[].\n";
    p = malloc(size);
    if(!p) {
        bad_alloc ba;
        throw ba;
    }
    return p;
}

// delete overloaded for loc arrays.
void loc::operator delete[](void *p)
{
    cout << "Freeing array using overloaded delete[]\n";
    free(p);
}
int main()
{
    loc *p1, *p2;
    int i;
    try {
        p1 = new loc (10, 20); // allocate an object
    } catch (bad_alloc xa) {
        cout << "Allocation error for p1.\n";
        return 1;
    }
    try {
        p2 = new loc [10]; // allocate an array
    } catch (bad_alloc xa) {
        cout << "Allocation error for p2.\n";
        return 1;
    }
    p1->show();
    for(i=0; i<10; i++)
    p2[i].show();
    delete p1; // free an object
    delete [] p2; // free an array
    return 0;
}

