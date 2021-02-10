#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <random>
template <typename T>
void bubbleSort(std::vector<T> &vec)
{
    std::cout << "##################\n";
    std::cout << "Before sort   : ";
    std::for_each(vec.begin(), vec.end(), [](const T &val) { std::cout << val << " "; });
    std::cout << std::endl;
    T temp = 0;
    for (int i = 0; i < vec.size() - 1; i++)
    {
        for (int j = 1; j < vec.size() - i; j++)
        {
            // std::cout << "i:" << i << " j:" << j << "|||";
            if (vec[j - 1] > vec[j])
            {
                temp = vec[j - 1];
                vec[j - 1] = vec[j];
                vec[j] = temp;
                std::cout << "Swapped " << vec[j - 1] << " & " << vec[j];
            }
            else
            {
                std::cout << "No swapping  ";
            }
            std::cout << "|||";
            std::for_each(vec.begin(), vec.end(), [](const T &val) { std::cout << val << " "; });
            std::cout << std::endl;
        }
    }
    std::cout << "After sort    : ";
    std::for_each(vec.begin(), vec.end(), [](const T &val) { std::cout << val << " "; });
    std::cout << std::endl;
    std::cout << "##################\n";
}
int main()
{
    std::vector<int> vecOfInt{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_device rdSeed;
    std::shuffle(vecOfInt.begin(), vecOfInt.end(), std::mt19937(rdSeed()));
    bubbleSort(vecOfInt);

    std::vector<char> vecOfChars{'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    std::shuffle(vecOfChars.begin(), vecOfChars.end(), std::mt19937(rdSeed()));
    bubbleSort(vecOfChars);

    std::cin.get();
}