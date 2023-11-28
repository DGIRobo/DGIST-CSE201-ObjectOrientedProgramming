#include <iostream>
#include <string>

#include "Account.h"
#include "Bank.h"
#include "ATM.h"
#include "Fee.h"
#include "SingleBankATM.h"
#include "MultiBankATM.h"

using namespace std;

void BankMake(vector<Bank*>& bank_list, int language_setting) {

	cout << "==================== < Bank Duplicate Session > ====================" << endl;
	string bank_name; string bank_name_save;

	while (true) {
		int dup = 0;

		if (language_setting == 1) { cout << "Please write bank name : ";	 cin >> bank_name; }
		if (language_setting == 2) { cout << "������� �Է����ּ���. : ";	 cin >> bank_name; }

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
				if (language_setting == 2) {
					cout << bank_name << " ������ �̹� �����մϴ�!" << endl;
				}
				dup = 1;
			}
		}
		if (dup == 0) {
			// bank_list.push_back(Bank(bank_name_save));
			bank_list.push_back(new Bank(bank_name_save));
			cout << "==================== < Bank Duplicate Session End! > ====================" << endl;
			break;
		}
	}
}

void BankService(vector<Bank*> bank_list, int language_setting) {

	cout << "==================== < Bank Service Session > ====================" << endl;
	if (language_setting == 1) { cout << "Please choose Bank number that you want to make account for." << endl; }
	if (language_setting == 2) { cout << "���¸� ����� ���� ������ �������ּ���." << endl; }

	for (int i = 0; i < bank_list.size(); i++) {
		cout << "[" << i << "] " << bank_list[i]->getBankName() << " Bank" << endl;
	}
	cout << endl;
	int bank_choose;
	if (language_setting == 1) { cout << "Bank number : "; }
	if (language_setting == 2) { cout << "���� ��ȣ : "; }
	cin >> bank_choose;
	if (language_setting == 1) { cout << bank_list[bank_choose]->getBankName() << " bank is selected." << endl; }
	if (language_setting == 2) { cout << bank_list[bank_choose]->getBankName() << " ������ ���õǾ����ϴ�." << endl; }

	int service_choose;
	if (language_setting == 1) {
		cout << "Please choose number that you want to get service." << endl;
		cout << "[1] Create Account" << endl;
		cout << "[2] Make Card" << endl;
		cout << endl;
		cout << "Serive number : ";
	}
	if (language_setting == 2) {
		cout << "�̿��ϰ��� �ϴ� ���񽺸� �������ּ���." << endl;
		cout << "[1] ���� ����" << endl;
		cout << "[2] ī�� ����" << endl;
		cout << endl;
		cout << "���� ��ȣ : ";
	}

	cin >> service_choose;

	if (service_choose == 1) {
		bank_list[bank_choose]->create_account();
	}
	if (service_choose == 2) {
		bank_list[bank_choose]->makeCard_session();
	}
	cout << "==================== < Bank Service Session End! > ====================" << endl;
}

void ATMMake(vector<ATM*>& ATM_list, vector<Bank>& bank_list, int* fee_list1[4], int* fee_list2[4]) {
	cout << "==================== < ATM Duplicate Session > ====================" << endl;
	//input : primary bank name, serial number, type, language, initial fund
	//constant : 
	for (int i = 0; i < bank_list.size(); i++) {
		cout << bank_list[i].getBankName() << " Bank : " << "[" << i << "]" << endl;
	}
	int bank_choose;
	cout << "Please choose Bank number that you want to make ATM for." << endl;
	cout << "Bank number : ";
	cin >> bank_choose;
	cout << bank_list[bank_choose].getBankName() << " bank is selected." << endl;
	int serial = 0;
	while (true) {
		int dup = 0;

		int serial_temp;
		cout << "Please input ATM serial number." << endl;
		cout << "ATM number : ";
		cin >> serial_temp;
		for (int i = 0; i < ATM_list.size(); i++) {
			if (serial_temp == ATM_list[i]->getSerial()) {
				cout << "ATM " << serial_temp << " is already exiested!" << endl;
				dup = 1;
			}
		}
		if (dup == 0) {
			serial == serial_temp;
			break;
		}
	}

	int type;
	while (true) {
		cout << "Please input ATM type." << endl << "[1] Single Bank ATM" << endl << "[2] Multi Bank ATM" << endl;
		cin >> type;
		if (type == 1 || type == 2) {
			break;
		}
		else {
			cout << "Wrong type. Please try one more time." << endl;
		}
	}

	int language;
	while (true) {
		cout << "Please input ATM language type." << endl << "[1] Unilingual ATM" << endl << "[2] Bilingual ATM" << endl;
		cin >> type;
		if (type == 1 || type == 2) {
			break;
		}
		else {
			cout << "Wrong language type. Please try one more time." << endl;
		}
	}

	int* fund[4] = { 0, };
	for (int i = 0; i < 4; i++) {
		fund[i] = new int(0);
	}
	cout << "Please Enter the Amount of 1000 won bills." << endl;
	cin >> *(fund[0]);
	cout << "Please Enter the Amount of 5000 won bills." << endl;
	cin >> *(fund[1]);
	cout << "Please Enter the Amount of 10000 won bills." << endl;
	cin >> *(fund[2]);
	cout << "Please Enter the Amount of 50000 won bills." << endl;
	cin >> *(fund[3]);

	switch (type) {
	case 1:
		//Single(bank_list[bank_choose].getBankName(), serial, language, fund, fee_list1);
		break;
	case 2:
		//Multi(bank_list[bank_choose].getBankName(), serial, language, fund, fee_list1, fee_list2);
		break;
	default:
		break;
	}


	return;
}

Account* BankSearch(vector<Bank*> bank_list, int language_setting) {
	cout << "==================== < Bank Search Session > ====================" << endl;
	if (language_setting == 1) {

	}
	if (language_setting == 2) {

	}
	cout << "Please choose serach service number that you want." << endl;
	cout << "[1] Account Number" << endl;
	cout << "[2] Card Number" << endl;
	cout << endl;
	cout << "Search service number : ";

	int search_choose;
	cin >> search_choose;

	while (true) {
		if (search_choose == 1) {
			string account_number;
			if (language_setting == 1) { cout << "Please write your account number : "; }
			if (language_setting == 2) { cout << "���¹�ȣ�� �Է����ּ���. : "; }
			cin >> account_number;

			for (int i = 0; i < bank_list.size(); i++) {
				if (bank_list[i]->search_account_number_BankSearch(account_number) != NULL) {
					cout << "==================== < Bank Search Session End! > ====================" << endl;
					return bank_list[i]->search_account_number_BankSearch(account_number);
				}
			}
			if (language_setting == 1) { cout << "Account is not found." << endl; }
			if (language_setting == 2) { cout << "���¸� ã�� �� �����ϴ�." << endl; }
		}
		if (search_choose == 2) {
			string card_number;
			if (language_setting == 1) { cout << "Please write your card number : "; }
			if (language_setting == 2) { cout << "ī�� ��ȣ�� �Է����ּ���. : "; }
			cin >> card_number;

			for (int i = 0; i < bank_list.size(); i++) {
				if (bank_list[i]->search_account_card_BankSearch(card_number) != NULL) {
					cout << "==================== < Bank Search Session End! > ====================" << endl;
					return bank_list[i]->search_account_card_BankSearch(card_number);
				}
			}
			if (language_setting == 1) { cout << "Account is not found." << endl; }
			if (language_setting == 2) { cout << "���¸� ã�� �� �����ϴ�." << endl; }
		}
	}
	cout << "==================== < Bank Search Session End! > ====================" << endl;
}

void feeConfig(int* fee_list1[4], int* fee_list2[4]) {
	cout << "Please Enter the deposit fee for primary bank." << endl;
	cin >> *(fee_list1[0]);
	cout << "Please Enter the withdrawal fee for primary bank." << endl;
	cin >> *(fee_list1[1]);
	cout << "Please Enter the account transfer fee between primary banks." << endl;
	cin >> *(fee_list1[2]);
	cout << "Please Enter the cash transfer fee." << endl;
	cin >> *(fee_list1[3]);
	cout << "Please Enter the deposit fee for primary bank." << endl;
	cin >> *(fee_list2[0]);
	cout << "Please Enter the withdrawal fee for primary bank." << endl;
	cin >> *(fee_list2[1]);
	cout << "Please Enter the account transfer fee between primary bank and non-primary banks." << endl;
	cin >> *(fee_list2[2]);
	cout << "Please Enter the account transfer fee between non-primary banks." << endl;
	cin >> *(fee_list2[3]);
	return;
}

int LanguageService(int language_setting) {
	cout << "===========================<Language Change Session>===========================" << endl;
	if (language_setting == 1) {
		cout << "Select language" << endl;
		cout << "[1] English" << endl;
		cout << "[2] Korean" << endl;
		cout << endl;
		cout << "Please Enter the Number: ";
	}
	if (language_setting == 2) {
		cout << "����" << endl;
		cout << "[1] ����" << endl;
		cout << "[2] �ѱ���" << endl;
		cout << endl;
		cout << "��ȣ �Է� : ";
	}

	cin >> language_setting;
	return language_setting;
}

int main() {
	vector<Bank*> bank_list;
	vector<ATM*> ATM_list;

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
			cout << "[2] Banking Service (Make Account of Make Card)" << endl;
			cout << "[3] Make ATM" << endl;
			cout << "[4] ATM Service (Deposit, Withdraw, etc...)" << endl;
			cout << "[5] Change Language Setting" << endl;
			cout << "[6] Shut Down the Bank System Service" << endl;
			cout << "[7] Fee Configuration" << endl;
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
			cout << endl;
			cout << "���ڸ� �Է����ּ��� : ";
		}

		int session_chice;
		cin >> session_chice;

		switch (session_chice) {
		case 1:
			BankMake(bank_list, language_setting);
			break;
		case 2:
			BankService(bank_list, language_setting);
			break;
		case 3:
			//ATMMake(ATM_list, bank_list, fee1, fee2);
			break;
		case 4:
			//ATMService(ATM_list);
			break;
		case 5:
			language_setting = LanguageService(language_setting);
			break;
		case 6:
			onSession = false;
			break;
		case 7:
			feeConfig(fee1, fee2);
			break;
		}
		cout << "===========================<End System Session>===========================" << endl;
	}

	cout << "===========================<End System>===========================" << endl;
	return 0;
}