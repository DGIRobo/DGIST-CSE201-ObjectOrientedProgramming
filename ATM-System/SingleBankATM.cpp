#include "SingleBankATM.h"

void Single::primary_deposit(Account a){
	this->deposit(a);
	cout << "요금을 지불합니다." << endl;
	if (this->my_fee.getPD() == 0) {
		cout << "지불할 요금이 없습니다." << endl;
	}
	else if(this->my_fee.getPD() > a.checkFunds()) {
		cout << "잔액이 부족합니다." << endl;
	}
	else {
		a.withdraw(my_fee.getPD());
	}
	return;
}

void Single::primary_withdraw(Account a) {
	this->withdraw(a);
	cout << "요금을 지불합니다." << endl;
	if (this->my_fee.getPW() == 0) {
		cout << "지불할 요금이 없습니다." << endl;
	}
	else if (this->my_fee.getPW() > a.checkFunds()) {
		cout << "잔액이 부족합니다." << endl;
	}
	else {
		a.withdraw(my_fee.getPW());
	}
	return;
}

void Single::primary_transfer(Account a, Account b) {
	this->account_transfer(a, b);
	cout << "요금을 지불합니다." << endl;
	if (this->my_fee.getPPT() == 0) {
		cout << "지불할 요금이 없습니다." << endl;
	}
	else if (this->my_fee.getPPT() > a.checkFunds()) {
		cout << "잔액이 부족합니다." << endl;
	}
	else {
		a.withdraw(my_fee.getPPT());
	}
	return;
}