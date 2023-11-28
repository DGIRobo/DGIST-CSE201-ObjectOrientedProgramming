#include <iostream>
#include <string>

#include "Account.h"
#include "Bank.h"
#include "ATM.h"
#include "Fee.h"
#include "SingleBankATM.h"
#include "MultiBankATM.h"

using namespace std;




/*
void initialize_account(vector<Bank> list) {
	cout << "�ʱ� Account�� �����մϴ�." << endl;
	cout << "���¸� ������ ������ ������ �ּ���." << endl;
	for (int i = 0; i < list.size(); i++) {
		cout << "[" << i << "] " << list.at(i).getBankName() << endl;
	}
	int bankselection;
	cin >> bankselection;
	if (sizeof(list) <= bankselection) {
		list.at(bankselection).create_account();
	}
	else {
		cout << "�ش��ϴ� ������ ã�� �� ���� ������ ����մϴ�." << endl;
		return;
	}
}

void initialize_Fee(int* fees) {
	int fee_list[8];
	cout << "Primary bank�κ����� deposit fee�� �Է��� �ֽʽÿ�." << endl << "��õ Fee : 0" << endl;
	cin >> fee_list[0];
	cout << "Primary bank�κ����� withdrawal fee�� �Է��� �ֽʽÿ�." << endl << "��õ Fee : 1000" << endl;
	cin >> fee_list[1];
	cout << "Primary bank������ transfer fee�� �Է��� �ֽʽÿ�." << endl << "��õ Fee : 2000" << endl;
	cin >> fee_list[2];
	cout << "Primary bank�κ����� deposit fee�� �Է��� �ֽʽÿ�." << endl << "��õ Fee : 1000" << endl;
	cin >> fee_list[3];
	cout << "Primary bank�κ����� withdrawal fee�� �Է��� �ֽʽÿ�." << endl << "��õ Fee : 2000" << endl;
	cin >> fee_list[4];
	cout << "Primary bank�� non-primary bank ������ transfer fee�� �Է��� �ֽʽÿ�." << endl << "��õ Fee : 3000" << endl;
	cin >> fee_list[5];
	cout << "Non-primary bank������ transfer fee�� �Է��� �ֽʽÿ�." << endl << "��õ Fee : 4000" << endl;
	cin >> fee_list[6];
	cout << "Cash transfer fee�� �Է��� �ֽʽÿ�." << endl << "��õ Fee : 5000" << endl;
	cin >> fee_list[7];
	//return Fee(fee_list[0], fee_list[1], fee_list[2], fee_list[3], fee_list[4], fee_list[5], fee_list[6], fee_list[7]);
	return;
}

ATM* initialize_ATM(vector<Bank> list) {
	//����, �Ϸù�ȣ, Ÿ��, ���, �ʱ�ݾ�(����)
	cout << "�ʱ� ATM�� ��ġ�մϴ�." << endl;
	cout << "ATM�� ��ġ�� ������ ������ �ּ���." << endl;
	for (int i = 0; i < list.size(); i++) {
		cout << "[" << i << "] " << list.at(i).getBankName() << endl;
	}
	int bankselection;
	cin >> bankselection;
	if (sizeof(list) <= bankselection) {
		int atmtype;
		cout << "ATM�� Ÿ���� �����մϴ�. Single bank ATM�̶�� 0��, Multi bank ATM�̶�� �� �̿��� ���ڸ� �Է��� �ּ���." << endl;
		cin >> atmtype;
		if (atmtype == 0) {
			int serial;
			cout << "ATM�� �Ϸù�ȣ�� �Է��� �ּ���." << endl;
			cin >> serial;
			string lang;
			cout << "ATM�� ���� ������ �� �Է��� �ּ���." << endl;
			cin >> lang;
			int* store[4];
			cout << "ATM�� ����� 1000������ ���� �Է��� �ּ���." << endl;
			cin >> *store[0];
			cout << "ATM�� ����� 5000������ ���� �Է��� �ּ���." << endl;
			cin >> *store[1];
			cout << "ATM�� ����� 10000������ ���� �Է��� �ּ���." << endl;
			cin >> *store[2];
			cout << "ATM�� ����� 50000������ ���� �Է��� �ּ���." << endl;
			cin >> *store[3];
			Single* pSingle = new Single(list.at(bankselection).getBankName(), "Single", serial, lang, store);
			ATM* pATM = pSingle;
			return pATM;
		}
		else {
			int serial;
			cout << "ATM�� �Ϸù�ȣ�� �Է��� �ּ���." << endl;
			cin >> serial;
			string lang;
			cout << "ATM�� ���� ������ �� �Է��� �ּ���." << endl;
			cin >> lang;
			int* store[4];
			cout << "ATM�� ����� 1000������ ���� �Է��� �ּ���." << endl;
			cin >> *store[0];
			cout << "ATM�� ����� 5000������ ���� �Է��� �ּ���." << endl;
			cin >> *store[1];
			cout << "ATM�� ����� 10000������ ���� �Է��� �ּ���." << endl;
			cin >> *store[2];
			cout << "ATM�� ����� 50000������ ���� �Է��� �ּ���." << endl;
			cin >> *store[3];
			Multi* pMulti = new Multi(list.at(bankselection).getBankName(), "Multi", serial, lang, store);
			ATM* pATM = pMulti;
			return pATM;
		}
	}
	else {
		cout << "�ش��ϴ� ������ ã�� �� ���� ��ġ�� ����մϴ�." << endl;
		return nullptr;
	}
	return;
}
*/

Bank initialize_bank() {
	cout << "Bank�� �����մϴ�." << endl << "Bank �̸��� �Է��� �ּ���." << endl;
	string name;
	cin >> name;
	return Bank(name);
}

void BankMake(vector<Bank>& bank_list) {
	
	cout << "==================== < Bank Duplicate Session > ====================" << endl;
	string bank_name; string bank_name_save;

	while (true) {
		int dup = 0;
		cout << "Please write bank name : ";	 cin >> bank_name;

		bank_name_save = bank_name;

		for (int i = 0; i < bank_name.size(); i++) {
			bank_name[i] = tolower(bank_name[i]);
		}

		for (int j = 0; j < bank_list.size(); j++) {

			string reference = bank_list[j].getBankName();

			for (int k = 0; k < reference.size(); k++) {
				reference[k] = tolower(reference[k]);
			}
			if (reference == bank_name) {
				cout << bank_name << " is already exiested!" << endl;
				dup = 1;
			}
		}
		if (dup == 0) {
			bank_list.push_back(Bank(bank_name_save));
			cout << "==================== < Bank Duplicate Session End! > ====================" << endl;
			break;
		}
	}
}

void BankService(vector<Bank>& bank_list) {

	cout << "==================== < Bank Service Session > ====================" << endl;
	for (int i = 0; i < bank_list.size(); i++) {
		cout << bank_list[i].getBankName() << " Bank : " << "[" << i << "]" << endl;
	}
	int bank_choose;
	cout << "Please choose Bank number that you want to make account for." << endl;
	cout << "Bank number : "; cin >> bank_choose;
	cout << bank_list[bank_choose].getBankName() << " bank is selected." << endl;

	int service_choose;
	cout << "Please choose number that you want to get service." << endl;
	cout << "Create account [1] / make Card [2]" << endl;
	cout << "Serive number : "; cin >> service_choose;

	if (service_choose == 1) {
		bank_list[bank_choose].create_account();
	}
	if (service_choose == 2) {
		bank_list[bank_choose].makeCard_session();
	}
	cout << "==================== < Bank Service Session End! > ====================" << endl;
}

Account* BankSearch(vector<Bank>& bank_list) {
	cout << "==================== < Bank Search Session > ====================" << endl;

	cout << "Please choose serach service number that you want." << endl;
	cout << "Account Number [1] / Card Number [2]" << endl;

	int search_choose;
	cout << "Search service number : "; cin >> search_choose;

	while (true) {
		if (search_choose == 1) {
			string account_number;
			cout << "Please write your account number : "; cin >> account_number;

			for (int i = 0; i < bank_list.size(); i++) {
				if (bank_list[i].search_account_number_BankSearch(account_number) != NULL) {
					cout << "==================== < Bank Search Session End! > ====================" << endl;
					return bank_list[i].search_account_number_BankSearch(account_number);
				}
			}
			cout << "Account is not found." << endl;
		}
		if (search_choose == 2) {
			string card_number;
			cout << "Please write your card number : "; cin >> card_number;

			for (int i = 0; i < bank_list.size(); i++) {
				if (bank_list[i].search_account_card_BankSearch(card_number) != NULL) {
					cout << "==================== < Bank Search Session End! > ====================" << endl;
					return bank_list[i].search_account_card_BankSearch(card_number);
				}
			}
			cout << "Account is not found." << endl;
		}
	}
	cout << "==================== < Bank Search Session End! > ====================" << endl;
}


int main() {
	// initialize_bank();
	
	vector<Bank> bank_list;

	BankMake(bank_list);
	BankService(bank_list);
	BankSearch(bank_list);
	BankSearch(bank_list);



	vector<ATM> ATM_list;
	vector<Account> account_list;

	/*
	Bank Kakao("Kakao");
	Kakao.create_account();
	Kakao.makeCard_session();
	*/

	/*
	for (int i = 0; i != 0 ;) {
		cout << "===bank initialization [" << i+1 << "]===" << endl;
		bank_list.push_back(initialize_bank());
		cout << "continue to press 0, stop to press 1(or else)" << endl;
		cin >> i;
	}
	for (int i = 0; i != 0;) {
		cout << "===ATM initialization [" << i + 1 << "]===" << endl;
		bank_list.push_back(initialize_bank());
		cout << "continue to press 0, stop to press 1(or else)" << endl;
		cin >> i;
	}
	cout << "======test======" << endl;
	for (int i = 0; i < bank_list.size(); i++) {
		cout << "Bank name : " << bank_list.at(i).getBankName() << endl;
	}
	*/
}
