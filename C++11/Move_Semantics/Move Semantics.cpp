#include <iostream>
#include <iomanip> // used for setting custom white space
#include <string>  //used only for support purpose of object name handling

// using namespace std;

int copyCounter = 1;
int moveCounter = 1;

/*
    C++ compiler provide default copy constructor (and assignment operator) with class. 
    When we don’t provide implementation of copy constructor (and assignment operator) 
    and tries to initialize object with already initialized object of same class then copy constructor gets called
    and copies members of class one by one in target object.

    The problem with default copy constructor (and assignment operator) is –
    When we have members which dynamically gets initialized at run time,
    default copy constructor copies this members with address of dynamically allocated memory and not real copy of this memory.
    Now both the objects points to the same memory and changes in one reflects in another object.
    Further the main disastrous effect is, when we delete one of this object other object still points to same memory,
    which will be dangling pointer, and memory leak is also possible problem with this approach.

    Hence, in such cases, we should always write our own copy constructor (and assignment operator).

    As per the rule of Big Five If we create any one of the copy constr, copy assignment, move constr, move assignment, destructor
    then all the five special member functions have to be created
*/
void memcpy(const void *dest, const void *src, size_t n)
{
    char *csrc = (char *)src;
    char *cdest = (char *)dest;
    for (int i = 0; i < n; ++i)
    {
        cdest[i] = csrc[i];
    }
}
size_t strlen(const char *str)
{
    size_t size = 0;
    while (str[size])
        ++size;
    return size;
}
class MoveSemantics
{
    const char *strPtr;
    int *intPtr;
    std::string objectName;

public:
    MoveSemantics() : strPtr(nullptr), intPtr(nullptr), objectName("")
    {
        std::cout << "Default constructor\n"
                  << std::endl;
    }

    MoveSemantics(const char *str, int intVal)
    {
        std::cout << "Parameterized constructor\t" << str << "\t" << intVal << "\n"
                  << std::endl;

        int strSize = strlen(str);

        strPtr = new char[strSize + 1];
        memcpy(strPtr, str, strSize + 1);

        intPtr = new int();
        *intPtr = intVal;

        objectName = str;
    }

    /*
        Copy Constructor
        Called when an object is created and copied in the same line of code e.g. MoveSemantics appleCopy1 = apple;
        The parameter takes const refernce so that it can take both lValue as an rValue(temporary values)
    */
    MoveSemantics(const MoveSemantics &moveSemantics)
    {
        std::cout << "Copy constructor" << std::endl;

        int strSize = strlen(moveSemantics.strPtr);

        strPtr = new char[strSize + 1];
        memcpy(strPtr, moveSemantics.strPtr, strSize + 1);

        intPtr = new int();
        // *intPtr = *(moveSemantics.intPtr);
        *this->intPtr = *moveSemantics.intPtr;

        objectName = moveSemantics.objectName + "Copy" + std::to_string(copyCounter++);

        std::cout << "Copied data of strPtr from addr " << &moveSemantics.strPtr << " of (" << moveSemantics.objectName << ") to " << &strPtr << " of (" << objectName << ")" << std::endl;
    }

    /*
        Copy Assignment
        Called when an already created object is being used to copy from another existing object e.g. appleCopy2 = apple; 
        The parameter takes const refernce so that it can take both lValue as an rValue(temporary values)
    */
    MoveSemantics &operator=(const MoveSemantics &moveSemantics)
    {
        std::cout << "Copy assignment" << std::endl;
        if (this != &moveSemantics)
        {
            int strSize = strlen(moveSemantics.strPtr);

            delete[] strPtr; // since there is a chance that the current object being copied into would have already been assigned we delete to avoid memory leak
            strPtr = new char[strSize + 1];
            memcpy(strPtr, moveSemantics.strPtr, strSize + 1);

            delete intPtr; // since there is a chance that the current object being copied into would have already been assigned we delete to avoid memory leak
            intPtr = new int();
            *intPtr = *(moveSemantics.intPtr);

            objectName = moveSemantics.objectName + "Copy" + std::to_string(copyCounter++);

            std::cout << "Copied data of strPtr from addr " << &moveSemantics.strPtr << " of (" << moveSemantics.objectName << ") to " << &strPtr << " of (" << objectName << ")" << std::endl;
        }
        else
        {
            std::cout << "Copy called on same object. Same object returned!\n"
                      << std::endl;
        }
        return *this;
    }

    /*
        Move Constructor
        Called when an object is created and moved(stealing resources) in the same line of code e.g. MoveSemantics mangoCopy1 = move(mango);
        The parameter takes rValue refernce. No constness is needed since it is a temporary refernce in the first place
    */
    MoveSemantics(MoveSemantics &&moveSemantics)
    {
        std::cout << "Move constructor" << std::endl;
        int strSize = strlen(moveSemantics.strPtr);

        strPtr = moveSemantics.strPtr;

        intPtr = moveSemantics.intPtr;

        objectName = moveSemantics.objectName + "Moved" + std::to_string(moveCounter++);

        moveSemantics.strPtr = nullptr;
        moveSemantics.intPtr = nullptr;
        //we will not reset the object name since we would like to keep it to identify the object name
    }

    /*
        Move Assignment
        Called when an already created object is being used to move data(stealing resources) from another existing object e.g. mangoCopy2 = move(mangoCopy1); 
        The parameter takes const refernce so that it can take both lValue as an rValue(temporary values)
    */
    MoveSemantics &operator=(MoveSemantics &&moveSemantics)
    {
        std::cout << "Move assignment" << std::endl;
        if (this != &moveSemantics)
        {
            int strSize = strlen(moveSemantics.strPtr);

            delete[] strPtr; // since there is a chance that the current object being copied into would have already been assigned we delete to avoid memory leak
            strPtr = moveSemantics.strPtr;

            delete intPtr; // since there is a chance that the current object being copied into would have already been assigned we delete to avoid memory leak
            intPtr = moveSemantics.intPtr;

            objectName = moveSemantics.objectName + "Moved" + std::to_string(moveCounter++);

            moveSemantics.strPtr = nullptr;
            moveSemantics.intPtr = nullptr;
            //we will not reset the object name since we would like to keep it to identify the object name
        }
        else
        {
            std::cout << "Move called on same object. Same object returned!\n"
                      << std::endl;
        }

        return *this;
    }

    // Destructor
    ~MoveSemantics()
    {
        std::cout << "Destructor called for : " << objectName << std::endl;

        // Delete all pointer objects which have been assigned memory using new keyword
        delete[] strPtr;
        delete intPtr;
    }
    friend std::ostream &operator<<(std::ostream &out, const MoveSemantics &ms);
};
std::ostream &operator<<(std::ostream &out, const MoveSemantics &ms)
{
    out << std::setw(18) << ms.objectName;
    out << "strptr: ";
    if (ms.strPtr != nullptr)
    {
        int strLength = strlen(ms.strPtr);
        for (int i = 0; i < strLength; i++)
        {
            out << ms.strPtr[i];
        }
    }
    else
    {
        out << "NULL";
    }

    out << "\tintptr: ";
    if (ms.intPtr != nullptr)
    {
        out << *ms.intPtr;
    }
    else
    {
        out << "NULL";
    }
    out << "\n";
    return out;
}
void myFunc()
{
    std::cout << std::left;

    MoveSemantics apple("apple", 1);  // Parameterized constructor will be called
    MoveSemantics appleCopy1 = apple; // Copy constructor will be called since a new object is being copied
    std::cout << "Checking the copy done..\n";
    std::cout << apple;
    std::cout << appleCopy1;

    MoveSemantics appleCopy2; // Default constructor called to create object
    appleCopy2 = apple;       // Copy assignment will be called since the object appleCopy2 is already created and will be only copied
    std::cout << "Checking the copy done..\n";
    std::cout << appleCopy2;

    appleCopy2 = appleCopy2; // Copy assignment is called but the same object shall be returned

    MoveSemantics mango("mango", 2);             // Parameterized constructor will be called
    MoveSemantics mangoCopy1 = std::move(mango); // Move constructor will be called since a new object is being created(mangocopy1) by moving existing object(mango)
    std::cout << "Checking the move done..\n";
    std::cout << mango;
    std::cout << mangoCopy1;

    mangoCopy1 = mangoCopy1;

    MoveSemantics mangoCopy2;           // Default constructor called to create object
    mangoCopy2 = std::move(mangoCopy1); // Move assignment will be called since the object(mangocopy2) is already created and data will be moved from existing object(mangoCopy1)
    std::cout << "Checking the move done..\n";
    std::cout << mangoCopy1;
    std::cout << mangoCopy2;

    mangoCopy2 = std::move(mangoCopy2); // Move assignment is called but the same object shall be returned

    std::cout << "\n\nDestructors: " << std::endl; // Destructors are called since the objects would be doing out of scope outside function scope
}

int main()
{
    myFunc();
    std::cin.get();
}