#include "ATM.h"

void ATM::languageChange() {
	cout << "Please chioce the language setting." << endl;
	cout << "1. Korean" << endl;
	cout << "2. English" << endl;

	int input_language_setting;
	cin >> input_language_setting;

	if (input_language_setting == 1) {
		this->language_setting = "Korean";
	}
	else if (input_language_setting == 2) {
		this->language_setting = "English";
	}
}


ATM::ATM(string input_primary_bank, int input_serial_number, string input_type, string input_lanuage_available, int* initial_fund[]) {
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
	this->type = "";
	this->language_available = "";

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


