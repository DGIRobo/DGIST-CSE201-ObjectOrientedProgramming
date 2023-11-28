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
			cout << "타 은행의 계좌로 입금합니다." << endl;
			account_count = 1;
		}
		else {
			cout << "본 은행의 계좌로 입금합니다." << endl;
		}
		if (account_count == 0) {
			cout << "요금을 지불합니다." << endl << "수수료를 입금해 주세요." << endl;
			if (*(this->fee_list[0]) == 0) {
				cout << "지불할 수수료가 없습니다." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->fee_list[0])) / 1000;
				cout << "수수료가 입금되었습니다." << endl;
			}
			cout << "입금을 개시합니다." << endl;
		}
		else {
			cout << "요금을 지불합니다." << endl << "수수료를 입금해 주세요." << endl;
			if (*(this->multi_fee_list[0]) == 0) {
				cout << "지불할 수수료가 없습니다." << endl;
			}
			else {
				*(this->cash_storage[0]) += (*(this->multi_fee_list[0])) / 1000;
				cout << "수수료가 입금되었습니다." << endl;
			}
			cout << "입금을 개시합니다." << endl;
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
		cout << "입금 수단을 선택해 주세요" << endl;
		cout << "[1] 현금" << "   " << "[2] 수표" << endl;
		cin >> deposit_method;
		if (deposit_method == 1) {
			cout << "본 기기가 처리할 수 있는 지폐의 매수는 50장까지입니다." << endl << "1000원권을 투입해 주세요." << endl;
			cin >> cash1000;
			cout << "5000원권을 투입해 주세요." << endl;
			cin >> cash5000;
			cout << "10000원권을 투입해 주세요." << endl;
			cin >> cash10000;
			cout << "50000원권을 투입해 주세요." << endl;
			cin >> cash50000;
			if (cash1000 + cash5000 + cash10000 + cash50000 > 51) {
				cout << "기기의 처리 한계를 초과하였습니다." << endl;
				return;
			}
			add_cash(cash1000, cash5000, cash10000, cash50000);
			a->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
			return;
		}
		else if (deposit_method == 2) {
			cout << "본 기기가 처리할 수 있는 수표의 매수는 50장까지입니다. 수표를 투입해 주세요." << endl << "올바르지 않은 수표를 입력하면 투입이 중단됩니다." << endl;
			int checks[50];
			for (int i = 0; i <= 50; i++) {
				cin >> checks[i];
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
			return;
		}
		else {
			cout << "오류가 발생했습니다. 입금을 중단합니다." << endl;
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
			cout << "타 은행의 계좌에서 출금합니다." << endl;
			coconut = 1;
		}
		else {
			cout << "본 은행의 계좌에서 출금합니다." << endl;
		}
		cout << "요금을 지불합니다." << endl;
		if (coconut == 0) {
			if (*(this->fee_list[1]) == 0) {
				cout << "지불할 요금이 없습니다." << endl;
			}
			else if (*(this->fee_list[1]) > a->checkFunds()) {
				cout << "잔액이 부족합니다." << endl;
				return;
			}
			else {
				a->withdraw(*(this->fee_list[1]));
			}
		}
		else {
			if (*(this->multi_fee_list[1]) == 0) {
				cout << "지불할 요금이 없습니다." << endl;
			}
			else if (*(this->multi_fee_list[1]) > a->checkFunds()) {
				cout << "잔액이 부족합니다." << endl;
				return;
			}
			else {
				a->withdraw(*(this->multi_fee_list[1]));
			}
		}
		//this->withdraw(a);
		int amount;
		cout << "출금할 액수를 1000의 배수 단위로 입력하세요. 최대 금액은 50만원입니다." << endl;
		cin >> amount;
		if (amount > 500000) {
			cout << "50만원을 초과한 금액을 입력하셨습니다. 출금을 취소합니다." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
		}
		if (amount % 1000 != 0) {
			cout << "1000의 배수가 아닌 금액을 입력하셨습니다. 출금을 취소합니다." << endl;
			if (coconut == 0) {
				a->deposit(*(this->fee_list[1]));
			}
			else {
				a->deposit(*(this->multi_fee_list[1]));
			}
			return;
		}
		if (amount > a->checkFunds()) {
			cout << "계좌에 잔액이 부족합니다. 출금을 취소합니다." << endl;
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
			cout << "ATM에 현금이 부족합니다. 출금을 취소합니다." << endl;
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
		cout << "출금이 완료되었습니다." << endl << "출금 계좌의 잔고는 " << a->checkFunds() << "입니다.";
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
			cout << "타 은행의 계좌에서 송금합니다." << endl;
			coconut = 1;
		}
		else {
			cout << "본 은행의 계좌에서 송금합니다." << endl;
		}
		if (b->getBankName() != this->primary_bank->getBankName()) {
			cout << "타 은행의 계좌로 송금합니다." << endl;
			cococonut = 1;
		}
		else {
			cout << "본 은행의 계좌로 송금합니다." << endl;
		}
		cout << "요금을 지불합니다." << endl;
		if (coconut == 0 && cococonut == 0) {
			if (*(this->fee_list[2]) == 0) {
				cout << "지불할 요금이 없습니다." << endl;
			}
			else if (*(this->fee_list[2]) > a->checkFunds()) {
				cout << "잔액이 부족합니다." << endl;
				return;
			}
			else {
				a->withdraw(*(this->fee_list[2]));
			}
		}
		else if (coconut == 1 && cococonut == 1) {
			if (*(this->multi_fee_list[3]) == 0) {
				cout << "지불할 요금이 없습니다." << endl;
			}
			else if (*(this->multi_fee_list[3]) > a->checkFunds()) {
				cout << "잔액이 부족합니다." << endl;
				return;
			}
			else {
				a->withdraw(*(this->multi_fee_list[3]));
			}
		}
		else {
			if (*(this->multi_fee_list[2]) == 0) {
				cout << "지불할 요금이 없습니다." << endl;
			}
			else if (*(this->multi_fee_list[2]) > a->checkFunds()) {
				cout << "잔액이 부족합니다." << endl;
				return;
			}
			else {
				a->withdraw(*(this->multi_fee_list[2]));
			}
		}
		//this->account_transfer(a, b);
		int amount;
		cout << "송금할 액수를 입력해 주세요." << endl;
		cin >> amount;
		if (amount > a->checkFunds()) {
			cout << "잔액이 부족합니다. 송금을 취소합니다." << endl;
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
		cout << "송금이 완료되었습니다." << endl << "출금 계좌의 잔고는 " << a->checkFunds() << "입니다.";
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
		cout << "요금을 지불합니다." << endl << "수수료를 입금해 주세요." << endl;
		*(this->cash_storage[0]) += (*(this->fee_list[3])) / 1000;
		cout << "수수료가 입금되었습니다. 현금 송금을 개시합니다." << endl;
		//this->cash_transfer(b);
		int cash1000;
		int cash5000;
		int cash10000;
		int cash50000;
		cout << "1000원권을 투입해 주세요." << endl;
		cin >> cash1000;
		cout << "5000원권을 투입해 주세요." << endl;
		cin >> cash5000;
		cout << "10000원권을 투입해 주세요." << endl;
		cin >> cash10000;
		cout << "50000원권을 투입해 주세요." << endl;
		cin >> cash50000;
		add_cash(cash1000, cash5000, cash10000, cash50000);
		b->deposit((cash1000 * 1000) + (cash5000 * 5000) + (cash10000 * 10000) + (cash50000 * 50000));
		cout << "송금이 완료되었습니다." << endl;
		return;
	}
}

void Multi::session(vector<Bank*> bank_list) {

	if (this->language_setting == "Korean") {
		cout << "카드를 삽입해 주세요." << endl;
		string cardinsert;
		cin >> cardinsert;
		if (cardinsert == this->admin_card) {
			see_transaction_history();
			return;
		}
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
			cout << "잘못된 카드입니다." << endl;
			return;
		}
		Account* acc = 0;
		for (int i = 0; i < bank_list[banknum]->get_account().size(); i++) {
			vector<string> card_list = bank_list[banknum]->get_account()[i]->getCardNumber();
			for (int j = 0; j < card_list.size(); j++) {
				if (card_list[j] == cardinsert) {
					acc = bank_list[banknum]->get_account()[i];
					break;
				}
			}
		}
		if (this->user_authorization(acc) == false) {
			cout << "비밀번호 입력에 3회 실패하셨습니다. 거래를 종료합니다." << endl;
			return;
		}
		cout << this->getSerial() << "번 ATM에 접속하셨습니다. 무슨 작업을 도와드릴까요?" << endl;
		cout << "[1] 입금" << endl << "[2] 출금" << endl << "[3] 계좌 송금" << endl << "[4] 현금 송금" << endl << "[5] 언어 변경" << endl << "[6] (관리자 메뉴) 거래 내역 확인" << endl;
		int selection = 1;
		switch (selection) {
		case 1:
			int pass;
			cout << "입금을 선택하셨습니다. 거래를 위해서는 비밀번호를 입력해 주세요 : ";
			cin >> pass;
			//this->user_authorization();
			cout << "비밀번호가 확인되었습니다. 거래를 진행합니다." << endl;
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