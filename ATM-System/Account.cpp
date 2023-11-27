#include "Account.h"

int Account::static_card_counter = 0;
int Account::static_account_counter = 0;

Account::Account(Bank* input_bank, string input_user_name, string input_password) {
	this->bank_name = input_bank->getBankName();
	this->user_name = input_user_name;
	this->password = input_password;
	this->avaliable_funds = initial_fund;
	string temp_bank_code;
	for (int i = 0; i < 3 - to_string(input_bank->getBankId()).size(); i++) {
		temp_bank_code += "0";
	}
	temp_bank_code += to_string(input_bank->getBankId());
	this->static_account_counter += 1;
	string temp_account_code;
	for (int i = 0; i < 6 - to_string(static_account_counter).size(); i++) {
		temp_bank_code += "0";
	}
	temp_bank_code += to_string(static_account_counter);
	this->account_number = "000-" + temp_bank_code + "-" + temp_account_code;
	this->avaliable_funds = 0;
	this->transaction_histories = input_user_name + ".txt";
	this->updateHistory("0", "None", "0", to_string(avaliable_funds), "Generate New Account"); // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecificInformation
}

Account::~Account() {
	this->bank_name = "";
	this->user_name = "";
	this->password = "";
	this->avaliable_funds = 0;
	this->updateHistory("0", "None", "0", to_string(avaliable_funds), "Delete Account"); // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecificInformation
}

string Account::getBankName() {
	return this->bank_name;
}

string Account::getUserName() {
	return this->user_name;
}

string Account::getPassword() {
	return this->password;
}

void Account::setPassword(string new_password) {
	this->password = new_password;
}

string Account::getAccountNumber() {
	return this->account_number;
}

string Account::makeCard() {
	static_card_counter += 1;
	string temp_card_num = "0000-0000-0000-";
	for (int i = 0; i < 4 - to_string(static_card_counter).size(); i++) {
		temp_card_num += "0";
	}
	temp_card_num += to_string(static_card_counter);
	this->access_cards.push_back(temp_card_num);
	return temp_card_num;
}

int Account::checkFunds() {
	return this->avaliable_funds;
}

void Account::deposit(int input_money) {
	this->avaliable_funds = this->avaliable_funds + input_money;
}

void Account::withdraw(int output_money) {
	this->avaliable_funds = this->avaliable_funds - output_money;
}

void Account::updateHistory(string TransactionID, string CardNumber, string TransactionTypes, string Amount, string TransactionSpecificInformation) {
	vector<string>new_history = { TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecificInformation }; // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecificInformation
	int len = static_cast<int>(new_history.size());

	ofstream writeFromFile(this->transaction_histories, ios::app);
	for (int i = 0; i < len; ++i) {
		string tmp = new_history[i];
		if (i != len - 1) {
			tmp += ", ";
		}
		writeFromFile << tmp;
	}
	writeFromFile << "\n";
}

void Account::printHistory() {
	ifstream readFile(this->transaction_histories);
	if (readFile.is_open()) {
		string str;
		while (readFile) {
			getline(readFile, str);
			cout << str << endl;
		}
	}
	else {
		cout << "������ ã�� �� �����ϴ�." << endl;
	}
}


vector<string > Account::getCardNumber() {
	return access_cards;
}