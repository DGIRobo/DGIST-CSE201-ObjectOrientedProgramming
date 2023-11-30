#include "SingleBankATM.h"

Single::Single(Bank* input_primary_bank, string input_serial_number, int input_lanuage_available, int* initial_fund[], int* fees[4]) : ATM(input_primary_bank, input_serial_number, 1, input_lanuage_available, initial_fund) {
	for (int i = 0; i < 4; i++) {
		this->fee_list[i] = fees[i];
	}
}

int Single::deposit(Account* a){
	if (this->lang_setting == true) {
		if (a->getBankName() != this->primary_bank->getBankName()) {
			cout << "타 은행의 계좌로 입금할 수 없습니다." << endl;
			return -1;
		}
		cout << "요금을 지불합니다." << endl << "수수료를 입금해 주세요." << endl;
		if (*(fee_list[0]) == 0) {
			cout << "지불할 수수료가 없습니다." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(fee_list[0])) / 1000;
			cout << "수수료가 입금되었습니다." << endl;
		}
		cout << "입금을 개시합니다." << endl;
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
		cout << "입금 수단을 선택해 주세요" << endl;
		cout << "[1] 현금" << "   " << "[2] 수표" << endl;
		deposit_method = no_error_range(lang_setting, 1, 2);
		if (deposit_method == 1) {
			cout << "본 기기가 처리할 수 있는 지폐의 매수는 50장까지입니다." << endl << "1000원권을 투입해 주세요." << endl;
			cash1000 = no_error(lang_setting);
			cout << "5000원권을 투입해 주세요." << endl;
			cash5000 = no_error(lang_setting);
			cout << "10000원권을 투입해 주세요." << endl;
			cash10000 = no_error(lang_setting);
			cout << "50000원권을 투입해 주세요." << endl;
			cash50000 = no_error(lang_setting);
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "기기의 처리 한계를 초과하였습니다." << endl;
				return -1;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			return (cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000);
		}
		else if (deposit_method == 2) {
			cout << "본 기기가 처리할 수 있는 수표의 매수는 50장까지입니다. 수표를 투입해 주세요." << endl << "올바르지 않은 수표를 입력하면 투입이 중단됩니다." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				checks[i] = no_error(lang_setting);
				if (checks[i] < 100000) {
					checks[i] = 0;
					cout << "투입이 중단되었습니다. 입금을 시작합니다." << endl;
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
			cout << "입금이 완료되었습니다." << endl << "입금 계좌의 잔고는 " << setw(10) << a->checkFunds() << "입니다.";
			return check_sum;
		}
		else {
			cout << "오류가 발생했습니다. 입금을 중단합니다." << endl;
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
			cout << "타 은행의 계좌에서 출금할 수 없습니다." << endl;
			return -1;
		}
		cout << "요금을 지불합니다." << endl;
		if (*(this->fee_list[1]) == 0) {
			cout << "지불할 요금이 없습니다." << endl;
		}
		else if (*(this->fee_list[1]) > a->checkFunds()) {
			cout << "잔액이 부족합니다." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[1]));
		}
		//this->withdraw(a);
		int amount;
		cout << "출금할 액수를 1000의 배수 단위로 입력하세요. 최대 금액은 50만원입니다." << endl;
		cout << "당신의 잔고는 " << setw(10) << a->checkFunds() << "원 입니다." << endl;
		amount = no_error(lang_setting);
		if (amount > 500000) {
			cout << "50만원을 초과한 금액을 입력하셨습니다. 출금을 취소합니다." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount % 1000 != 0) {
			cout << "1000의 배수가 아닌 금액을 입력하셨습니다. 출금을 취소합니다." << endl;
			a->deposit(*(this->fee_list[1]));
			return -1;
		}
		if (amount > a->checkFunds()) {
			cout << "계좌에 잔액이 부족합니다. 출금을 취소합니다." << endl;
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
			cout << "ATM에 현금이 부족합니다. 출금을 취소합니다." << endl;
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
		cout << "출금이 완료되었습니다." << endl << "출금 계좌의 잔고는 " << setw(10) << a->checkFunds() << "입니다.";
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
			cout << "타 은행의 계좌에서 송금할 수 없습니다." << endl;
			return -1;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "타 은행의 계좌로 송금할 수 없습니다." << endl;
			return -1;
		}
		cout << "요금을 지불합니다." << endl;
		if (*(this->fee_list[2]) == 0) {
			cout << "지불할 요금이 없습니다." << endl;
		}
		else if (*(this->fee_list[2]) > a->checkFunds()) {
			cout << "잔액이 부족합니다." << endl;
			return -1;
		}
		else {
			a->withdraw(*(this->fee_list[2]));
		}
		//this->account_transfer(a, b);
		int amount;
		cout << "송금할 액수를 입력해 주세요." << endl;
		cout << "당신의 잔고는 " << setw(10) << a->checkFunds() << "원 입니다." << endl;
		amount = no_error(lang_setting);
		if (amount > a->checkFunds()) {
			cout << "잔액이 부족합니다. 송금을 취소합니다." << endl;
			a->deposit(*(this->fee_list[2]));
			return -1;
		}
		a->withdraw(amount);
		b->deposit(amount);
		cout << "송금이 완료되었습니다." << endl << "출금 계좌의 잔고는 " << setw(10) << a->checkFunds() << "입니다.";
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
			cout << "타 은행의 계좌로 송금할 수 없습니다." << endl;
			return -1;
		}
		cout << "요금을 지불합니다." << endl << "수수료를 입금해 주세요." << endl;
		if (*(this->fee_list[3]) == 0) {
			cout << "지불할 수수료가 없습니다." << endl;
		}
		else {
			*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
			cout << "수수료가 입금되었습니다." << endl;
		}
		cout << "현금 송금을 개시합니다." << endl;
		cout << "1000원권을 투입해 주세요." << endl;
		int cash1000 = no_error(lang_setting);;
		cout << "5000원권을 투입해 주세요." << endl;
		int cash5000 = no_error(lang_setting);;
		cout << "10000원권을 투입해 주세요." << endl;
		int cash10000 = no_error(lang_setting);;
		cout << "50000원권을 투입해 주세요." << endl;
		int cash50000 = no_error(lang_setting);;
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "송금이 완료되었습니다." << endl;
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
		if (this->lang_setting == 1) { cout << "지원되지 않는 카드입니다." << endl; }
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
		if (this->lang_setting == 1) { cout << "지원되지 않는 계좌입니다." << endl; }
		if (this->lang_setting == 0) { cout << "Unsupported account." << endl; }
		return nullptr;
	}
	return ac;
}

string Single::getType() {
	return "Single-bank ATM";
}