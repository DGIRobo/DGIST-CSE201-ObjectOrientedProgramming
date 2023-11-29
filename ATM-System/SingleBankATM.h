#pragma once
#include "ATM.h"
//#include "Fee.h"

using namespace std;

class Single : public ATM {
private:
	//Fee my_fee;
	int* fee_list[4];
protected:
public:
	Single();
	Single(Bank* input_primary_bank, string input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4]);
	~Single();

	void deposit(Account* a);
	void withdraw(Account* a);
	void account_transfer(Account* a, Account* b);
	void cash_transfer(Account* b);
	Account* card2account(string card, vector<Bank*> bank_list);
	Account* num2account(string num, vector<Bank*> bank_list);
	string getType();
};