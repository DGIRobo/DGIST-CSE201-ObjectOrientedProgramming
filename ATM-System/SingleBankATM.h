#pragma once
#include "ATM.h"
#include "Fee.h"

using namespace std;

class Single : public ATM {
private:
	Fee my_fee;
protected:
public:
	Single();
	~Single();

	void primary_deposit(Account a);
	void primary_withdraw(Account a);
	void primary_transfer(Account a, Account b);
	void cash_transfer(Account a);
};