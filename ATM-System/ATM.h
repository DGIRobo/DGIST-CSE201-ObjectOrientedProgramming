#pragma once
#include <string>
#include <vector>
#include "Bank.h"
#include "Account.h"

using namespace std;

class Account;
class Bank;

class ATM {
private:

protected:
	int serial_number;
	string admin_card;
	string language_setting = "English";
	int* cash_storage[4]; // #1000, #5000, #10000, #50000 // initial fund
	string transaction_histories;
	int type;

	Bank* primary_bank;
	int language_available;
	
public:

	// primary bank name / serial numbeer / type : single or multi bank / language : uni, bi / initial fund
	ATM(Bank* input_primary_bank, int input_serial_number, int input_type, int input_lanuage_available, int* initial_fund[]);
	~ATM();

	void session();
	void transaction();
	void languageChange();
	virtual void deposit(Account a) = 0;
	virtual void withdraw(Account a) = 0;
	virtual void account_transfer(Account a, Account b) = 0;
	virtual void cash_transfer(Account b) = 0;
	void see_transaction_history();
	void valid_checks_check();
	void user_authorization();
	void add_cash(int cash1000, int cash5000, int cash10000, int cash50000);
	int getSerial();
};