#include <vector>
#include <iostream>
#include <algorithm>

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
    return t.key==12;
}
void usingFindIf(const vector<Tuple> &tuples)
{
    //using Lambda expression
    auto keyToLookUp = 6;
    auto pair = find_if(tuples.begin(),tuples.end(),
    [keyToLookUp](const Tuple &t){ return t.key==keyToLookUp;});
    cout<<"Key '"<<keyToLookUp<<"' has value '"<<pair->value<<"'"<<endl;

    //using function predicate
    auto pair2 = find_if(tuples.begin(),tuples.end(),findIfTuple);
    cout<<"Key '12' has value '"<<pair2->value<<"'"<<endl;
}
//FIND IF END

int main()
{
    vector<Tuple> tuples;
    auto temp = 'a';
    for (int i = 1; i <= 15; i++)
    {
         tuples.emplace_back(Tuple{i,temp++});
    }
    printVector(tuples);
    
    // find_if is used whenever we need to have a conditional predicate
    // OR 
    // in our case to work on non primitive data types like a struct
    usingFindIf(tuples);

    cin.get();
    return 0;
}