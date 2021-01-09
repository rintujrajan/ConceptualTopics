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
    cout << "\n";
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

    cout << "\n***** Before sort *****";
    printVector(tuples);

    // sort descending order using predicate - predicates are functors that alsways return bool
    sort(tuples.begin(), tuples.end(), sortTupleDescending);

    cout << "\n***** After sorting descending order *****";
    printVector(tuples);

    //sort ascending order using Lambda expression
    sort(tuples.begin(), tuples.end(),
         [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; });

    // same as the above but,
    // we can also assign the lambda to an auto object so that we can reuse it if needed
    auto sortAscendingUsingLambda = [](const Tuple &t1, const Tuple &t2) { return t1.key < t2.key; };
    sort(tuples.begin(), tuples.end(), sortAscendingUsingLambda);

    cout << "\n***** After sorting ascending order *****";
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

    cout << "\n***** Before sort *****";
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
    cout << "\n***** After sorting ascending order upto element " << middleRange << " *****";
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

    cout << "\n***** The original container before sort *****";
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

    cout << "\n***** The original container after partial sort copy(unchanged) *****";
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

    cout << "\n***** The original container before sort *****";
    printVector(tuples);

    /*
        The below code shall sort only the 3rd element in the container and leave the rest are left without any specific order
    */
    int nthElementToSort = 2; // beginning at 0th
    std::nth_element(tuples.begin(), tuples.begin() + nthElementToSort, tuples.end(),
                     [](const Tuple &l, const Tuple &r) { return l.value < r.value; });

    cout << "\n***** After the element no. " << nthElementToSort + 1 << " is in sorted position  *****";
    printVector(tuples);
}

int main()
{
    /*
        The sort algorithms are used with containers having random access iterator support
        STL containers - deque, vector and array or any custom container which would support random access iterator 
    */
    vector<Tuple> tuples;
    auto temp = 'a';
    for (int i = 1; i <= 5; i++)
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
                  << "\t0.Exit\n"
                  << "Your choice:";
        std::cin >> input;
        if (system("CLS"))
            system("clear");
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
        }
    }
    return 0;
}