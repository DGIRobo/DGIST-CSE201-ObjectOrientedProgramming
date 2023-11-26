#pragma once
#include <string>
#include <vector>
#include "Account.h"
#include "ATM.h"

using namespace std;

class Account;
class ATM;

class Bank {
private:
	static int static_bank_counter;
	int bank_id;
	string bank_name;
	vector<Account*>accounts;
protected:
public:
	Bank(string name);
	~Bank();
	int getBankId();
	string getBankName();
	void deposit2ATM(ATM* target_ATM, int numOf1000, int numOf5000, int numOf10000, int numOf50000);
	Account* open_account();
};