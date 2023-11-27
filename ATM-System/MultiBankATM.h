#pragma once
#include "ATM.h"
#include "Fee.h"

using namespace std;

class Multi : public ATM {
private:
	Fee my_fee;
protected:
public:
	void primary_deposit(Account a);
	void primary_withdraw(Account a);
	void primary_transfer(Account a, Account b);
	void non_deposit(Account a);
	void non_withdraw(Account a);
	void non_primary_transfer(Account a, Account b);
	void non_non_transfer(Account a, Account b);
	void cash_transfer(Account a);
};