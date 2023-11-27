#include "SingleBankATM.h"

void Single::primary_deposit(Account a){
	this->deposit(a);
	cout << "����� �����մϴ�." << endl;
	if (this->my_fee.getPD() == 0) {
		cout << "������ ����� �����ϴ�." << endl;
	}
	else if(this->my_fee.getPD() > a.checkFunds()) {
		cout << "�ܾ��� �����մϴ�." << endl;
	}
	else {
		a.withdraw(my_fee.getPD());
	}
	return;
}

void Single::primary_withdraw(Account a) {
	this->withdraw(a);
	cout << "����� �����մϴ�." << endl;
	if (this->my_fee.getPW() == 0) {
		cout << "������ ����� �����ϴ�." << endl;
	}
	else if (this->my_fee.getPW() > a.checkFunds()) {
		cout << "�ܾ��� �����մϴ�." << endl;
	}
	else {
		a.withdraw(my_fee.getPW());
	}
	return;
}

void Single::primary_transfer(Account a, Account b) {
	this->account_transfer(a, b);
	cout << "����� �����մϴ�." << endl;
	if (this->my_fee.getPPT() == 0) {
		cout << "������ ����� �����ϴ�." << endl;
	}
	else if (this->my_fee.getPPT() > a.checkFunds()) {
		cout << "�ܾ��� �����մϴ�." << endl;
	}
	else {
		a.withdraw(my_fee.getPPT());
	}
	return;
}