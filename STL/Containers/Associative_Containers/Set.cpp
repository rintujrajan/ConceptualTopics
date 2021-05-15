#include <iostream>
#include <set>

#include "Entity.h"

int main()
{
    std::set<Entity> mySet{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};

    std::cin.get();
    return 0;
}
