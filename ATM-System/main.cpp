#include <iostream>
#include <string>

#include "Account.h"
#include "Bank.h"
#include "ATM.h"

using namespace std;

Bank initialize_bank() {
	cout << "Bank를 설립합니다." << endl << "Bank 이름을 입력해 주세요." << endl;
	string name;
	cin >> name;
	return Bank(name);
}

void initialize_account(Bank** list) {
	cout << "초기 Account를 개설합니다." << endl;
	cout << "개설할 은행을 선택해 주세요." << endl;
	for (int i = 0; i < sizeof(list); i++) {
		cout << "[" << i << "] " << list[i]->getBankName() << endl;
	}
	int bankselection;
	cin >> bankselection;
	if (sizeof(list) <= bankselection) {
		list[bankselection]->create_account();
	}
	else {
		cout << "해당하는 은행을 찾을 수 없어 개설을 취소합니다." << endl;
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