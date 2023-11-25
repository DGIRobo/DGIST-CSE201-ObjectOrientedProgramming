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
	int* cash_storage[4]; // #1000, #5000, #10000, #50000 // initial fund
	string transaction_histories;

	string primary_bank;
	string type;
	string language_available;

protected:
public:

	// primary bank name / serial numbeer / type : single or multi bank / language : uni, bi / initial fund
	ATM(string input_primary_bank, int input_serial_number, string input_type, string input_lanuage_available, int* initial_fund[]);
	~ATM();

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