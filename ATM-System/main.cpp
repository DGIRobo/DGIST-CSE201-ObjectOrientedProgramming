#include <iostream>
#include <string>

#include "Account.h"
#include "Bank.h"
#include "ATM.h"

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

int main() {
	// Account Test Code
	Bank Kakao("kakao");
	Account a1(&Kakao, "lee", "abc");
	cout << a1.getBankName() << endl;
	cout << a1.getUserName() << endl;
	cout << a1.getPassword() << endl;
	a1.printHistory();
}