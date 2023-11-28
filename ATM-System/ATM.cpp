#include "ATM.h"

void ATM::languageChange() {
	if (language_available == 1) {
		cout << "unilingual ATM cannot change language!" << endl;
		return;
	}
	cout << "Please choose the language setting." << endl;
	cout << "[1] English" << endl;
	cout << "[2] Korean" << endl;

	int input_language_setting;
	while (true) {
		cin >> input_language_setting;
		if (input_language_setting == 1 or input_language_setting == 2) {
			break;
		}
		else {
			cout << "Wrong choice! Please choose appropriate choice."  << endl;
		}
	}

	if (input_language_setting == 2) {
		this->language_setting = "Korean";
	}
	if (input_language_setting == 1) {
		this->language_setting = "English";
	}
	return;
}


ATM::ATM(Bank* input_primary_bank, int input_serial_number, int input_type, int input_lanuage_available, int* initial_fund[]) {
	this->primary_bank = input_primary_bank;
	this->serial_number = input_serial_number;
	this->type = input_type;
	this->language_available = input_lanuage_available;

	for (int i = 0; i < 4; ++i) {
		this->cash_storage[i] = initial_fund[i];
	}
}

ATM::~ATM() {
	this->primary_bank = nullptr;
	this->serial_number = 0;
	this->type = 0;
	this->language_available = 0;

	for (int i = 0; i < 4; ++i) {
		this->cash_storage[i] = 0;
	}
}

int ATM::transaction(Account* a) {
	cout << this->getSerial() << "�� ATM�� �����ϼ̽��ϴ�. ���� �۾��� ���͵帱���?" << endl;
	cout << "[1] �Ա�" << endl << "[2] ���" << endl << "[3] ���� �۱�" << endl << "[4] ���� �۱�" << endl << "[5] ��� ����" << endl;
	int selection = 1;
	switch (selection) {
	case 1:
		deposit(a);
		break;
	case 2:
		withdraw(a);
		break;
	case 3:
		//account_transfer(a, b);
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case -1:
		return -1;
	}
	return 0;
}

void ATM::add_cash(int cash1000, int cash5000, int cash10000, int cash50000) {
	this->cash_storage[0] += cash1000;
	this->cash_storage[1] += cash5000;
	this->cash_storage[2] += cash10000;
	this->cash_storage[3] += cash50000;
}

bool ATM::user_authorization(Account* a) {
	//ī�� �Է�
	
	//ī�� ��ȿ�� �˻�

	//��й�ȣ �Է�

	//��й�ȣ �˻�

	//3�� ���� Ʋ���� ���� �ߴܵǰ�
	cout << "��й�ȣ�� 3ȸ Ʋ����, �ŷ��� ����˴ϴ�." << endl;
	string pass;
	for (int i = 0; i < 3; i++) {
		cout << "��й�ȣ�� �Է��� �ֽʽÿ�." << endl;
		cout << "���� �Է� Ƚ�� : " << 3-i << "ȸ" << endl;
		cin >> pass;
		if (a->getPassword() == pass) {
			return true;
		}
		cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
	}
	return false;
}

void ATM::valid_checks_check() {
	return;
}

void ATM::see_transaction_history() {
	//Transaction ID
	//Card Number
	//Transaction Types : deposit, withdraw, account transfer, cash_transfer
	//Amount
	//other transaction-specific information
	//account transfer:enemy account number
	//cash transfer:enemy account number

	cout << "������ ī�尡 �ԷµǾ����ϴ�." << endl << "������ �������� �ŷ� ������ Ȯ���Ͻðڽ��ϱ�?" << endl << "[0] ��" << "[1] �ƴϿ�" << endl;
	bool no;
	cin >> no;
	if (true) {
		return;
	}
	//�����丮 ���� �ڵ�
	return;
}

void ATM::make_history(string TransactionID, string CardNumber, string TransactionTypes, string Amount, string Specific) {
	vector<string>new_history = { TransactionID, CardNumber, TransactionTypes, Amount, Specific }; // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecificInformation
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
	return;
}

void ATM::display_transaction(string TransactionID, string CardNumber, string TransactionTypes, string Amount, string Specific) {
	cout << "Transaction ID : " << TransactionID << endl;
	cout << "CardNumber : " << CardNumber << endl;
	cout << "TransactionTypes : " << TransactionTypes << endl;
	cout << "Amount : " << Amount << endl;
	cout << "Note : " << Specific << endl;
	return;
}

int ATM::getSerial() {
	return serial_number;
}