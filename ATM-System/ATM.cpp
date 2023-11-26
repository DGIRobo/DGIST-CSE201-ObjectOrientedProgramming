#include "ATM.h"

void ATM::languageChange() {
	cout << "Please chioce the language setting." << endl;
	cout << "1. Korean" << endl;
	cout << "2. English" << endl;

	int input_language_setting;
	cin >> input_language_setting;

	if (input_language_setting == 1) {
		this->language_setting = "Korean";
	}
	if (input_language_setting == 2) {
		this->language_setting = "English";
	}
}


ATM::ATM(string input_primary_bank, int input_serial_number, string input_type, string input_lanuage_available, int* initial_fund[]) {
	this->primary_bank = input_primary_bank;
	this->serial_number = input_serial_number;
	this->type = input_type;
	this->language_available = input_lanuage_available;

	for (int i = 0; i < 4; ++i) {
		this->cash_storage[i] = initial_fund[i];
	}
}

ATM::~ATM() {
	this->primary_bank = "";
	this->serial_number = 0;
	this->type = "";
	this->language_available = "";

	for (int i = 0; i < 4; ++i) {
		this->cash_storage[i] = 0;
	}
}



void ATM::session() {

	if (this->language_setting == "Korean") {

	}
	if (this->language_setting == "English") {

	}

}

void ATM::add_cash(int cash1000, int cash5000, int cash10000, int cash50000) {
	this->cash_storage[0] += cash1000;
	this->cash_storage[1] += cash5000;
	this->cash_storage[2] += cash10000;
	this->cash_storage[3] += cash50000;
}

void ATM::deposit(Account a) {
	if (this->language_setting == "Korean") {
		cout << "�Ա� ������ ������ �ּ���" << endl;
		cout << "[1] ����" << "   " << "[2] ��ǥ" << endl;
	}
	if (this->language_setting == "English") {
		cout << "Please select deposit method" << endl;
		cout << "[1] cash" << "   " << "[2] check" << endl;
	}
	int deposit_method;
	cin >> deposit_method;
	if (deposit_method == 1) {
		if (this->language_setting == "Korean") {
			cout << "�� ��Ⱑ ó���� �� �ִ� ������ �ż��� 50������Դϴ�." << endl;
		}
		if (this->language_setting == "English") {
			cout << "This device can process up to 50 cashes." << endl;
		}
		if (this->language_setting == "Korean") {
			cout << "1000������ ������ �ּ���." << endl;
		}
		if (this->language_setting == "English") {
			cout << "Please input 1000 won bills." << endl;
		}
		int cash1000;
		cin >> cash1000;
		if (this->language_setting == "Korean") {
			cout << "5000������ ������ �ּ���." << endl;
		}
		if (this->language_setting == "English") {
			cout << "Please input 5000 won bills." << endl;
		}
		int cash5000;
		cin >> cash5000;
		if (this->language_setting == "Korean") {
			cout << "10000������ ������ �ּ���." << endl;
		}
		if (this->language_setting == "English") {
			cout << "Please input 10000 won bills." << endl;
		}
		int cash10000;
		cin >> cash10000;
		if (this->language_setting == "Korean") {
			cout << "50000������ ������ �ּ���." << endl;
		}
		if (this->language_setting == "English") {
			cout << "Please input 50000 won bills." << endl;
		}
		int cash50000;
		cin >> cash50000;
		if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
			if (this->language_setting == "Korean") {
				cout << "����� ó�� �Ѱ踦 �ʰ��Ͽ����ϴ�." << endl;
			}
			if (this->language_setting == "English") {
				cout << "The device's processing limit has been exceeded." << endl;
			}
			return;
		}
		add_cash(cash1000, cash5000, cash10000, cash50000);
		a.deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		return;
	}
	else if (deposit_method == 2) {
		if (this->language_setting == "Korean") {
			cout << "�� ��Ⱑ ó���� �� �ִ� ��ǥ�� �ż��� 50������Դϴ�. ��ǥ�� ������ �ּ���." << endl << "�ùٸ��� ���� ��ǥ�� �Է��ϸ� ������ �ߴܵ˴ϴ�." << endl;
		}
		if (this->language_setting == "English") {
			cout << "This device can process up to 50 checks. Please insert checks." << endl << "If you enter an incorrect check, the insertion will be ended." << endl;
		}
		int checks[50];
		for (int i = 0; i <= 50; i++) {
			cin >> checks[i];
			if (checks[i] < 100000) {
				checks[i] = 0;
				break;
			}
		}
		int check_sum;
		for (int i = 0; i <= 50; i++) {
			if (checks[i] >= 100000) {
				check_sum += checks[i];
			}
			else break;
		}
		a.deposit(check_sum);
		return;
	}
	else {
		if (this->language_setting == "Korean") {
			cout << "������ �߻��߽��ϴ�. �Ա��� �ߴ��մϴ�." << endl;
		}
		if (this->language_setting == "English") {
			cout << "Error detected. Deposit will be stopped." << endl;
		}
		return;
	}
}