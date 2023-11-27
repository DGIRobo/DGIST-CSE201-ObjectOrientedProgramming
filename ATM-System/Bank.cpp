#include "Bank.h"

int Bank::static_bank_counter = 0;

Bank::Bank(string name) {
	this->bank_name = name;
	static_bank_counter += 1;
	this->bank_id = static_bank_counter;

	cout << this->getBankName() << "������ �����Ǿ����ϴ�." << endl;
}

Bank::~Bank() {

	cout << this->bank_name << "������ ���ŵǾ����ϴ�." << endl;

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
//	cout << "���°� ��ȸ�Ǿ����ϴ�." << endl;
//
//	string input_password;
//	cout << "��й�ȣ�� �Է����ּ���." << endl;
//	cin >> input_password;
//
//	if (a->getPassword() == input_password) {
//		cout << "���� : " << a->getBankName() << endl;
//		cout << "������ : " << a->getUserName() << endl;
//		cout << "���¹�ȣ : " << a->getAccountNumber() << endl;
//		cout << "��й�ȣ : " << a->getPassword() << endl;
//	}
//	else {
//		cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
//	}
//}
	
Account* Bank::create_account() {

	cout << "==================== < Account Create Session > ====================" << endl;

	string input_user_name;
	string account_number;
	string input_password;
	int initial_fund;
	cout << this->getBankName() << "�����Դϴ�. ���¸� �����ϱ� ���� ���ϴ� ����, ��й�ȣ�� �Է����ּ���." << endl;

	cout << "���� : ";		cin >> input_user_name;
	cout << "��й�ȣ : ";	cin >> input_password;

	cout << "�ʱ⿹���� �Է����ּ���." << endl;
	cin >> initial_fund;

	Account* new_account = new Account(this, input_user_name, input_password, initial_fund);
	accounts.push_back(new_account);

	cout << "���°� �����Ǿ����ϴ�." << endl;
	cout << "���� : " << new_account->getBankName() << endl;
	cout << "������ : " << new_account->getUserName() << endl;
	cout << "���¹�ȣ : " << new_account->getAccountNumber() << endl;
	cout << "��й�ȣ : " << new_account->getPassword() << endl;

	cout << "==================== < Account Create Session End! > ====================" << endl;

	return new_account;
}

Account* Bank::search_account_number() {
	vector<Account*> accounts_list = get_account();

	cout << this->getBankName() << "�����Դϴ�. ���¹�ȣ�� �Է����ּ���." << endl;

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

	cout << this->getBankName() << "�����Դϴ�. ī�带 �Է����ּ���." << endl;

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