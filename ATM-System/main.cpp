#include <iostream>
#include <string>

#include "Account.h"
#include "Bank.h"
#include "ATM.h"
#include "Fee.h"

using namespace std;

Bank initialize_bank() {
	cout << "Bank�� �����մϴ�." << endl << "Bank �̸��� �Է��� �ּ���." << endl;
	string name;
	cin >> name;
	return Bank(name);
}

void initialize_account(Bank** list) {
	cout << "�ʱ� Account�� �����մϴ�." << endl;
	cout << "������ ������ ������ �ּ���." << endl;
	for (int i = 0; i < sizeof(list); i++) {
		cout << "[" << i << "] " << list[i]->getBankName() << endl;
	}
	int bankselection;
	cin >> bankselection;
	if (sizeof(list) <= bankselection) {
		list[bankselection]->create_account();
	}
	else {
		cout << "�ش��ϴ� ������ ã�� �� ���� ������ ����մϴ�." << endl;
		return;
	}
}

ATM initialize_ATM();

Fee initialize_Fee() {
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
	return Fee(fee_list[0], fee_list[1], fee_list[2], fee_list[3], fee_list[4], fee_list[5], fee_list[6], fee_list[7]);
}

int main() {
	// Account Test Code
	Bank Kakao("kakao");
	Account a1(&Kakao, "lee", "abc");
	cout << a1.getBankName() << endl;
	cout << a1.getUserName() << endl;
	cout << a1.getPassword() << endl;
	a1.printHistory();
}