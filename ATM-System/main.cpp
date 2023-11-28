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
Bank initialize_bank() {
	cout << "Bank�� �����մϴ�." << endl << "Bank �̸��� �Է��� �ּ���." << endl;
	string name;
	cin >> name;
	return Bank(name);
}

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

int main() {
	//initialization test
	vector<Bank> bank_list;
	vector<ATM> ATM_list;
	vector<Account> account_list;
	Bank Kakao("Kakao");
	Kakao.create_account();
	Kakao.makeCard_session();
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
