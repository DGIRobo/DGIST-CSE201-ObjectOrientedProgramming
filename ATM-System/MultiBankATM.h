#pragma once
#include "ATM.h"
//#include "Fee.h"

using namespace std;

class Multi : public ATM {
private:
	//Fee my_fee;
	int* fee_list[4];
	int* multi_fee_list[4];
protected:
public:
	Multi();
	Multi(Bank* input_primary_bank, string input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4], int* mfees[4]);
	~Multi();

	int deposit(Account* a);
	int withdraw(Account* a);
	int account_transfer(Account* a, Account* b);
	int cash_transfer(Account* b);
	Account* card2account(string card, vector<Bank*> bank_list);
	Account* num2account(string num, vector<Bank*> bank_list);
	string getType();
};