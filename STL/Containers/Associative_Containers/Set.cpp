#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#include "Entity.h"

void checkInsert(std::set<Entity> mySet)
{
    std::cout << "*** Modifier - Insert ***\n";
    printContainerValues(mySet, "MySet original contents");
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
    std::cout << "*** Modifier - Erase ***\n";
    printContainerValues(setParam, "MySet original contents");
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
        std::cout << "From original set, we shall remove by value the element " << entityToRemove << "..\n";
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

void checkLowerBound(const std::set<Entity> &mySet)
{
    printContainerValues(mySet, "MySet original contents");
    /*
    
    The function returns an iterator pointing to the element which is just greater than current element.
    In case element is not present in the set container, the function returns an iterator pointing to the immediate next element which is just greater than cur element.
    If the key passed in the parameter exceeds the maximum value in the container, then the iterator returned is equivalent to end() 
    */
    auto entityToCheckLowerBound = Entity{3, "Charlie"};
    auto mySetIt = mySet.lower_bound(entityToCheckLowerBound);
    std::cout << "Searching for lower_bound of entity " << entityToCheckLowerBound << ", the returned iterator value is " << *mySetIt << "\n";

    entityToCheckLowerBound = Entity{5, "Echo"}; // not present,upper_bound shall be returned
    mySetIt = mySet.lower_bound(entityToCheckLowerBound);
    std::cout << "Searching for lower_bound of entity " << entityToCheckLowerBound << ", the returned iterator value is " << *mySetIt << "\n";

    entityToCheckLowerBound = Entity{12, "Lima"}; // not present in the max bound
    mySetIt = mySet.lower_bound(entityToCheckLowerBound);
    if (mySetIt != mySet.end())
    {
        std::cout << "Searching for lower_bound of entity " << entityToCheckLowerBound << " , the returned iterator value is " << *mySetIt << "\n";
    }
    else
    {
        std::cout << "entity " << entityToCheckLowerBound << " could not be found. Reached end()\n";
    }
}

void checkUpperBound(const std::set<Entity> &mySet)
{
    printContainerValues(mySet, "MySet original contents");
    /*
    
    The function returns an iterator pointing to the element in the container which is equivalent to k passed in the parameter.
    In case k is not present in the set container, the function returns an iterator pointing to the immediate next element which is just greater than k.
    If the key passed in the parameter exceeds the maximum value in the container, then the iterator returned is equivalent to end() 
    */
    auto entityToCheckUpperBound = Entity{3, "Charlie"};
    auto mySetIt = mySet.upper_bound(entityToCheckUpperBound);
    std::cout << "Searching for upper_bound of entity " << entityToCheckUpperBound << ", the returned iterator value is " << *mySetIt << "\n";

    entityToCheckUpperBound = Entity{5, "Echo"};
    mySetIt = mySet.upper_bound(entityToCheckUpperBound); //not prsent, upper_bound shall be returned anyway
    std::cout << "Searching for upper_bound of entity " << entityToCheckUpperBound << ", the returned iterator value is " << *mySetIt << "\n";

    entityToCheckUpperBound = Entity{12, "Lima"}; // not present in the max bound
    mySetIt = mySet.upper_bound(entityToCheckUpperBound);
    if (mySetIt != mySet.end())
    {
        std::cout << "Searching for upper_bound of entity " << entityToCheckUpperBound << " , the returned iterator value is " << *mySetIt << "\n";
    }
    else
    {
        std::cout << "entity " << entityToCheckUpperBound << " could not be found. Reached end()\n";
    }
}

int main()
{
    //*****************************************************

    // using custom data type for set
    // operator< is to be overloaded - option 1
    std::set<Entity> mySet{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}, Entity{11, "Kilo"}};

    // functor is used as comparator - option 2. function with decltype can also be used as third option
    std::set<Entity, Comp> mySetUsingFunctor{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};

    int input = -1;
    while (input != 0)
    {
        std::cout << "\n\nSelect a set modifier operation :\n"
                  << "\t1.Insert\n"
                  << "\t2.Erase\n"
                  // not mentioned - emplace(same as insert except move semantics), clear (clears the set) , swap(swaps contents of two sets)
                  << "\t\tOR\n"
                  << "\tSelect a set lookup operation:\n"
                  << "\t3.Lower Bound\n"
                  << "\t4.Upper Bound\n"
                  // not mentioned - find(use consists[c++17] if only presence is to be detected)
                  << "\t0.Exit\n"
                  << "Your choice:";
        std::cin >> input;

        if (system("CLS"))
            system("clear"); //to clear screen

        switch (input)
        {
        case 0: //Exit
            return 0;
            break;
        case 1:
            //*****************************************************
            // Modifier - Insert
            checkInsert(mySet);
            // Instead of insert emplace can be used if doing in place creation to avoid a copy
            break;
        case 2:
            //*****************************************************
            // Modifier - erase
            checkErase(mySet);
            break;
        case 3:
            //*****************************************************
            // Lookup - lower_bound
            checkLowerBound(mySet);
            break;
        case 4:
            //*****************************************************
            // Lookup - upper_bound
            checkUpperBound(mySet);
            break;
        }
    }

    std::cin.get();
    return 0;
}
