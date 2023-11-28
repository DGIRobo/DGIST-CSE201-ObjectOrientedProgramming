#include "MultiBankATM.h"

Multi::Multi(Bank* input_primary_bank, int input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4], int* fees2[4]) : ATM(input_primary_bank, input_serial_number, 2, input_lanuage_available, initial_fund) {
	for (int i = 0; i < 4; i++) {
		this->fee_list[i] = fees[i];
	}
	for (int i = 0; i < 4; i++) {
		this->multi_fee_list[i] = fees2[i];
	}
}

void Multi::deposit(Account* a) {
	int account_count = 0;
	if (this->language_setting == "Korean") {
		if (a->getBankName() == this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �Ա��մϴ�." << endl;
			account_count = 1;
		}
		else {
			cout << "�� ������ ���·� �Ա��մϴ�." << endl;
		}
		if (account_count == 0) {
			cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
			if (*(this->fee_list[0]) == 0) {
				cout << "������ �����ᰡ �����ϴ�." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->fee_list[0])) / 1000;
				cout << "�����ᰡ �ԱݵǾ����ϴ�." << endl;
			}
			cout << "�Ա��� �����մϴ�." << endl;
		}
		else {
			cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
			if (*(this->multi_fee_list[0]) == 0) {
				cout << "������ �����ᰡ �����ϴ�." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->multi_fee_list[0])) / 1000;
				cout << "�����ᰡ �ԱݵǾ����ϴ�." << endl;
			}
			cout << "�Ա��� �����մϴ�." << endl;
		}
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Deposits will be made to accounts at other banks." << endl;
			account_count = 1;
			return;
		}
		if (account_count == 0) {
			cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
			if (*(this->fee_list[0]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->fee_list[0])) / 1000;
				cout << "The fee has been deposited." << endl;
			}
			cout << "Initiate deposit." << endl;
		}
		else {
			cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
			if (*(this->multi_fee_list[0]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->multi_fee_list[0])) / 1000;
				cout << "The fee has been deposited." << endl;
			}
			cout << "Initiate deposit." << endl;
		}
	}
	int deposit_method;
	int cash1000;
	int cash5000;
	int cash10000;
	int cash50000;
	if (this->language_setting == "Korean") {
		cout << "�Ա� ������ ������ �ּ���" << endl;
		cout << "[1] ����" << "   " << "[2] ��ǥ" << endl;
		cin >> deposit_method;
		if (deposit_method == 1) {
			cout << "�� ��Ⱑ ó���� �� �ִ� ������ �ż��� 50������Դϴ�." << endl << "1000������ ������ �ּ���." << endl;
			cin >> cash1000;
			cout << "5000������ ������ �ּ���." << endl;
			cin >> cash5000;
			cout << "10000������ ������ �ּ���." << endl;
			cin >> cash10000;
			cout << "50000������ ������ �ּ���." << endl;
			cin >> cash50000;
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "����� ó�� �Ѱ踦 �ʰ��Ͽ����ϴ�." << endl;
				return;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			return;
		}
		else if (deposit_method == 2) {
			cout << "�� ��Ⱑ ó���� �� �ִ� ��ǥ�� �ż��� 50������Դϴ�. ��ǥ�� ������ �ּ���." << endl << "�ùٸ��� ���� ��ǥ�� �Է��ϸ� ������ �ߴܵ˴ϴ�." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				cin >> checks[i];
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
			return;
		}
		else {
			cout << "������ �߻��߽��ϴ�. �Ա��� �ߴ��մϴ�." << endl;
			return;
		}
	}
	if (this->language_setting == "English") {
		cout << "Please select deposit method" << endl;
		cout << "[1] cash" << "   " << "[2] check" << endl;
		int deposit_method;
		cin >> deposit_method;
		if (deposit_method == 1) {
			cout << "This device can process up to 50 cashes." << endl << "Please input 1000 won bills." << endl;
			cin >> cash1000;
			cout << "Please input 5000 won bills." << endl;
			cin >> cash5000;
			cout << "Please input 10000 won bills." << endl;
			cin >> cash10000;
			cout << "Please input 50000 won bills." << endl;
			cin >> cash50000;
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "The device's processing limit has been exceeded." << endl;
				return;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			return;
		}
		else if (deposit_method == 2) {
			cout << "This device can process up to 50 checks. Please insert checks." << endl << "If you enter an incorrect check, the insertion will be ended." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				cin >> checks[i];
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
			return;
		}
		else {
			cout << "Error detected. Deposit will be stopped." << endl;
			return;
		}
	}
	return;
}

void Multi::withdraw(Account* a) {
	int coconut = 0;
	if (this->language_setting == "Korean") {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���¿��� ����մϴ�." << endl;
			coconut = 1;
		}
		else {
			cout << "�� ������ ���¿��� ����մϴ�." << endl;
		}
		cout << "����� �����մϴ�." << endl;
		if (coconut == 0) {
			if (*(this->fee_list[1]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->fee_list[1]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return;
			}
			else {
				a->withdraw(*(this->fee_list[1]));
			}
		}
		else {
			if (*(this->multi_fee_list[1]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->multi_fee_list[1]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return;
			}
			else {
				a->withdraw(*(this->multi_fee_list[1]));
			}
		}
		//this->withdraw(a);
		int amount;
		cout << "����� �׼��� 1000�� ��� ������ �Է��ϼ���. �ִ� �ݾ��� 50�����Դϴ�." << endl;
		cin >> amount;
		if (amount > 500000) {
			cout << "50������ �ʰ��� �ݾ��� �Է��ϼ̽��ϴ�. ����� ����մϴ�." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
		}
		if (amount % 1000 != 0) {
			cout << "1000�� ����� �ƴ� �ݾ��� �Է��ϼ̽��ϴ�. ����� ����մϴ�." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
		}
		if (amount > a->checkFunds()) {
			cout << "���¿� �ܾ��� �����մϴ�. ����� ����մϴ�." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
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
			temp1 += 5 * (temp2 - *(this->cash_storage[0]));
		}
		if (temp1 > *(this->cash_storage[0])) {
			cout << "ATM�� ������ �����մϴ�. ����� ����մϴ�." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
		}
		else {
			*(this->cash_storage[3]) -= temp4;
			*(this->cash_storage[2]) -= temp3;
			*(this->cash_storage[1]) -= temp2;
			*(this->cash_storage[0]) -= temp1;
		}
		a->withdraw(amount);
		cout << "����� �Ϸ�Ǿ����ϴ�." << endl << "��� ������ �ܰ�� " << a->checkFunds() << "�Դϴ�.";
		return;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Withdrawals will be made from accounts at other banks." << endl;
			coconut = 1;
		}
		else {
			cout << "Withdrawals will be made from accounts at this banks." << endl;
		}
		if (coconut == 0) {
			cout << "Pay the fee." << endl;
			if (*(this->fee_list[1]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->fee_list[1]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return;
			}
			else {
				a->withdraw(*(this->fee_list[1]));
			}
		}
		else {
			cout << "Pay the fee." << endl;
			if (*(this->multi_fee_list[1]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->multi_fee_list[1]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return;
			}
			else {
				a->withdraw(*(this->multi_fee_list[1]));
			}
		}
		//this->withdraw(a);
		int amount;
		cout << "Enter the amount you wish to withdraw in multiples of 1000. The maximum amount is 500,000 won." << endl;
		cin >> amount;
		if (amount > 500000) {
			cout << "You entered an amount exceeding 500,000 won. Cancel withdrawal." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
		}
		if (amount % 1000 != 0) {
			cout << "You entered an amount that is not a multiple of 1000. Cancel withdrawal." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
		}
		if (amount > a->checkFunds()) {
			cout << "There are insufficient funds in your account. Cancel withdrawal." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
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
			temp1 += 5 * (temp2 - *(this->cash_storage[0]));
		}
		if (temp1 > *(this->cash_storage[0])) {
			cout << "The ATM is out of cash. Cancel withdrawal." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
		}
		else {
			*(this->cash_storage[3]) -= temp4;
			*(this->cash_storage[2]) -= temp3;
			*(this->cash_storage[1]) -= temp2;
			*(this->cash_storage[0]) -= temp1;
		}
		a->withdraw(amount);
		cout << "Withdrawal has been completed." << endl << "The balance of the withdrawal account is " << a->checkFunds() << ".";
		return;
	}
}

void Multi::account_transfer(Account* a, Account* b) {
	int coconut = 0;
	int cococonut = 0;
	if (this->language_setting == "English") {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Transfer money from an account at another bank." << endl;
			coconut = 1;
		}
		else {
			cout << "Transfer money from an account at this bank." << endl;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Transferred to another bank's account." << endl;
			cococonut = 1;
		}
		else {
			cout << "Transferred to this bank's account." << endl;
		}
		if (coconut == 0 && cococonut == 0) {
			cout << "Pay the fee." << endl;
			if (*(this->fee_list[2]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->fee_list[2]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return;
			}
			else {
				a->withdraw(*(this->fee_list[2]));
			}
		}
		if (coconut == 1 && cococonut == 1) {
			cout << "Pay the fee." << endl;
			if (*(this->multi_fee_list[3]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->multi_fee_list[3]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return;
			}
			else {
				a->withdraw(*(this->multi_fee_list[3]));
			}
		}
		else {
			cout << "Pay the fee." << endl;
			if (*(this->multi_fee_list[2]) == 0) {
				cout << "There are no fees to pay." << endl;
			}
			else if (*(this->multi_fee_list[2]) > a->checkFunds()) {
				cout << "Your balance is insufficient." << endl;
				return;
			}
			else {
				a->withdraw(*(this->multi_fee_list[2]));
			}
		}
		//this->account_transfer(a, b);
		int amount;
		cout << "Please enter the amount you wish to transfer." << endl;
		cin >> amount;
		if (amount > a->checkFunds()) {
			cout << "Your balance is insufficient. Cancel the transfer." << endl;
			if (coconut == 0 && cococonut == 0) {
				a->deposit(*(this->fee_list[2]));
			}
			else if (coconut == 1 && cococonut == 1) {
				a->deposit(*(this->multi_fee_list[3]));
			}
			else {
				a->deposit(*(this->multi_fee_list[2]));
			}
			return;
		}
		a->withdraw(amount);
		b->deposit(amount);
		cout << "The transfer has been completed." << endl << "The balance of the source account is" << a->checkFunds() << ".";
		return;
	}
	else {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���¿��� �۱��մϴ�." << endl;
			coconut = 1;
		}
		else {
			cout << "�� ������ ���¿��� �۱��մϴ�." << endl;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "Ÿ ������ ���·� �۱��մϴ�." << endl;
			cococonut = 1;
		}
		else {
			cout << "�� ������ ���·� �۱��մϴ�." << endl;
		}
		cout << "����� �����մϴ�." << endl;
		if (coconut == 0 && cococonut == 0) {
			if (*(this->fee_list[2]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->fee_list[2]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return;
			}
			else {
				a->withdraw(*(this->fee_list[2]));
			}
		}
		else if (coconut == 1 && cococonut == 1) {
			if (*(this->multi_fee_list[3]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->multi_fee_list[3]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return;
			}
			else {
				a->withdraw(*(this->multi_fee_list[3]));
			}
		}
		else {
			if (*(this->multi_fee_list[2]) == 0) {
				cout << "������ ����� �����ϴ�." << endl;
			}
			else if (*(this->multi_fee_list[2]) > a->checkFunds()) {
				cout << "�ܾ��� �����մϴ�." << endl;
				return;
			}
			else {
				a->withdraw(*(this->multi_fee_list[2]));
			}
		}
		//this->account_transfer(a, b);
		int amount;
		cout << "�۱��� �׼��� �Է��� �ּ���." << endl;
		cin >> amount;
		if (amount > a->checkFunds()) {
			cout << "�ܾ��� �����մϴ�. �۱��� ����մϴ�." << endl;
			if (coconut == 0 && cococonut == 0) {
				a->deposit(*(this->fee_list[2]));
			}
			else if (coconut == 0 && cococonut == 0) {
				a->deposit(*(this->multi_fee_list[3]));
			}
			else {
				a->deposit(*(this->multi_fee_list[2]));
			}
			return;
		}
		a->withdraw(amount);
		b->deposit(amount);
		cout << "�۱��� �Ϸ�Ǿ����ϴ�." << endl << "��� ������ �ܰ�� " << a->checkFunds() << "�Դϴ�.";
		return;
	}
}

void Multi::cash_transfer(Account* b) {
	if (this->language_setting == "English") {
		cout << "Pay the fee." << endl << "Please deposit the fee." << endl;
		*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
		cout << "The fee has been deposited. Initiate cash transfer." << endl;
		//this->cash_transfer(b);
		int cash1000;
		int cash5000;
		int cash10000;
		int cash50000;
		cout << "Please insert a 1,000 won bill." << endl;
		cin >> cash1000;
		cout << "Please insert a 5,000 won bill." << endl;
		cin >> cash5000;
		cout << "Please insert a 10,000 won bill." << endl;
		cin >> cash10000;
		cout << "Please insert a 50,000 won bill." << endl;
		cin >> cash50000;
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "The transfer has been completed." << endl;
		return;
	}
	else {
		cout << "����� �����մϴ�." << endl << "�����Ḧ �Ա��� �ּ���." << endl;
		*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
		cout << "�����ᰡ �ԱݵǾ����ϴ�. ���� �۱��� �����մϴ�." << endl;
		//this->cash_transfer(b);
		int cash1000;
		int cash5000;
		int cash10000;
		int cash50000;
		cout << "1000������ ������ �ּ���." << endl;
		cin >> cash1000;
		cout << "5000������ ������ �ּ���." << endl;
		cin >> cash5000;
		cout << "10000������ ������ �ּ���." << endl;
		cin >> cash10000;
		cout << "50000������ ������ �ּ���." << endl;
		cin >> cash50000;
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "�۱��� �Ϸ�Ǿ����ϴ�." << endl;
		return;
	}
}

void Multi::session(vector<Bank*> bank_list) {

	if (this->language_setting == "Korean") {
		cout << "ī�带 ������ �ּ���." << endl;
		string cardinsert;
		cin >> cardinsert;
		int banknum = -1;
		for (int k = 0; k < bank_list.size(); k++) {
			for (int i = 0; i < primary_bank->get_account().size(); i++) {
				vector<string> card_list = primary_bank->get_account()[i]->getCardNumber();
				for (int j = 0; j < card_list.size(); j++) {
					if (card_list[j] == cardinsert) {
						banknum = i;
						break;
					}
				}
				if (banknum == i) { break; }
			}
			if (banknum != -1) { break; }
		}
		if (banknum == -1) {
			cout << "�߸��� ī���Դϴ�." << endl;
			return;
		}
		Account* acc;
		for (int i = 0; i < bank_list[banknum]->get_account().size(); i++) {
			vector<string> card_list = bank_list[banknum]->get_account()[i]->getCardNumber();
			for (int j = 0; j < card_list.size(); j++) {
				if (card_list[j] == cardinsert) {
					acc = bank_list[banknum]->get_account()[i];
					break;
				}
			}
		}
		cout << this->getSerial() << "�� ATM�� �����ϼ̽��ϴ�. ���� �۾��� ���͵帱���?" << endl;
		cout << "[1] �Ա�" << endl << "[2] ���" << endl << "[3] ���� �۱�" << endl << "[4] ���� �۱�" << endl << "[5] ��� ����" << endl << "[6] (������ �޴�) �ŷ� ���� Ȯ��" << endl;
		int selection = 1;
		switch (selection) {
		case 1:
			int pass;
			cout << "�Ա��� �����ϼ̽��ϴ�. �ŷ��� ���ؼ��� ��й�ȣ�� �Է��� �ּ��� : ";
			cin >> pass;
			//this->user_authorization();
			cout << "��й�ȣ�� Ȯ�εǾ����ϴ�. �ŷ��� �����մϴ�." << endl;
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