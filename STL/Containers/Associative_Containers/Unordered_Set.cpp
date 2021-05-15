#include <iostream>
#include <unordered_set>

#include "Entity.h"

int main()
{

    // Method 1 with Template Specialization
    std::unordered_set<Entity> myUOSetWithTemplateSpecialization{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};

    // Method 2 with Functor
    std::unordered_set<Entity, HashFunctionFunctor> myUOSetWithHashFunctor{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};

    // Method 3 with function
    std::unordered_set<Entity, decltype(&HashFunction)> myUOSetWithHashFunction{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};

    std::cin.get();
    return 0;
}
