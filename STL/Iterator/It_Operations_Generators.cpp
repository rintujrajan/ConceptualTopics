#include <vector>
#include <deque>
#include <list>
#include <array>
#include <iostream>
#include <algorithm>
#include <random>
#include <set>
#include <unordered_set>

struct Tuple
{
    int key;
    char value;
    friend std::ostream &operator<<(std::ostream &out, const Tuple &tuple);
};
std::ostream &operator<<(std::ostream &out, const Tuple &tuple)
{
    out << tuple.key << "\t" << tuple.value << std::endl;
    return out;
}
template <typename Type>
void print(const Type &tuples, const std::string &msg = "")
{
    std::cout << "\n***** " << msg << " *****\n";
    int count = 0;
    for (const auto &tuple : tuples)
    {
        std::cout << "Pos:" << count << "\t" << tuple << std::endl;
        count++;
    }
}
template <typename Type>
void randomShuffle(Type &tuples)
{
    // obtain a random-device seed:
    std::random_device rdSeed;
    std::shuffle(tuples.begin(), tuples.end(), std::mt19937(rdSeed()));
}

template <typename Type>
void advance(Type &tuples)
{
    /*
        std::advance
        Advances the iterator it by n element positions.
    */
    std::cout << "##### std::advance #####\n";

    print(tuples, "Container data starting with");
    auto itTuple = tuples.begin();
    int advanceBy = 2;
    std::cout << "Advance by " << advanceBy << " positions iteratively.\n";
    while (itTuple != tuples.end())
    {
        std::cout << "Current iteration position values : " << itTuple->key << itTuple->value << "\n";
        std::advance(itTuple, advanceBy);
    }
}

template <typename Type>
void distance(Type &tuples)
{
    /*
        std::distance
        Returns the number of hops from first to last.
    */
    std::cout << "##### std::distance #####\n";

    print(tuples, "Container data starting with");
    auto itTuple = tuples.begin();
    int advanceBy = 2;
    std::cout << "Advance by " << advanceBy << " positions iteratively and get distance.\n";
    while (itTuple != tuples.end())
    {
        std::cout << "Distance between current iterator position and end : " << std::distance(itTuple, tuples.end()) << "\n";
        std::advance(itTuple, advanceBy);
    }
}

void backInserter()
{
    std::list<int> lst{1, 2, 3, 4, 5}; // the container to be inserted into should have push_back function(vector, deque, list). Not possible for array, set, map
    print(lst, "List before insertion");
    std::set<int> set{6, 7, 8, 9}; // can be any containers
    print(set, "Set to be inserted");
    std::copy(set.begin(), set.end(), std::back_inserter(lst)); // (starting iterator position, ending iterator position, (container to fill into) )
    print(lst, "List after insertion at end of list");
}

void frontInserter()
{
    std::deque<int> dq{1, 2, 3, 4, 5}; // the container to be inserted into should have push_back function(vector, deque, list). Not possible for array, set, map
    print(dq, "Deque before insertion");
    std::array<int, 4> arr{6, 7, 8, 9}; // can be any containers
    print(arr, "Array to be inserted");
    std::copy(arr.begin(), arr.end(), std::front_inserter(dq)); // (starting iterator position, ending iterator position, (container to fill into) )
    print(dq, "Deque after insertion at front of deque");
}

void inserter()
{
    std::vector<int> vec{1, 2, 3, 4, 5}; // the container to be inserted into should have insert function(all except array)
    print(vec, "Vec before insertion");
    std::array<int, 4> arr{6, 7, 8, 9}; // can be any containers
    print(arr, "Array to be inserted");
    auto vecIt = vec.begin();
    std::advance(vecIt, 2);
    std::copy(arr.begin() + 1, arr.end(), std::inserter(vec, vecIt)); // (starting iterator position, ending iterator position, (container to fill into, pos to insert) )
    print(vec, "Vec after insertion post two positions with array after first position");
}

int main()
{
    /*
        The Iterator types have been described in root stl folder note - Iterators_with_containers_supporting_them.txt
        The current code is to demonstrate Iterator Operations and Generators
        ** Iterator Operations(valid on all containers)
            1. advance - Advance iterator 
            2. distance - Return distance between iterators 
            3. begin - Iterator to beginning 
            4. end - Iterator to end 
            5. prev - Get iterator to previous element 
            6. next - Get iterator to next element 
        ** Iterator Generators
            1. back_inserter - Constructs a back-insert iterator that inserts new elements at the end of container
                * A back-insert iterator is a special type of output iterator designed to allow algorithms,
                  that usually overwrite elements (such as copy) to instead insert new elements automatically at the end of the container
                * Applicable on containers with a push_back member function (such as the standard containers vector, deque and list) 
            2. front_inserter - Constructs front insert iterator that inserts new elements at the beginning of a container
                * A front-insert interator is a special type of output iterator designed to allow algorithms,
                  that usually overwrite elements (such as copy) to instead insert new elements automatically at the beginning of the container
                * Applicable on containers with a push_front member function (such as the standard containers deque and list)
            3. inserter - Construct insert iterator that inserts new elements into x in successive locations starting at the position pointed by it
                * An insert interator is a special type of output iterator designed to allow algorithms,
                  that usually overwrite elements (such as copy) to instead insert new elements automatically at a specific position in the container
                * Applicable on containers with a insert member function (such as most standard containers)
            4. make_move_iterator - Construct move iterator
        
    */
    std::vector<Tuple> tuples;
    auto temp = 'a';
    for (int i = 1; i <= 8; i++)
    {
        tuples.emplace_back(Tuple{i, temp++});
    }
    randomShuffle(tuples);

    int input = -1;
    while (input != 0)
    {
        std::cout << "\n\nSelect an Iterator operation :\n"
                  << "\t1.std::advance\n"
                  << "\t2.std::distance\n"

                  << "\t\tOR\n"
                  << "\tSelect an Iterator Generator:\n"
                  << "\t3.std::back_inserter\n"
                  << "\t4.std::front_inserter\n"
                  << "\t5.std::inserter\n"
                  << "\t6.std::make_move_iterator\n"
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
            /*
                std::advance
                Advances the iterator it by n element positions.
                Complexity:
                Constant for random-access iterators.
                Otherwise, linear in n.
            */
            advance(tuples);
            break;
        case 2:
            /*
                std::distance
                Returns the number of hops from first to last.
                Complexity:
                Constant for random-access iterators.
                Otherwise, linear in n.
            */
            distance(tuples);
            break;
        case 3: //back_inserter
            /*
                Data from one container can be insterted into the back of another container
                The container to be inserted into should have push_back function(vector, deque, list). Not possible for array, set, map
                The container to be insterted can be any containers
            */
            backInserter();
            break;
        case 4: //front_inserter
            /*
                Data from one container can be insterted at the front of another container
                The container to be inserted into should have push_front function(vector, deque, list). Not possible for array, set, map
                The container to be insterted can be any containers
            */
            frontInserter();
            break;
        case 5: //inserter
            inserter();
            break;
        case 6: //make_move_iterator
            std::cout << "TBD\n";
            break;
        }
    }
    return 0;
}