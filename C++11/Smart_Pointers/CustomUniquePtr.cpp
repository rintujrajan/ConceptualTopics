#include <iostream>

using namespace std;

template <typename T>
class UniquePtr
{
private:
    T *mPtr;

public:
    // copy constructor and assignment are deleted
    UniquePtr(const UniquePtr<T> &) = delete;
    UniquePtr<T> &operator=(const UniquePtr<T> &) = delete;

    // constructors
    UniquePtr() : mPtr(nullptr){};
    UniquePtr(T *requestedPtr) : mPtr(requestedPtr) {}

    // move constructor
    UniquePtr(UniquePtr<T> &&movPtr)
    {
        std::cout << "Move constructor called\n";
        mPtr = movPtr.mPtr;
        movPtr.mPtr = nullptr;
    }

    // move assignment operator
    UniquePtr<T> &operator=(UniquePtr<T> &&movPtr)
    {
        std::cout << "Move assignment called\n";
        if (this != &movPtr)
        {
            __cleanUp__();
            mPtr = movPtr.mPtr;
            movPtr.mPtr = nullptr;
        }
        return *this;
    }

    // additional methods which can be used on unique ptr
    T *get()
    {
        return mPtr;
    }
    void reset()
    {
        __cleanUp__();
    }
    T &operator*()
    {
        return *mPtr;
    }
    T *operator->()
    {
        return mPtr;
    }

    // destructor
    ~UniquePtr()
    {
        __cleanUp__();
    }

    // support methods
    void __cleanUp__()
    {
        if (mPtr != nullptr)
        {
            delete mPtr;
            mPtr = nullptr;
        }
    }
};
class Entity
{
private:
    int val;
    int *valPtr;

public:
    void setValue(const int &valParam, int *valPtrParam)
    {
        val = valParam;
        valPtr = valPtrParam;
    }
    int getValue() { return val; }
    int *getValuePtr() { return valPtr; }
    void printValues(UniquePtr<Entity> *wrapperUnqPtr)
    {
        std::cout << "This  Addr:" << this
                  << "\tWrapperUnqPtr Addr" << wrapperUnqPtr
                  << "\tval : " << (*wrapperUnqPtr).get()->getValue()
                  << "\t\tvalptr : " << (*wrapperUnqPtr).get()->getValuePtr() << "\n";
    }
};
int main()
{

    UniquePtr<Entity> unqPtr(new Entity);
    int valueForPtr = 10;
    unqPtr.get()->setValue(5, &valueForPtr);
    unqPtr.get()->printValues(&unqPtr);

    UniquePtr<Entity> movedUnqPtr(std::move(unqPtr));
    std::cout << "Using get() : ";
    movedUnqPtr.get()->printValues(&movedUnqPtr);
    std::cout << "Using -> : ";
    movedUnqPtr->printValues(&movedUnqPtr);

    UniquePtr<Entity> movedUnqPtr1;
    movedUnqPtr1 = std::move(movedUnqPtr);

    movedUnqPtr.reset();

    std::cin.get();
    return 0;
}
