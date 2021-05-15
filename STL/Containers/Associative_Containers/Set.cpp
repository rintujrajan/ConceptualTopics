#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#include "Entity.h"

void checkInsert(std::set<Entity> mySet)
{
    std::cout << "*** Modifier - Insert ***\n";
    auto entityToInsert = Entity{2, "Bravo"};
    std::cout << "Trying to insert " << entityToInsert << "...\n"; //would not be inserted since it already exists

    // The single element insert version return a pair,
    // pair::first set to an iterator pointing to either the newly inserted element or to the equivalent element already in the set.
    // pair::second element in the pair is set to true if a new element was inserted or false if an equivalent element already existed.
    std::pair<std::set<Entity>::iterator, bool> ret = mySet.insert(entityToInsert);
    if (ret.second == false)
    {
        std::cout << "Element already present. Returned iterator to the position of the element :" << *ret.first << "\n";
    }

    entityToInsert = Entity{5, "Echo"};
    std::cout << "Trying to insert " << entityToInsert << "...\n";
    ret = mySet.insert(entityToInsert);
    if (ret.second == false)
    {
        std::cout << "Element already present. Returned iterator to the position of the element present :" << *ret.first << "\n";
    }
    else
    {
        std::cout << "Element inserted. Returned iterator to the position of the element :" << *ret.first << "\n";
    }
    printContainerValues(mySet, "MySet contents after single insertion");

    // insert using initializer list
    mySet.insert({Entity{5, "ECHO"}, Entity{6, "Foxtrot"}, Entity{7, "Golf"}});
    printContainerValues(mySet, "MySet contents after insertion using initializer list");

    // insert using iterators of another container
    std::vector<Entity> myVec{Entity{8, "Hotel"}, Entity{10, "Juliet"}};
    mySet.insert(myVec.begin(), myVec.end());
    printContainerValues(mySet, "MySet contents after insertion using iterators of another container");

    /*
    //insert using hint
    If you check the file bits/stl_tree.h (in GNU libstdc++),
    you'll find that the _M_insert_unique member function with a hint argument looks one node to the left of the hint, then one node to the right,
    then defaults to calling the ordinary insert routine.
    */
    auto mySetIt = mySet.begin();
    // The function optimizes its insertion time if position points to the element(10) that will follow the inserted element(9)(definition)
    // We advance iterator such that we are on the position of element {10, "Juliet"}. This would act as the hint to insert new element{9, "India"} to left
    std::advance(mySetIt, mySet.size() - 1);
    mySet.insert(mySetIt, Entity{9, "India"});
    printContainerValues(mySet, "MySet contents after insertion using position hint");
}

void checkErase(const std::set<Entity> &setParam)
{
    {
        auto mySet = setParam;
        // Erase by iterator position
        auto mySetIt = mySet.begin();
        std::advance(mySetIt, 3);
        std::cout << "From original set, we shall remove iterator position having element " << *mySetIt << "..\n";
        mySetIt = mySet.erase(mySetIt); //returns Iterator following the last removed element.
        if (mySetIt != mySet.end())     // check that the return value is not end(if we removed the last element from set)
        {
            std::cout << "Return value(iterator) after erase : " << *mySetIt << "\n";
        }
        printContainerValues(mySet, "MySet contents after erasing element by iterator position");
    }
    {
        auto mySet = setParam;
        // Erase by value
        auto entityToRemove = Entity{3, "Charlie"};
        std::cout << "From original set, we shall remove  element " << entityToRemove << "..\n";
        auto ret = mySet.erase(entityToRemove); //Returns number of elements removed (0 or 1).
        std::cout << "Return value after erase : " << ret << "(number of elements removed (0 or 1))\n";
        printContainerValues(mySet, "MySet contents after erasing element by value");
    }
    {
        auto mySet = setParam;
        // Erase elements in range
        auto mySetIt = mySet.begin();
        std::advance(mySetIt, 2);
        std::cout << "From original set, we shall remove all elements from iterator position " << *mySetIt << "..\n";
        auto ret = mySet.erase(mySetIt, mySet.end()); //returns Iterator following the last removed element.
        // if (mySetIt != mySet.end())                   // check that the return value is not end(if we removed the last element from set)
        // {
        //     std::cout << "Return value(iterator) after erase : " << *mySetIt << "\n";
        // }
        printContainerValues(mySet, "MySet contents after erasing element by iterator range");
    }
}

int main()
{
    //*****************************************************

    // using custom data type for set
    // operator< is to be overloaded
    std::set<Entity> mySet{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};
    printContainerValues(mySet, "MySet original contents");

    //*****************************************************
    // Modifier - Insert
    //checkInsert(mySet);

    //*****************************************************
    // Modifier - erase
    checkErase(mySet);

    std::cin.get();
    return 0;
}
