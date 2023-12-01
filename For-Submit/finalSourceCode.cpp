// Initialization
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <iomanip>
#include <typeinfo>

using namespace std;

class Bank;
class ATM;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ Account Class Declaration
class Account {
private:
	Bank* bank;
	int account_id;
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
	int getAccountID();
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Bank Class Declaration
class Bank {
private:
	static int static_bank_counter;
	int bank_id;
	string bank_name;
	vector<Account*>accounts;
	vector<Bank*>* blist;
	vector<ATM*>* alist;
protected:
public:
	void printNow();
	void Qsearch(string* str);
	int no_error(int language_setting);
	int no_error_range(int language_setting, int min, int max);
	Bank(string name, vector<Bank*>* blist, vector<ATM*>* alist);
	~Bank();
	int getBankId();
	string getBankName();
	void deposit2ATM(ATM* target_ATM, int numOf1000, int numOf5000, int numOf10000, int numOf50000);
	void create_account(int language_setting);
	Account* search_account_number(int language_setting);
	Account* search_account_number_BankSearch(string input_account, int language_setting);
	Account* search_account_card(int language_setting);
	Account* search_account_card_BankSearch(string input_card, int language_setting);
	vector<Account*> get_account();
	void makeCard_session(int language_setting);
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ATM Class Declaration
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
	vector<Bank*>* blist;
	vector<ATM*>* alist;
	Bank* primary_bank;
	int language_available;
public:
	void Qsearch(string* str);
	// primary bank name / serial numbeer / type : single or multi bank / language : uni, bi / initial fund
	ATM(Bank* input_primary_bank, string input_serial_number, int input_type, int input_lanuage_available, int* initial_fund[], vector<Bank*>* blist, vector<ATM*>* alist);
	~ATM();
	void session(vector<Bank*> bank_list);
	vector<string> transaction(Account* a, vector<Bank*> bank_list, string CardNumber, int* with_counter);
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
	void printNow();
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Single Bank ATM Class Declaration
class Single : public ATM {
private:
	//Fee my_fee;
	int* fee_list[4];
protected:
public:
	Single();
	Single(Bank* input_primary_bank, string input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4], vector<Bank*>* blist, vector<ATM*>* alist);
	~Single();
	int deposit(Account* a);
	int withdraw(Account* a);
	int account_transfer(Account* a, Account* b);
	int cash_transfer(Account* b);
	Account* card2account(string card, vector<Bank*> bank_list);
	Account* num2account(string num, vector<Bank*> bank_list);
	string getType();
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Multi Bank ATM Class Declaration
class Multi : public ATM {
private:
	//Fee my_fee;
	int* fee_list[4];
	int* multi_fee_list[4];
protected:
public:
	Multi();
	Multi(Bank* input_primary_bank, string input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4], int* mfees[4], vector<Bank*>* blist, vector<ATM*>* alist);
	~Multi();
	int deposit(Account* a);
	int withdraw(Account* a);
	int account_transfer(Account* a, Account* b);
	int cash_transfer(Account* b);
	Account* card2account(string card, vector<Bank*> bank_list);
	Account* num2account(string num, vector<Bank*> bank_list);
	string getType();
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Account Class Member Definition
int Account::static_card_counter = 0;
int Account::static_account_counter = 0;

Account::Account(Bank* input_bank, string input_user_name, string input_password, int initial_fund) {
	this->bank = input_bank;
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
	this->account_id = this->static_account_counter;
	string temp_account_code;
	for (int i = 0; i < 6 - to_string(this->account_id).size(); i++) {
		temp_account_code += "0";
	}
	temp_account_code += to_string(this->account_id);
	this->account_number = "000-" + temp_bank_code + "-" + temp_account_code;
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
	string temp_bank_code;
	for (int i = 0; i < 4 - to_string(this->bank->getBankId()).size(); i++) {
		temp_bank_code += "0";
	}
	temp_bank_code += to_string(this->bank->getBankId());
	// this->static_account_counter += 1;
	string temp_account_code;
	for (int i = 0; i < 4 - to_string(this->getAccountID()).size(); i++) {
		temp_account_code += "0";
	}
	temp_account_code += to_string(this->getAccountID());
	this->static_card_counter += 1;
	string temp_card_code;
	for (int i = 0; i < 4 - to_string(static_card_counter).size(); i++) {
		temp_card_code += "0";
	}
	temp_card_code += to_string(static_card_counter);
	string card_number = "0000-" + temp_bank_code + "-" + temp_account_code + "-" + temp_card_code;
	this->access_cards.push_back(card_number);
	return card_number;
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
		cout << "�ش��ϴ� ������ �����ϴ�." << endl;
	}
}

vector<string> Account::getCardNumber() {
	return access_cards;
}

int Account::getAvailableFund() {
	return avaliable_funds;
}

int Account::getAccountID() {
	return account_id;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Bank Class Member Definition
int Bank::static_bank_counter = 0;

void Bank::printNow() {
	for (int i = 0; i < (*blist).size(); i++) {
		for (int j = 0; j < (*blist)[i]->get_account().size(); j++) {
			cout << "Account[" << (*blist)[i]->get_account()[j]->getUserName() << "] : " << (*blist)[i]->get_account()[j]->checkFunds() << "/" << (*blist)[i]->get_account()[j]->getAccountNumber() << "/" << (*blist)[i]->get_account()[j]->getBankName() << endl;
		}
	}
	for (int i = 0; i < (*alist).size(); i++) {
		cout << "ATM " << "[" << i << "] " << "Primary Bank : " << (*alist)[i]->getPrimary()->getBankName() << " " << (*alist)[i]->getType() << " " << (*alist)[i]->getLangType() << endl;
		cout << "Remaing cash : " << 1000 * (*alist)[i]->get1000() + 5000 * (*alist)[i]->get5000() + 10000 * (*alist)[i]->get10000() + 50000 * (*alist)[i]->get50000() << " (1000 : " << (*alist)[i]->get1000() << ", 5000 : " << (*alist)[i]->get5000() << ", 10000 : " << (*alist)[i]->get10000() << ", 50000 : " << (*alist)[i]->get50000() << ")" << endl;
		// cout << "ATM [" << ATM_list[i]->getSerial() << "] Remaing cash : " << 1000 * ATM_list[i]->get1000() + 5000 * ATM_list[i]->get5000() + 10000 * ATM_list[i]->get10000() + 50000 * ATM_list[i]->get50000() << " (1000 : " << ATM_list[i]->get1000() << ", 5000 : " << ATM_list[i]->get5000() << ", 10000 : " << ATM_list[i]->get10000() << ", 50000 : " << ATM_list[i]->get50000() << ")" << endl;
	}
	cout << endl;
	cout << "Please re-enter here : ";
	return;
}

void Bank::Qsearch(string* str) {
	while (true) {
		cin >> *str;
		if (*str == "Q" || *str == "q") {
			printNow();
		}
		else {
			return;
		}
	}
}

int Bank::no_error(int language_setting) {
	int temp = 0;
	while (true) {
		string abc = "";
		//cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow();
			}
			else {
				break;
			}
		}
		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp >= 0) { return temp; }
			else {
				if (language_setting == 1) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 2) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 1) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
	}
}

int Bank::no_error_range(int language_setting, int min, int max) {
	int temp = 0;
	while (true) {
		string abc = "";
		//cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow();
			}
			else {
				break;
			}
		}
		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp > min - 1 && temp < max + 1) { return temp; }
			else {
				if (language_setting == 1) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 2) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 1) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
	}
}

Bank::Bank(string name, vector<Bank*>* blist, vector<ATM*>* alist) {
	this->bank_name = name;
	static_bank_counter += 1;
	this->bank_id = static_bank_counter;
	this->blist = blist;
	this->alist = alist;
	cout << this->getBankName() << " Bank is created." << endl;
}

Bank::~Bank() {
	cout << this->bank_name << " Bank is eliminated." << endl;
}

int Bank::getBankId() {
	return this->bank_id;
}

string Bank::getBankName() {
	return this->bank_name;
}

void Bank::deposit2ATM(ATM* target_ATM, int numOf1000, int numOf5000, int numOf10000, int numOf50000) {
	target_ATM->add_cash(numOf1000, numOf5000, numOf10000, numOf50000);
}

void Bank::makeCard_session(int language_setting) {
	cout << "==================== < Card Create Session > ====================" << endl;
	if (accounts.size() == 0) {
		if (language_setting == 1) { cout << "There is no account. So making card is not available." << endl; }
		if (language_setting == 2) { cout << "���࿡ �����ϴ� ���°� ���� ī�� ������ ������ �� �����ϴ�." << endl; }
		return;
	}
	int c = 0;
	Account* account = search_account_number(language_setting);
	if (account == NULL) { c = 1; }
	if (c == 0) {
		string input_password;
		if (language_setting == 1) { cout << "To make card, please write password." << endl; }
		if (language_setting == 2) { cout << "ī�带 ����� ���� ��й�ȣ�� �Է����ּ���." << endl; }
		int a = 3;
		while (true) {
			if (a == 0) {
				if (language_setting == 1) { cout << "You write wrong password 3 times. " << endl; }
				if (language_setting == 2) { cout << "��й�ȣ 3ȸ Ʋ�Ƚ��ϴ�." << endl; }
				cout << "==================== < Card Create Session End! > ====================" << endl;
				break;
			}
			if (language_setting == 1) {
				cout << a << " attempts left." << endl;
				cout << "Password : ";
			}
			if (language_setting == 2) {
				cout << a << " ȸ ����." << endl;
				cout << "��й�ȣ : ";
			}
			string* pinput_password = &input_password;
			Qsearch(pinput_password);
			a--;
			if (account->getPassword() == input_password) {
				if (language_setting == 1) { cout << "Correct password." << endl; }
				if (language_setting == 2) { cout << "���� ��й�ȣ." << endl; }
				string now_created_card_number;
				now_created_card_number = account->makeCard();
				if (language_setting == 1) {
					cout << "Card is created." << endl;
					cout << "Card Number : " << now_created_card_number << endl;
					cout << "This is card number list that connected to your account." << endl;
				}
				if (language_setting == 2) {
					cout << "ī�尡 �����Ǿ����ϴ�." << endl;
					cout << "ī�� ��ȣ : " << now_created_card_number << endl;
					cout << "���¿� ����� ī�� ��ȣ ����Դϴ�." << endl;
				}
				vector <string > card_list = account->getCardNumber();
				for (int i = 0; i < card_list.size(); i++) {
					cout << card_list[i] << endl;
				}
				break;
			}
		}
	}
	cout << "==================== < Card Create Session End! > ====================" << endl;
}

void Bank::create_account(int language_setting) {
	cout << "==================== < Account Create Session > ====================" << endl;
	string input_user_name;
	string* pinput_user_name = &input_user_name;
	string account_number;
	string input_password;
	string* pinput_password = &input_password;
	if (language_setting == 1) {
		cout << this->getBankName() << "Bank. To create account. please write name, password and initial fund." << endl;
		cout << "Name : ";
		// cin >> input_user_name;
		Qsearch(pinput_user_name);
		cout << "Password : ";
		// cin >> input_password;
		Qsearch(pinput_password);
		cout << "Initial fund : ";
	}
	if (language_setting == 2) {
		cout << this->getBankName() << "����. ���¸� �����ϱ� ���� �̸�, ����, �ʱ� �ڱ��� �Է����ּ���." << endl;
		cout << "������ : ";
		// cin >> input_user_name;
		Qsearch(pinput_user_name);
		cout << "��й�ȣ : ";
		// cin >> input_password;
		Qsearch(pinput_password);
		cout << "�ʱ��ڱ� : ";
	}
	int initial_fund;
	// cin >> initial_fund;
	initial_fund = no_error(language_setting);
	Account* new_account = new Account(this, input_user_name, input_password, initial_fund);
	accounts.push_back(new_account);
	if (language_setting == 1) {
		cout << "Account is created." << endl;
		cout << "Bank : " << new_account->getBankName() << endl;
		cout << "Owner : " << new_account->getUserName() << endl;
		cout << "Account number : " << new_account->getAccountNumber() << endl;
		cout << "Password : " << new_account->getPassword() << endl;
		cout << "Available fund : " << new_account->getAvailableFund() << endl;
		cout << "Do you want to make card? [Agree Y / Disagree N] : ";
	}
	if (language_setting == 2) {
		cout << "���°� �����Ǿ����ϴ�." << endl;
		cout << "���� : " << new_account->getBankName() << endl;
		cout << "������ : " << new_account->getUserName() << endl;
		cout << "���¹�ȣ : " << new_account->getAccountNumber() << endl;
		cout << "��й�ȣ : " << new_account->getPassword() << endl;
		cout << "�����ܰ� : " << new_account->getAvailableFund() << endl;
		cout << "ī�带 �����Ͻðڽ��ϱ�? [���� Y / ���� N] : ";
	}
	string agreement;
	string* pagreement = &agreement;
	// cin >> agreement;
	while (true) {
		// cin >> agreement;
		Qsearch(pagreement);
		if (agreement != "n" && agreement != "N" && agreement != "y" && agreement != "Y") {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "[Agree Y / Disagree N] : ";
			}
			if (language_setting == 2) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "[���� Y / ���� N] : ";
			}
		}
		else { break; }
	}
	if (agreement == "n" || agreement == "N") { cout << "==================== < Card Create Session End! > ====================" << endl; }
	if (agreement == "y" || agreement == "Y") {
		cout << "==================== < Card Create Session > ====================" << endl;
		string now_created_card_number;
		now_created_card_number = new_account->makeCard();

		if (language_setting == 1) {
			cout << "Card is created." << endl;
			cout << "Card number : " << now_created_card_number << endl;
			cout << "This is card number list that connected to your account." << endl;
		}
		if (language_setting == 2) {
			cout << "ī�尡 �����Ǿ����ϴ�." << endl;
			cout << "ī�� ��ȣ : " << now_created_card_number << endl;
			cout << "���¿� ����� ī�� ��ȣ ����Դϴ�." << endl;
		}
		vector <string> card_list = new_account->getCardNumber();
		for (int i = 0; i < card_list.size(); i++) {
			cout << card_list[i] << endl;
		}
		cout << "==================== < Card Create Session End! > ====================" << endl;
	}
	cout << "==================== < Account Create Session End! > ====================" << endl;
	//return new_account;
}

Account* Bank::search_account_number(int language_setting) {
	cout << "==================== < Account Number Search Session > ====================" << endl;
	vector<Account*> accounts_list = get_account();
	int a = 3;
	while (true) {
		if (a == 0) {
			if (language_setting == 1) { cout << this->getBankName() << " Bank cannot find your account." << endl; }
			if (language_setting == 2) { cout << this->getBankName() << " ������ ���¸� ã�� ���߽��ϴ�." << endl; }
			break;
		}
		if (language_setting == 1) {
			cout << a << " attempts left." << endl;
			cout << "Account number : ";
		}
		if (language_setting == 2) {
			cout << a << " ȸ ����." << endl;
			cout << "���¹�ȣ : ";
		}
		a--;
		string input_account_number;
		string* pinput_account_number = &input_account_number;
		// cin >> input_account_number;
		Qsearch(pinput_account_number);
		for (int i = 0; i < accounts_list.size(); i++) {
			if (accounts_list[i]->getAccountNumber() == input_account_number) {
				if (language_setting == 1) {
					cout << this->getBankName() << " Bank find your account." << endl;
					cout << "Bank : " << accounts_list[i]->getBankName() << endl;
					cout << "Owner : " << accounts_list[i]->getUserName() << endl;
					cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
				}
				if (language_setting == 2) {
					cout << this->getBankName() << " ������ ���¸� ã�ҽ��ϴ�." << endl;
					cout << "���� : " << accounts_list[i]->getBankName() << endl;
					cout << "������ : " << accounts_list[i]->getUserName() << endl;
					cout << "���¹�ȣ : " << accounts_list[i]->getAccountNumber() << endl;
				}
				cout << "==================== < Account Number Search Session End! > ====================" << endl;
				return accounts_list[i];
			}
		}
	}
	if (language_setting == 1) { cout << "You write wrong account number 3 times." << endl; }
	if (language_setting == 2) { cout << "�߸��� ���� ��ȣ�� 3ȸ �Է��߽��ϴ�." << endl; }
	cout << "==================== < Account Number Search Session End! > ====================" << endl;
	return NULL;
}

Account* Bank::search_account_number_BankSearch(string input_account, int language_setting) {
	vector<Account*> accounts_list = get_account();
	string input_account_number = input_account;
	for (int i = 0; i < accounts_list.size(); i++) {
		if (accounts_list[i]->getAccountNumber() == input_account_number) {
			if (language_setting == 1) {
				cout << this->getBankName() << " Bank find your account." << endl;
				cout << "Bank : " << accounts_list[i]->getBankName() << endl;
				cout << "Owner : " << accounts_list[i]->getUserName() << endl;
				cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
			}
			if (language_setting == 2) {
				cout << this->getBankName() << " ������ ���¸� ã�ҽ��ϴ�." << endl;
				cout << "���� : " << accounts_list[i]->getBankName() << endl;
				cout << "������ : " << accounts_list[i]->getUserName() << endl;
				cout << "���¹�ȣ : " << accounts_list[i]->getAccountNumber() << endl;
			}
			return accounts_list[i];
		}
	}
	return NULL;
}

Account* Bank::search_account_card(int language_setting) {
	cout << "==================== < Account Card Search Session > ====================" << endl;
	vector<Account*> accounts_list = get_account();
	if (language_setting == 1) { cout << this->getBankName() << " Bank. Please write card number." << endl; }
	if (language_setting == 2) { cout << this->getBankName() << " ����. ī�� ��ȣ�� �Է����ּ���." << endl; }
	string input_card_number;
	string* pinput_card_number = &input_card_number;
	if (language_setting == 1) {
		cout << "Card number : ";
		Qsearch(pinput_card_number);
	}
	if (language_setting == 2) {
		cout << "ī�� ��ȣ : ";
		Qsearch(pinput_card_number);
	}
	for (int i = 0; i < accounts_list.size(); i++) {
		vector<string> card_list = accounts_list[i]->getCardNumber();
		for (int j = 0; j < card_list.size(); j++) {
			if (card_list[j] == input_card_number) {
				if (language_setting == 1) {
					cout << this->getBankName() << " Bank find your account." << endl;
					cout << "Bank : " << accounts_list[i]->getBankName() << endl;
					cout << "Owner : " << accounts_list[i]->getUserName() << endl;
					cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
				}
				if (language_setting == 2) {
					cout << this->getBankName() << " ������ ���¸� ã�ҽ��ϴ�." << endl;
					cout << "���� : " << accounts_list[i]->getBankName() << endl;
					cout << "������ : " << accounts_list[i]->getUserName() << endl;
					cout << "���¹�ȣ : " << accounts_list[i]->getAccountNumber() << endl;
				}
				cout << "==================== < Account Card Search Session End! > ====================" << endl;
				return accounts_list[i];
			}
		}
	}
	if (language_setting == 1) { cout << this->getBankName() << " Bank cannot find your account." << endl; }
	if (language_setting == 2) { cout << this->getBankName() << " ������ ���¸� ã�� ���߽��ϴ�." << endl; }
	cout << "==================== < Account Card Search Session End! > ====================" << endl;
	return NULL;
}

Account* Bank::search_account_card_BankSearch(string input_card, int language_setting) {
	vector<Account*> accounts_list = get_account();
	string input_card_number = input_card;
	for (int i = 0; i < accounts_list.size(); i++) {
		vector<string> card_list = accounts_list[i]->getCardNumber();
		for (int j = 0; j < card_list.size(); j++) {
			if (card_list[j] == input_card_number) {
				if (language_setting == 1) {
					cout << this->getBankName() << " Bank find your account." << endl;
					cout << "Bank : " << accounts_list[i]->getBankName() << endl;
					cout << "Owner : " << accounts_list[i]->getUserName() << endl;
					cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
				}
				if (language_setting == 2) {
					cout << this->getBankName() << " ������ ���¸� ã�ҽ��ϴ�." << endl;
					cout << "���� : " << accounts_list[i]->getBankName() << endl;
					cout << "������ : " << accounts_list[i]->getUserName() << endl;
					cout << "���¹�ȣ : " << accounts_list[i]->getAccountNumber() << endl;
				}
				return accounts_list[i];
			}
		}
	}
	return NULL;
}

vector<Account*> Bank::get_account() {
	return accounts;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ATM Class Member Definition
int ATM::static_ATM_counter = 0;
int ATM::static_transaction_counter = 0;

void ATM::Qsearch(string* str) {

	while (true) {
		cin >> *str;
		if (*str == "Q" || *str == "q") {
			printNow();
		}
		else {
			return;
		}
	}
}

int ATM::no_error(bool language_setting) {
	int temp = 0;
	while (true) {

		string abc = "";
		// cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow();
			}
			else {
				break;
			}
		}

		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 0) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 1) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}

		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp >= 0) { return temp; }
			else {
				if (language_setting == 0) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 1) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 0) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 1) {
				cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
	}
}

int ATM::no_error_range(bool language_setting, int min, int max) {
	int temp = 0;
	while (true) {

		string abc = "";
		// cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow();
			}
			else {
				break;
			}
		}

		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 0) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 1) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}

		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp > min - 1 && temp < max + 1) { return temp; }
			else {
				if (language_setting == 0) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 1) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 0) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 1) {
				cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
	}
}

void ATM::languageChange() {
	if (language_available == 1) {
		cout << "unilingual ATM cannot change language!" << endl;
		return;
	}
	if (lang_setting == false) { cout << "Please choose the language setting." << endl; }
	else { cout << "�� ������ �ּ���." << endl; }
	cout << "[1] English" << endl;
	cout << "[2] �ѱ���" << endl;
	if (lang_setting == false) { cout << "Input : " << endl; }
	else { cout << "�Է� : " << endl; }

	int input_language_setting = no_error_range(lang_setting, 1, 2);

	if (input_language_setting == 2) {
		//this->language_setting = "Korean";
		this->lang_setting = true;
	}
	if (input_language_setting == 1) {
		//this->language_setting = "English";
		this->lang_setting = false;
	}
	return;
}

ATM::ATM(Bank* input_primary_bank, string input_serial_number, int input_type, int input_lanuage_available, int* initial_fund[], vector<Bank*>* blist, vector<ATM*>* alist) {
	this->primary_bank = input_primary_bank;
	this->serial_number = input_serial_number;
	this->type = input_type;
	this->language_available = input_lanuage_available;
	this->transaction_histories = input_serial_number + ".txt";
	this->admin_card = input_primary_bank->getBankName() + "admin";
	this->blist = blist;
	this->alist = alist;

	for (int i = 0; i < 4; ++i) {
		this->cash_storage[i] = initial_fund[i];
	}
}

ATM::~ATM() {
	this->primary_bank = nullptr;
	this->serial_number = "";
	this->type = 0;
	this->language_available = 0;

	for (int i = 0; i < 4; ++i) {
		this->cash_storage[i] = 0;
	}
}

void ATM::session(vector<Bank*> bank_list) {
	if (this->lang_setting == true) { cout << "ī�带 ������ �ּ���." << endl << "ī�� ��ȣ : "; }
	if (this->lang_setting == false) { cout << "Please insert your card." << endl << "Card number : "; }
	string cardinsert = "";
	string* pcardinsert = &cardinsert;
	//cin >> cardinsert;

	Qsearch(pcardinsert);

	if (cardinsert == this->admin_card) {
		see_transaction_history();
		return;
	}
	Account* acc = card2account(cardinsert, bank_list);
	if (acc == nullptr) {
		if (this->lang_setting == 1) { cout << "�߸��� ī�尡 �ԷµǾ����ϴ�. ī�带 ��ȯ�մϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Wrong card has inserted. Card will be return." << endl; }
		return;
	}
	if (this->user_authorization(acc) == false) {
		if (this->lang_setting == 1) { cout << "��й�ȣ �Է¿� 3ȸ �����ϼ̽��ϴ�. �ŷ��� �����մϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Failed to enter password 3 times. Transaction will be canceled." << endl; }
		return;
	}
	int* with_counter = new int(0);
	vector<vector<string>> record;
	for (int i = 0;; i++) {
		record.push_back(transaction(acc, bank_list, cardinsert, with_counter));
		if (record.at(i).at(2) == "Termination") {
			break;
		}
	}
	delete with_counter;
	for (int i = 0; i < record.size(); i++) {
		display_transaction_short(record.at(i));
	}
	return;
}

vector<string> ATM::transaction(Account* a, vector<Bank*> bank_list, string CardNumber, int* with_counter) {
	vector<string> rec; //transactionID, card number, transaction type, success or failure, amount, note
	rec.push_back(to_string(++static_transaction_counter));
	rec.push_back(CardNumber);
	int amount = 0;
	string note = "";

	if (this->lang_setting == 1) { cout << this->getSerial() << "�� ATM�� �����ϼ̽��ϴ�. ���� �۾��� ���͵帱���?" << endl; }
	else if (this->lang_setting == 0) { cout << "You've accessed ATM number " << this->getSerial() << ".What can we do for you ? " << endl; }
	if (this->lang_setting == 1) { cout << "[1] �Ա�" << endl << "[2] ���" << endl << "[3] ���� �۱�" << endl << "[4] ���� �۱�" << endl << "[5] ��� ����" << endl << "[6] ���� ��ȸ" << endl << "[7] �ŷ� ����" << endl << "���ϴ� �۾� : "; }
	else if (this->lang_setting == 0) { cout << "[1] deposit" << endl << "[2] withdraw" << endl << "[3] account transfer" << endl << "[4] cash transfer" << endl << "[5] language change" << endl << "[6] account inquiry" << endl << "[7] end transfer" << endl << "What you want to do : "; }

	int selection = no_error_range(lang_setting, 1, 7);
	if (selection == 1) {
		rec.push_back("Deposit");
		amount = deposit(a);
	}
	else if (selection == 2 && *with_counter < 3) {
		rec.push_back("Withdraw");
		amount = withdraw(a);
		*with_counter += 1;
	}
	else if (selection == 2 && *with_counter >= 3) {
		rec.push_back("Withdraw");
		if (this->lang_setting == 1) { cout << "����� �� ���ǿ� 3ȸ������ �����մϴ�!!" << endl; }
		else { cout << "The maximum number of withdrawals per each session is 3!!" << endl; }
		amount = -1;
	}
	else if (selection == 3) {
		rec.push_back("account transfer");
		if (this->lang_setting == 1) { cout << "�۱��� ������ ��ȣ�� �Է��� �ּ��� : "; }
		if (this->lang_setting == 0) { cout << "Please enter the number of the account you want to transfer : "; }
		string numinsert1 = "";
		string* pnuminsert1 = &numinsert1;
		Qsearch(pnuminsert1);
		Account* b = num2account(numinsert1, bank_list);
		if (b == nullptr) {
			if (this->lang_setting == 1) { cout << "�߸��� ���� ��ȣ�� �Է��ϼ̽��ϴ�. �ŷ��� �����մϴ�." << endl; }
			if (this->lang_setting == 0) { cout << "Invalid account number. Transaction will be canceled." << endl; }
			amount = -1;
		}
		else {
			amount = account_transfer(a, b);
			note = b->getAccountNumber();
		}
	}
	else if (selection == 4) {
		rec.push_back("cash transfer");
		if (this->lang_setting == 1) { cout << "�۱��� ������ ��ȣ�� �Է��� �ּ��� : "; }
		if (this->lang_setting == 0) { cout << "Please enter the number of the account you want to transfer : "; }
		string numinsert2 = "";
		string* pnuminsert2 = &numinsert2;
		Qsearch(pnuminsert2);
		Account* b = num2account(numinsert2, bank_list);
		if (b == nullptr) {
			if (this->lang_setting == 1) { cout << "�߸��� ���� ��ȣ�� �Է��ϼ̽��ϴ�. �ŷ��� �����մϴ�." << endl; }
			if (this->lang_setting == 0) { cout << "Invalid account number. Transaction will be canceled." << endl; }
			amount = -1;
		}
		else {
			amount = cash_transfer(b);
			note = b->getAccountNumber();
		}
	}
	else if (selection == 5) {
		rec.push_back("language change");
		languageChange();
		amount = 0;
	}
	else if (selection == 6) {
		rec.push_back("Account inquiry");
		a->printHistory();
		amount = 0;
	}
	else if (selection == 7) {
		rec.push_back("Termination");
		amount = 0;
	}
	else {
		if (lang_setting == true) { cout << "�Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl; }
		else { cout << "An input error has occurred. Please type the input again." << endl; }
		rec.push_back("invalid transaction");
		rec.push_back("Failure");
		rec.push_back("-1");
	}
	if (amount == -1) { rec.push_back("Failure"); }
	else { rec.push_back("Success"); }
	rec.push_back(to_string(amount));
	rec.push_back(note);
	make_history(rec);
	a->updateHistory(rec[0], rec[1], rec[2], rec[4], rec[5]);
	return rec;
}

void ATM::add_cash(int cash1000, int cash5000, int cash10000, int cash50000) {
	*(this->cash_storage[0]) += cash1000;
	*(this->cash_storage[1]) += cash5000;
	*(this->cash_storage[2]) += cash10000;
	*(this->cash_storage[3]) += cash50000;
}

bool ATM::user_authorization(Account* a) {
	//ī�� �Է�

	//ī�� ��ȿ�� �˻�

	//��й�ȣ �Է�

	//��й�ȣ �˻�

	//3�� ���� Ʋ���� ���� �ߴܵǰ�
	if (this->lang_setting == 1) { cout << "�ȳ��ϼ���, " << a->getUserName() << "." << endl; }
	if (this->lang_setting == 0) { cout << "Hello, " << a->getUserName() << "." << endl; }
	if (this->lang_setting == 1) { cout << "��й�ȣ�� 3ȸ Ʋ����, �ŷ�<�� ����˴ϴ�." << endl; }
	if (this->lang_setting == 0) { cout << "If you get the password wrong 3 times, the transaction ends." << endl; }
	string pass = "";
	string* ppass = &pass;
	for (int i = 0; i < 3; i++) {
		if (this->lang_setting == 1) { cout << "��й�ȣ�� �Է��� �ֽʽÿ�." << endl; }
		else if (this->lang_setting == 0) { cout << "Please enter your password." << endl; }
		if (this->lang_setting == 1) { cout << "���� �Է� Ƚ�� : " << 3 - i << "ȸ" << endl << "��й�ȣ : "; }
		else if (this->lang_setting == 0) { cout << "remaining : " << 3 - i << " times" << endl << "password : "; }
		Qsearch(ppass);
		if (a->getPassword() == pass) {
			return true;
		}
		if (this->lang_setting == 1) { cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Wrong password." << endl; }
	}
	return false;
}

void ATM::see_transaction_history() {
	if (this->lang_setting == 1) { cout << "������ ī�尡 �ԷµǾ����ϴ�." << endl << "������ �������� � �۾��� �Ͻðڽ��ϱ�?" << endl << "[0] �ŷ� ���� Ȯ�� " << endl; }
	if (this->lang_setting == 0) { cout << "Admin card has inserted." << endl << "What do you want to do with administrator privileges?" << endl << "[0] Transaction history " << endl; }
	int no = no_error_range(lang_setting, 0, 2);
	if (no == 2) {
		if (lang_setting == true) { cout << "�ʱ� ȭ������ ���ư��ϴ�." << endl; }
		else { cout << "Returning to the initial screen." << endl; }
		return;
	}
	if (no == 1) {
		int replenish[4] = { 0,0,0,0 };
		if (this->lang_setting == 1) { cout << "������ 1000������ ���� �Է��� �ּ���." << endl; }
		if (this->lang_setting == 0) { cout << "Please enter the amount of 1,000 won bills to be replenished." << endl; }
		replenish[0] = no_error(lang_setting);
		if (this->lang_setting == 1) { cout << "������ 5000������ ���� �Է��� �ּ���." << endl; }
		if (this->lang_setting == 0) { cout << "Please enter the amount of 5,000 won bills to be replenished." << endl; }
		replenish[1] = no_error(lang_setting);
		if (this->lang_setting == 1) { cout << "������ 10000������ ���� �Է��� �ּ���." << endl; }
		if (this->lang_setting == 0) { cout << "Please enter the amount of 10,000 won bills to be replenished." << endl; }
		replenish[2] = no_error(lang_setting);
		if (this->lang_setting == 1) { cout << "������ 50000������ ���� �Է��� �ּ���." << endl; }
		if (this->lang_setting == 0) { cout << "Please enter the amount of 50,000 won bills to be replenished." << endl; }
		replenish[3] = no_error(lang_setting);
		add_cash(replenish[0], replenish[1], replenish[2], replenish[3]);
		return;
	}
	else if (no == 0) {
		if (this->lang_setting == 1) { cout << "�ŷ� ������ ����մϴ�." << endl << endl; }
		else if (this->lang_setting == 0) { cout << "Printing transaction histories." << endl << endl; }
		ifstream readFile(this->transaction_histories);
		if (readFile.is_open()) {
			string str;
			while (readFile) {
				getline(readFile, str);
				cout << str << endl;
			}
		}
		else {
			if (this->lang_setting == 1) { cout << "�ش��ϴ� ������ �����ϴ�." << endl; }
			if (this->lang_setting == 0) { cout << "No corresponding files exist." << endl; }
		}
		return;
	}
	else {
		if (lang_setting == true) { cout << "�ʱ� ȭ������ ���ư��ϴ�." << endl; }
		else { cout << "Returning to the initial screen." << endl; }
		return;
	}
	return;
}

void ATM::make_history(vector<string> rec) {
	//Transaction ID
	//Card Number
	//Transaction Types : deposit, withdraw, account transfer, cash_transfer
	//Amount
	//other transaction-specific information
	//account transfer:enemy account number
	//cash transfer:enemy account number
	//vector<string>new_history = { TransactionID, CardNumber, TransactionTypes, sorf, Amount, Specific }; // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecific Information
	//int len = static_cast<int>(rec.size());

	ofstream writeFromFile(this->transaction_histories, ios::app);
	writeFromFile << "TransactionID : " << rec[0] << "\n";
	writeFromFile << "CardNumber : " << rec[1] << "\n";
	writeFromFile << "TransactionTypes : " << rec[2] << "\n";
	writeFromFile << "Success or failure : " << rec[3] << "\n";
	writeFromFile << "Amount : " << rec[4] << "\n";
	writeFromFile << "Note : " << rec[5] << "\n";
	writeFromFile << "\n";
	return;
}

void ATM::display_transaction(vector<string> rec) {
	//string TransactionID, string CardNumber, string TransactionTypes, string sorf, string Amount, string Specific
	cout << "Transaction ID : " << rec[0] << endl;
	cout << "CardNumber : " << rec[1] << endl;
	cout << "TransactionTypes : " << rec[2] << endl;
	cout << "Success or Failure : " << rec[3] << endl;
	cout << "Amount : " << rec[4] << endl;
	cout << "Note : " << rec[5] << endl;
	return;
}

void ATM::display_transaction_short(vector<string> rec) {
	//string TransactionID, string CardNumber, string TransactionTypes, string sorf, string Amount, string Specific
	cout << "[/";
	for (int i = 0; i < rec.size(); i++) {
		if (rec[i] != "") { cout << rec[i] << "/"; }
	}
	cout << "]" << endl;
	return;
}

void ATM::printNow() {
	for (int i = 0; i < (*blist).size(); i++) {
		for (int j = 0; j < (*blist)[i]->get_account().size(); j++) {
			cout << "Account[" << (*blist)[i]->get_account()[j]->getUserName() << "] : " << (*blist)[i]->get_account()[j]->checkFunds() << "/" << (*blist)[i]->get_account()[j]->getAccountNumber() << "/" << (*blist)[i]->get_account()[j]->getBankName() << endl;
		}
	}
	for (int i = 0; i < (*alist).size(); i++) {
		cout << "ATM " << "[" << i << "] " << "Primary Bank : " << (*alist)[i]->getPrimary()->getBankName() << " " << (*alist)[i]->getType() << " " << (*alist)[i]->getLangType() << endl;
		cout << "Remaing cash : " << 1000 * (*alist)[i]->get1000() + 5000 * (*alist)[i]->get5000() + 10000 * (*alist)[i]->get10000() + 50000 * (*alist)[i]->get50000() << " (1000 : " << (*alist)[i]->get1000() << ", 5000 : " << (*alist)[i]->get5000() << ", 10000 : " << (*alist)[i]->get10000() << ", 50000 : " << (*alist)[i]->get50000() << ")" << endl;
		// cout << "ATM [" << ATM_list[i]->getSerial() << "] Remaing cash : " << 1000 * ATM_list[i]->get1000() + 5000 * ATM_list[i]->get5000() + 10000 * ATM_list[i]->get10000() + 50000 * ATM_list[i]->get50000() << " (1000 : " << ATM_list[i]->get1000() << ", 5000 : " << ATM_list[i]->get5000() << ", 10000 : " << ATM_list[i]->get10000() << ", 50000 : " << ATM_list[i]->get50000() << ")" << endl;
	}
	cout << endl;
	cout << "Please re-enter here : ";
	return;
}

string ATM::getSerial() {
	return serial_number;
}

Bank* ATM::getPrimary() {
	return primary_bank;
}

string ATM::getLangType() {
	if (language_available == 1) {
		return "Unilingual";
	}
	else {
		return "Bilingual";
	}
}

int ATM::get1000() {
	return *(cash_storage[0]);
}
int ATM::get5000() {
	return *(cash_storage[1]);
}
int ATM::get10000() {
	return *(cash_storage[2]);
}
int ATM::get50000() {
	return *(cash_storage[3]);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Single Bank ATM Class Member Definition
Single::Single(Bank* input_primary_bank, string input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4], vector<Bank*>* blist, vector<ATM*>* alist) : ATM(input_primary_bank, input_serial_number, 1, input_lanuage_available, initial_fund, blist, alist) {
	for (int i = 0; i < 4; i++) {
		this->fee_list[i] = fees[i];
	}
}

int Single::deposit(Account* a) {
	if (this->lang_setting == true) {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �Ա��� �� �����ϴ�." << endl;
			return -1;
		}
		cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
		if (*(fee_list[0]) == 0) {
			cout << "������ �����ᰡ �����ϴ�." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(fee_list[0])) / 1000;
			cout << "�����ᰡ �ԱݵǾ����ϴ�." << endl;
		}
		cout << "�Ա��� �����մϴ�." << endl;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Deposits cannot be made to accounts at other banks." << endl;
			return -1;
		}
		cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
		if (*(fee_list[0]) == 0) {
			cout << "There are no fees to pay." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(fee_list[0])) / 1000;
			cout << "The fee has been deposited." << endl;
		}
		cout << "Initiate deposit." << endl;
	}
	int deposit_method;
	int cash1000;
	int cash5000;
	int cash10000;
	int cash50000;
	if (this->lang_setting == true) {
		cout << "�Ա� ������ ������ �ּ���" << endl;
		cout << "[1] ����" << "   " << "[2] ��ǥ" << endl;
		deposit_method = no_error_range(lang_setting, 1, 2);
		if (deposit_method == 1) {
			cout << "�� ��Ⱑ ó���� �� �ִ� ������ �ż��� 50������Դϴ�." << endl << "1000������ ������ �ּ���." << endl;
			cash1000 = no_error(lang_setting);
			cout << "5000������ ������ �ּ���." << endl;
			cash5000 = no_error(lang_setting);
			cout << "10000������ ������ �ּ���." << endl;
			cash10000 = no_error(lang_setting);
			cout << "50000������ ������ �ּ���." << endl;
			cash50000 = no_error(lang_setting);
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "����� ó�� �Ѱ踦 �ʰ��Ͽ����ϴ�." << endl;
				return -1;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl << "�Ա� ������ �ܰ�� " << a->checkFunds() << "�Դϴ�." << endl;
			return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
		}
		else if (deposit_method == 2) {
			cout << "�� ��Ⱑ ó���� �� �ִ� ��ǥ�� �ż��� 50������Դϴ�. ��ǥ�� ������ �ּ���." << endl << "�ùٸ��� ���� ��ǥ�� �Է��ϸ� ������ �ߴܵ˴ϴ�." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				checks[i] = no_error(lang_setting);
				if (checks[i] < 100000) {
					checks[i] = 0;
					cout << "������ �ߴܵǾ����ϴ�. �Ա��� �����մϴ�." << endl;
					break;
				}
			}
			int check_sum = 0;
			for (int i = 0; i <= 50; i++) {
				if (checks[i] >= 100000) {
					check_sum += checks[i];
				}
				else break;
			}
			a->deposit(check_sum);
			cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl << "�Ա� ������ �ܰ�� " << a->checkFunds() << "�Դϴ�." << endl;
			return check_sum;
		}
		else {
			cout << "������ �߻��߽��ϴ�. �Ա��� �ߴ��մϴ�." << endl;
			return -1;
		}
	}
	else {
		cout << "Please select deposit method" << endl;
		cout << "[1] cash" << "   " << "[2] check" << endl;
		int deposit_method = no_error_range(lang_setting, 1, 2);
		if (deposit_method == 1) {
			cout << "This device can process up to 50 cashes." << endl << "Please input 1000 won bills." << endl;
			cash1000 = no_error(lang_setting);
			cout << "Please input 5000 won bills." << endl;
			cash5000 = no_error(lang_setting);
			cout << "Please input 10000 won bills." << endl;
			cash10000 = no_error(lang_setting);
			cout << "Please input 50000 won bills." << endl;
			cash50000 = no_error(lang_setting);
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "The device's processing limit has been exceeded." << endl;
				return -1;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			cout << "Deposit has been completed." << endl << "The balance of the deposit account is " << setw(10) << a->checkFunds() << "." << endl;
			return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
		}
		else if (deposit_method == 2) {
			cout << "This device can process up to 50 checks. Please insert checks." << endl << "If you enter an incorrect check, the insertion will be ended." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				checks[i] = no_error(lang_setting);
				if (checks[i] < 100000) {
					checks[i] = 0;
					cout << "Insertion ended. deposit is starting." << endl;
					break;
				}
			}
			int check_sum = 0;
			for (int i = 0; i <= 50; i++) {
				if (checks[i] >= 100000) {
					check_sum += checks[i];
				}
				else break;
			}
			a->deposit(check_sum);
			cout << "Deposit has been completed." << endl << "The balance of the deposit account is " << setw(10) << a->checkFunds() << "." << endl;
			return check_sum;
		}
		else {
			cout << "Error detected. Deposit will be stopped." << endl;
			return -1;
		}
	}
	return -1;
}

int Single::withdraw(Account* a) {
	if (this->lang_setting == true) {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���¿��� ����� �� �����ϴ�." << endl;
			return -1;
		}
		cout << "����� �����մϴ�." << endl;
		if (*(this->fee_list[1]) == 0) {
			cout << "������ ����� �����ϴ�." << endl;
		}
		else if (*(this->fee_list[1]) > a->checkFunds()) {
			cout << "�ܾ��� �����մϴ�." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[1]));
		}
		//this->withdraw(a);
		int amount;
		cout << "����� �׼��� 1000�� ��� ������ �Է��ϼ���. �ִ� �ݾ��� 50�����Դϴ�." << endl;
		cout << "����� �ܰ�� " << setw(10) << a->checkFunds() << "�� �Դϴ�." << endl;
		amount = no_error(lang_setting);
		if (amount > 500000) {
			cout << "50������ �ʰ��� �ݾ��� �Է��ϼ̽��ϴ�. ����� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount % 1000 != 0) {
			cout << "1000�� ����� �ƴ� �ݾ��� �Է��ϼ̽��ϴ�. ����� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount > a->checkFunds()) {
			cout << "���¿� �ܾ��� �����մϴ�. ����� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		int temp4 = amount / 50000;
		int temp3 = (amount % 50000) / 10000;
		int temp2 = (amount % 10000) / 5000;
		int temp1 = (amount % 5000) / 1000;
		if (temp4 > *(this->cash_storage[3])) {
			temp3 += 5 * (temp4 - *(this->cash_storage[3]));
		}
		if (temp3 > *(this->cash_storage[2])) {
			temp2 += 2 * (temp3 - *(this->cash_storage[2]));
		}
		if (temp2 > *(this->cash_storage[1])) {
			temp1 += 5 * (temp2 - *(this->cash_storage[1]));
		}
		if (temp1 > *(this->cash_storage[0])) {
			cout << "ATM�� ������ �����մϴ�. ����� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		else {
			*(this->cash_storage[3]) -= temp4;
			*(this->cash_storage[2]) -= temp3;
			*(this->cash_storage[1]) -= temp2;
			*(this->cash_storage[0]) -= temp1;
		}
		a->withdraw(amount);
		cout << "����� �Ϸ�Ǿ����ϴ�." << endl << "��� ������ �ܰ�� " << setw(10) << a->checkFunds() << "�Դϴ�.";
		return amount;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Withdrawals cannot be made from accounts at other banks." << endl;
			return -1;
		}
		cout << "Pay the fee." << endl;
		if (*(this->fee_list[1]) == 0) {
			cout << "There are no fees to pay." << endl;
		}
		else if (*(this->fee_list[1]) > a->checkFunds()) {
			cout << "Your balance is insufficient." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[1]));
		}
		//this->withdraw(a);
		int amount;
		cout << "Enter the amount you wish to withdraw in multiples of 1000. The maximum amount is 500,000 won." << endl;
		cout << "Your remaining fund is " << setw(10) << a->checkFunds() << "." << endl;
		amount = no_error(lang_setting);
		if (amount > 500000) {
			cout << "You entered an amount exceeding 500,000 won. Cancel withdrawal." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount % 1000 != 0) {
			cout << "You entered an amount that is not a multiple of 1000. Cancel withdrawal." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount > a->checkFunds()) {
			cout << "There are insufficient funds in your account. Cancel withdrawal." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		int temp4 = amount / 50000;
		int temp3 = (amount % 50000) / 10000;
		int temp2 = (amount % 10000) / 5000;
		int temp1 = (amount % 5000) / 1000;
		if (temp4 > *(this->cash_storage[3])) {
			temp3 += 5 * (temp4 - *(this->cash_storage[3]));
		}
		if (temp3 > *(this->cash_storage[2])) {
			temp2 += 2 * (temp3 - *(this->cash_storage[2]));
		}
		if (temp2 > *(this->cash_storage[1])) {
			temp1 += 5 * (temp2 - *(this->cash_storage[1]));
		}
		if (temp1 > *(this->cash_storage[0])) {
			cout << "The ATM is out of cash. Cancel withdrawal." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		else {
			*(this->cash_storage[3]) -= temp4;
			*(this->cash_storage[2]) -= temp3;
			*(this->cash_storage[1]) -= temp2;
			*(this->cash_storage[0]) -= temp1;
		}
		a->withdraw(amount);
		cout << "Withdrawal has been completed." << endl << "The balance of the withdrawal account is " << setw(10) << a->checkFunds() << ".";
		return amount;
	}
}

int Single::account_transfer(Account* a, Account* b) {
	if (this->lang_setting == false) {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "You cannot transfer money from an account at another bank." << endl;
			return -1;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Money cannot be transferred to another bank's account." << endl;
			return -1;
		}
		cout << "Pay the fee." << endl;
		if (*(this->fee_list[2]) == 0) {
			cout << "There are no fees to pay." << endl;
		}
		else if (*(this->fee_list[2]) > a->checkFunds()) {
			cout << "Your balance is insufficient." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[2]));
		}
		//this->account_transfer(a, b);
		int amount;
		cout << "Please enter the amount you wish to transfer." << endl;
		cout << "Your remaining fund is " << setw(10) << a->checkFunds() << "." << endl;
		amount = no_error(lang_setting);
		if (amount > a->checkFunds()) {
			cout << "Your balance is insufficient. Cancel the transfer." << endl;
			a->deposit(*(this->fee_list[2]));
			return -1;
		}
		a->withdraw(amount);
		b->deposit(amount);
		cout << "The transfer has been completed." << endl << "The balance of the source account is" << setw(10) << a->checkFunds() << ".";
		return amount;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���¿��� �۱��� �� �����ϴ�." << endl;
			return -1;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �۱��� �� �����ϴ�." << endl;
			return -1;
		}
		cout << "����� �����մϴ�." << endl;
		if (*(this->fee_list[2]) == 0) {
			cout << "������ ����� �����ϴ�." << endl;
		}
		else if (*(this->fee_list[2]) > a->checkFunds()) {
			cout << "�ܾ��� �����մϴ�." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[2]));
		}
		//this->account_transfer(a, b);
		int amount;
		cout << "�۱��� �׼��� �Է��� �ּ���." << endl;
		cout << "����� �ܰ�� " << setw(10) << a->checkFunds() << "�� �Դϴ�." << endl;
		amount = no_error(lang_setting);
		if (amount > a->checkFunds()) {
			cout << "�ܾ��� �����մϴ�. �۱��� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[2]));
			return -1;
		}
		a->withdraw(amount);
		b->deposit(amount);
		cout << "�۱��� �Ϸ�Ǿ����ϴ�." << endl << "��� ������ �ܰ�� " << setw(10) << a->checkFunds() << "�Դϴ�.";
		return amount;
	}
}

int Single::cash_transfer(Account* b) {
	if (this->lang_setting == false) {
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Money cannot be transferred to another bank's account." << endl;
			return -1;
		}
		cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
		if (*(this->fee_list[3]) == 0) {
			cout << "There are no fees to pay." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
			cout << "The fee has been deposited." << endl;
		}
		cout << "Initiate cash transfer." << endl;
		cout << "Please insert a 1,000 won bill." << endl;
		int cash1000 = no_error(lang_setting);
		cout << "Please insert a 5,000 won bill." << endl;
		int cash5000 = no_error(lang_setting);
		cout << "Please insert a 10,000 won bill." << endl;
		int cash10000 = no_error(lang_setting);
		cout << "Please insert a 50,000 won bill." << endl;
		int cash50000 = no_error(lang_setting);
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "The transfer has been completed." << endl;
		return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
	}
	else {
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �۱��� �� �����ϴ�." << endl;
			return -1;
		}
		cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
		if (*(this->fee_list[3]) == 0) {
			cout << "������ �����ᰡ �����ϴ�." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
			cout << "�����ᰡ �ԱݵǾ����ϴ�." << endl;
		}
		cout << "���� �۱��� �����մϴ�." << endl;
		cout << "1000������ ������ �ּ���." << endl;
		int cash1000 = no_error(lang_setting);;
		cout << "5000������ ������ �ּ���." << endl;
		int cash5000 = no_error(lang_setting);;
		cout << "10000������ ������ �ּ���." << endl;
		int cash10000 = no_error(lang_setting);;
		cout << "50000������ ������ �ּ���." << endl;
		int cash50000 = no_error(lang_setting);;
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "�۱��� �Ϸ�Ǿ����ϴ�." << endl;
		return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
	}
}

Account* Single::card2account(string card, vector<Bank*> bank_list) {
	bool isPrimary = false;
	Account* ac = 0;
	for (int i = 0; i < primary_bank->get_account().size(); i++) {
		vector<string> card_list = primary_bank->get_account()[i]->getCardNumber();
		for (int j = 0; j < card_list.size(); j++) {
			if (card_list[j] == card) {
				isPrimary = true;
				ac = primary_bank->get_account()[i];
				break;
			}
		}
	}
	if (isPrimary == false) {
		if (this->lang_setting == 1) { cout << "�������� �ʴ� ī���Դϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Unsupported card." << endl; }
		return nullptr;
	}
	return ac;
}

Account* Single::num2account(string num, vector<Bank*> bank_list) {
	bool isPrimary = false;
	Account* ac = 0;
	for (int i = 0; i < primary_bank->get_account().size(); i++) {
		string acc_num = primary_bank->get_account()[i]->getAccountNumber();
		if (acc_num == num) {
			isPrimary = true;
			ac = primary_bank->get_account()[i];
			break;
		}
	}
	if (isPrimary == false) {
		if (this->lang_setting == 1) { cout << "�������� �ʴ� �����Դϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Unsupported account." << endl; }
		return nullptr;
	}
	return ac;
}

string Single::getType() {
	return "Single-bank ATM";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Multi Bank ATM Class Member Definition
Multi::Multi(Bank* input_primary_bank, string input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4], int* fees2[4], vector<Bank*>* blist, vector<ATM*>* alist) : ATM(input_primary_bank, input_serial_number, 2, input_lanuage_available, initial_fund, blist, alist) {
	for (int i = 0; i < 4; i++) {
		this->fee_list[i] = fees[i];
	}
	for (int i = 0; i < 4; i++) {
		this->multi_fee_list[i] = fees2[i];
	}
}

int Multi::deposit(Account* a) {
	int account_count = 0;
	if (this->lang_setting == true) {
		if (a->getBankName() == this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �Ա��մϴ�." << endl;
			account_count = 1;
		}
		else {
			cout << "�� ������ ���·� �Ա��մϴ�." << endl;
		}
		if (account_count == 0) {
			cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
			if (*(this->fee_list[0]) == 0) {
				cout << "������ �����ᰡ �����ϴ�." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->fee_list[0])) / 1000;
				cout << "�����ᰡ �ԱݵǾ����ϴ�." << endl;
			}
			cout << "�Ա��� �����մϴ�." << endl;
		}
		else {
			cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
			if (*(this->multi_fee_list[0]) == 0) {
				cout << "������ �����ᰡ �����ϴ�." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->multi_fee_list[0])) / 1000;
				cout << "�����ᰡ �ԱݵǾ����ϴ�." << endl;
			}
			cout << "�Ա��� �����մϴ�." << endl;
		}
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Deposits will be made to accounts at other banks." << endl;
			account_count = 1;
		}
		if (account_count == 0) {
			cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
			if (*(this->fee_list[0]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->fee_list[0])) / 1000;
				cout << "The fee has been deposited." << endl;
			}
			cout << "Initiate deposit." << endl;
		}
		else {
			cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
			if (*(this->multi_fee_list[0]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->multi_fee_list[0])) / 1000;
				cout << "The fee has been deposited." << endl;
			}
			cout << "Initiate deposit." << endl;
		}
	}
	int deposit_method;
	if (this->lang_setting == true) {
		cout << "�Ա� ������ ������ �ּ���" << endl;
		cout << "[1] ����" << "   " << "[2] ��ǥ" << endl;
		deposit_method = no_error_range(lang_setting, 1, 2);
		if (deposit_method == 1) {
			cout << "�� ��Ⱑ ó���� �� �ִ� ������ �ż��� 50������Դϴ�." << endl << "1000������ ������ �ּ���." << endl;
			int cash1000 = no_error(lang_setting);
			cout << "5000������ ������ �ּ���." << endl;
			int cash5000 = no_error(lang_setting);
			cout << "10000������ ������ �ּ���." << endl;
			int cash10000 = no_error(lang_setting);
			cout << "50000������ ������ �ּ���." << endl;
			int cash50000 = no_error(lang_setting);
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "����� ó�� �Ѱ踦 �ʰ��Ͽ����ϴ�." << endl;
				return -1;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl << "�Ա� ������ �ܰ�� " << setw(10) << a->checkFunds() << "�Դϴ�." << endl;
			return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
		}
		else if (deposit_method == 2) {
			cout << "�� ��Ⱑ ó���� �� �ִ� ��ǥ�� �ż��� 50������Դϴ�. ��ǥ�� ������ �ּ���." << endl << "�ùٸ��� ���� ��ǥ�� �Է��ϸ� ������ �ߴܵ˴ϴ�." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				checks[i] = no_error(lang_setting);
				if (checks[i] < 100000) {
					checks[i] = 0;
					cout << "������ �ߴܵǾ����ϴ�. �Ա��� �����մϴ�." << endl;
					break;
				}
			}
			int check_sum = 0;
			for (int i = 0; i <= 50; i++) {
				if (checks[i] >= 100000) {
					check_sum += checks[i];
				}
				else break;
			}
			a->deposit(check_sum);
			cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl << "�Ա� ������ �ܰ�� " << setw(10) << a->checkFunds() << "�Դϴ�." << endl;
			return check_sum;
		}
		else {
			cout << "������ �߻��߽��ϴ�. �Ա��� �ߴ��մϴ�." << endl;
			return -1;
		}
	}
	else {
		cout << "Please select deposit method" << endl;
		cout << "[1] cash" << "   " << "[2] check" << endl;
		int deposit_method = no_error_range(lang_setting, 1, 2);
		if (deposit_method == 1) {
			cout << "This device can process up to 50 cashes." << endl << "Please input 1000 won bills." << endl;
			int cash1000 = no_error(lang_setting);
			cout << "Please input 5000 won bills." << endl;
			int cash5000 = no_error(lang_setting);
			cout << "Please input 10000 won bills." << endl;
			int cash10000 = no_error(lang_setting);
			cout << "Please input 50000 won bills." << endl;
			int cash50000 = no_error(lang_setting);
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "The device's processing limit has been exceeded." << endl;
				return -1;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			cout << "Deposit has been completed." << endl << "The balance of the deposit account is " << setw(10) << a->checkFunds() << "." << endl;
			return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
		}
		else if (deposit_method == 2) {
			cout << "This device can process up to 50 checks. Please insert checks." << endl << "If you enter an incorrect check, the insertion will be ended." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				checks[i] = no_error(lang_setting);
				if (checks[i] < 100000) {
					checks[i] = 0;
					cout << "Insertion ended. deposit is starting." << endl;
					break;
				}
			}
			int check_sum = 0;
			for (int i = 0; i <= 50; i++) {
				if (checks[i] >= 100000) {
					check_sum += checks[i];
				}
				else break;
			}
			a->deposit(check_sum);
			cout << "Deposit has been completed." << endl << "The balance of the deposit account is " << setw(10) << a->checkFunds() << "." << endl;
			return check_sum;
		}
		else {
			cout << "Error detected. Deposit will be stopped." << endl;
			return -1;
		}
	}
	return -1;
}

int Multi::withdraw(Account* a) {
	int coconut = 0;
	if (this->lang_setting == true) {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���¿��� ����մϴ�." << endl;
			coconut = 1;
		}
		else {
			cout << "�� ������ ���¿��� ����մϴ�." << endl;
		}
		cout << "����� �����մϴ�." << endl;
		if (coconut == 0) {
			if (*(this->fee_list[1]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->fee_list[1]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->fee_list[1]));
			}
		}
		else {
			if (*(this->multi_fee_list[1]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->multi_fee_list[1]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->multi_fee_list[1]));
			}
		}
		//this->withdraw(a);
		cout << "����� �׼��� 1000�� ��� ������ �Է��ϼ���. �ִ� �ݾ��� 50�����Դϴ�." << endl;
		cout << "����� �ܰ�� " << setw(10) << a->checkFunds() << "�� �Դϴ�." << endl;
		int amount = no_error(lang_setting);
		if (amount > 500000) {
			cout << "50������ �ʰ��� �ݾ��� �Է��ϼ̽��ϴ�. ����� ����մϴ�." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return -1;
		}
		if (amount % 1000 != 0) {
			cout << "1000�� ����� �ƴ� �ݾ��� �Է��ϼ̽��ϴ�. ����� ����մϴ�." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return -1;
		}
		if (amount > a->checkFunds()) {
			cout << "���¿� �ܾ��� �����մϴ�. ����� ����մϴ�." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return -1;
		}
		int temp4 = amount / 50000;
		int temp3 = (amount % 50000) / 10000;
		int temp2 = (amount % 10000) / 5000;
		int temp1 = (amount % 5000) / 1000;
		if (temp4 > *(this->cash_storage[3])) {
			temp3 += 5 * (temp4 - *(this->cash_storage[3]));
		}
		if (temp3 > *(this->cash_storage[2])) {
			temp2 += 2 * (temp3 - *(this->cash_storage[2]));
		}
		if (temp2 > *(this->cash_storage[1])) {
			temp1 += 5 * (temp2 - *(this->cash_storage[1]));
		}
		if (temp1 > *(this->cash_storage[0])) {
			cout << "ATM�� ������ �����մϴ�. ����� ����մϴ�." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return -1;
		}
		else {
			*(this->cash_storage[3]) -= temp4;
			*(this->cash_storage[2]) -= temp3;
			*(this->cash_storage[1]) -= temp2;
			*(this->cash_storage[0]) -= temp1;
		}
		a->withdraw(amount);
		cout << "����� �Ϸ�Ǿ����ϴ�." << endl << "��� ������ �ܰ�� " << setw(10) << a->checkFunds() << "�Դϴ�.";
		return amount;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Withdrawals will be made from accounts at other banks." << endl;
			coconut = 1;
		}
		else {
			cout << "Withdrawals will be made from accounts at this banks." << endl;
		}
		if (coconut == 0) {
			cout << "Pay the fee." << endl;
			if (*(this->fee_list[1]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->fee_list[1]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->fee_list[1]));
			}
		}
		else {
			cout << "Pay the fee." << endl;
			if (*(this->multi_fee_list[1]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->multi_fee_list[1]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->multi_fee_list[1]));
			}
		}
		//this->withdraw(a);
		cout << "Enter the amount you wish to withdraw in multiples of 1000. The maximum amount is 500,000 won." << endl;
		cout << "Your remaining fund is " << setw(10) << a->checkFunds() << "." << endl;
		int amount = no_error(lang_setting);
		if (amount > 500000) {
			cout << "You entered an amount exceeding 500,000 won. Cancel withdrawal." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return -1;
		}
		if (amount % 1000 != 0) {
			cout << "You entered an amount that is not a multiple of 1000. Cancel withdrawal." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return -1;
		}
		if (amount > a->checkFunds()) {
			cout << "There are insufficient funds in your account. Cancel withdrawal." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return -1;
		}
		int temp4 = amount / 50000;
		int temp3 = (amount % 50000) / 10000;
		int temp2 = (amount % 10000) / 5000;
		int temp1 = (amount % 5000) / 1000;
		if (temp4 > *(this->cash_storage[3])) {
			temp3 += 5 * (temp4 - *(this->cash_storage[3]));
		}
		if (temp3 > *(this->cash_storage[2])) {
			temp2 += 2 * (temp3 - *(this->cash_storage[2]));
		}
		if (temp2 > *(this->cash_storage[1])) {
			temp1 += 5 * (temp2 - *(this->cash_storage[1]));
		}
		if (temp1 > *(this->cash_storage[0])) {
			cout << "The ATM is out of cash. Cancel withdrawal." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return -1;
		}
		else {
			*(this->cash_storage[3]) -= temp4;
			*(this->cash_storage[2]) -= temp3;
			*(this->cash_storage[1]) -= temp2;
			*(this->cash_storage[0]) -= temp1;
		}
		a->withdraw(amount);
		cout << "Withdrawal has been completed." << endl << "The balance of the withdrawal account is " << setw(10) << a->checkFunds() << ".";
		return amount;
	}
}

int Multi::account_transfer(Account* a, Account* b) {
	int coconut = 0;
	int cococonut = 0;
	if (this->lang_setting == false) {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Transfer money from an account at another bank : " << a->getUserName() << endl;
			coconut = 1;
		}
		//else {
		if (a->getBankName() == this->primary_bank->getBankName()) {
			cout << "Transfer money from an account at this bank : " << a->getUserName() << endl;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Transferred to another bank's account : " << b->getUserName() << endl;
			cococonut = 1;
		}
		//else {
		if (b->getBankName() == this->primary_bank->getBankName()) {
			cout << "Transferred to this bank's account : " << b->getUserName() << endl;
		}
		if (coconut == 0 && cococonut == 0) {
			cout << "Pay the fee." << endl;
			if (*(this->fee_list[2]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->fee_list[2]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->fee_list[2]));
			}
		}
		else if (coconut == 1 && cococonut == 1) {
			cout << "Pay the fee." << endl;
			if (*(this->multi_fee_list[3]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->multi_fee_list[3]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->multi_fee_list[3]));
			}
		}
		else {
			cout << "Pay the fee." << endl;
			if (*(this->multi_fee_list[2]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->multi_fee_list[2]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->multi_fee_list[2]));
			}
		}
		//this->account_transfer(a, b);
		cout << "Please enter the amount you wish to transfer." << endl;
		cout << "Your remaining fund is " << setw(10) << a->checkFunds() << "." << endl;
		int amount = no_error(lang_setting);
		if (a->checkFunds() < amount) {
			cout << "Your balance is insufficient. Cancel the transfer." << endl;
			if (coconut == 0 && cococonut == 0) {
				a->deposit(*(this->fee_list[2]));
			}
			else if (coconut == 1 && cococonut == 1) {
				a->deposit(*(this->multi_fee_list[3]));
			}
			else {
				a->deposit(*(this->multi_fee_list[2]));
			}
			return -1;
		}
		a->withdraw(amount);
		b->deposit(amount);
		cout << "The transfer has been completed." << endl << "The balance of the source account is" << setw(10) << a->checkFunds() << "." << endl;
		return amount;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���¿��� �۱��մϴ� : " << a->getUserName() << endl;
			coconut = 1;
		}
		else {
			cout << "�� ������ ���¿��� �۱��մϴ� : " << a->getUserName() << endl;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �۱��մϴ� : " << b->getUserName() << endl;
			cococonut = 1;
		}
		else {
			cout << "�� ������ ���·� �۱��մϴ� : " << b->getUserName() << endl;
		}
		cout << "����� �����մϴ�." << endl;
		if (coconut == 0 && cococonut == 0) {
			if (*(this->fee_list[2]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->fee_list[2]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->fee_list[2]));
			}
		}
		else if (coconut == 1 && cococonut == 1) {
			if (*(this->multi_fee_list[3]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->multi_fee_list[3]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->multi_fee_list[3]));
			}
		}
		else {
			if (*(this->multi_fee_list[2]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->multi_fee_list[2]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return -1;
			}
			else {
				a->withdraw(*(this->multi_fee_list[2]));
			}
		}
		//this->account_transfer(a, b);
		cout << "�۱��� �׼��� �Է��� �ּ���." << endl;
		cout << "�����Ͻ� �ܰ�� " << setw(10) << a->checkFunds() << "�� �Դϴ�." << endl;
		int amount = no_error(lang_setting);
		if (amount > a->checkFunds()) {
			cout << "�ܾ��� �����մϴ�. �۱��� ����մϴ�." << endl;
			if (coconut == 0 && cococonut == 0) {
				a->deposit(*(this->fee_list[2]));
			}
			else if (coconut == 0 && cococonut == 0) {
				a->deposit(*(this->multi_fee_list[3]));
			}
			else {
				a->deposit(*(this->multi_fee_list[2]));
			}
			return -1;
		}
		a->withdraw(amount);
		b->deposit(amount);
		cout << "�۱��� �Ϸ�Ǿ����ϴ�." << endl << "��� ������ �ܰ�� " << setw(10) << a->checkFunds() << "�Դϴ�." << endl;
		return amount;
	}
}

int Multi::cash_transfer(Account* b) {
	if (this->lang_setting == false) {
		cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
		*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
		cout << "The fee has been deposited. Initiate cash transfer." << endl;
		//this->cash_transfer(b);
		cout << "Please insert a 1,000 won bill." << endl;
		int cash1000 = no_error(lang_setting);
		cout << "Please insert a 5,000 won bill." << endl;
		int cash5000 = no_error(lang_setting);
		cout << "Please insert a 10,000 won bill." << endl;
		int cash10000 = no_error(lang_setting);
		cout << "Please insert a 50,000 won bill." << endl;
		int cash50000 = no_error(lang_setting);
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "The transfer has been completed." << endl;
		return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
	}
	else {
		cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
		*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
		cout << "�����ᰡ �ԱݵǾ����ϴ�. ���� �۱��� �����մϴ�." << endl;
		//this->cash_transfer(b);
		cout << "1000������ ������ �ּ���." << endl;
		int cash1000 = no_error(lang_setting);
		cout << "5000������ ������ �ּ���." << endl;
		int cash5000 = no_error(lang_setting);
		cout << "10000������ ������ �ּ���." << endl;
		int cash10000 = no_error(lang_setting);
		cout << "50000������ ������ �ּ���." << endl;
		int cash50000 = no_error(lang_setting);
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "�۱��� �Ϸ�Ǿ����ϴ�." << endl;
		return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
	}
}

Account* Multi::card2account(string card, vector<Bank*> bank_list) {
	int* banknum = new int(-1);
	Account* ac = 0;
	for (int k = 0; k < bank_list.size(); k++) {
		for (int i = 0; i < bank_list[k]->get_account().size(); i++) {
			vector<string> card_list = bank_list[k]->get_account()[i]->getCardNumber();
			for (int j = 0; j < card_list.size(); j++) {
				if (card_list[j] == card) {
					*banknum = k;
					return bank_list[k]->get_account()[i];
					delete banknum;
					break;
				}
			}
		}
	}
	if (*banknum == -1) {
		if (this->lang_setting == true) { cout << "�������� �ʴ� ī���Դϴ�." << endl; }
		else { cout << "Unsupported card." << endl; }
		delete banknum;
		return nullptr;
	}
	delete banknum;
	return ac;
}

Account* Multi::num2account(string num, vector<Bank*> bank_list) {
	int* banknum = new int(-1);
	Account* ac = nullptr;
	for (int k = 0; k < bank_list.size(); k++) {
		for (int i = 0; i < bank_list[k]->get_account().size(); i++) {
			string acc_num = bank_list[k]->get_account()[i]->getAccountNumber();
			if (acc_num == num) {
				*banknum = k;
				ac = bank_list[*banknum]->get_account()[i];
				break;
			}
		}
	}
	//delete banknum;
	return ac;
}

string Multi::getType() {
	return "Multi-bank ATM";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------General Function Definition
void printNow(vector<ATM*>& ATM_list, vector<Bank*>& bank_list) {

	for (int i = 0; i < bank_list.size(); i++) {
		for (int j = 0; j < bank_list[i]->get_account().size(); j++) {
			cout << "Account[" << (bank_list)[i]->get_account()[j]->getUserName() << "] : " << (bank_list)[i]->get_account()[j]->checkFunds() << "/" << (bank_list)[i]->get_account()[j]->getAccountNumber() << "/" << (bank_list)[i]->get_account()[j]->getBankName() << endl;
		}
	}
	for (int i = 0; i < (ATM_list).size(); i++) {
		cout << "ATM " << "[" << i << "] " << "Primary Bank : " << (ATM_list)[i]->getPrimary()->getBankName() << " " << (ATM_list)[i]->getType() << " " << (ATM_list)[i]->getLangType() << endl;
		cout << "Remaing cash : " << 1000 * (ATM_list)[i]->get1000() + 5000 * (ATM_list)[i]->get5000() + 10000 * (ATM_list)[i]->get10000() + 50000 * (ATM_list)[i]->get50000() << " (1000 : " << (ATM_list)[i]->get1000() << ", 5000 : " << (ATM_list)[i]->get5000() << ", 10000 : " << (ATM_list)[i]->get10000() << ", 50000 : " << (ATM_list)[i]->get50000() << ")" << endl;
	}

	cout << endl;
	cout << "Please re-enter here : ";
	return;
}

string Qsearch(vector<ATM*>& ATM_list, vector<Bank*>& bank_list) {
	string str;
	while (true) {
		cin >> str;
		if (str == "Q" || str == "q") {
			printNow(ATM_list, bank_list);
		}
		else {
			return str;
		}
	}
}

int no_error(vector<ATM*>& ATM_list, vector<Bank*>& bank_list, int language_setting) {
	int temp = 0;
	while (true) {

		string abc = "";
		// cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow(ATM_list, bank_list);
			}
			else {
				break;
			}
		}

		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}

		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp >= 0) { return temp; }
			else {
				if (language_setting == 1) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 2) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 1) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
	}
}

int no_error_range(vector<ATM*>& ATM_list, vector<Bank*>& bank_list, int language_setting, int min, int max) {
	int temp = 0;
	while (true) {

		string abc = "";
		// cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow(ATM_list, bank_list);
			}
			else {
				break;
			}
		}

		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}

		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp > min - 1 && temp < max + 1) { return temp; }
			else {
				if (language_setting == 1) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 2) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 1) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
	}
}

void BankMake(vector<ATM*>& ATM_list, vector<Bank*>& bank_list, int language_setting, vector<Bank*>* blist, vector<ATM*>* alist) {

	cout << "==================== < Bank Duplicate Session > ====================" << endl;
	string bank_name; string bank_name_save;

	while (true) {
		int dup = 0;

		if (language_setting == 1) { cout << "Please write bank name : "; }
		if (language_setting == 2) { cout << "������� �Է����ּ���. : "; }

		cin >> bank_name;
		// Qsearch(ATM_list, bank_list, bank_name);

		bank_name_save = bank_name;

		for (int i = 0; i < bank_name.size(); i++) {
			bank_name[i] = tolower(bank_name[i]);
		}

		for (int j = 0; j < bank_list.size(); j++) {

			// string reference = bank_list[j].getBankName();
			string reference = bank_list[j]->getBankName();

			for (int k = 0; k < reference.size(); k++) {
				reference[k] = tolower(reference[k]);
			}
			if (reference == bank_name) {
				if (language_setting == 1) { cout << bank_name << " is already exiested!" << endl; }
				if (language_setting == 2) { cout << bank_name << " ������ �̹� �����մϴ�!" << endl; }
				dup = 1;
			}
		}
		if (dup == 0) {
			// bank_list.push_back(Bank(bank_name_save));
			bank_list.push_back(new Bank(bank_name_save, blist, alist));
			cout << "==================== < Bank Duplicate Session End! > ====================" << endl;
			break;
		}
	}
}

void BankService(vector<ATM*>& ATM_list, vector<Bank*> bank_list, int language_setting) {

	cout << "==================== < Bank Service Session > ====================" << endl;

	if (bank_list.size() == 0) {
		if (language_setting == 1) { cout << "There is no bank. So bank service is not available." << endl; }
		if (language_setting == 2) { cout << "������ ���� ���� ���񽺸� ������ �� �����ϴ�." << endl; }
		return;
	}

	if (language_setting == 1) { cout << "Please choose Bank number that you want to make account for." << endl; }
	if (language_setting == 2) { cout << "���¸� ����� ���� ������ �������ּ���." << endl; }

	for (int i = 0; i < bank_list.size(); i++) {
		cout << "[" << i << "] " << bank_list[i]->getBankName() << " Bank" << endl;
	}
	cout << endl;

	if (language_setting == 1) { cout << "Bank number : "; }
	if (language_setting == 2) { cout << "���� ��ȣ : "; }

	int bank_choose = 0;
	bank_choose = no_error_range(ATM_list, bank_list, language_setting, 0, (int)bank_list.size() - 1);

	if (language_setting == 1) { cout << bank_list[bank_choose]->getBankName() << " bank is selected." << endl; }
	if (language_setting == 2) { cout << bank_list[bank_choose]->getBankName() << " ������ ���õǾ����ϴ�." << endl; }

	if (language_setting == 1) {
		cout << "Please choose number that you want to get service." << endl;
		cout << "[1] Create Account" << endl;
		cout << "[2] Make Card" << endl;
		cout << "[3] Account history" << endl;
		cout << endl;
		cout << "Serive number : ";
	}
	if (language_setting == 2) {
		cout << "�̿��ϰ��� �ϴ� ���񽺸� �������ּ���." << endl;
		cout << "[1] ���� ����" << endl;
		cout << "[2] ī�� ����" << endl;
		cout << "[3] ���� ���" << endl;
		cout << endl;
		cout << "���� ��ȣ : ";
	}

	int service_choose = 0;
	// cin >> service_choose;
	service_choose = no_error_range(ATM_list, bank_list, language_setting, 1, 3);


	if (service_choose == 1) {
		bank_list[bank_choose]->create_account(language_setting);
	}
	if (service_choose == 2) {
		bank_list[bank_choose]->makeCard_session(language_setting);
	}
	if (service_choose == 3) {
		Account* input_account = bank_list[bank_choose]->search_account_number(language_setting);
		if (input_account == NULL) { return; }
		string input_password;
		int a = 3;
		while (true) {

			if (a == 0) {
				if (language_setting == 1) { cout << "You write wrong password 3 times. " << endl; }
				if (language_setting == 2) { cout << "��й�ȣ 3ȸ Ʋ�Ƚ��ϴ�." << endl; }
				cout << "==================== < Account History Session End! > ====================" << endl;
				return;
			}
			if (language_setting == 1) {
				cout << a << " attempts left." << endl;
				cout << "Password : ";
			}
			if (language_setting == 2) {
				cout << a << " ȸ ����." << endl;
				cout << "��й�ȣ : ";
			}

			// password is string!
			a--;
			//cin >> input_password;
			input_password = Qsearch(ATM_list, bank_list);
			//cout << input_password;

			if (input_account->getPassword() == input_password) {
				if (language_setting == 1) { cout << "Correct password." << endl; }
				if (language_setting == 2) { cout << "���� ��й�ȣ." << endl; }
				cout << endl;
				input_account->printHistory();
				cout << "==================== < Account History Session End! > ====================" << endl;
				return;
			}
		}
	}

	cout << "==================== < Bank Service Session End! > ====================" << endl;
}

void ATMMake(vector<ATM*>& ATM_list, vector<Bank*>& bank_list, int* fee_list1[4], int* fee_list2[4], int language_setting, vector<Bank*>* blist, vector<ATM*>* alist) {
	cout << "==================== < ATM Duplicate Session > ====================" << endl;
	//input : primary bank name, serial number, type, language, initial fund
	//constant : 
	if (language_setting == 1) { cout << "Please choose Bank number that you want to make ATM for : " << endl; }
	if (language_setting == 2) { cout << "ATM�� ��ġ�� ������ �����ϼ��� : " << endl; }
	for (int i = 0; i < bank_list.size(); i++) {
		cout << "[" << i << "] " << bank_list[i]->getBankName() << " Bank" << endl;
	}

	int bank_choose = 0;
	// cin >> bank_choose;
	bank_choose = no_error_range(ATM_list, bank_list, language_setting, 0, (int)bank_list.size() - 1);

	if (bank_choose >= bank_list.size()) {
		if (language_setting == 1) { cout << "The corresponding bank does not exist." << endl; }
		if (language_setting == 2) { cout << "�ش��ϴ� ������ �������� �ʽ��ϴ�." << endl; }
		cout << "==================== < ATM Make Session End! > ====================" << endl;
		return;
	}
	if (language_setting == 1) { cout << bank_list[bank_choose]->getBankName() << " bank is selected." << endl; }
	if (language_setting == 2) { cout << bank_list[bank_choose]->getBankName() << " ������ ���õǾ����ϴ�.." << endl; }

	string serial = "";
	for (int i = 0; i < 6 - to_string(ATM_list.size()).size(); i++) {
		serial += "0";
	}
	serial += to_string(ATM_list.size());
	if (language_setting == 1) { cout << "Serial number of ATM will be automatically issued. Serial number of this ATM is " << serial << "." << endl; }
	if (language_setting == 2) { cout << "ATM�� �Ϸù�ȣ�� �ڵ����� �߱޵˴ϴ�. �� ATM�� �Ϸù�ȣ�� " << serial << "�Դϴ�." << endl; }

	if (language_setting == 1) { cout << "Please input ATM type." << endl << "[1] Single Bank ATM" << endl << "[2] Multi Bank ATM" << endl; }
	if (language_setting == 2) { cout << "ATM�� type�� �Է��ϼ���." << endl << "[1] Single Bank ATM" << endl << "[2] Multi Bank ATM" << endl; }

	int type = 0;
	// cin >> type;
	type = no_error_range(ATM_list, bank_list, language_setting, 1, 2);

	if (language_setting == 1) { cout << "Please input ATM language type." << endl << "[1] Unilingual ATM" << endl << "[2] Bilingual ATM" << endl; }
	if (language_setting == 2) { cout << "ATM�� ��� type�� ������ �ּ���." << endl << "[1] Unilingual ATM" << endl << "[2] Bilingual ATM" << endl; }

	int language = 0;
	// cin >> language;
	language = no_error_range(ATM_list, bank_list, language_setting, 1, 2);

	int* fund[4] = { 0, };
	for (int i = 0; i < 4; i++) {
		fund[i] = new int(0);
	}
	if (language_setting == 1) { cout << "Please Enter the Amount of 1000 won bills." << endl; }
	if (language_setting == 2) { cout << "1000������ ���� �Է��� �ּ���." << endl; }
	// cin >> *(fund[0]);
	*(fund[0]) = no_error(ATM_list, bank_list, language_setting);

	if (language_setting == 1) { cout << "Please Enter the Amount of 5000 won bills." << endl; }
	if (language_setting == 2) { cout << "5000������ ���� �Է��� �ּ���." << endl; }
	// cin >> *(fund[1]);
	*(fund[1]) = no_error(ATM_list, bank_list, language_setting);

	if (language_setting == 1) { cout << "Please Enter the Amount of 10000 won bills." << endl; }
	if (language_setting == 2) { cout << "10000������ ���� �Է��� �ּ���." << endl; }
	// cin >> *(fund[2]);
	*(fund[2]) = no_error(ATM_list, bank_list, language_setting);

	if (language_setting == 1) { cout << "Please Enter the Amount of 50000 won bills." << endl; }
	if (language_setting == 2) { cout << "50000������ ���� �Է��� �ּ���." << endl; }
	// cin >> *(fund[3]);
	*(fund[3]) = no_error(ATM_list, bank_list, language_setting);

	switch (type) {
	case 1:
		//Single(bank_list[bank_choose].getBankName(), serial, language, fund, fee_list1);
		ATM_list.push_back(new Single(bank_list[bank_choose], serial, language, fund, fee_list1, blist, alist));
		cout << "==================== < ATM Duplicate Session End! > ====================" << endl;
		break;
	case 2:
		//Multi(bank_list[bank_choose].getBankName(), serial, language, fund, fee_list1, fee_list2);
		ATM_list.push_back(new Multi(bank_list[bank_choose], serial, language, fund, fee_list1, fee_list2, blist, alist));
		cout << "==================== < ATM Duplicate Session End! > ====================" << endl;
		break;
	default:
		break;
	}

	return;
}

void ATMService(vector<ATM*> ATM_list, vector<Bank*> bank_list, int language_setting) {
	cout << "==================== < ATM Service Session > ====================" << endl;

	if (ATM_list.size() == 0) {
		if (language_setting == 1) { cout << "There is no ATM existed." << endl; }
		if (language_setting == 2) { cout << "�����ϴ� ATM�� �����ϴ�." << endl; }
		return;
	}

	if (language_setting == 1) { cout << "Please choose ATM number that you want to use for." << endl; }
	if (language_setting == 2) { cout << "�ŷ��� �����ϰ� ���� ATM�� �������ּ���." << endl; }

	for (int i = 0; i < ATM_list.size(); i++) {
		cout << "[" << i << "] ATM " << ATM_list[i]->getSerial() << " [Bank " << ATM_list[i]->getPrimary()->getBankName() << "/" << ATM_list[i]->getType() << "/" << ATM_list[i]->getLangType() << "]" << endl;
	}
	cout << endl;
	if (language_setting == 1) { cout << "ATM number : "; }
	if (language_setting == 2) { cout << "ATM ��ȣ : "; }

	int ATM_choose = 0;
	// cin >> ATM_choose;
	ATM_choose = no_error_range(ATM_list, bank_list, language_setting, 0, (int)ATM_list.size() - 1);

	//if (ATM_choose >= ATM_list.size()) {
	//	if (language_setting == 1) { cout << "The corresponding ATM does not exist." << endl; }
	//	if (language_setting == 2) { cout << "�ش��ϴ� ATM�� �������� �ʽ��ϴ�." << endl; }
	//	cout << "==================== < ATM Service Session End! > ====================" << endl;
	//	return;
	//}

	if (language_setting == 1) { cout << ATM_list[ATM_choose]->getSerial() << " ATM is selected." << endl << "Connecting to ATM..." << endl; }
	if (language_setting == 2) { cout << ATM_list[ATM_choose]->getSerial() << " ATM�� ���õǾ����ϴ�." << endl << "ATM�� �����մϴ�..." << endl; }

	ATM_list[ATM_choose]->session(bank_list);
	cout << "==================== < ATM Service Session End! > ====================" << endl;
	return;
}

Account* BankSearch(vector<ATM*>& ATM_list, vector<Bank*> bank_list, int language_setting) {
	cout << "==================== < Bank Search Session > ====================" << endl;
	if (language_setting == 1) {
		cout << "Please choose searach service number that you want." << endl;
		cout << "[1] By Account Number" << endl;
		cout << "[2] By Card Number" << endl;
		cout << endl;
		cout << "Search service number : ";
	}
	if (language_setting == 2) {
		cout << "���ϴ� ��ȸ ������ ��ȣ�� ����ּ���.." << endl;
		cout << "[1] ���� ��ȣ��" << endl;
		cout << "[2] ī�� ��ȣ��" << endl;
		cout << endl;
		cout << "Search service number : ";
	}

	int search_choose = 0;
	// cin >> search_choose;
	search_choose = no_error_range(ATM_list, bank_list, language_setting, 1, 2);

	while (true) {
		if (search_choose == 1) {
			string account_number;
			if (language_setting == 1) { cout << "Please write your account number : "; }
			if (language_setting == 2) { cout << "���¹�ȣ�� �Է����ּ���. : "; }

			//cin >> account_number;
			account_number = Qsearch(ATM_list, bank_list);

			for (int i = 0; i < bank_list.size(); i++) {
				if (bank_list[i]->search_account_number_BankSearch(account_number, language_setting) != NULL) {
					cout << "==================== < Bank Search Session End! > ====================" << endl;
					return bank_list[i]->search_account_number_BankSearch(account_number, language_setting);
				}
			}
			if (language_setting == 1) { cout << "Account is not found." << endl; }
			if (language_setting == 2) { cout << "���¸� ã�� �� �����ϴ�." << endl; }
		}
		if (search_choose == 2) {
			string card_number;
			if (language_setting == 1) { cout << "Please write your card number : "; }
			if (language_setting == 2) { cout << "ī�� ��ȣ�� �Է����ּ���. : "; }

			//cin >> card_number;
			card_number = Qsearch(ATM_list, bank_list);

			for (int i = 0; i < bank_list.size(); i++) {
				if (bank_list[i]->search_account_card_BankSearch(card_number, language_setting) != NULL) {
					cout << "==================== < Bank Search Session End! > ====================" << endl;
					return bank_list[i]->search_account_card_BankSearch(card_number, language_setting);
				}
			}
			if (language_setting == 1) { cout << "Account is not found." << endl; }
			if (language_setting == 2) { cout << "���¸� ã�� �� �����ϴ�." << endl; }
		}
	}
	cout << "==================== < Bank Search Session End! > ====================" << endl;
}

void feeConfig(vector<ATM*>& ATM_list, vector<Bank*> bank_list, int* fee_list1[4], int* fee_list2[4], int language_setting) {
	if (language_setting == 1) { cout << "Please Enter the deposit fee for primary bank." << endl; }
	if (language_setting == 2) { cout << "Primary bank ���¿����� �Ա� �����Ḧ �Է��� �ּ���." << endl; }
	// cin >> *(fee_list1[0]);
	*(fee_list1[0]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the withdrawal fee for primary bank." << endl; }
	if (language_setting == 2) { cout << "Primary bank ���¿����� ��� �����Ḧ �Է��� �ּ���." << endl; }
	// cin >> *(fee_list1[1]);
	*(fee_list1[1]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the account transfer fee between primary banks." << endl; }
	if (language_setting == 2) { cout << "Primary bank ���³����� �۱� �����Ḧ �Է��� �ּ���." << endl; }
	// cin >> *(fee_list1[2]);
	*(fee_list1[2]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the cash transfer fee." << endl; }
	if (language_setting == 2) { cout << "���� �۱� �����Ḧ �Է��� �ּ���." << endl; }
	// cin >> *(fee_list1[3]);
	*(fee_list1[3]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the deposit fee for non-primary bank." << endl; }
	if (language_setting == 2) { cout << "Non-Primary bank ���¿����� �Ա� �����Ḧ �Է��� �ּ���." << endl; }
	// cin >> *(fee_list2[0]);
	*(fee_list2[0]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the withdrawal fee for non-primary bank." << endl; }
	if (language_setting == 2) { cout << "Non-primary bank ���¿����� ��� �����Ḧ �Է��� �ּ���." << endl; }
	// cin >> *(fee_list2[1]);
	*(fee_list2[1]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the account transfer fee between primary bank and non-primary banks." << endl; }
	if (language_setting == 2) { cout << "Primary bank ���¿� non-primary bank ���� ������ �۱� �����Ḧ �Է��� �ּ���." << endl; }
	// cin >> *(fee_list2[2]);
	*(fee_list2[2]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the account transfer fee between non-primary banks." << endl; }
	if (language_setting == 2) { cout << "Non-primary bank ���³����� �۱� �����Ḧ �Է��� �ּ���." << endl; }
	// cin >> *(fee_list2[3]);
	*(fee_list2[3]) = no_error(ATM_list, bank_list, language_setting);
	return;
}

int LanguageService(vector<ATM*>& ATM_list, vector<Bank*> bank_list, int language_setting) {
	cout << "===========================<Language Change Session>===========================" << endl;
	if (language_setting == 1) {
		cout << "Select language" << endl;
		cout << "[1] English" << endl;
		cout << "[2] �ѱ���" << endl;
		cout << endl;
		cout << "Please Enter the Number: ";
	}
	if (language_setting == 2) {
		cout << "����" << endl;
		cout << "[1] English" << endl;
		cout << "[2] �ѱ���" << endl;
		cout << endl;
		cout << "��ȣ �Է� : ";
	}

	int setting = 0;
	// cin >> setting;
	setting = no_error_range(ATM_list, bank_list, language_setting, 1, 2);
	language_setting = setting;

	return language_setting;
}

void Admin(vector<ATM*> ATM_list, vector<Bank*> bank_list, int language_setting) {
	string admin_password = "admin";

	// \t
	if (language_setting == 1) {
		cout << "This is Admin session." << endl;
		cout << endl;
		cout << "Please Enter the password : ";
	}
	if (language_setting == 2) {
		cout << "������ �����Դϴ�." << endl;
		cout << endl;
		cout << "��й�ȣ�� �Է����ּ��� : ";
	}
	string input_password;

	int a = 0;
	for (int i = 0; i < 3; i++) {

		//cin >> input_password;
		input_password = Qsearch(ATM_list, bank_list);

		if (admin_password == input_password) {
			if (language_setting == 1) { cout << "Admin confirmed." << endl; }
			if (language_setting == 2) { cout << "������ Ȯ�� �Ϸ�." << endl; }
			a = 1;
			break;
		}
		if (a == 0) {
			if (language_setting == 1) { cout << 2 - i << " attempt left." << endl; }
			if (language_setting == 2) { cout << 2 - i << " ȸ ����." << endl; }
		}
	}

	if (a == 0) {
		if (language_setting == 1) { cout << "You write wrong password 3 times." << endl; }
		if (language_setting == 2) { cout << "�߸��� ��й�ȣ�� 3ȸ �Է��ϼ̽��ϴ�." << endl; }
		return;
	}

	if (a == 1) {
		if (language_setting == 1) {
			cout << "Please Select the task you want to do." << endl;
			cout << "[1] Bank & Account Info" << endl;
			cout << "[2] ATM Info" << endl;
			cout << endl;
			cout << "Please Enter the Number : ";
		}
		if (language_setting == 2) {
			cout << "�����ϰ��� �ϴ� ������ �����ϼ���." << endl;
			cout << "[1] ���� & ���� ����" << endl;
			cout << "[2] ATM ����" << endl;
			cout << endl;
			cout << "���ڸ� �Է����ּ��� : ";
		}
	}

	int choice = 0;
	// cin >> choice;
	choice = no_error_range(ATM_list, bank_list, language_setting, 1, 2);

	if (choice == 1) {
		if (language_setting == 1) {
			cout << "==================== < Bank & Account Info > ====================" << endl;
			for (int i = 0; i < bank_list.size(); i++) {
				cout << endl;
				cout << "Bank : " << bank_list[i]->getBankName() << endl;
				cout << endl;

				for (int j = 0; j < bank_list[i]->get_account().size(); j++) {
					cout << "Name : " << bank_list[i]->get_account()[j]->getUserName() << " ID : " << bank_list[i]->get_account()[j]->getAccountNumber() << " Password : " << bank_list[i]->get_account()[j]->getPassword() << " Available Fund : " << bank_list[i]->get_account()[j]->getAvailableFund() << endl;
					cout << "Card : ";
					for (int k = 0; k < bank_list[i]->get_account()[j]->getCardNumber().size(); k++) {
						cout << bank_list[i]->get_account()[j]->getCardNumber()[k] << "\t";
					}
					cout << endl;
				}
				cout << "========================================" << endl;
			}
			cout << "==================== < Bank & Account Info End!> ====================" << endl;
		}
		if (language_setting == 2) {
			cout << "==================== < Bank & Account Info > ====================" << endl;
			for (int i = 0; i < bank_list.size(); i++) {
				cout << endl;
				cout << "���� : " << bank_list[i]->getBankName() << endl;
				cout << endl;

				for (int j = 0; j < bank_list[i]->get_account().size(); j++) {
					cout << "������ : " << bank_list[i]->get_account()[j]->getUserName() << " ���¹�ȣ : " << bank_list[i]->get_account()[j]->getAccountNumber() << " ��й�ȣ : " << bank_list[i]->get_account()[j]->getPassword() << " �����ܰ� : " << bank_list[i]->get_account()[j]->getAvailableFund() << endl;
					cout << "ī���ȣ : ";
					for (int k = 0; k < bank_list[i]->get_account()[j]->getCardNumber().size(); k++) {
						cout << bank_list[i]->get_account()[j]->getCardNumber()[k] << "\t";
					}
					cout << endl;
				}
				cout << "========================================" << endl;
			}
			cout << "==================== < Bank & Account Info End!> ====================" << endl;
		}
	}

	if (choice == 2) {
		if (language_setting == 1) {
			cout << "==================== < ATM Info > ====================" << endl;
			for (int i = 0; i < ATM_list.size(); i++) {
				cout << endl;
				cout << "ATM " << "[" << i << "] " << "Primary Bank : " << ATM_list[i]->getPrimary()->getBankName() << " " << ATM_list[i]->getType() << " " << ATM_list[i]->getLangType() << endl;
				cout << "Remaing cash : " << 1000 * ATM_list[i]->get1000() + 5000 * ATM_list[i]->get5000() + 10000 * ATM_list[i]->get10000() + 50000 * ATM_list[i]->get50000() << " (1000 : " << ATM_list[i]->get1000() << ", 5000 : " << ATM_list[i]->get5000() << ", 10000 : " << ATM_list[i]->get10000() << ", 50000 : " << ATM_list[i]->get50000() << ")" << endl;
			}
			cout << "==================== < ATM Info End!> ====================" << endl;
		}
		if (language_setting == 2) {
			cout << "==================== < ATM Info > ====================" << endl;
			for (int i = 0; i < ATM_list.size(); i++) {
				cout << endl;
				cout << "ATM " << "[" << i << "] " << "Primary Bank : " << ATM_list[i]->getPrimary()->getBankName() << " " << ATM_list[i]->getType() << " " << ATM_list[i]->getLangType() << endl;
				cout << "�ܿ����� : " << 1000 * ATM_list[i]->get1000() + 5000 * ATM_list[i]->get5000() + 10000 * ATM_list[i]->get10000() + 50000 * ATM_list[i]->get50000() << " (1000 : " << ATM_list[i]->get1000() << ", 5000 : " << ATM_list[i]->get5000() << ", 10000 : " << ATM_list[i]->get10000() << ", 50000 : " << ATM_list[i]->get50000() << ")" << endl;
			}
			cout << "==================== < ATM Info End!> ====================" << endl;
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------main Function Call
int main() {
	vector<Bank*> bank_list;
	vector<ATM*> ATM_list;
	vector<Bank*>* blist = &bank_list;
	vector<ATM*>* alist = &ATM_list;

	int* fee1[4] = { 0, };
	int* fee2[4] = { 0, };
	for (int i = 0; i < 4; i++) {
		fee1[i] = new int(0);
	}
	for (int i = 0; i < 4; i++) {
		fee2[i] = new int(0);
	}

	bool onSession = true;
	int language_setting = 1; // 1: English, 2: Korean

	while (onSession) {
		cout << "===========================<Welcome to Bank System Service>===========================" << endl;
		if (language_setting == 1) {
			cout << "Please Select the task you want to do." << endl;
			cout << "[1] Make Bank" << endl;
			cout << "[2] Banking Service (Make Account or Make Card)" << endl;
			cout << "[3] Make ATM" << endl;
			cout << "[4] ATM Service (Deposit, Withdraw, etc...)" << endl;
			cout << "[5] Change Language Setting" << endl;
			cout << "[6] Shut Down the Bank System Service" << endl;
			cout << "[7] Fee Configuration" << endl;
			cout << "[8] Admin" << endl;
			cout << endl;

			cout << "Please Enter the Number : ";
		}
		if (language_setting == 2) {
			cout << "�����ϰ��� �ϴ� ������ �����ϼ���." << endl;
			cout << "[1] ���� �����" << endl;
			cout << "[2] ���� ���� (���� �� ī�� ����)" << endl;
			cout << "[3] ATM �����" << endl;
			cout << "[4] ATM ���� (�Ա�, ��� ��...)" << endl;
			cout << "[5] ��� ���� ����" << endl;
			cout << "[6] Bank System Service ����" << endl;
			cout << "[7] ������ ����" << endl;
			cout << "[8] ������" << endl;
			cout << endl;
			cout << "���ڸ� �Է����ּ��� : ";
		}

		int session_chice = 0;
		session_chice = no_error_range(ATM_list, bank_list, language_setting, 1, 8);

		switch (session_chice) {
		case 1:
			BankMake(ATM_list, bank_list, language_setting, blist, alist);
			break;
		case 2:
			BankService(ATM_list, bank_list, language_setting);
			break;
		case 3:
			ATMMake(ATM_list, bank_list, fee1, fee2, language_setting, blist, alist);
			break;
		case 4:
			ATMService(ATM_list, bank_list, language_setting);
			break;
		case 5:
			language_setting = LanguageService(ATM_list, bank_list, language_setting);
			break;
		case 6:
			onSession = false;
			break;
		case 7:
			feeConfig(ATM_list, bank_list, fee1, fee2, language_setting);
			break;
		case 8:
			Admin(ATM_list, bank_list, language_setting);
		}
		cout << "===========================<End System Session>===========================" << endl;
	}

	cout << "===========================<End System>===========================" << endl;

	for (int i = 0; i < 4; i++) {
		delete fee1[i];
	}
	for (int i = 0; i < 4; i++) {
		delete fee2[i];
	}
	for (int i = 0; i < (int) bank_list.size(); i++) {
		delete bank_list[i];
	}
	for (int i = 0; i < (int)ATM_list.size(); i++) {
		delete ATM_list[i];
	}

	return 0;
}