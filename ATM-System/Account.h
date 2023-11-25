#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Account {
private:
	string bank_name;
	string user_name;
	static int static_account_counter;
	int account_number;
	string password;
	int avaliable_funds;
	string transaction_histories; // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecificInformation
protected:
public:
	Account(string input_bank_name, string input_user_name, string input_password);
	~Account();
	string getBankName();
	string getUserName();
	string getPassword();
	void setPassword(string new_password);
	int checkFunds();
	void deposit(int input_money);
	void withdraw(int output_money);
	void updateHistory(string TransactionID, string CardNumber, string TransactionTypes, string Amount, string TransactionSpecificInformation);
	void printHistory();
};