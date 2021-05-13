#include <iostream>
#include <algorithm>

class Entity
{
    int counter;

public:
    Entity() : counter(0){};
    void increment()
    {
        [obj = *this]() mutable {
            obj.counter++;
        }();
    }
    void printCounterVal() { std::cout << "counter : " << counter << "\n"; }
};

int main()
{
    //*****************************************************************************************************************************************************
    std::string str = "Hello World";

    [&strRef = str, strCpy = str]() {
        std::cout << "Printed using refernce inside lambda : "; // strRef is not external to this Lambda
        std::for_each(std::begin(strRef), std::end(strRef), [](const char &ch) {
            std::cout << ch;
        });
        std::cout << "\nPrinted using copy inside lambda    : "; // strCpy is not external to this Lambda
        std::for_each(std::begin(strCpy), std::end(strCpy), [](const char &ch) {
            std::cout << ch;
        });
    }(); // the () at the end of the lambda is to invoke it immediately

    std::cout << "\n****************************************************************\n";

    //*****************************************************************************************************************************************************

    // initialize variable for the lambda
    [i = 2, y = 1]() { std::cout << "i:" << i << " || y:" << y; }();

    std::cout << "\n****************************************************************\n";

    //*****************************************************************************************************************************************************

    int externVar = 5;
    std::cout << "externVar before : " << externVar;
    //to do any change on an external non refernce variable taken into scope, the mutable keyword is needed.
    [externVar]() mutable {
        externVar++; //The change will not persit outside the lambda
        std::cout << " || externVar inside lambda : " << externVar;
    }();
    std::cout << " || externVar after : " << externVar;

    std::cout << "\n****************************************************************\n";

    //*****************************************************************************************************************************************************

    auto add = [](int a, int b) -> int { return a + b; };
    std::cout << "Add using lambda : " << add(5, 6);

    std::cout << "\n****************************************************************\n";

    //*****************************************************************************************************************************************************
    Entity entityInst;
    entityInst.increment();
    entityInst.increment();
    entityInst.printCounterVal();
    std::cin.get();
    return 0;
}