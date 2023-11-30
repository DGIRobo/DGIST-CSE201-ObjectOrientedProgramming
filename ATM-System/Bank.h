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
	int no_error(int language_setting);
	int no_error_range(int language_setting, int min, int max);

	Bank(string name);
	~Bank();
	int getBankId();
	string getBankName();
	void deposit2ATM(ATM* target_ATM, int numOf1000, int numOf5000, int numOf10000, int numOf50000);

	// Account* open_account(Account* a);

	void create_account(int language_setting);
	Account* search_account_number(int language_setting);
	Account* search_account_number_BankSearch(string input_account, int language_setting);

	Account* search_account_card(int language_setting);
	Account* search_account_card_BankSearch(string input_card, int language_setting);

	vector<Account*> get_account();

	void makeCard_session(int language_setting);

};