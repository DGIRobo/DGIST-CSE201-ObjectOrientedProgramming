#pragma once
#include <string>
#include <vector>
#include "Account.h"
#include "ATM.h"

using namespace std;

class ATM {
private:
	int serial_number;
	string admin_card;
	string language_setting;
	int* cash_storage[4]; // #1000, #5000, #10000, #50000
	string transaction_histories;
protected:
public:
	void session();
	void transaction();
	void languageChange();
	void deposit();
	void withdraw();
	void account_transfer();
	void see_transaction_history();
	void valid_checks_check();
	void user_authorization();
};