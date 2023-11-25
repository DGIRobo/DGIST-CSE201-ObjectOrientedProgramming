#pragma once
#include <string>
#include <vector>
#include "Account.h"
#include "ATM.h"

using namespace std;

class Bank {
private:
	string bank_name;
	vector<Account*>accounts;
protected:
public:
	void deposit2ATM(ATM* target_ATM, int numOf1000, int numOf5000, int numOf10000, int numOf50000);
	Account* open_account();
};