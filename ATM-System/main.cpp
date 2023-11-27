#include <iostream>
#include <string>

#include "Account.h"
#include "Bank.h"
#include "ATM.h"
#include "Fee.h"

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

Fee initialize_Fee() {
	int fee_list[8];
	cout << "Primary bank로부터의 deposit fee를 입력해 주십시오." << endl << "추천 Fee : 0" << endl;
	cin >> fee_list[0];
	cout << "Primary bank로부터의 withdrawal fee를 입력해 주십시오." << endl << "추천 Fee : 1000" << endl;
	cin >> fee_list[1];
	cout << "Primary bank끼리의 transfer fee를 입력해 주십시오." << endl << "추천 Fee : 2000" << endl;
	cin >> fee_list[2];
	cout << "Primary bank로부터의 deposit fee를 입력해 주십시오." << endl << "추천 Fee : 1000" << endl;
	cin >> fee_list[3];
	cout << "Primary bank로부터의 withdrawal fee를 입력해 주십시오." << endl << "추천 Fee : 2000" << endl;
	cin >> fee_list[4];
	cout << "Primary bank와 non-primary bank 사이의 transfer fee를 입력해 주십시오." << endl << "추천 Fee : 3000" << endl;
	cin >> fee_list[5];
	cout << "Non-primary bank끼리의 transfer fee를 입력해 주십시오." << endl << "추천 Fee : 4000" << endl;
	cin >> fee_list[6];
	cout << "Cash transfer fee를 입력해 주십시오." << endl << "추천 Fee : 5000" << endl;
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