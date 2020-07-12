#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

void printPrimeNumbersInRange(int start, int end)
{

    bool breakLoop = false;
    int widthSize = to_string(end).length();
    for (int num = start; num <= end; ++num)
    {
        breakLoop = false;
        for(int i = 2;i<num;++i)
        {
            if(num%i==0)
            {
                breakLoop = true;
                break;
            }
        }
        if(!breakLoop && num != 1)
        {
            cout<<setw(widthSize)<<num<<"\t";
        }
    }
    
}

int main()
{
    cout<<right;
    printPrimeNumbersInRange(1,2000);
    cin.get();
}