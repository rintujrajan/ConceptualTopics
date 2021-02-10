#include <iostream>

class Multiply
{
    int multiplicand;

public:
    Multiply()
    {
        std::cout << "Call for default constructor"
                  << "\n";
    }
    Multiply(int param) : multiplicand{param}
    {
        std::cout << "Call for constructor with 1 parameter.multiplicand:" << param << "\n";
    }
    int operator()(int multiplier)
    {
        std::cout << "Functor called with multiplier as " << multiplier << "\n";
        return multiplicand * multiplier;
    }
};

int add10(int num)
{
    return num + 10;
}

int multiplyFunc(int multiplicand, int multiplier)
{
    return multiplicand * multiplier;
}

int main()
{
    int multiplicand = 2;
    int multiplier = 3;
    Multiply mul = Multiply(multiplicand);
    Multiply multiply(multiplicand);
    int productUsingFunctor = multiply(multiplier);
    std::cout << "Multiplication product using functor: " << productUsingFunctor << "\n";

    auto lambdaFunc = [&multiplicand](int lMultiplier) -> int { return multiplicand * lMultiplier; };
    int productUsingLambda = lambdaFunc(multiplier);
    std::cout << "Multiplication product using lambda expression: " << productUsingLambda << "\n";

    int (*fpAdd10)(int);
    fpAdd10 = add10;
    std::cout << fpAdd10(20) << "\n";

    int (*functionPointer)(int, int);
    functionPointer = multiplyFunc;
    int productUsingFunctionPointer = functionPointer(multiplicand, multiplier);
    std::cout << "Multiplication product using functionPointer: " << productUsingFunctionPointer << "\n";

    auto functionPointerAuto = multiplyFunc;
    int productUsingFunctionPointerAuto = functionPointerAuto(multiplicand, multiplier);
    std::cout << "Multiplication product using functionPointerAuto: " << productUsingFunctionPointerAuto << "\n";

    std::cin.get();
}

/* 
	Lambda expressions are nothing but sugar coated functors
	
	E.g.
	auto func = [&](int multiplicand,int multiplier)->int{ return multiplicand*multiplier;}; becomes
	
	class __lambda_27_17
	{
    public: 
    inline  int operator()(int multiplicand, int multiplier) const
    {
      return multiplicand * multiplier;
    }
	};
	
	Lambda Expressions can be used to overload operator() for a single signature(2 parameters used above)
	Functors can have more than one operator() overloaded with different signatures(0 and 1 parameters are seen in the Multiply Functor Class)
  
*/