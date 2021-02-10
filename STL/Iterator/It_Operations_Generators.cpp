#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;
struct Tuple
{
    int key;
    char value;
};
void printVector(const vector<Tuple> &tuples)
{
    for (const auto &tuple : tuples)
    {
        cout << "\t" << tuple.key << "\t" << tuple.value << endl;
    }
}
void printDeQue(const deque<Tuple> &tuples)
{
    for (const auto &tuple : tuples)
    {
        cout << "\t" << tuple.key << "\t" << tuple.value << endl;
    }
}
void randomShuffle(vector<Tuple> &tuples)
{
    // obtain a random-device seed:
    std::random_device rdSeed;
    shuffle(tuples.begin(), tuples.end(), std::mt19937(rdSeed()));
}

void advance(vector<Tuple> tuples)
{
    /*
        std::advance
        Advances the iterator it by n element positions.
    */
    std::cout << "##### std::advance #####\n";

    cout << "\n***** Available Container *****\n";
    printVector(tuples);
    auto itTuple = tuples.begin();
    int advanceBy = 0;
    while (itTuple != --tuples.end())
    {
        std::advance(itTuple, advanceBy);
        std::cout << "Iterator advanced by " << advanceBy << " positions. Current iteration position values : " << itTuple->key << itTuple->value << "\n";
        advanceBy++;
    }
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
    vector<Tuple> tuples;
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
        case 1: //std::sort
            advance(tuples);
            /*
                std::stable_sort - NOT USED HERE
                Apart from std::sort there is another sort called std::stable_sort which uses mergesort
                The apparent use is to keep the order of equivalent isntances when sorting - use still to be found
            */
            break;
            // case 2: //partial_sort
            //     partialSort(tuples);
            //     break;
            // case 3: //partial_sort_copy
            //     partialSortCopy(tuples);
            //     break;
            // case 4: //nth_element
            //     nthElement(tuples);
            //     break;
            // case 5: //is_sorted
            //     isSorted(tuples);
            //     break;
            // case 6: //is_sorted_until
            //     isSortedUntil(tuples);
            //     break;
        }
    }
    return 0;
}