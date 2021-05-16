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