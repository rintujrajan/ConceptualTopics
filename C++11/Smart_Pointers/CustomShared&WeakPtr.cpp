#include <iostream>
#include <mutex>

template <typename T>
class SharedPtr
{
private:
    T *mPtr;
    int *refCount;
    static std::mutex mut;

public:
    SharedPtr() : mPtr(nullptr)
    {
        std::lock_guard<std::mutex> lg(mut);
        refCount = new int(0);
    };
    SharedPtr(T *ptrToShare) : mPtr(ptrToShare)
    {
        {
            std::lock_guard<std::mutex> lg(mut);
            refCount = new int(1);
        }
    }
    SharedPtr(const SharedPtr<T> &copyShrdPtr)
    {
        mPtr = nullptr;
        refCount = nullptr;
        if (copyShrdPtr.mPtr)
        {
            mPtr = copyShrdPtr.mPtr;
            refCount = copyShrdPtr.refCount;
            {
                std::lock_guard<std::mutex> lg(mut);
                (*refCount)++;
            }
        }
    }
    SharedPtr &operator=(const SharedPtr<T> &copyShrdPtr)
    {
        if (copyShrdPtr.mPtr)
        {
            mPtr = copyShrdPtr.mPtr;
            refCount = copyShrdPtr.refCount;
            {
                std::lock_guard<std::mutex> lg(mut);
                (*refCount)++;
            }
        }
        return *this;
    }
    SharedPtr(SharedPtr<T> &&movShrdPtr)
    {
        if (movShrdPtr.mPtr)
        {
            mPtr = movShrdPtr.mPtr;
            refCount = movShrdPtr.refCount;
            movShrdPtr.mPtr = nullptr;
            movShrdPtr.refCount = nullptr;
        }
    }
    SharedPtr<T> &operator=(SharedPtr<T> &&movShrdPtr)
    {
        if (mPtr != nullptr)
            delete mPtr;
        mPtr = movShrdPtr.mPtr;
        refCount = movShrdPtr.refCount;
        movShrdPtr.mPtr = nullptr;
        movShrdPtr.refCount = nullptr;
        return *this;
    }

    // auxilary functions and operators
    T *get()
    {
        return mPtr;
    }
    T *operator->()
    {
        return mPtr;
    }
    operator bool()
    {
        return mPtr != nullptr;
    }
    int use_count() { return *refCount; }

    void reset()
    {
        __cleanUp__();
        if (mPtr != nullptr)
        {
            delete mPtr;
            mPtr = nullptr;
        }
    }

    ~SharedPtr()
    {
        __cleanUp__();
    }

    void __cleanUp__()
    {
        if (mPtr != nullptr)
        {
            if (refCount != nullptr)
            {
                std::lock_guard<std::mutex> lg(mut);
                (*refCount)--;
            }
            if (*refCount == 0)
            {
                delete mPtr;
                mPtr = nullptr;

                delete refCount;
                refCount = nullptr;
            }
        }
    }
};
template <typename T>
std::mutex SharedPtr<T>::mut;

template <typename T>
class WeakPtr
{
private:
    SharedPtr<T> &msharedPtr;

public:
    // WeakPtr() : msharedPtr(nullptr){};
    WeakPtr(SharedPtr<T> &sharedPtr)
        : msharedPtr(sharedPtr) {}
    SharedPtr<T> lock()
    {
        return msharedPtr;
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
    void printValues(SharedPtr<Entity> &wrapperShrdPtr) const
    {
        std::cout << "This  Addr:" << this
                  << "\twrapperShrdPtr Addr" << &wrapperShrdPtr
                  << "\tval : " << wrapperShrdPtr.get()->val
                  << "\t\tvalptr : " << wrapperShrdPtr.get()->valPtr << "(" << *(wrapperShrdPtr.get()->valPtr) << ")"
                  << "\tTotal references : " << wrapperShrdPtr.use_count() << "\n";
    }
};

int main()
{

    int valueForPtr = 10;
    SharedPtr<Entity> sharedPtr(new Entity(5, &valueForPtr));
    sharedPtr.get()->printValues(sharedPtr);
    {
        SharedPtr<Entity> shareCpydPtr = sharedPtr; //Copy constructor
        shareCpydPtr.get()->printValues(shareCpydPtr);
    }
    sharedPtr.get()->printValues(sharedPtr);

    //***********************************************************************************************************************************************
    // Move constructor

    SharedPtr<Entity> sharedMovPtr(std::move(sharedPtr));
    if (sharedPtr) //operator bool
    {
        sharedPtr.get()->printValues(sharedPtr);
    }
    sharedMovPtr.get()->printValues(sharedMovPtr);

    //***********************************************************************************************************************************************
    // Move assignment operator

    SharedPtr<Entity> sharedMovPtr2;
    sharedMovPtr2 = std::move(sharedMovPtr);
    sharedMovPtr2.get()->printValues(sharedMovPtr2);

    //***********************************************************************************************************************************************
    // Weak Pointer

    WeakPtr<Entity> weakPtr = sharedMovPtr2;
    if (auto sharedPtrCreated = weakPtr.lock())
    {
        sharedPtrCreated.get()->printValues(sharedPtrCreated);
    }
    sharedMovPtr2.get()->printValues(sharedMovPtr2);
    sharedMovPtr2.reset();
    sharedMovPtr2.get()->printValues(sharedMovPtr2);
    if (auto sharedPtrCreated = weakPtr.lock())
    {
        sharedPtrCreated.get()->printValues(sharedPtrCreated);
    }
    else
    {
        std::cout << "Weak Ptr lock could not be obtained\n";
    }
    std::cin.get();
}