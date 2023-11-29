#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ATM.h"
#include "Bank.h"

using namespace std;

class Bank;
class ATM;

class Account {
private:
	
	Bank* bank;

	string bank_name;
	string user_name;
	static int static_account_counter;
	static int static_card_counter;
	string account_number;
	vector<string>access_cards;
	string password;
	int avaliable_funds;
	string transaction_histories; // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecificInformation
protected:
public:
	Account(Bank* input_bank, string input_user_name, string input_password, int initial_fund);
	~Account();
	string getBankName();
	string getUserName();
	string getPassword();
	void setPassword(string new_password);
	string getAccountNumber();
	string makeCard();
	int checkFunds();
	void deposit(int input_money);
	void withdraw(int output_money);
	void updateHistory(string TransactionID, string CardNumber, string TransactionTypes, string Amount, string TransactionSpecificInformation);
	void printHistory();
	
	vector<string> getCardNumber();

	int getAvailableFund();
};