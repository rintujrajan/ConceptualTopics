#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

condition_variable cv;  
mutex mut;
int balance = 0;

void depositMoney(int depositAmount)
{
    this_thread::sleep_for(chrono::seconds(1));
    lock_guard<mutex> lg(mut);
    balance+=depositAmount;
    cout<<"Amount "<<depositAmount<<" deposited. Current balance :"<<balance<<endl;
    cv.notify_all();
}

void withdrawMoney(int withdrawAmount)
{
    cout<<"Request to withdraw "<<withdrawAmount<<endl;
    unique_lock<mutex> ul(mut);
    cv.wait(ul,[]{
        if(balance!=0)
        {
            return true;
        }
        else
        {
            cout<<"Balance is 0. Waiting for any deposit"<<endl;
            return false;
        }});
    if(balance>=withdrawAmount)
    {
        balance-=withdrawAmount;
        cout<<"Amount "<<withdrawAmount<<" withdrawn. Current balance :"<<balance<<endl;
    }
    else
    {
        cout<<"Amount "<<withdrawAmount<<" could not be withdrawn. Current balance :"<<balance<<endl;
    }
    
}
int main()
{
    thread withdrawThread(withdrawMoney,500);
    thread depositThread(depositMoney, 1000);
    withdrawThread.join();
    depositThread.join();
    thread withdrawThread2(withdrawMoney,1500);
    withdrawThread2.join();
    cin.get();
}