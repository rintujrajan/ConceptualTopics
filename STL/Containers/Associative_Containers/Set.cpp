#include <iostream>
#include <set>
#include <unordered_set>

struct Entity
{
    int id;
    std::string name;

    /*
         for set/map
         If we want to store user-defined datatype in a set (eg. structure) then the compiler will show an error message.
         That is because of the property of the set that value kept in the set must be ascending or descending order.
         While doing so the compiler cant compare two structures(as they are user-defined) and that’s the reason why the compiler shows us the error message.
         So, in order to store a structure in a set, some comparison function need s to be designed
    */
    bool operator<(const Entity &entity) const
    {
        return id > entity.id;
    }

    /* 
        for unordered_set/unordered_map
        If we want to store the element of user defined type as structure then compiler will show an error
        because, before storing elements into unordered_set compiler performs some checking.
        And while comparing two user defined type compiler can not compare them hence it generate an error.
        So, in order to store a structure in a unordered_set, some comparison function need to be designed.
    */
    bool operator==(const Entity &entity) const
    {
        return id == entity.id;
    }
};

//struct for hash function
struct HashFunctionFunctor
{
    // id is returned as hash function
    size_t operator()(const Entity &entity) const
    {
        return entity.id;
    }
};

size_t HashFunction(const Entity &entity)
{
    return entity.id;
}

int main()
{
    std::set<Entity> mySet{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};

    // Method 1 with Functor
    std::unordered_set<Entity, HashFunctionFunctor> myUOSetWithHashFunctor{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};

    // Method 2 with function
    std::unordered_set<Entity, decltype(&HashFunction)> myUOSetWithHashFunction{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};

    std::cin.get();
    return 0;
}
