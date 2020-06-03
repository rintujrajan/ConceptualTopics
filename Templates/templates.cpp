#include <iostream>

using namespace std;

template <typename T>
class Maths
{
    public:
    T multiply(T a, T b)
    {
        return a * b;
    }
};
// template <typename T>
// T Maths<T>::multiply(T a, T b)
// {
//     return a * b;
// }
int main()
{
    Maths<int> mathInt;
    cout<<mathInt.multiply(5,5)<<endl;
    Maths<float> mathFloat;
    cout<<mathFloat.multiply(5.5,5.5);
   
    cin.get();
}