
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
		lockMutex.lock();
		int locMoney = accountMoney + 1;
		this_thread::sleep_for(chrono::seconds(2));
		accountMoney = locMoney;
		cout << "New Balance : " << accountMoney << endl;
		lockMutex.unlock();
	}
	int getMoneyStatement()
	{
		return accountMoney;
	}
};
int main()
{

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

	cout << "Final Balance: " << myBankAccount.getMoneyStatement() << endl;

	cin.get();
}