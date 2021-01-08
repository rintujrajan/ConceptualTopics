#include <iostream>
#include <queue>

using namespace std;

struct Slot
{
    int distance;
    char id;
};

struct OrderByDistance
{
    bool operator()(Slot& left, Slot& right)
    {
        return left.distance > right.distance;
    }
};

int main()
{
   /*
   *  This is not a true container, but an adaptor.  It holds
   *  another container, and provides a wrapper interface to that
   *  container.  The wrapper is what enforces priority-based sorting
   *  and queue behavior.  
   *
   *  The second template parameter defines the type of the underlying
   *  sequence/container.  It defaults to std::vector, but it can be
   *  any type that supports front(), push_back(), pop_back(), empty(), size()
   *  and random-access iterators, such as std::deque
   *  or an appropriate user-defined type.
   *
   *  The third template parameter supplies the means of making
   *  priority comparisons.  It defaults to less<value_type> but
   *  can be anything defining a strict weak ordering.
   */
    priority_queue<Slot,deque<Slot>,OrderByDistance> prioQueue;
    prioQueue.push(Slot{ 3, 'C'});
    prioQueue.push(Slot{ 1, 'A'});
    prioQueue.push(Slot{ 2, 'B'});

    while(!prioQueue.empty())
    {
        cout<<prioQueue.top().distance<<" "<<prioQueue.top().id <<"\n";
        prioQueue.pop();
    }

    prioQueue.emplace(Slot{ 3, 'C'});
    prioQueue.emplace(Slot{ 1, 'A'});
    prioQueue.emplace(Slot{ 2, 'B'});

    while(!prioQueue.empty())
    {
        cout<<prioQueue.top().distance<<" "<<prioQueue.top().id <<"\n";
        prioQueue.pop();
    }
    std::cin.get();
    return 0;
}
