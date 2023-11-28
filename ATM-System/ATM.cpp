#include "ATM.h"

void ATM::languageChange() {
	cout << "Please chioce the language setting." << endl;
	cout << "1. English" << endl;
	cout << "2. Korean" << endl;

	int input_language_setting;
	cin >> input_language_setting;

	if (input_language_setting == 2) {
		this->language_setting = "Korean";
	}
	if (input_language_setting == 1) {
		this->language_setting = "English";
	}
}


ATM::ATM(string input_primary_bank, int input_serial_number, int input_type, int input_lanuage_available, int* initial_fund[]) {
	this->primary_bank = input_primary_bank;
	this->serial_number = input_serial_number;
	this->type = input_type;
	this->language_available = input_lanuage_available;

	for (int i = 0; i < 4; ++i) {
		this->cash_storage[i] = initial_fund[i];
	}
}

ATM::~ATM() {
	this->primary_bank = "";
	this->serial_number = 0;
	this->type = 0;
	this->language_available = 0;

	for (int i = 0; i < 4; ++i) {
		this->cash_storage[i] = 0;
	}
}



void ATM::session() {

	if (this->language_setting == "Korean") {

	}
	if (this->language_setting == "English") {

	}

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