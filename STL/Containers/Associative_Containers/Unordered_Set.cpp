#include <iostream>
#include <unordered_set>

#include "Entity.h"
inline void breakPart()
{
    std::cout << "\n*******************************************************************************************************\n\n";
}
int main()
{

    // Method 1 with Template Specialization
    std::unordered_set<Entity> myUOSetWithTemplateSpecialization{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}, Entity{3, "Charlie"}, Entity{11, "Foxtrot"}, Entity{12, "Echo"}};

    // Method 2 with Functor
    std::unordered_set<Entity, HashFunctionFunctor> myUOSetWithHashFunctor{Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}};

    // Method 3 with function/ lambda function - much tricky(use option 1/option 2)
    std::unordered_set<Entity, decltype(&HashFunction)> myUOSetWithHashFunction(4, HashFunction); //(bucket size, hash function)
    myUOSetWithHashFunction.insert({Entity{3, "Charlie"}, Entity{1, "Alpha"}, Entity{4, "Delta"}, Entity{2, "Bravo"}});

    auto &mySet = myUOSetWithTemplateSpecialization;
    printContainerValues(mySet, "Original Unordered_Set contents");

    // *************************************************************************************************************************************************
    /*
    
    Modifiers and look up operations are same as std::Set.
    There are additional functions in unordered_set since it uses hash table to store data.
    Below are the data associated with hash table.
    */
    // *************************************************************************************************************************************************

    // *************************************************************************************************************************************************
    /*
                                    *****************************   BUCKET INTERFACE   *****************************

    A bucket is a slot in the container's internal hash table to which elements are assigned based on their hash value.
    The number of buckets influences directly the load factor of the container's hash table (and thus the probability of collision).
    The container automatically increases the number of buckets to keep the load factor below a specific threshold (its max_load_factor),
    causing a rehash each time the number of buckets needs to be increased.

    */
    auto bucketCount = mySet.bucket_count(); //*** bucket_count - total rows/buckets in the hash table
    std::cout << "UO Set has size " << mySet.size() << " and " << bucketCount << " buckets";
    breakPart();

    for (unsigned i = 0; i < bucketCount; ++i) // loop through all buckets and print the bucket size and the bucket elements
    {
        std::cout << "bucket #" << i << " has " << mySet.bucket_size(i) << " element(s). It contains:"; //*** bucket_size total elements inside a row/bucket of HT
        for (auto it = mySet.begin(i); it != mySet.end(i); ++it)
        {
            std::cout << " " << *it;
        }
        std::cout << "\n";
    }
    breakPart();

    for (auto &&item : mySet) // loop through the set and print the bucket containing each of the item in the set
    {
        std::cout << item << " is in bucket #" << mySet.bucket(item) << std::endl; //*** bucket(item) - returns the order number of the bucket corresponding to the item
    }
    breakPart();

    // max_bucket_count is the maximum potential number of buckets the container can have due to system constraints or limitations on its library implementation.
    std::cout << "max_size = " << mySet.max_size() << "\tmax_bucket_count = " << mySet.max_bucket_count();
    breakPart();

    // *************************************************************************************************************************************************

    /*
                                        *****************************   HASH POLICY   *****************************

    The load factor is the ratio between the number of elements in the container (its size) and the number of buckets (bucket_count).
    The load factor influences the probability of collision in the hash table (i.e., the probability of two elements being located in the same bucket).

    By default, unordered_set containers have a max_load_factor of 1.0.
    The container uses the value of max_load_factor as the threshold that forces an increase in the number of buckets (and thus causing a rehash).

    */
    std::cout << "load_factor = " << mySet.load_factor() << "\tmax_load_factor = " << mySet.max_load_factor();
    breakPart();

    /*
    
    rehash(n)/reserve(n) => n is the new bucket_count
    If n is greater than the current no of buckets in the container(bucket_count),a rehash is forced.The new bucket count can either be equal or greater than n.
    If n is lower than the current number of buckets in the container(bucket_count),the function may have no effect on the bucket count and may not force a rehash.

    rehash vs reserve
    The difference is in purpose, although both are doing something similar.
    - rehash takes an existing map and rebuilds a new size of buckets, rehashing in the process and redistributing elements into the new buckets.
    - reserve guarantees you that if you don't insert more than the reserved number of elements, there will be no rehashing (i.e. your iterators will remain valid).

    reserve is just a wrapper around rehash. reserve is specified in terms of rehash(ceil(new bucket_count / max_load_factor()))

    */

    mySet.rehash(10); //no effect. Bucket count already 11
    mySet.rehash(12); //rehash would happen

    mySet.reserve(10); //no effect. Bucket count already 11
    mySet.reserve(12); //bucket count would be increased and rehash would happen

    std::cin.get();
    return 0;
}
