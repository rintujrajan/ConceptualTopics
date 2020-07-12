#include <iostream>

using namespace std;

class Base
{
    public:
    Base()
    {
        cout<<"Base class constructor\n"<<endl;
    }

    /* The destructor is made virtual so that when the destructor of this base class is called,
       the vtable shows a derived implemenation and it si also called
       If the destructor is not made virtual then the destructor of the derived class is not called
       and if it has any pointer objects then it would lead to memory leaks
    */
    virtual ~Base()
    {
        cout<<"Base class destructor\n"<<endl;
    }
};
class Derived:public Base
{
    public:
    Derived()
    {
        cout<<"Derived class constructor\n"<<endl;
    }

    ~Derived()
    {
        cout<<"Derived class destructor\n"<<endl;
    }

};

int main()
{
    
    Base* basePtr = new Derived();

    delete basePtr; //destructor called of base class and being a virtual one, it calls destcructor of derived class

    cin.get();
}