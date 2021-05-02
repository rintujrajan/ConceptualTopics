#include <iostream>
#include <memory>

class Entity
{
private:
    std::weak_ptr<Entity> m_pFriend; // if made shared_ptr the created entities would not be destroyed because of cyclic dependency
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
    void setFriend(std::shared_ptr<Entity> friendEntity)
    {
        m_pFriend = friendEntity;
    }
};

int main()
{
    {
        std::cout << "Example 1:\n";
        // Example 1
        std::shared_ptr<Entity> orange = std::make_shared<Entity>("Orange");
        std::shared_ptr<Entity> lemon = std::make_shared<Entity>("Lemon");
        orange->setFriend(lemon);
        lemon->setFriend(orange);
    }
    {
        std::cout << "\n\nExample 2:\n";
        //Example 2
        Entity *mango = new Entity("Mango");
        Entity *mangoRef = mango;
        delete mango;
        // usage of mangoRef can lead to undefined behaviour

        std::cout << "\n\n";
        // instead for the refernce use weak pointer
        std::shared_ptr<Entity> appleShared = std::make_shared<Entity>("SharedApple");
        std::weak_ptr<Entity> appleWeakRef = appleShared;

        if (std::shared_ptr<Entity> sharedAppleInstance = appleWeakRef.lock())
        {
            std::cout << "The appleWeakRef exists currently\n";
        }
        else
        {
            std::cout << "The appleWeakRef no longer exists\n";
        }

        appleShared.reset();

        if (std::shared_ptr<Entity> sharedAppleInstance = appleWeakRef.lock())
        {
            std::cout << "The appleWeakRef exists currently\n";
        }
        else
        {
            std::cout << "The appleWeakRef no longer exists\n";
        }
    }
    std::cin.get();
    return 0;
}