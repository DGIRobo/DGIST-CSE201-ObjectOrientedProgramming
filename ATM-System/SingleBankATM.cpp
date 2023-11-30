#include "SingleBankATM.h"

Single::Single(Bank* input_primary_bank, string input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4]) : ATM(input_primary_bank, input_serial_number, 1, input_lanuage_available, initial_fund) {
	for (int i = 0; i < 4; i++) {
		this->fee_list[i] = fees[i];
	}
}

int Single::deposit(Account* a){
	if (this->lang_setting == true) {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �Ա��� �� �����ϴ�." << endl;
			return -1;
		}
		cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
		if (*(fee_list[0]) == 0) {
			cout << "������ �����ᰡ �����ϴ�." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(fee_list[0])) / 1000;
			cout << "�����ᰡ �ԱݵǾ����ϴ�." << endl;
		}
		cout << "�Ա��� �����մϴ�." << endl;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Deposits cannot be made to accounts at other banks." << endl;
			return -1;
		}
		cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
		if (*(fee_list[0]) == 0) {
			cout << "There are no fees to pay." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(fee_list[0])) / 1000;
			cout << "The fee has been deposited." << endl;
		}
		cout << "Initiate deposit." << endl;
	}
	int deposit_method;
	int cash1000;
	int cash5000;
	int cash10000;
	int cash50000;
	if (this->lang_setting == true) {
		cout << "�Ա� ������ ������ �ּ���" << endl;
		cout << "[1] ����" << "   " << "[2] ��ǥ" << endl;
		deposit_method = no_error_range(lang_setting, 1, 2);
		if (deposit_method == 1) {
			cout << "�� ��Ⱑ ó���� �� �ִ� ������ �ż��� 50������Դϴ�." << endl << "1000������ ������ �ּ���." << endl;
			cash1000 = no_error(lang_setting);
			cout << "5000������ ������ �ּ���." << endl;
			cash5000 = no_error(lang_setting);
			cout << "10000������ ������ �ּ���." << endl;
			cash10000 = no_error(lang_setting);
			cout << "50000������ ������ �ּ���." << endl;
			cash50000 = no_error(lang_setting);
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "����� ó�� �Ѱ踦 �ʰ��Ͽ����ϴ�." << endl;
				return -1;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
		}
		else if (deposit_method == 2) {
			cout << "�� ��Ⱑ ó���� �� �ִ� ��ǥ�� �ż��� 50������Դϴ�. ��ǥ�� ������ �ּ���." << endl << "�ùٸ��� ���� ��ǥ�� �Է��ϸ� ������ �ߴܵ˴ϴ�." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				checks[i] = no_error(lang_setting);
				if (checks[i] < 100000) {
					checks[i] = 0;
					cout << "������ �ߴܵǾ����ϴ�. �Ա��� �����մϴ�." << endl;
					break;
				}
			}
			int check_sum = 0;
			for (int i = 0; i <= 50; i++) {
				if (checks[i] >= 100000) {
					check_sum += checks[i];
				}
				else break;
			}
			a->deposit(check_sum);
			cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl << "�Ա� ������ �ܰ�� " << setw(10) << a->checkFunds() << "�Դϴ�.";
			return check_sum;
		}
		else {
			cout << "������ �߻��߽��ϴ�. �Ա��� �ߴ��մϴ�." << endl;
			return -1;
		}
	}
	else {
		cout << "Please select deposit method" << endl;
		cout << "[1] cash" << "   " << "[2] check" << endl;
		int deposit_method = no_error_range(lang_setting, 1, 2);
		if (deposit_method == 1) {
			cout << "This device can process up to 50 cashes." << endl << "Please input 1000 won bills." << endl;
			cash1000 = no_error(lang_setting);
			cout << "Please input 5000 won bills." << endl;
			cash5000 = no_error(lang_setting);
			cout << "Please input 10000 won bills." << endl;
			cash10000 = no_error(lang_setting);
			cout << "Please input 50000 won bills." << endl;
			cash50000 = no_error(lang_setting);
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "The device's processing limit has been exceeded." << endl;
				return -1;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
		}
		else if (deposit_method == 2) {
			cout << "This device can process up to 50 checks. Please insert checks." << endl << "If you enter an incorrect check, the insertion will be ended." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				checks[i] = no_error(lang_setting);
				if (checks[i] < 100000) {
					checks[i] = 0;
					cout << "Insertion ended. deposit is starting." << endl;
					break;
				}
			}
			int check_sum = 0;
			for (int i = 0; i <= 50; i++) {
				if (checks[i] >= 100000) {
					check_sum += checks[i];
				}
				else break;
			}
			a->deposit(check_sum);
			cout << "Deposit has been completed." << endl << "The balance of the deposit account is " << setw(10) << a->checkFunds() << ".";
			return check_sum;
		}
		else {
			cout << "Error detected. Deposit will be stopped." << endl;
			return -1;
		}
	}
	return -1;
}

int Single::withdraw(Account* a) {
	if (this->lang_setting == true) {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���¿��� ����� �� �����ϴ�." << endl;
			return -1;
		}
		cout << "����� �����մϴ�." << endl;
		if (*(this->fee_list[1]) == 0) {
			cout << "������ ����� �����ϴ�." << endl;
		}
		else if (*(this->fee_list[1]) > a->checkFunds()) {
			cout << "�ܾ��� �����մϴ�." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[1]));
		}
		//this->withdraw(a);
		int amount;
		cout << "����� �׼��� 1000�� ��� ������ �Է��ϼ���. �ִ� �ݾ��� 50�����Դϴ�." << endl;
		cout << "����� �ܰ�� " << setw(10) << a->checkFunds() << "�� �Դϴ�." << endl;
		amount = no_error(lang_setting);
		if (amount > 500000) {
			cout << "50������ �ʰ��� �ݾ��� �Է��ϼ̽��ϴ�. ����� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount % 1000 != 0) {
			cout << "1000�� ����� �ƴ� �ݾ��� �Է��ϼ̽��ϴ�. ����� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount > a->checkFunds()) {
			cout << "���¿� �ܾ��� �����մϴ�. ����� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		int temp4 = amount / 50000;
		int temp3 = (amount % 50000) / 10000;
		int temp2 = (amount % 10000) / 5000;
		int temp1 = (amount % 5000) / 1000;
		if (temp4 > *(this->cash_storage[3])) {
			temp3 += 5 * (temp4 - *(this->cash_storage[3]));
		}
		if (temp3 > *(this->cash_storage[2])) {
			temp2 += 2 * (temp3 - *(this->cash_storage[2]));
		}
		if (temp2 > *(this->cash_storage[1])) {
			temp1 += 5 * (temp2 - *(this->cash_storage[1]));
		}
		if (temp1 > *(this->cash_storage[0])) {
			cout << "ATM�� ������ �����մϴ�. ����� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		else {
			*(this->cash_storage[3]) -= temp4;
			*(this->cash_storage[2]) -= temp3;
			*(this->cash_storage[1]) -= temp2;
			*(this->cash_storage[0]) -= temp1;
		}
		a->withdraw(amount);
		cout << "����� �Ϸ�Ǿ����ϴ�." << endl << "��� ������ �ܰ�� " << setw(10) << a->checkFunds() << "�Դϴ�.";
		return amount;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Withdrawals cannot be made from accounts at other banks." << endl;
			return -1;
		}
		cout << "Pay the fee." << endl;
		if (*(this->fee_list[1]) == 0) {
			cout << "There are no fees to pay." << endl;
		}
		else if (*(this->fee_list[1]) > a->checkFunds()) {
			cout << "Your balance is insufficient." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[1]));
		}
		//this->withdraw(a);
		int amount;
		cout << "Enter the amount you wish to withdraw in multiples of 1000. The maximum amount is 500,000 won." << endl;
		cout << "Your remaining fund is " << setw(10) << a->checkFunds() << "." << endl;
		amount = no_error(lang_setting);
		if (amount > 500000) {
			cout << "You entered an amount exceeding 500,000 won. Cancel withdrawal." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount % 1000 != 0) {
			cout << "You entered an amount that is not a multiple of 1000. Cancel withdrawal." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount > a->checkFunds()) {
			cout << "There are insufficient funds in your account. Cancel withdrawal." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		int temp4 = amount / 50000;
		int temp3 = (amount % 50000) / 10000;
		int temp2 = (amount % 10000) / 5000;
		int temp1 = (amount % 5000) / 1000;
		if (temp4 > *(this->cash_storage[3])) {
			temp3 += 5 * (temp4 - *(this->cash_storage[3]));
		}
		if (temp3 > *(this->cash_storage[2])) {
			temp2 += 2 * (temp3 - *(this->cash_storage[2]));
		}
		if (temp2 > *(this->cash_storage[1])) {
			temp1 += 5 * (temp2 - *(this->cash_storage[1]));
		}
		if (temp1 > *(this->cash_storage[0])) {
			cout << "The ATM is out of cash. Cancel withdrawal." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		else {
			*(this->cash_storage[3]) -= temp4;
			*(this->cash_storage[2]) -= temp3;
			*(this->cash_storage[1]) -= temp2;
			*(this->cash_storage[0]) -= temp1;
		}
		a->withdraw(amount);
		cout << "Withdrawal has been completed." << endl << "The balance of the withdrawal account is " << setw(10) << a->checkFunds() << ".";
		return amount;
	}
}

int Single::account_transfer(Account* a, Account* b) {
	if (this->lang_setting == false) {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "You cannot transfer money from an account at another bank." << endl;
			return -1;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Money cannot be transferred to another bank's account." << endl;
			return -1;
		}
		cout << "Pay the fee." << endl;
		if (*(this->fee_list[2]) == 0) {
			cout << "There are no fees to pay." << endl;
		}
		else if (*(this->fee_list[2]) > a->checkFunds()) {
			cout << "Your balance is insufficient." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[2]));
		}
		//this->account_transfer(a, b);
		int amount;
		cout << "Please enter the amount you wish to transfer." << endl;
		cout << "Your remaining fund is " << setw(10) << a->checkFunds() << "." << endl;
		amount = no_error(lang_setting);
		if (amount > a->checkFunds()) {
			cout << "Your balance is insufficient. Cancel the transfer." << endl;
			a->deposit(*(this->fee_list[2]));
			return -1;
		}
		a->withdraw(amount);
		b->deposit(amount);
		cout << "The transfer has been completed." << endl << "The balance of the source account is" << setw(10) << a->checkFunds() << ".";
		return amount;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���¿��� �۱��� �� �����ϴ�." << endl;
			return -1;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �۱��� �� �����ϴ�." << endl;
			return -1;
		}
		cout << "����� �����մϴ�." << endl;
		if (*(this->fee_list[2]) == 0) {
			cout << "������ ����� �����ϴ�." << endl;
		}
		else if (*(this->fee_list[2]) > a->checkFunds()) {
			cout << "�ܾ��� �����մϴ�." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[2]));
		}
		//this->account_transfer(a, b);
		int amount;
		cout << "�۱��� �׼��� �Է��� �ּ���." << endl;
		cout << "����� �ܰ�� " << setw(10) << a->checkFunds() << "�� �Դϴ�." << endl;
		amount = no_error(lang_setting);
		if (amount > a->checkFunds()) {
			cout << "�ܾ��� �����մϴ�. �۱��� ����մϴ�." << endl;
			a->deposit(*(this->fee_list[2]));
			return -1;
		}
		a->withdraw(amount);
		b->deposit(amount);
		cout << "�۱��� �Ϸ�Ǿ����ϴ�." << endl << "��� ������ �ܰ�� " << setw(10) << a->checkFunds() << "�Դϴ�.";
		return amount;
	}
}

int Single::cash_transfer(Account* b) {
	if (this->lang_setting == false) {
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Money cannot be transferred to another bank's account." << endl;
			return -1;
		}
		cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
		if (*(this->fee_list[3]) == 0) {
			cout << "There are no fees to pay." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
			cout << "The fee has been deposited." << endl;
		}
		cout << "Initiate cash transfer." << endl;
		cout << "Please insert a 1,000 won bill." << endl;
		int cash1000 = no_error(lang_setting);
		cout << "Please insert a 5,000 won bill." << endl;
		int cash5000 = no_error(lang_setting);
		cout << "Please insert a 10,000 won bill." << endl;
		int cash10000 = no_error(lang_setting);
		cout << "Please insert a 50,000 won bill." << endl;
		int cash50000 = no_error(lang_setting);
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "The transfer has been completed." << endl;
		return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
	}
	else {
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �۱��� �� �����ϴ�." << endl;
			return -1;
		}
		cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
		if (*(this->fee_list[3]) == 0) {
			cout << "������ �����ᰡ �����ϴ�." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
			cout << "�����ᰡ �ԱݵǾ����ϴ�." << endl;
		}
		cout << "���� �۱��� �����մϴ�." << endl;
		cout << "1000������ ������ �ּ���." << endl;
		int cash1000 = no_error(lang_setting);;
		cout << "5000������ ������ �ּ���." << endl;
		int cash5000 = no_error(lang_setting);;
		cout << "10000������ ������ �ּ���." << endl;
		int cash10000 = no_error(lang_setting);;
		cout << "50000������ ������ �ּ���." << endl;
		int cash50000 = no_error(lang_setting);;
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "�۱��� �Ϸ�Ǿ����ϴ�." << endl;
		return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
	}
}

Account* Single::card2account(string card, vector<Bank*> bank_list) {
	bool isPrimary = false;
	Account* ac = 0;
	for (int i = 0; i < primary_bank->get_account().size(); i++) {
		vector<string> card_list = primary_bank->get_account()[i]->getCardNumber();
		for (int j = 0; j < card_list.size(); j++) {
			if (card_list[j] == card) {
				isPrimary = true;
				ac = primary_bank->get_account()[i];
				break;
			}
		}
	}
	if (isPrimary == false) {
		if (this->lang_setting == 1) { cout << "�������� �ʴ� ī���Դϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Unsupported card." << endl; }
		return nullptr;
	}
	return ac;
}

Account* Single::num2account(string num, vector<Bank*> bank_list) {
	bool isPrimary = false;
	Account* ac = 0;
	for (int i = 0; i < primary_bank->get_account().size(); i++) {
		string acc_num = primary_bank->get_account()[i]->getAccountNumber();
		if (acc_num == num) {
			isPrimary = true;
			ac = primary_bank->get_account()[i];
			break;
		}
	}
	if (isPrimary == false) {
		if (this->lang_setting == 1) { cout << "�������� �ʴ� �����Դϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Unsupported account." << endl; }
		return nullptr;
	}
	return ac;
}

string Single::getType() {
	return "Single-bank ATM";
}