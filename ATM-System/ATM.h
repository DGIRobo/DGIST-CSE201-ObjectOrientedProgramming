#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <typeinfo>
#include <exception>
#include "Bank.h"
#include "Account.h"

using namespace std;

class Account;
class Bank;

class ATM {
private:

protected:
	string serial_number;
	string admin_card;
	string language_setting = "English";
	bool lang_setting = false;
	int* cash_storage[4]; // #1000, #5000, #10000, #50000 // initial fund
	static int static_ATM_counter;
	static int static_transaction_counter;
	string transaction_histories;
	int type;

	Bank* primary_bank;
	int language_available;
	
public:

	// primary bank name / serial numbeer / type : single or multi bank / language : uni, bi / initial fund
	ATM(Bank* input_primary_bank, string input_serial_number, int input_type, int input_lanuage_available, int* initial_fund[]);
	~ATM();

	void session(vector<Bank*> bank_list);
	vector<string> transaction(Account* a, vector<Bank*> bank_list, string CardNumber);
	void languageChange();
	virtual int deposit(Account* a) = 0;
	virtual int withdraw(Account* a) = 0;
	virtual int account_transfer(Account* a, Account* b) = 0;
	virtual int cash_transfer(Account* b) = 0;
	void see_transaction_history();
	bool user_authorization(Account* a);
	void add_cash(int cash1000, int cash5000, int cash10000, int cash50000);
	string getSerial();
	Bank* getPrimary();
	void make_history(vector<string> rec);
	void display_transaction(vector<string> rec);
	void display_transaction_short(vector<string> rec);
	virtual Account* card2account(string card, vector<Bank*> bank_list) = 0;
	virtual Account* num2account(string num, vector<Bank*> bank_list) = 0;
	virtual string getType() = 0;
	string getLangType();
	int get1000();
	int get5000();
	int get10000();
	int get50000();
	int no_error(bool language_setting);
	int no_error_range(bool language_setting, int min, int max);
};