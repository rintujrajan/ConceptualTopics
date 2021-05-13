#include <iostream>

using namespace std;
template <typename T>
void CustomDeleter(const T *ptr)
{
    delete ptr;
}
template <typename T, typename TD = decltype(&CustomDeleter<T>)>
class UniquePtr
{
private:
    T *mPtr;
    TD customDeleter;

    // support methods
    void __cleanUp__()
    {
        if (mPtr != nullptr)
        {
            delete mPtr;
            // mPtr = nullptr;
            customDeleter(mPtr);
        }
    }

public:
    // copy constructor and assignment are deleted
    UniquePtr(const UniquePtr<T> &) = delete;
    UniquePtr<T> &operator=(const UniquePtr<T> &) = delete;

    // constructors
    UniquePtr() : mPtr(nullptr){};
    UniquePtr(T *requestedPtr) : mPtr(requestedPtr) {}
    UniquePtr(T *requestedPtr, TD providedDeleter) : mPtr(requestedPtr), customDeleter(providedDeleter) {}

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
};

class Entity
{
private:
    int val;
    int *valPtr;

public:
    Entity() = default;
    Entity(const int &valParam, int *valPtrParam)
    {
        val = valParam;
        valPtr = valPtrParam;
    }
    void printValues(UniquePtr<Entity> *wrapperUnqPtr)
    {
        std::cout << "This  Addr:" << this
                  << "\tWrapperUnqPtr Addr" << wrapperUnqPtr
                  << "\tval : " << (*wrapperUnqPtr).get()->val
                  << "\t\tvalptr : " << (*wrapperUnqPtr).get()->valPtr << "\n";
    }
};
int main()
{
    int valueForPtr = 10;
    UniquePtr<Entity> unqPtr(new Entity(5, &valueForPtr));
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
