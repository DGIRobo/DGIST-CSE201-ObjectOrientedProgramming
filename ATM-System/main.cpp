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
				if (language_setting == 2) { cout << bank_name << " ������ �̹� �����մϴ�!" << endl; }
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
		bank_list[bank_choose]->create_account(language_setting);
	}
	if (service_choose == 2) {
		bank_list[bank_choose]->makeCard_session(language_setting);
	}
	cout << "==================== < Bank Service Session End! > ====================" << endl;
}

void ATMMake(vector<ATM*>& ATM_list, vector<Bank*>& bank_list, int* fee_list1[4], int* fee_list2[4], int language_setting) {
	cout << "==================== < ATM Duplicate Session > ====================" << endl;
	//input : primary bank name, serial number, type, language, initial fund
	//constant : 
	if (language_setting == 1) { cout << "Please choose Bank number that you want to make ATM for : " << endl; }
	if (language_setting == 2) { cout << "ATM�� ��ġ�� ������ �����ϼ��� : " << endl; }
	for (int i = 0; i < bank_list.size(); i++) {
		cout << "[" << i << "] " << bank_list[i]->getBankName() << " Bank" << endl;
	}
	int bank_choose;
	cin >> bank_choose;
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

	int type;
	while (true) {
		if (language_setting == 1) { cout << "Please input ATM type." << endl << "[1] Single Bank ATM" << endl << "[2] Multi Bank ATM" << endl; }
		if (language_setting == 2) { cout << "ATM�� type�� �Է��ϼ���." << endl << "[1] Single Bank ATM" << endl << "[2] Multi Bank ATM" << endl; }
		cin >> type;
		if (type == 1 || type == 2) {
			break;
		}
		else {
			if (language_setting == 1) { cout << "Wrong type. Please try one more time." << endl; }
			if (language_setting == 2) { cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��� �ּ���." << endl; }
		}
	}

	int language;
	while (true) {
		if (language_setting == 1) { cout << "Please input ATM language type." << endl << "[1] Unilingual ATM" << endl << "[2] Bilingual ATM" << endl; }
		if (language_setting == 2) { cout << "ATM�� ��� type�� ������ �ּ���." << endl << "[1] Unilingual ATM" << endl << "[2] Bilingual ATM" << endl; }
		cin >> language;
		if (type == 1 || type == 2) {
			break;
		}
		else {
			if (language_setting == 1) { cout << "Wrong language type. Please try one more time." << endl; }
			if (language_setting == 2) { cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��� �ּ���." << endl; }
		}
	}

	int* fund[4] = { 0, };
	for (int i = 0; i < 4; i++) {
		fund[i] = new int(0);
	}
	if (language_setting == 1) { cout << "Please Enter the Amount of 1000 won bills." << endl; }
	if (language_setting == 2) { cout << "1000������ ���� �Է��� �ּ���." << endl; }
	cin >> *(fund[0]);
	if (language_setting == 1) { cout << "Please Enter the Amount of 5000 won bills." << endl; }
	if (language_setting == 2) { cout << "5000������ ���� �Է��� �ּ���." << endl; }
	cin >> *(fund[1]);
	if (language_setting == 1) { cout << "Please Enter the Amount of 10000 won bills." << endl; }
	if (language_setting == 2) { cout << "10000������ ���� �Է��� �ּ���." << endl; }
	cin >> *(fund[2]);
	if (language_setting == 1) { cout << "Please Enter the Amount of 50000 won bills." << endl; }
	if (language_setting == 2) { cout << "50000������ ���� �Է��� �ּ���." << endl; }
	cin >> *(fund[3]);

	switch (type) {
	case 1:
		//Single(bank_list[bank_choose].getBankName(), serial, language, fund, fee_list1);
		ATM_list.push_back(new Single(bank_list[bank_choose], serial, language, fund, fee_list1));
		cout << "==================== < ATM Duplicate Session End! > ====================" << endl;
		break;
	case 2:
		//Multi(bank_list[bank_choose].getBankName(), serial, language, fund, fee_list1, fee_list2);
		ATM_list.push_back(new Multi(bank_list[bank_choose], serial, language, fund, fee_list1, fee_list2));
		cout << "==================== < ATM Duplicate Session End! > ====================" << endl;
		break;
	default:
		break;
	}


	return;
}

void ATMService(vector<ATM*> ATM_list, vector<Bank*> bank_list, int language_setting) {
	cout << "==================== < ATM Service Session > ====================" << endl;
	if (language_setting == 1) { cout << "Please choose ATM number that you want to use for." << endl; }
	if (language_setting == 2) { cout << "�ŷ��� �����ϰ� ���� ATM�� �������ּ���." << endl; }

	for (int i = 0; i < ATM_list.size(); i++) {
		cout << "[" << i << "] ATM " << ATM_list[i]->getSerial() << " [Bank " << ATM_list[i]->getPrimary()->getBankName() << "/" << ATM_list[i]->getType() << "/" << ATM_list[i]->getLangType() << "]" << endl;
	}
	cout << endl;
	int ATM_choose;
	if (language_setting == 1) { cout << "ATM number : "; }
	if (language_setting == 2) { cout << "ATM ��ȣ : "; }
	cin >> ATM_choose;
	if (ATM_choose >= ATM_list.size()) {
		if (language_setting == 1) { cout << "The corresponding ATM does not exist." << endl; }
		if (language_setting == 2) { cout << "�ش��ϴ� ATM�� �������� �ʽ��ϴ�." << endl; }
		cout << "==================== < ATM Service Session End! > ====================" << endl;
		return;
	}
	if (language_setting == 1) { cout << ATM_list[ATM_choose]->getSerial() << " ATM is selected." << endl << "Connecting to ATM..." << endl; }
	if (language_setting == 2) { cout << ATM_list[ATM_choose]->getSerial() << " ATM�� ���õǾ����ϴ�." << endl << "ATM�� �����մϴ�..." << endl; }

	ATM_list[ATM_choose]->session(bank_list);
	cout << "==================== < ATM Service Session End! > ====================" << endl;
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
			cin >> card_number;

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

void feeConfig(int* fee_list1[4], int* fee_list2[4], int language_setting) {
	if (language_setting == 1) { cout << "Please Enter the deposit fee for primary bank." << endl; }
	if (language_setting == 2) { cout << "Primary bank ���¿����� �Ա� �����Ḧ �Է��� �ּ���." << endl; }
	cin >> *(fee_list1[0]);
	if (language_setting == 1) { cout << "Please Enter the withdrawal fee for primary bank." << endl; }
	if (language_setting == 2) { cout << "Primary bank ���¿����� ��� �����Ḧ �Է��� �ּ���." << endl; }
	cin >> *(fee_list1[1]);
	if (language_setting == 1) { cout << "Please Enter the account transfer fee between primary banks." << endl; }
	if (language_setting == 2) { cout << "Primary bank ���³����� �۱� �����Ḧ �Է��� �ּ���." << endl; }
	cin >> *(fee_list1[2]);
	if (language_setting == 1) { cout << "Please Enter the cash transfer fee." << endl; }
	if (language_setting == 2) { cout << "���� �۱� �����Ḧ �Է��� �ּ���." << endl; }
	cin >> *(fee_list1[3]);
	if (language_setting == 1) { cout << "Please Enter the deposit fee for non-primary bank." << endl; }
	if (language_setting == 2) { cout << "Non-Primary bank ���¿����� �Ա� �����Ḧ �Է��� �ּ���." << endl; }
	cin >> *(fee_list2[0]);
	if (language_setting == 1) { cout << "Please Enter the withdrawal fee for non-primary bank." << endl; }
	if (language_setting == 2) { cout << "Non-primary bank ���¿����� ��� �����Ḧ �Է��� �ּ���." << endl; }
	cin >> *(fee_list2[1]);
	if (language_setting == 1) { cout << "Please Enter the account transfer fee between primary bank and non-primary banks." << endl; }
	if (language_setting == 2) { cout << "Primary bank ���¿� non-primary bank ���� ������ �۱� �����Ḧ �Է��� �ּ���." << endl; }
	cin >> *(fee_list2[2]);
	if (language_setting == 1) { cout << "Please Enter the account transfer fee between non-primary banks." << endl; }
	if (language_setting == 2) { cout << "Non-primary bank ���³����� �۱� �����Ḧ �Է��� �ּ���." << endl; }
	cin >> *(fee_list2[3]);
	return;
}

int LanguageService(int language_setting) {
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

	cin >> language_setting;
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
		cin >> input_password;
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

	int choice;
	cin >> choice;

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

void AccountHistory(vector<Bank*> bank_list, int language_setting) {

	cout << "==================== < Account History Session > ====================" << endl;
	Account* account = BankSearch(bank_list, language_setting);
	
	string input_password;
	int a = 3;
	while (true) {

		if (a == 0) {
			if (language_setting == 1) { cout << "You write wrong password 4 times. " << endl; }
			if (language_setting == 2) { cout << "��й�ȣ 4ȸ Ʋ�Ƚ��ϴ�." << endl; }
			cout << "==================== < Account History Session End! > ====================" << endl;
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

		cin >> input_password;
		a--;
		if (account->getPassword() == input_password) {
			if (language_setting == 1) { cout << "Correct password." << endl; }
			if (language_setting == 2) { cout << "���� ��й�ȣ." << endl; }
			cout << endl;
			account->printHistory();
			cout << "==================== < Account History Session End! > ====================" << endl;
		}
	}
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
			cout << "[2] Banking Service (Make Account or Make Card)" << endl;
			cout << "[3] Make ATM" << endl;
			cout << "[4] ATM Service (Deposit, Withdraw, etc...)" << endl;
			cout << "[5] Change Language Setting" << endl;
			cout << "[6] Shut Down the Bank System Service" << endl;
			cout << "[7] Fee Configuration" << endl;
			cout << "[8] Admin" << endl;
			cout << "[9] Account History" << endl;
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
			cout << "[9] ���� ���" << endl;
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
			ATMMake(ATM_list, bank_list, fee1, fee2, language_setting);
			break;
		case 4:
			ATMService(ATM_list, bank_list, language_setting);
			break;
		case 5:
			language_setting = LanguageService(language_setting);
			break;
		case 6:
			onSession = false;
			break;
		case 7:
			feeConfig(fee1, fee2, language_setting);
			break;
		case 8:
			Admin(ATM_list, bank_list, language_setting);
		case 9:
			AccountHistory(bank_list, language_setting);
		}
		cout << "===========================<End System Session>===========================" << endl;
	}

	cout << "===========================<End System>===========================" << endl;
	return 0;
}