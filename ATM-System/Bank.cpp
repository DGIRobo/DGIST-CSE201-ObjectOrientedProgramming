#include "Bank.h"

int Bank::static_bank_counter = 0;

Bank::Bank(string name) {
	this->bank_name = name;
	static_bank_counter += 1;
	this->bank_id = static_bank_counter;
}

Bank::~Bank() {

}

int Bank::getBankId() {
	return this->bank_id;
}

string Bank::getBankName() {
	return this->bank_name;
}

void Bank::deposit2ATM(ATM* target_ATM, int numOf1000, int numOf5000, int numOf10000, int numOf50000) {
	target_ATM->add_cash(numOf1000, numOf5000, numOf10000, numOf50000);
}