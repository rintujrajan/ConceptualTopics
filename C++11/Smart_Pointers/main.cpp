#include <iostream>
#include <memory>

class Entity
{
private:
    std::string pName;

public:
    Entity(std::string name)
        : pName(name)
    {
        std::cout << "Created Entity: " << name << "\n";
    }
    ~Entity()
    {
        std::cout << "Destroyed Entity: " << pName << "!\n";
    }
    void setName(std::string name)
    {
        std::cout << "Pointer name changed from " << pName << " to " << name << "\n";
        pName = name;
    }
};

void checkUniquePointer()
{
    std::cout << "Checking Unique Pointer.. " << std::endl;
    {
        std::cout << "Entering scoped block.. " << std::endl;
        // Unique pointer

        // Two ways to utilize it
        // 1. Assign raw pointer to the unique ptr object
        std::unique_ptr<Entity> entityWithRawPointer(new Entity("UniqueEntityWithRawPointer"));
        std::cout << "entityWithRawPointer :" << entityWithRawPointer.get() << std::endl;

        /*
            2. Use the make_unique
            This is preferred since it is guaranteed that the pointer would be deleted when an exception happens
            Note with C++17 this issue should not happen
        */
        std::unique_ptr<Entity>
            entityWithMakeUnique = std::make_unique<Entity>("UniqueEntityWithMakeUnique");

        /*
            Since it is a unique pointer which can have only one unique pointer pointing one block of memory,
            the unique pointer cannot be copied.
            The copy constructor and copy assignment operator are deleted 
        */
        // std::unique_ptr<Entity> entityCopy = entityWithMakeUnique;    This will not work

        /*
            Although a unique pointer cannot be copied, it can be moved - ownership transferred
            Moving entityWithMakeUnique to entityCopy
        */
        entityWithMakeUnique->setName("EntityCopy");
        std::unique_ptr<Entity> entityCopy = std::move(entityWithMakeUnique); //This will work
        std::cout << "entityCopy :" << entityCopy.get() << std::endl;

        /*
            get() does not make unique_ptr release ownership of the pointer
            (it is still responsible for deleting the managed data at some point). Hence delete should not be called for the contained pointer
        */
        Entity *getEntityPointer = entityWithRawPointer.get();
        getEntityPointer->setName("GetEntityPointer");

        /*
            A step further than get(), 
            release() does not destroy the managed object, but the unique_ptr object is released from the responsibility of deleting the object.
            Some other ptr must take responsibility for deleting the object eventually since the unique_ptr becomes empty, managing no object.
        */
        Entity *releasedPointer = entityWithRawPointer.release();
        releasedPointer->setName("ReleasedPointer");
        delete releasedPointer; //this should not be missed since unique pointer no longer has owenership of this raw pointer

        /*
            Reset() would destroy the pointer and release ownership
            To release the ownership of the stored pointer without destroying it, use member function release instead.
            If any pointer is passed as parameter to reset function it would start managing it henceforth
        */
        entityCopy.reset();

        std::unique_ptr<Entity> entityGoingOutOfScopeOnExitingBlock = std::make_unique<Entity>("EntityGoingOutOfScopeOnExitingBlock");
        std::cout << "Exiting scoped block. Stack unwinding would happen to delete created smart pointers if existing.. " << std::endl;
    }
}

void checkSharedPointer()
{
    std::cout << "Checking Shared Pointer.. " << std::endl;
    std::shared_ptr<Entity> entityWithMakeShared;
    std::cout << "Shared Pointer Count:" << entityWithMakeShared.use_count() << std::endl;
    {
        std::cout << "Entering scoped block.. " << std::endl;
        // Shared pointer

        // Two ways to utilize it
        // 1. Assign raw pointer to the unique ptr object
        // This way is not preferred since it is less efficient (see reason below)
        std::shared_ptr<Entity> entityWithRawPointer(new Entity("SharedEntityWithRawPointer"));

        // 2. Use the make_shared
        /*
        This is the preferred way to use shared ptr
        std::make_shared performs a single heap-allocation accounting for the space necessary for both,
        the control block and the data. 
        In the other case, new Entity("foo") invokes a heap-allocation for the managed data
        and the std::shared_ptr constructor performs another one for the control block.

        Where do the heap-allocations happen?
            std::shared_ptr manages two entities:
            1. the control block (stores meta data such as ref-counts, type-erased deleter, etc) - thread safe
            2. the object being managed - not thread safe

        refer to https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c
        */
        entityWithMakeShared = std::make_shared<Entity>("SharedEntityWithMakeUnique");

        std::shared_ptr<Entity> copyOfEntityWithMakeShared = entityWithMakeShared;             // This will work unlike unique_ptr
        std::cout << "Shared Pointer Count:" << entityWithMakeShared.use_count() << std::endl; // copyOfEntityWithMakeShared.use_count() would be same

        std::cout << "Exiting scoped block.. " << std::endl;
    }
    std::cout << "Shared Pointer Count:" << entityWithMakeShared.use_count() << std::endl;
    std::cout << "Exiting function block.. " << std::endl;
}

void checkWeakPointer()
{
    // Weak pointer are used instead of having a shared pointer to break cycling references, dangling pointers etc.
    // Check out for uses - https://stackoverflow.com/questions/12030650/when-is-stdweak-ptr-useful
    std::cout << "Checking Weak Pointer.. " << std::endl;
    std::shared_ptr<Entity> entityWithMakeShared;
    std::cout << "Shared Pointer Count:" << entityWithMakeShared.use_count() << std::endl;
    {
        // initialising shared pointer
        entityWithMakeShared = std::make_shared<Entity>("SharedEntityWithMakeUnique");
        std::cout << "Shared Pointer Count:" << entityWithMakeShared.use_count() << std::endl;

        std::cout << "Creating weak pointer instance\n";
        std::weak_ptr<Entity> entityWeak = entityWithMakeShared;                               // weak pointer is always created as a copy of the shared pointer
        std::cout << "Shared Pointer Count:" << entityWithMakeShared.use_count() << std::endl; //no change in use_count

        if (std::shared_ptr<Entity> tmpShared = entityWeak.lock()) //thread safe and use this instead of checking for expired() function
        {
            std::cout << "Accessing SharedEntityWithMakeUnique via a weak pointer\n";
        }
        else
        {
            std::cout << "Weak Entity Pointer is out of scope";
        }

        std::cout << "Reseting Shared Entity Pointer\n";
        entityWithMakeShared.reset();
        std::cout << "Shared Pointer Count:" << entityWithMakeShared.use_count() << std::endl;

        if (std::shared_ptr<Entity> tmpShared = entityWeak.lock())
        {
            std::cout << "Accessing SharedEntityWithMakeUnique via a weak pointer\n";
        }
        else
        {
            std::cout << "Weak Entity Pointer is out of scope";
        }
    }
}

int main()
{
    checkUniquePointer();
    std::cout << "\n\n";
    checkSharedPointer();
    std::cout << "\n\n";
    checkWeakPointer();
    std::cin.get();
    return 0;
}