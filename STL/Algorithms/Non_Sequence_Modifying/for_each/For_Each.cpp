#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
struct Tuple
{
    int key;
    char value;
};

template <typename T>
void printVector(const T &tuples)
{
    cout << "\nCurrent tuples:" << endl;
    for (const auto &tuple : tuples)
    {
        cout << tuple.key << "\t" << tuple.value << endl;
    }
}

int main()
{
    vector<Tuple> tuples;
    auto temp = 'a';
    for (int i = 1; i <= 15; i++)
    {
        tuples.emplace_back(Tuple{i, temp++});
    }
    printVector(tuples);

    std::cout << "Multiply even position key by 10 and capitalize odd position values..\n";
    /*
    
    necessary to pass paramater as refernce, since the values are modified in place(no values are returned)
        
    for_each vs transform:
    1. for_each can modify the iterated element in place, while transform returns the modified element and is overwritten in the sequence in the position specified
    2. since for_each modifies in place, it cannot change the container which is being iterated on to change its size. transform can do that

    */
    std::for_each(tuples.begin(), tuples.end(),
                  [count = 1](Tuple &tuple) mutable
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
                  });
    printVector(tuples);
    cin.get();
    return 0;
}