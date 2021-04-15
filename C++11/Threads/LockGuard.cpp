
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
class BankAccount
{
	int accountMoney;
	mutex lockMutex;

public:
	BankAccount() : accountMoney(0){};
	void addMoney(int money)
	{
		/*We could use mutex.lock and unlock to avoid race condition as is in MutexLockUnlock.cpp,
		but what if we forgot to unlock the mutex at the end of function.
		In such scenario, one thread will exit without releasing the lock and other threads will remain in waiting.
		This kind of scenario can happen in case some exception came after locking the mutex.To avoid such scenarios we should use std::lock_guard.*/
		lock_guard<mutex> lock(lockMutex);
		int locMoney = accountMoney + 1;
		this_thread::sleep_for(chrono::nanoseconds(10000));
		accountMoney = locMoney;
	}
	int getMoneyStatement()
	{
		return accountMoney;
	}
};
int accountMoney;
void addMoney(int money)
{
	accountMoney += money;
}
int getMoneyStatement()
{
	return accountMoney;
}
int main()
{

	// checking non class thread
	thread nonClassThread(addMoney, 10);
	nonClassThread.join();
	cout << getMoneyStatement() << endl;

	// checking lambda
	int money = 1;
	thread lambdaThread([&]() { money += 1; });
	lambdaThread.join();
	cout << money << endl;

	BankAccount myBankAccount;
	vector<thread> vecThreads;
	for (int i = 0; i < 5; i++)
	{
		vecThreads.push_back(thread(&BankAccount::addMoney, &myBankAccount, 1));
	}
	for (int i = 0; i < vecThreads.size(); i++)
	{
		vecThreads[i].join();
	}

	cout << myBankAccount.getMoneyStatement() << endl;

	cin.get();
}