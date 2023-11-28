#include "Bank.h"

int Bank::static_bank_counter = 0;

Bank::Bank(string name) {
	this->bank_name = name;
	static_bank_counter += 1;
	this->bank_id = static_bank_counter;

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

//Account* Bank::open_account(Account* a) {
//
//	cout << "계좌가 조회되었습니다." << endl;
//
//	string input_password;
//	cout << "비밀번호를 입력해주세요." << endl;
//	cin >> input_password;
//
//	if (a->getPassword() == input_password) {
//		cout << "은행 : " << a->getBankName() << endl;
//		cout << "예금주 : " << a->getUserName() << endl;
//		cout << "계좌번호 : " << a->getAccountNumber() << endl;
//		cout << "비밀번호 : " << a->getPassword() << endl;
//	}
//	else {
//		cout << "비밀번호가 틀렸습니다." << endl;
//	}
//}
// account 주소를 없을때 만들 수있는 bank용 makeCard;

void Bank::makeCard_session() {
	cout << "==================== < Card Create Session > ====================" << endl;

	Account* account = search_account_number();

	string now_created_card_number;
	now_created_card_number = account->makeCard();

	cout << "Card is created." << endl;
	cout << "Card Number : " << now_created_card_number << endl;

	cout << "This is card number list that connected to your account." << endl;
	vector <string > card_list = account->getCardNumber();
	for (int i = 0; i < card_list.size(); i++) {
		cout << card_list[i] << endl;
	}
	cout << "==================== < Card Create Session End! > ====================" << endl;
}

// Account*
void Bank::create_account() {
	cout << "==================== < Account Create Session > ====================" << endl;
	string input_user_name;
	string account_number;
	string input_password;
	int initial_fund;

	cout << this->getBankName() << "Bank. To create account. please write name, password and initial fund." << endl;

	cout << "Name : ";			cin >> input_user_name;
	cout << "Password : ";		cin >> input_password;
	cout << "Initial fund : ";	cin >> initial_fund;

	Account* new_account = new Account(this, input_user_name, input_password, initial_fund);
	accounts.push_back(new_account);

	cout << "Account is created." << endl;
	cout << "Bank : " << new_account->getBankName() << endl;
	cout << "Owner : " << new_account->getUserName() << endl;
	cout << "Account number : " << new_account->getAccountNumber() << endl;
	cout << "Password : " << new_account->getPassword() << endl;

	string agreement;
	cout << "Do you want to make card? [Agree Y / Disagree N] : "; 	cin >> agreement;

	for (int i = 0; i < agreement.size(); i++) {
		agreement[i] = tolower(agreement[i]);
	}

	if (agreement == "y") {
		cout << "==================== < Card Create Session > ====================" << endl;
		string now_created_card_number;
		now_created_card_number = new_account->makeCard();
		cout << "Card is created." << endl;
		cout << "Card number : " << now_created_card_number << endl;

		cout << "This is card number list that connected to your account." << endl;

		vector <string> card_list = new_account->getCardNumber();
		for (int i = 0; i < card_list.size(); i++) {
			cout << card_list[i] << endl;
		}

		cout << "==================== < Card Create Session End! > ====================" << endl;
	}
	cout << "==================== < Account Create Session End! > ====================" << endl;
	//return new_account;
}

// Account*
Account* Bank::search_account_number() {

	cout << "==================== < Account Number Search Session > ====================" << endl;

	vector<Account*> accounts_list = get_account();

	cout << this->getBankName() << " Bank. Please write account number." << endl;

	string input_account_number;
	cout << "Account number : ";	cin >> input_account_number;

	for (int i = 0; i < accounts_list.size(); i++) {

		if (accounts_list[i]->getAccountNumber() == input_account_number) {
			cout << this->getBankName() << " Bank find your account." << endl;

			cout << "Bank : " << accounts_list[i]->getBankName() << endl;
			cout << "Owner : " << accounts_list[i]->getUserName() << endl;
			cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
			cout << "==================== < Account Number Search Session End! > ====================" << endl;
			return accounts_list[i];
		}
	}
	cout << this->getBankName() << " Bank cannot find your account." << endl;
	cout << "==================== < Account Number Search Session End! > ====================" << endl;
	return NULL;
}

Account* Bank::search_account_number_BankSearch(string input_account) {
	vector<Account*> accounts_list = get_account();
	string input_account_number = input_account;

	for (int i = 0; i < accounts_list.size(); i++) {

		if (accounts_list[i]->getAccountNumber() == input_account_number) {
			cout << this->getBankName() << " Bank find your account." << endl;
			cout << "Bank : " << accounts_list[i]->getBankName() << endl;
			cout << "Owner : " << accounts_list[i]->getUserName() << endl;
			cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
			return accounts_list[i];
		}
	}
	// cout << this->getBankName() << "Bank cannot find your account." << endl;
	return NULL;
}

// Account*
Account* Bank::search_account_card() {

	cout << "==================== < Account Card Search Session > ====================" << endl;

	vector<Account*> accounts_list = get_account();

	cout << this->getBankName() << " Bank. Please write card number." << endl;

	string input_card_number;
	cout << "Card number : ";	cin >> input_card_number;

	for (int i = 0; i < accounts_list.size(); i++) {
		vector<string> card_list = accounts_list[i]->getCardNumber();

		for (int j = 0; j < card_list.size(); j++) {
			if (card_list[j] == input_card_number) {
				cout << this->getBankName() << " Bank find your account." << endl;

				cout << "Bank : " << accounts_list[i]->getBankName() << endl;
				cout << "Owner : " << accounts_list[i]->getUserName() << endl;
				cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
				cout << "==================== < Account Card Search Session End! > ====================" << endl;
				return accounts_list[i];
			}
		}
	}
	cout << this->getBankName() << " Bank cannot find your account." << endl;
	cout << "==================== < Account Card Search Session End! > ====================" << endl;
	return NULL;
}

Account* Bank::search_account_card_BankSearch(string input_card) {

	vector<Account*> accounts_list = get_account();

	string input_card_number = input_card;

	for (int i = 0; i < accounts_list.size(); i++) {
		vector<string> card_list = accounts_list[i]->getCardNumber();

		for (int j = 0; j < card_list.size(); j++) {
			if (card_list[j] == input_card_number) {
				cout << this->getBankName() << " Bank find your account." << endl;
				cout << "Bank : " << accounts_list[i]->getBankName() << endl;
				cout << "Owner : " << accounts_list[i]->getUserName() << endl;
				cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
				return accounts_list[i];
			}
		}
	}
	// cout << this->getBankName() << "Bank cannot find your account." << endl;
	return NULL;
}

vector<Account*> Bank::get_account() {
	return accounts;
}