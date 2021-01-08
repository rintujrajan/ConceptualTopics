#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
struct Tuple
{
    int key;
    char value;
};

void printVector(const vector<Tuple> &tuples)
{
    cout<<"\nCurrent tuples:"<<endl;
    for (const auto &tuple : tuples)
    {
        cout<<tuple.key<<"\t"<<tuple.value<<endl;
    }
}


// SORT START
bool sortTuple(const Tuple &t1,const Tuple &t2)
{
    return t1.key>t2.key;
}
void usingSort(vector<Tuple> tuples)
{
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(tuples.begin(), tuples.end(), std::default_random_engine(seed));

    cout<<"After shuffle:";
    printVector(tuples);

    //sort descending order using predicate
    // sort(tuples.begin(),tuples.end(),
    // [](const Tuple &t1,const Tuple &t2){ return t1.key>t2.key;});
    sort(tuples.begin(),tuples.end(),sortTuple);

    cout<<"\nAfter sorting descending order:";
    printVector(tuples);

    //sort ascending order using Lambda expression
    sort(tuples.begin(),tuples.end(),
    [](const Tuple &t1,const Tuple &t2){ return t1.key<t2.key;});

    cout<<"\nAfter sorting ascending order:";
    printVector(tuples);
    
}
//SORT END

int main()
{
    vector<Tuple> tuples;
    auto temp = 'a';
    for (int i = 1; i < 15; i++)
    {
         tuples.emplace_back(Tuple{i,temp++});
    }
    printVector(tuples);

    usingSort(tuples);

    cin.get();
    return 0;
}