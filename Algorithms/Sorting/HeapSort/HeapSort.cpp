#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <random>
#include <iomanip>
#include <chrono>

template <typename T>
void printVector(const std::vector<T> &vec, std::string message)
{
    std::cout << std::setw(20) << message << ": ";
    std::for_each(vec.begin(), vec.end(), [](const T &val) { std::cout << val << " "; });
    std::cout << "\n"
              << std::endl;
}
int maxRange;
template <typename T>
void heapify(std::vector<T> &vec, int curPos, bool returnBackAfterOnce = false)
{
    int curPosMarker = curPos; //at the end
    T temp;
    while (curPosMarker >= 0)
    {
        //get left child node
        int leftChildPos = curPosMarker * 2 + 1;
        int rightChildPos = curPosMarker * 2 + 2;
        if (leftChildPos <= maxRange)
        {
            if (vec[leftChildPos] > vec[curPosMarker])
            {
                //swap
                temp = vec[curPosMarker];
                vec[curPosMarker] = vec[leftChildPos];
                vec[leftChildPos] = temp;
                int leftPos = leftChildPos * 2 + 1;
                std::string message = "swapped " + std::to_string(vec[leftChildPos]) + " & " + std::to_string(vec[curPosMarker]);
                printVector(vec, message);
                if (leftPos <= maxRange)
                    heapify(vec, leftChildPos, true);
            }
            if (rightChildPos <= maxRange)
            {
                if (vec[rightChildPos] > vec[curPosMarker])
                {
                    //swap
                    temp = vec[curPosMarker];
                    vec[curPosMarker] = vec[rightChildPos];
                    vec[rightChildPos] = temp;
                    std::string message = "swapped " + std::to_string(vec[rightChildPos]) + " & " + std::to_string(vec[curPosMarker]);
                    printVector(vec, message);
                    int rightPos = rightChildPos * 2 + 2;
                    if (rightPos <= maxRange)
                        heapify(vec, rightChildPos, true);
                }
            }
        }
        if (returnBackAfterOnce)
            break;
        curPosMarker--;
    }
}

template <typename T>
void heapSort(std::vector<T> &vec)
{
    std::cout << "##################\n";
    printVector(vec, "Before sort");

    T top;

    for (int i = 0; i < vec.size(); ++i)
    {
        // first step is to Heapify(create a max heap) and then to delete one by one and add the deleted elements towards the end

        // Heapify

        // custom heapify-although does the job takes more time than the std heapify method - make_heap(used below) which is much efficient
        // maxRange = vec.size() - 1 - i;
        // heapify(vec, vec.size() - 1 - i);

        std::make_heap(vec.begin(), vec.end() - i); // make heap using stl
        printVector(vec, "After final heapify");

        // swap the first element in the maxheap(largest) with the last elements in a way that the last slot is filled then second last and so on
        std::swap(vec[0], vec[vec.size() - i - 1]);
        printVector(vec, "After adding at end");
        // if (breakLoop)
        //     break;
    }
    printVector(vec, "After sort");
    std::cout << "##################\n";
}
int main()
{
    std::vector<int> vecOfInt{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_device rdSeed;
    std::shuffle(vecOfInt.begin(), vecOfInt.end(), std::mt19937(rdSeed()));

    heapSort(vecOfInt);

    std::vector<char> vecOfChars{'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    std::shuffle(vecOfChars.begin(), vecOfChars.end(), std::mt19937(rdSeed()));
    heapSort(vecOfChars);

    std::cin.get();
}