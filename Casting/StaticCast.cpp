#include <iostream>

class AnotherEntity
{
};

class Entity
{
    int memVar;
    std::string myString;

public:
    Entity() = default;

    Entity(int input) : memVar(input) {} // conversion operator to int

    Entity(std::string input) : myString(input) {} // conversion operator to string

    /*
    The return type of operator T() is always T. It's a special case of C++.
    It does not use standard function prototype syntax T foo() because, 2 functions with the same name differing only by the return type cannot coexist
    (e.g. int foo() conflicts with double foo()).
        
    */
    operator int() // conversion operator for Entity->int
    {
        return memVar;
    }
    operator std::string() // conversion operator for Entity->string
    {
        return myString;
    }

    operator AnotherEntity()
    {
        return AnotherEntity();
    }
};
class EntityDerived : public Entity
{
};

int main()
{
    Entity entityInst1 = 99;                 // conversion constructor (tries to convert single parameter int)
    int var = static_cast<int>(entityInst1); // conversion operator for int is called(Entity->int)
    std::cout << var;

    std::string inputString = "Hello World";
    Entity entityInst2 = inputString;                        // conversion constructor (tries to convert single parameter string)
    std::string str = static_cast<std::string>(entityInst2); // conversion operator for int is called(Entity->string)
    std::cin.get();

    Entity *entPtr = new Entity;
    EntityDerived *entityDerived = static_cast<EntityDerived *>(entPtr);

    AnotherEntity *anotherEntity = static_cast<AnotherEntity *>(entPtr);
}