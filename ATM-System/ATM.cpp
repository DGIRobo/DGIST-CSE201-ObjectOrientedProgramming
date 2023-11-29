#include "ATM.h"

int ATM::static_ATM_counter = 0;
int ATM::static_transaction_counter = 0;

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
		//this->language_setting = "Korean";
		this->lang_setting = true;
	}
	if (input_language_setting == 1) {
		//this->language_setting = "English";
		this->lang_setting = false;
	}
	return;
}

ATM::ATM(Bank* input_primary_bank, string input_serial_number, int input_type, int input_lanuage_available, int* initial_fund[]) {
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
	this->serial_number = "";
	this->type = 0;
	this->language_available = 0;

	for (int i = 0; i < 4; ++i) {
		this->cash_storage[i] = 0;
	}
}

void ATM::session(vector<Bank*> bank_list) {
	if (this->lang_setting == true) { cout << "카드를 삽입해 주세요." << endl; }
	if (this->lang_setting == false) { cout << "Please insert your card." << endl; }
	string cardinsert;
	cin >> cardinsert;
	if (cardinsert == this->admin_card) {
		see_transaction_history();
		return;
	}
	Account* acc = card2account(cardinsert, bank_list);
	if (acc == nullptr) {
		if (this->lang_setting == 1) { cout << "잘못된 카드가 입력되었습니다. 카드를 반환합니다." << endl; }
		if (this->lang_setting == 0) { cout << "Wrong card has inserted. Card will be return." << endl; }
		return;
	}
	if (this->user_authorization(acc) == false) {
		if (this->lang_setting == 1) { cout << "비밀번호 입력에 3회 실패하셨습니다. 거래를 종료합니다." << endl; }
		if (this->lang_setting == 0) { cout << "Failed to enter password 3 times. Transaction will be canceled." << endl; }
		return;
	}
	int rec;
	while (true) {
		rec = transaction(acc, bank_list);
		if (rec == -1) {
			break;
		}
	}
	return;
}

int ATM::transaction(Account* a, vector<Bank*> bank_list) {
	if (this->lang_setting == 1) { cout << this->getSerial() << "번 ATM에 접속하셨습니다. 무슨 작업을 도와드릴까요?" << endl; }
	if (this->lang_setting == 0) { cout << "You've accessed ATM number " << this->getSerial() << ".What can we do for you ? " << endl; }
	if (this->lang_setting == 1) { cout << "[1] 입금" << endl << "[2] 출금" << endl << "[3] 계좌 송금" << endl << "[4] 현금 송금" << endl << "[5] 언어 변경" << endl; }
	if (this->lang_setting == 0) { cout << "[1] deposit" << endl << "[2] withdraw" << endl << "[3] account transfer" << endl << "[4] cash transfer" << endl << "[5] language change" << endl; }
	int selection = 0;
	cin >> selection;
	if (selection == 1) {
		deposit(a);
	}
	else if (selection == 2) {
		withdraw(a);
	}
	else if (selection == 3) {
		if (this->lang_setting == 1) { cout << "송금할 계좌의 번호를 입력해 주세요 : "; }
		if (this->lang_setting == 0) { cout << "Please enter the number of the account you want to transfer : "; }
		string numinsert1 = "";
		cin >> numinsert1;
		Account* b = num2account(numinsert1, bank_list);
		if (b == nullptr) {
			if (this->lang_setting == 1) { cout << "잘못된 계좌 번호를 입력하셨습니다. 거래를 종료합니다." << endl; }
			if (this->lang_setting == 0) { cout << "Invalid account number. Transaction will be canceled." << endl; }
			return -1;
		}
		account_transfer(a, b);
	}
	else if (selection == 4) {
		if (this->lang_setting == 1) { cout << "송금할 계좌의 번호를 입력해 주세요 : "; }
		if (this->lang_setting == 0) { cout << "Please enter the number of the account you want to transfer : "; }
		string numinsert2 = "";
		cin >> numinsert2;
		Account* b = num2account(numinsert2, bank_list);
		if (b == nullptr) {
			if (this->lang_setting == 1) { cout << "잘못된 계좌 번호를 입력하셨습니다. 거래를 종료합니다." << endl; }
			if (this->lang_setting == 0) { cout << "Invalid account number. Transaction will be canceled." << endl; }
			return -1;
		}
		cash_transfer(b);
	}
	else if (selection == 5) {
		languageChange();
	}
	return 0;
}

void ATM::add_cash(int cash1000, int cash5000, int cash10000, int cash50000) {
	this->cash_storage[0] += cash1000;
	this->cash_storage[1] += cash5000;
	this->cash_storage[2] += cash10000;
	this->cash_storage[3] += cash50000;
}

bool ATM::user_authorization(Account* a) {
	//카드 입력
	
	//카드 유효성 검사

	//비밀번호 입력

	//비밀번호 검사

	//3번 연속 틀리면 세션 중단되게
	if (this->lang_setting == 1) { cout << "비밀번호를 3회 틀리면, 거래가 종료됩니다." << endl; }
	if (this->lang_setting == 0) { cout << "If you get the password wrong 3 times, the transaction ends." << endl; }
	string pass;
	for (int i = 0; i < 3; i++) {
		if (this->lang_setting == 1) { cout << "비밀번호를 입력해 주십시오." << endl; }
		if (this->lang_setting == 1) { cout << "남은 입력 횟수 : " << 3 - i << "회" << endl; }
		if (this->lang_setting == 0) { cout << "Please enter your password." << endl; }
		if (this->lang_setting == 0) { cout << "remaining : " << 3 - i << " times" << endl; }
		cin >> pass;
		if (a->getPassword() == pass) {
			return true;
		}
		if (this->lang_setting == 1) { cout << "비밀번호가 틀렸습니다." << endl; }
		if (this->lang_setting == 0) { cout << "Wrong password." << endl; }
	}
	return false;
}

void ATM::see_transaction_history() {
	if (this->lang_setting == 1) { cout << "관리자 카드가 입력되었습니다." << endl << "관리자 권한으로 거래 내역을 확인하시겠습니까?" << endl << "[0] 네" << "[1] 아니오" << endl; }
	if (this->lang_setting == 0) { cout << "Admin card has inserted." << endl << "Do you want to see the transaction history with administrator privileges?" << endl << "[0] Yes" << "[1] No" << endl; }
	bool no;
	cin >> no;
	if (no == true) {
		return;
	}
	ifstream readFile(this->transaction_histories);
	if (readFile.is_open()) {
		string str;
		while (readFile) {
			getline(readFile, str);
			cout << str << endl;
		}
	}
	else {
		if (this->lang_setting == 1) { cout << "해당하는 파일이 없습니다." << endl; }
		if (this->lang_setting == 0) { cout << "No corresponding files exist." << endl; }
	}
	return;
}

void ATM::make_history(string TransactionID, string CardNumber, string TransactionTypes, string Amount, string Specific) {
	//Transaction ID
	//Card Number
	//Transaction Types : deposit, withdraw, account transfer, cash_transfer
	//Amount
	//other transaction-specific information
	//account transfer:enemy account number
	//cash transfer:enemy account number
	vector<string>new_history = { TransactionID, CardNumber, TransactionTypes, Amount, Specific }; // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecificInformation
	int len = static_cast<int>(new_history.size());

	ofstream writeFromFile(this->transaction_histories, ios::app);
	for (int i = 0; i < len; ++i) {
		string tmp = new_history[i];
		if (i != len - 1) {
			tmp += ", ";
		}
		writeFromFile << tmp;
	}
	writeFromFile << "\n";
	return;
}

void ATM::display_transaction(string TransactionID, string CardNumber, string TransactionTypes, string Amount, string Specific) {
	cout << "Transaction ID : " << TransactionID << endl;
	cout << "CardNumber : " << CardNumber << endl;
	cout << "TransactionTypes : " << TransactionTypes << endl;
	cout << "Amount : " << Amount << endl;
	cout << "Note : " << Specific << endl;
	return;
}

string ATM::getSerial() {
	return serial_number;
}

Bank* ATM::getPrimary() {
	return primary_bank;
}

string ATM::getLangType() {
	if (language_available == 1) {
		return "Unilingual";
	}
	else {
		return "Bilingual";
	}
}