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



void ATM::session() {

	if (this->language_setting == "Korean") {
		cout << "카드를 삽입해 주세요." << endl;
		string cardinsert;
		cin >> cardinsert;

		cout << getSerial() << "번 ATM에 접속하셨습니다. 무슨 작업을 도와드릴까요?" << endl;
		cout << "[1] 입금" << endl << "[2] 출금" << endl << "[3] 계좌 송금" << endl << "[4] 현금 송금" << endl << "[5] 언어 변경" << endl << "[6] (관리자 메뉴) 거래 내역 확인" << endl;
		int selection = 1;
		switch (selection) {
		case 1:
			cout << "입금을 선택하셨습니다. 해 주세요 : " << endl;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		}
	}
	if (this->language_setting == "English") {

	}
	return;
}

void ATM::add_cash(int cash1000, int cash5000, int cash10000, int cash50000) {
	this->cash_storage[0] += cash1000;
	this->cash_storage[1] += cash5000;
	this->cash_storage[2] += cash10000;
	this->cash_storage[3] += cash50000;
}

void ATM::user_authorization() {
	//카드 입력
	
	//카드 유효성 검사

	//비밀번호 입력

	//비밀번호 검사

	//3번 연속 틀리면 세션 중단되게

	return;
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

	return;
}

void ATM::transaction() {
	return;
}

int ATM::getSerial() {
	return serial_number;
}