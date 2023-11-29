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
	Multi(Bank* input_primary_bank, int input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4], int* mfees[4]);
	~Multi();

	void deposit(Account* a);
	void withdraw(Account* a);
	void account_transfer(Account* a, Account* b);
	void cash_transfer(Account* b);
	void session(vector<Bank*> bank_list);
};