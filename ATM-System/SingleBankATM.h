#pragma once
#include "ATM.h"

using namespace std;

class Single : public ATM {
private:
	Fee my_fee;
protected:
public:
	Single();
	~Single();

	void Single_deposit(Account a);
	void Single_withdraw(Account a);
	void Single_account_transfer(Account a, Account b);
};