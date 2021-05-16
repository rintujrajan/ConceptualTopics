#pragma once
#include <iostream>

struct Entity
{
    int id;
    std::string name;

    /*

    ************ for set/map
    If we want to store user-defined datatype in a set (eg. structure) then the compiler will show an error message.
    That is because of the property of the set/map that value kept in the set must be ascending or descending order.
    While doing so the compiler cant compare two structures(as they are user-defined) and that’s the reason why the compiler shows us the error message.
    So, in order to store a structure in a set, some comparison function needs to be designed as the one below

    */
    // for set/map option - 1 lt comparator
    bool operator<(const Entity &entity) const
    {
        return id < entity.id;
    }

    /* 

    ************ for unordered_set/unordered_map
    If we want to store the element of user defined type as structure then compiler will show an error. Here a hash is used to maintain hash table.
    A comparison function for equality is required because the hash cannot rely on the fact that the hash function will always provide a unique hash value for every distinct key (i.e., it needs to be able to deal with collisions),
    so it needs a way to compare two given keys for an exact match.

    The other item to be defined is a hash function, in three optional ways which are defined below

    */
    bool operator==(const Entity &entity) const
    {
        return id == entity.id;
    }

    friend std::ostream &operator<<(std::ostream &out, const Entity &entity);
};
std::ostream &operator<<(std::ostream &out, const Entity &entity)
{
    out << "(" << entity.id << "," << entity.name << ")";
    return out;
}
// for set/map option - 2 comparator functor. 3rd option shall be function used with decltype
struct Comp
{
    bool operator()(const Entity &entityLHS, const Entity &entityRHS) const
    {
        return entityLHS.id < entityRHS.id;
    }
};

// for unordered_set/unordered_map - hash function specialization - option 1
namespace std
{
    template <>
    struct hash<Entity>
    {
        std::size_t operator()(const Entity &entity) const noexcept
        {
            return entity.id; //can be made complex, as a combination of the members
        }
    };
}

// for unordered_set/unordered_map - struct for hash function - option 2
struct HashFunctionFunctor
{
    // id is returned as hash function
    size_t operator()(const Entity &entity) const
    {
        return entity.id;
    }
};

// for unordered_set/unordered_map. Optional to the Functor above - option 3
size_t HashFunction(const Entity &entity)
{
    return entity.id;
}

template <typename Container>
void printContainerValues(const Container &container, const std::string &msg)
{
    std::cout << "*************** " << msg << " ***************\n";
    for (auto &&item : container)
    {
        std::cout << item << " ";
    }
    std::cout << "\n\n\n";
}