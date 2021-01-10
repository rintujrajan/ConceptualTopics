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
    cout << "\n";
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

// SORT START
bool sortTupleDescending(const Tuple &t1, const Tuple &t2)
{
    return t1.key > t2.key;
}
void Sort(vector<Tuple> tuples)
{
    /*
        std::sort
        sort uses a sort called introsort, which is a hybrid of quicksort+heapsort
    */
    std::cout << "##### std::sort #####\n";

    cout << "\n***** Before sort *****\n";
    printVector(tuples);

    // sort descending order using predicate - predicates are functors that alsways return bool
    sort(tuples.begin(), tuples.end(), sortTupleDescending);

    cout << "\n***** After sorting descending order *****\n";
    printVector(tuples);

    //sort ascending order using Lambda expression
    sort(tuples.begin(), tuples.end(),
         [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; });

    // same as the above but,
    // we can also assign the lambda to an auto object so that we can reuse it if needed
    auto sortAscendingUsingLambda = [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; };
    sort(tuples.begin(), tuples.end(), sortAscendingUsingLambda);

    cout << "\n***** After sorting ascending order *****\n";
    printVector(tuples);
}
//SORT END

void partialSort(vector<Tuple> tuples)
{
    /*
        std::partial_sort
        Takes three parameters - range begin, range middle and range end apart from the optional comparator
    */
    std::cout << "\n\n##### std::partial_sort #####\n";

    cout << "\n***** Before sort *****\n";
    printVector(tuples);

    int middleRange = 2;
    /* 
        Sorts in such a way that from begin till the middle all values are sorted while,
        the remaining elements are left without any specific order(check the function example comment).

        As the middle range is 2, the first two elements would be the two smallest elements of the range from begin to end.
        The elements after position 2 will not have any specific order
        Use - first n sorted elements in a range 
    */
    std::partial_sort(tuples.begin(), tuples.begin() + middleRange, tuples.end(),
                      [](const Tuple &l, const Tuple &r) { return l.value < r.value; });
    cout << "\n***** After sorting ascending order upto element " << middleRange << " *****\n";
    printVector(tuples);
}

void partialSortCopy(vector<Tuple> tuples)
{
    /*
        std::partial_sort_copy
        Non-modifying algorithm as it does not change the source container.
        The contents from the original container is copied to a newer container in a sorted order based on the specified range
    */
    std::cout << "\n\n##### std::partial_sort_copy #####\n";

    cout << "\n***** The original container before sort *****\n";
    printVector(tuples);

    /*
        The 2nd element to the 4th element from the original container(vector-tuples) shall be sorted and copied to the new container(deque - tuplesSortedCopy) 
        It is obligatory for the new container to have atleast the size as the begin and end range provided for the original container
    */
    std::deque<Tuple> tuplesSortedCopy(3);
    int startRange = 1; //inclusive
    int endRange = 4;   //exclusive(not include in range)
    std::partial_sort_copy(tuples.begin() + startRange, tuples.begin() + endRange, tuplesSortedCopy.begin(), tuplesSortedCopy.end(),
                           [](const Tuple &l, const Tuple &r) { return l.value < r.value; });

    cout << "\n***** The new container after partial sort copy *****";
    printDeQue(tuplesSortedCopy);

    cout << "\n***** The original container after partial sort copy(unchanged) *****\n";
    printVector(tuples);
}

void nthElement(vector<Tuple> tuples)
{
    /*
        std::nthElement
        Rearranges the elements in the range [first,last),
        in such a way that the element at the nth position is the element that would be in that position in a sorted sequence.
        The other elements are left without any specific order, except that none of the elements preceding nth are greater than it,
        and none of the elements following it are less.

        The elements are compared using operator< for the first version, or with the compare for the complex operaions.
    */
    std::cout << "\n\n##### std::nthElement #####\n";

    cout << "\n***** The original container before sort *****\n";
    printVector(tuples);

    /*
        The below code shall sort only the 3rd element in the container and leave the rest are left without any specific order
    */
    int nthElementToSort = 2; // beginning at 0th
    std::nth_element(tuples.begin(), tuples.begin() + nthElementToSort, tuples.end(),
                     [](const Tuple &l, const Tuple &r) { return l.value < r.value; });

    cout << "\n***** After the element no. " << nthElementToSort + 1 << " is in sorted position  *****\n";
    printVector(tuples);
}

void isSorted(vector<Tuple> tuples)
{
    /*
        std::is_sorted
        Returns true if the range [begin,end) is in sorted order.
    */
    std::cout << "##### std::is_sorted #####\n";

    cout << "\n***** Before sort *****\n";
    printVector(tuples);
    std::cout << "std::is_sorted:" << std::boolalpha
              << std::is_sorted(tuples.begin(), tuples.end(), [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; });

    // let's sort it
    auto sortAscendingUsingLambda = [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; };
    sort(tuples.begin(), tuples.end(), sortAscendingUsingLambda);

    cout << "\n\n***** After sorting ascending order *****\n";
    printVector(tuples);
    std::cout << "std::is_sorted:" << std::is_sorted(tuples.begin(), tuples.end(), [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; });
}

void isSortedUntil(vector<Tuple> tuples)
{
    /*
        std::is_sorted_until
        Returns an iterator to the first element in the range [first,last) which does not follow an ascending order.
    */
    std::cout << "##### std::is_sorted_until #####\n";

    cout << "\n***** Before sort *****\n";
    printVector(tuples);
    std::cout << "std::is_sorted:" << std::boolalpha
              << std::is_sorted(tuples.begin(), tuples.end(), [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; });

    // let's sort first n elements using partial sort in a loop to see how it goes
    for (int middle = 1; middle < tuples.size(); ++middle)
    {
        auto sortAscendingUsingLambda = [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; };
        partial_sort(tuples.begin(), tuples.begin() + middle, tuples.end(), sortAscendingUsingLambda);

        cout << "\n\n***** After sorting first " << middle << " elements in ascending order *****\n";
        printVector(tuples);
        // would point to the first element which is not in order irrespective of wether it was part of sorting or not
        auto it = std::is_sorted_until(tuples.begin(), tuples.end(), [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; });
        if (it != tuples.end())
        {
            std::cout << "std::is_sorted_until:" << it->key << it->value << "\n";
        }
        else
        {
            std::cout << "All data sorted\n";
        }
    }
}

int main()
{
    /*
        The  sort algorithms are used with containers having random access iterator support
        STL containers - deque, vector, string and array or any custom container which would support random access iterator 

        The auxilary support functions to check if a container is sorted are used with containers having forward iterator support
        All STL containers support forward iterators
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
        std::cout << "\n\nSelect an algorithm :\n"
                  << "\t1.std::sort\n"
                  << "\t2.std::partial_sort\n"
                  << "\t3.std::partial_sort_copy\n"
                  << "\t4.std::nth_element\n"
                  << "\tAux support functions\n"
                  << "\t5.std::is_sorted\n"
                  << "\t6.std::is_sorted_until\n"
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
            Sort(tuples);
            /*
                std::stable_sort - NOT USED HERE
                Apart from std::sort there is another sort called std::stable_sort which uses mergesort
                The apparent use is to keep the order of equivalent isntances when sorting - use still to be found
            */
            break;
        case 2: //partial_sort
            partialSort(tuples);
            break;
        case 3: //partial_sort_copy
            partialSortCopy(tuples);
            break;
        case 4: //nth_element
            nthElement(tuples);
            break;
        case 5: //is_sorted
            isSorted(tuples);
            break;
        case 6: //is_sorted_until
            isSortedUntil(tuples);
            break;
        }
    }
    return 0;
}