#include "Bank.h"

int Bank::static_bank_counter = 0;

Bank::Bank(string name) {
	this->bank_name = name;
	static_bank_counter += 1;
	this->bank_id = static_bank_counter;

	cout << this->getBankName() << "은행이 생성되었습니다." << endl;
}

Bank::~Bank() {

	cout << this->bank_name << "은행이 제거되었습니다." << endl;

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
	
Account* Bank::create_account() {

	cout << "==================== < Account Create Session > ====================" << endl;

	string input_user_name;
	string account_number;
	string input_password;
	int initial_fund;
	
	cout << this->getBankName() << "은행입니다. 계좌 개설을 위해 이름과 비밀번호, 초기자금을 입력해주세요." << endl;

	cout << "이름 : ";		cin >> input_user_name;
	cout << "비밀번호 : ";	cin >> input_password;

	cout << "초기자금을 입력해주세요." << endl;
	cin >> initial_fund;

	Account* new_account = new Account(this, input_user_name, input_password, initial_fund);
	accounts.push_back(new_account);

	cout << "계좌 개설되었습니다." << endl;
	cout << "은행 : " << new_account->getBankName() << endl;
	cout << "예금주 : " << new_account->getUserName() << endl;
	cout << "계좌번호 : " << new_account->getAccountNumber() << endl;
	cout << "비밀번호 : " << new_account->getPassword() << endl;

	cout << "==================== < Account Create Session End! > ====================" << endl;

	return new_account;
}

Account* Bank::search_account_number() {
	vector<Account*> accounts_list = get_account();

	cout << this->getBankName() << "은행입니다. 계좌번호를 입력해주세요." << endl;

	string input_account_number;
	cin >> input_account_number;

	for (int i = 0; i < accounts_list.size();i++){
		
		if (accounts_list[i]->getAccountNumber() == input_account_number) {
	
			return accounts_list[i];
			
		}
	}
}

Account* Bank::search_account_card() {
	vector<Account*> accounts_list = get_account();

	cout << this->getBankName() << "은행입니다. 카드번호를 입력해주세요." << endl;

	string input_card_number;
	cin >> input_card_number;

	for (int i = 0; i < accounts_list.size(); i++) {
		vector<string> card_list = accounts_list[i]->getCardNumber();

		for (int j = 0; j < card_list.size(); j++) {
			if (card_list[j] == input_card_number) {
				return accounts_list[i];
			}
		}
	}
}


vector<Account*> Bank::get_account() {
	return accounts;
}