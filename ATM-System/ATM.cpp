#include "ATM.h"

int ATM::static_ATM_counter = 0;
int ATM::static_transaction_counter = 0;

void ATM::languageChange() {
	if (language_available == 1) {
		cout << "unilingual ATM cannot change language!" << endl;
		return;
	}
	if (lang_setting == false) { cout << "Please choose the language setting." << endl; }
	else { cout << "�� ������ �ּ���." << endl; }
	cout << "[1] English" << endl;
	cout << "[2] �ѱ���" << endl;
	if (lang_setting == false) { cout << "Input : " << endl; }
	else { cout << "�Է� : " << endl; }

	int input_language_setting;
	while (true) {
		cin >> input_language_setting;
		if (input_language_setting == 1 or input_language_setting == 2) {
			break;
		}
		else {
			if (lang_setting == false) { cout << "An unsupported language. Return to the previous screen." << endl; }
			if (lang_setting == true) { cout << "�������� �ʴ� ����Դϴ�. ���� ȭ������ ���ư��ϴ�." << endl; }
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
	this->transaction_histories = input_serial_number + ".txt";
	this->admin_card = input_primary_bank->getBankName() + "admin";

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
	if (this->lang_setting == true) { cout << "ī�带 ������ �ּ���." << endl; }
	if (this->lang_setting == false) { cout << "Please insert your card." << endl; }
	string cardinsert;
	cout << "Card number : ";
	cin >> cardinsert;
	if (cardinsert == this->admin_card) {
		see_transaction_history();
		return;
	}
	Account* acc = card2account(cardinsert, bank_list);
	if (acc == nullptr) {
		if (this->lang_setting == 1) { cout << "�߸��� ī�尡 �ԷµǾ����ϴ�. ī�带 ��ȯ�մϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Wrong card has inserted. Card will be return." << endl; }
		return;
	}
	if (this->user_authorization(acc) == false) {
		if (this->lang_setting == 1) { cout << "��й�ȣ �Է¿� 3ȸ �����ϼ̽��ϴ�. �ŷ��� �����մϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Failed to enter password 3 times. Transaction will be canceled." << endl; }
		return;
	}
	vector<vector<string>> record;
	for (int i = 0;;i++) {
		record.push_back(transaction(acc, bank_list, cardinsert));
		if (record.at(i).at(2) == "Termination") {
			break;
		}
	}
	for (int i = 0; i < record.size(); i++) {
		display_transaction_short(record.at(i));
	}
	return;
}

vector<string> ATM::transaction(Account* a, vector<Bank*> bank_list, string CardNumber) {
	vector<string> rec; //transactionID, card number, transaction type, success or failure, amount, note
	rec.push_back(to_string(++static_transaction_counter));
	rec.push_back(CardNumber);
	int amount = 0;
	string note = "";

	if (this->lang_setting == 1) { cout << this->getSerial() << "�� ATM�� �����ϼ̽��ϴ�. ���� �۾��� ���͵帱���?" << endl; }
	else if (this->lang_setting == 0) { cout << "You've accessed ATM number " << this->getSerial() << ".What can we do for you ? " << endl; }
	if (this->lang_setting == 1) { cout << "[1] �Ա�" << endl << "[2] ���" << endl << "[3] ���� �۱�" << endl << "[4] ���� �۱�" << endl << "[5] ��� ����" << endl << "[6] �ŷ� ����" << endl; }
	else if (this->lang_setting == 0) { cout << "[1] deposit" << endl << "[2] withdraw" << endl << "[3] account transfer" << endl << "[4] cash transfer" << endl << "[5] language change" << endl << "[6] end transfer" << endl; }
	
	int selection = 0;
	cin >> selection;
	if (selection == 1) {
		rec.push_back("Deposit");
		amount = deposit(a);
	}
	else if (selection == 2) {
		rec.push_back("Withdraw");
		amount = withdraw(a);
	}
	else if (selection == 3) {
		rec.push_back("account transfer");
		if (this->lang_setting == 1) { cout << "�۱��� ������ ��ȣ�� �Է��� �ּ��� : "; }
		if (this->lang_setting == 0) { cout << "Please enter the number of the account you want to transfer : "; }
		string numinsert1 = "";
		cin >> numinsert1;
		Account* b = num2account(numinsert1, bank_list);
		if (b == nullptr) {
			if (this->lang_setting == 1) { cout << "�߸��� ���� ��ȣ�� �Է��ϼ̽��ϴ�. �ŷ��� �����մϴ�." << endl; }
			if (this->lang_setting == 0) { cout << "Invalid account number. Transaction will be canceled." << endl; }
			amount = -1;
		}
		else {
			amount = account_transfer(a, b);
			note = b->getAccountNumber();
		}
	}
	else if (selection == 4) {
		rec.push_back("cash transfer");
		if (this->lang_setting == 1) { cout << "�۱��� ������ ��ȣ�� �Է��� �ּ��� : "; }
		if (this->lang_setting == 0) { cout << "Please enter the number of the account you want to transfer : "; }
		string numinsert2 = "";
		cin >> numinsert2;
		Account* b = num2account(numinsert2, bank_list);
		if (b == nullptr) {
			if (this->lang_setting == 1) { cout << "�߸��� ���� ��ȣ�� �Է��ϼ̽��ϴ�. �ŷ��� �����մϴ�." << endl; }
			if (this->lang_setting == 0) { cout << "Invalid account number. Transaction will be canceled." << endl; }
			amount = -1;
		}
		else {
			amount = cash_transfer(b);
			note = b->getAccountNumber();
		}
	}
	else if (selection == 5) {
		rec.push_back("language change");
		languageChange();
		amount = 0;
	}
	else if (selection == 6) {
		rec.push_back("Termination");
		amount = 0;
	}
	else {
		rec.push_back("invalid transaction");
		rec.push_back("Failure");
		rec.push_back("-1");
	}
	if (amount == -1) { rec.push_back("Failure"); }
	else { rec.push_back("Success"); }
	rec.push_back(to_string(amount));
	rec.push_back(note);
	make_history(rec);
	a->updateHistory(rec[0], rec[1], rec[2], rec[4], rec[5]);
	return rec;
}

void ATM::add_cash(int cash1000, int cash5000, int cash10000, int cash50000) {
	this->cash_storage[0] += cash1000;
	this->cash_storage[1] += cash5000;
	this->cash_storage[2] += cash10000;
	this->cash_storage[3] += cash50000;
}

bool ATM::user_authorization(Account* a) {
	//ī�� �Է�
	
	//ī�� ��ȿ�� �˻�

	//��й�ȣ �Է�

	//��й�ȣ �˻�

	//3�� ���� Ʋ���� ���� �ߴܵǰ�
	if (this->lang_setting == 1) { cout << "��й�ȣ�� 3ȸ Ʋ����, �ŷ��� ����˴ϴ�." << endl; }
	if (this->lang_setting == 0) { cout << "If you get the password wrong 3 times, the transaction ends." << endl; }
	string pass;
	for (int i = 0; i < 3; i++) {
		if (this->lang_setting == 1) { cout << "��й�ȣ�� �Է��� �ֽʽÿ�." << endl; }
		if (this->lang_setting == 1) { cout << "���� �Է� Ƚ�� : " << 3 - i << "ȸ" << endl; }
		if (this->lang_setting == 0) { cout << "Please enter your password." << endl; }
		if (this->lang_setting == 0) { cout << "remaining : " << 3 - i << " times" << endl; }
		cin >> pass;
		if (a->getPassword() == pass) {
			return true;
		}
		if (this->lang_setting == 1) { cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "Wrong password." << endl; }
	}
	return false;
}

void ATM::see_transaction_history() {
	if (this->lang_setting == 1) { cout << "������ ī�尡 �ԷµǾ����ϴ�." << endl << "������ �������� �ŷ� ������ Ȯ���Ͻðڽ��ϱ�?" << endl << "[0] ��" << "[1] �ƴϿ�" << endl; }
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
		if (this->lang_setting == 1) { cout << "�ش��ϴ� ������ �����ϴ�." << endl; }
		if (this->lang_setting == 0) { cout << "No corresponding files exist." << endl; }
	}
	return;
}

void ATM::make_history(vector<string> rec) {
	//Transaction ID
	//Card Number
	//Transaction Types : deposit, withdraw, account transfer, cash_transfer
	//Amount
	//other transaction-specific information
	//account transfer:enemy account number
	//cash transfer:enemy account number
	//vector<string>new_history = { TransactionID, CardNumber, TransactionTypes, sorf, Amount, Specific }; // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecificInformation
	int len = static_cast<int>(rec.size());

	ofstream writeFromFile(this->transaction_histories, ios::app);
	for (int i = 0; i < len; ++i) {
		string tmp = rec[i];
		if (i != len - 1) {
			tmp += ", ";
		}
		writeFromFile << tmp;
	}
	writeFromFile << "\n";
	return;
}

void ATM::display_transaction(vector<string> rec) {
	//string TransactionID, string CardNumber, string TransactionTypes, string sorf, string Amount, string Specific
	cout << "Transaction ID : " << rec[0] << endl;
	cout << "CardNumber : " << rec[1] << endl;
	cout << "TransactionTypes : " << rec[2] << endl;
	cout << "Success or Failure : " << rec[3] << endl;
	cout << "Amount : " << rec[4] << endl;
	cout << "Note : " << rec[5] << endl;
	return;
}

void ATM::display_transaction_short(vector<string> rec) {
	//string TransactionID, string CardNumber, string TransactionTypes, string sorf, string Amount, string Specific
	cout << "[/";
	for (int i = 0; i < rec.size(); i++) {
		if (rec[i] != "") { cout << rec[i] << "/"; }
	}
	cout << "]" << endl;
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

int ATM::get1000() {
	return *(cash_storage[0]);
}
int ATM::get5000() {
	return *(cash_storage[1]);
}
int ATM::get10000() {
	return *(cash_storage[2]);
}
int ATM::get50000() {
	return *(cash_storage[3]);
}