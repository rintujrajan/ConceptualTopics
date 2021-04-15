#include <iostream>

using namespace std;

template <typename T>
class UniquePtr
{
private:
    T *mPtr;

public:
    UniquePtr(const UniquePtr<T> &) = delete;
    UniquePtr<T> &operator=(const UniquePtr<T> &) = delete;
    UniquePtr() = default;
    UniquePtr(T *requestedPtr)
        : mPtr(requestedPtr)
    {
    }
    ~UniquePtr()
    {
        delete mPtr;
    }
    UniquePtr(UniquePtr<T> &&movPtr)
    {
        mPtr = movPtr.mPtr;
        movPtr.mPtr = nullptr;
    }
    UniquePtr<T> &operator=(UniquePtr<T> &&movPtr)
    {
        if (this != &movPtr)
        {
            mPtr = movPtr.mPtr;
            movPtr.mPtr = nullptr;
        }
        return *mPtr;
    }
    T *get()
    {
        return mPtr;
    }
    void reset()
    {
        delete this;
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
    void printValues(UniquePtr<Entity> *wrapperUnqPtr)
    {
        std::cout << "This  Addr:" << this
                  << "\tWrapperUnqPtr Addr" << wrapperUnqPtr
                  << "\tval : " << val
                  << "\t\tvalptr : " << *valPtr << "\n";
    }
};
int main()
{

    UniquePtr<Entity> unqPtr(new Entity);
    int valueForPtr = 10;
    unqPtr.get()->setValue(5, &valueForPtr);
    unqPtr.get()->printValues(&unqPtr);

    UniquePtr<Entity> movedUnqPtr(std::move(unqPtr));
    movedUnqPtr.get()->printValues(&movedUnqPtr);

    movedUnqPtr.reset();

    std::cin.get();
    return 0;
}
