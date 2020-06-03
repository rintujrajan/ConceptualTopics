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

// FIND IF START
bool findIfTuple(const Tuple &t)
{
    return t.key==20;
}
void usingFindIf(const vector<Tuple> &tuples)
{
    //using Lamda expression
    auto keyToLookUp = 6;
    auto pair = find_if(tuples.begin(),tuples.end(),
    [keyToLookUp](const Tuple &t){ return t.key==keyToLookUp;});
    cout<<"Key '"<<keyToLookUp<<"' has value '"<<pair->value<<"'"<<endl;

    //using function predicate
    auto pair2 = find_if(tuples.begin(),tuples.end(),findIfTuple);
    cout<<"Key '20' has value '"<<pair2->value<<"'"<<endl;
}
//FIND IF END

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

    //sort ascending order using Lamda expression
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
    
    // find_if is used whenever we need to have a conditional predicate
    // OR 
    // in our case to work on non primitive data types like a struct
    usingFindIf(tuples);

    usingSort(tuples);

    cin.get();
    return 0;
}