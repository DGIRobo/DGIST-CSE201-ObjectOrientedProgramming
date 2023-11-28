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
	cout << "Bank를 설립합니다." << endl << "Bank 이름을 입력해 주세요." << endl;
	string name;
	cin >> name;
	return Bank(name);
}

void initialize_account(vector<Bank> list) {
	cout << "초기 Account를 개설합니다." << endl;
	cout << "계좌를 개설할 은행을 선택해 주세요." << endl;
	for (int i = 0; i < list.size(); i++) {
		cout << "[" << i << "] " << list.at(i).getBankName() << endl;
	}
	int bankselection;
	cin >> bankselection;
	if (sizeof(list) <= bankselection) {
		list.at(bankselection).create_account();
	}
	else {
		cout << "해당하는 은행을 찾을 수 없어 개설을 취소합니다." << endl;
		return;
	}
}

void initialize_Fee(int* fees) {
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
	//return Fee(fee_list[0], fee_list[1], fee_list[2], fee_list[3], fee_list[4], fee_list[5], fee_list[6], fee_list[7]);
	return;
}

ATM* initialize_ATM(vector<Bank> list) {
	//은행, 일련번호, 타입, 언어, 초기금액(현금)
	cout << "초기 ATM을 설치합니다." << endl;
	cout << "ATM을 설치할 은행을 선택해 주세요." << endl;
	for (int i = 0; i < list.size(); i++) {
		cout << "[" << i << "] " << list.at(i).getBankName() << endl;
	}
	int bankselection;
	cin >> bankselection;
	if (sizeof(list) <= bankselection) {
		int atmtype;
		cout << "ATM의 타입을 결정합니다. Single bank ATM이라면 0을, Multi bank ATM이라면 그 이외의 숫자를 입력해 주세요." << endl;
		cin >> atmtype;
		if (atmtype == 0) {
			int serial;
			cout << "ATM의 일련번호를 입력해 주세요." << endl;
			cin >> serial;
			string lang;
			cout << "ATM이 지원 가능한 언어를 입력해 주세요." << endl;
			cin >> lang;
			int* store[4];
			cout << "ATM에 저장된 1000원권의 수를 입력해 주세요." << endl;
			cin >> *store[0];
			cout << "ATM에 저장된 5000원권의 수를 입력해 주세요." << endl;
			cin >> *store[1];
			cout << "ATM에 저장된 10000원권의 수를 입력해 주세요." << endl;
			cin >> *store[2];
			cout << "ATM에 저장된 50000원권의 수를 입력해 주세요." << endl;
			cin >> *store[3];
			Single* pSingle = new Single(list.at(bankselection).getBankName(), "Single", serial, lang, store);
			ATM* pATM = pSingle;
			return pATM;
		}
		else {
			int serial;
			cout << "ATM의 일련번호를 입력해 주세요." << endl;
			cin >> serial;
			string lang;
			cout << "ATM이 지원 가능한 언어를 입력해 주세요." << endl;
			cin >> lang;
			int* store[4];
			cout << "ATM에 저장된 1000원권의 수를 입력해 주세요." << endl;
			cin >> *store[0];
			cout << "ATM에 저장된 5000원권의 수를 입력해 주세요." << endl;
			cin >> *store[1];
			cout << "ATM에 저장된 10000원권의 수를 입력해 주세요." << endl;
			cin >> *store[2];
			cout << "ATM에 저장된 50000원권의 수를 입력해 주세요." << endl;
			cin >> *store[3];
			Multi* pMulti = new Multi(list.at(bankselection).getBankName(), "Multi", serial, lang, store);
			ATM* pATM = pMulti;
			return pATM;
		}
	}
	else {
		cout << "해당하는 은행을 찾을 수 없어 설치를 취소합니다." << endl;
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
