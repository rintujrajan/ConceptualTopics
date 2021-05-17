#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
#include <list>

using namespace std;
struct Tuple
{
    int key;
    char value;
};
struct TupleOfString
{
    int key;
    std::string value;
};
template <typename T>
void print(const T &container, const std::string &msg = "")
{
    cout << "\n*************** "
         << msg << " ***************\n";
    for (const auto &elem : container)
    {
        cout << elem.key << "\t" << elem.value << endl;
    }
}

int main()
{
    vector<Tuple> myVec;
    auto temp = 'a';
    for (int i = 1; i <= 10; i++)
    {
        myVec.emplace_back(Tuple{i, temp++});
    }
    print(myVec, "Original vector contents");

    /*
    
    The parameter passed in lambda function is not needed as refernce, since the return value replaces by overwriting the element by the returned element
    
    for_each vs transform:
    1. for_each can modify the iterated element in place, while transform returns the modified element and is overwritten in the sequence in the position specified
    2. since for_each modifies in place, it cannot change the container which is being iterated on to change its size. transform can do that
    3. while iterating transform can take single argument(unary operation) from one iterator and copy the modified element in same container or a second different container
    4. while iterating transform can take two arguments(binary operation ) from two iterators and copy the modified element in same container or a third different container

    */

    // returns the modified element and is overwritten in the sequence in the position specified
    // while iterating transform can take single argument(unary operation) from one iterator and copy the modified element in same container
    std::transform(myVec.begin(), myVec.end(), myVec.begin(),
                   [count = 1](Tuple tuple) mutable
                   {
                       if (count % 2 == 0)
                       {
                           tuple.key *= 10;
                       }
                       else
                       {
                           tuple.value -= 32;
                       }
                       count++;
                       return tuple;
                   });
    print(myVec, "Same vector after multiply even position key by 10 and capitalize odd position values");

    // returns the modified element and is overwritten in the sequence in the position specified
    // while iterating transform can take single argument(unary operation) from one iterator and copy the modified element in second different container
    std::deque<Tuple> myDQ; //size could be preallocated, instead we use inserter which can be dynamic
    std::transform(myVec.cbegin(), myVec.cend(), std::back_inserter(myDQ),
                   [count = 1](Tuple tuple) mutable
                   {
                       if (count % 2 == 0)
                       {
                           tuple.key /= 10;
                       }
                       else
                       {
                           tuple.value += 32;
                       }
                       count++;
                       return tuple;
                   });

    print(myDQ, "A new Deque being transformed by taking the transformed vector and changing back to original state");

    std::list<TupleOfString> myList;
    std::transform(myVec.cbegin(), myVec.cend(), myDQ.cbegin(), std::back_inserter(myList),
                   [](Tuple tupleFromVec, Tuple tupleFromDQ)
                   {
                       TupleOfString tupleToReturn;
                       tupleToReturn.key = tupleFromVec.key + tupleFromDQ.key;
                       tupleToReturn.value += tupleFromVec.value;
                       tupleToReturn.value += tupleFromDQ.value;
                       return tupleToReturn;
                   });
    print(myList, "A new list being transformed by adding the vector and deque values");

    cin.get();
    return 0;
}