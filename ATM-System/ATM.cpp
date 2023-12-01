#include "ATM.h"


int ATM::static_ATM_counter = 0;
int ATM::static_transaction_counter = 0;

void ATM::Qsearch(string str) {

	while (true) {
		cin >> str;
		if (str == "Q" || str == "q") {
			printNow();
		}
		else {
			return;
		}
	}
}

int ATM::no_error(bool language_setting) {
	int temp = 0;
	while (true) {

		string abc = "";
		// cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow();
			}
			else {
				break;
			}
		}

		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 0) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 1) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}

		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp >= 0) { return temp; }
			else {
				if (language_setting == 0) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 1) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 0) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 1) {
				cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
	}
}

int ATM::no_error_range(bool language_setting, int min, int max) {
	int temp = 0;
	while (true) {

		string abc = "";
		// cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow();
			}
			else {
				break;
			}
		}

		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 0) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 1) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}

		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp > min - 1 && temp < max + 1) { return temp; }
			else {
				if (language_setting == 0) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 1) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 0) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 1) {
				cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			continue;
		}
	}
}

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

	int input_language_setting = no_error_range(lang_setting, 1, 2);

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

ATM::ATM(Bank* input_primary_bank, string input_serial_number, int input_type, int input_lanuage_available, int* initial_fund[], vector<Bank*>* blist, vector<ATM*>* alist) {
	this->primary_bank = input_primary_bank;
	this->serial_number = input_serial_number;
	this->type = input_type;
	this->language_available = input_lanuage_available;
	this->transaction_histories = input_serial_number + ".txt";
	this->admin_card = input_primary_bank->getBankName() + "admin";
	this->blist = blist;
	this->alist = alist;

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
	if (this->lang_setting == true) { cout << "ī�带 ������ �ּ���." << endl << "ī�� ��ȣ : "; }
	if (this->lang_setting == false) { cout << "Please insert your card." << endl << "Card number : "; }
	string cardinsert;
	//cin >> cardinsert;

	Qsearch(cardinsert);

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
	int* with_counter = new int(0);
	vector<vector<string>> record;
	for (int i = 0;;i++) {
		record.push_back(transaction(acc, bank_list, cardinsert, with_counter));
		if (record.at(i).at(2) == "Termination") {
			break;
		}
	}
	delete with_counter;
	for (int i = 0; i < record.size(); i++) {
		display_transaction_short(record.at(i));
	}
	return;
}

vector<string> ATM::transaction(Account* a, vector<Bank*> bank_list, string CardNumber, int* with_counter) {
	vector<string> rec; //transactionID, card number, transaction type, success or failure, amount, note
	rec.push_back(to_string(++static_transaction_counter));
	rec.push_back(CardNumber);
	int amount = 0;
	string note = "";

	if (this->lang_setting == 1) { cout << this->getSerial() << "�� ATM�� �����ϼ̽��ϴ�. ���� �۾��� ���͵帱���?" << endl; }
	else if (this->lang_setting == 0) { cout << "You've accessed ATM number " << this->getSerial() << ".What can we do for you ? " << endl; }
	if (this->lang_setting == 1) { cout << "[1] �Ա�" << endl << "[2] ���" << endl << "[3] ���� �۱�" << endl << "[4] ���� �۱�" << endl << "[5] ��� ����" << endl << "[6] ���� ��ȸ" << endl << "[7] �ŷ� ����" << endl << "���ϴ� �۾� : "; }
	else if (this->lang_setting == 0) { cout << "[1] deposit" << endl << "[2] withdraw" << endl << "[3] account transfer" << endl << "[4] cash transfer" << endl << "[5] language change" << endl << "[6] account inquiry" << endl << "[7] end transfer" << endl << "What you want to do : "; }
	
	int selection = no_error_range(lang_setting, 1, 7);
	if (selection == 1) {
		rec.push_back("Deposit");
		amount = deposit(a);
	}
	else if (selection == 2 && *with_counter < 3) {
		rec.push_back("Withdraw");
		amount = withdraw(a);
		*with_counter += 1;
	}
	else if (selection == 2 && *with_counter >= 3) {
		rec.push_back("Withdraw");
		if (this->lang_setting == 1) { cout << "����� �� ���ǿ� 3ȸ������ �����մϴ�!!" << endl; }
		else { cout << "The maximum number of withdrawals per each session is 3!!" << endl; }
		amount = -1;
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
		rec.push_back("Account inquiry");
		a->printHistory();
		amount = 0;
	}
	else if (selection == 7) {
		rec.push_back("Termination");
		amount = 0;
	}
	else {
		if (lang_setting == true) { cout << "�Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl; }
		else { cout << "An input error has occurred. Please type the input again." << endl; }
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
	*(this->cash_storage[0]) += cash1000;
	*(this->cash_storage[1]) += cash5000;
	*(this->cash_storage[2]) += cash10000;
	*(this->cash_storage[3]) += cash50000;
}

bool ATM::user_authorization(Account* a) {
	//ī�� �Է�
	
	//ī�� ��ȿ�� �˻�

	//��й�ȣ �Է�

	//��й�ȣ �˻�

	//3�� ���� Ʋ���� ���� �ߴܵǰ�
	if (this->lang_setting == 1) { cout << "�ȳ��ϼ���, " << a->getUserName() << "." << endl; }
	if (this->lang_setting == 0) { cout << "Hello, " << a->getUserName() << "." << endl; }
	if (this->lang_setting == 1) { cout << "��й�ȣ�� 3ȸ Ʋ����, �ŷ�<�� ����˴ϴ�." << endl; }
	if (this->lang_setting == 0) { cout << "If you get the password wrong 3 times, the transaction ends." << endl; }
	string pass = "";
	for (int i = 0; i < 3; i++) {
		if (this->lang_setting == 1) { cout << "��й�ȣ�� �Է��� �ֽʽÿ�." << endl; }
		else if (this->lang_setting == 0) { cout << "Please enter your password." << endl; }
		if (this->lang_setting == 1) { cout << "���� �Է� Ƚ�� : " << 3 - i << "ȸ" << endl << "��й�ȣ : "; }
		else if (this->lang_setting == 0) { cout << "remaining : " << 3 - i << " times" << endl << "password : "; }
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
	if (this->lang_setting == 1) { cout << "������ ī�尡 �ԷµǾ����ϴ�." << endl << "������ �������� � �۾��� �Ͻðڽ��ϱ�?" << endl << "[0] �ŷ� ���� Ȯ�� " << endl; }
	if (this->lang_setting == 0) { cout << "Admin card has inserted." << endl << "What do you want to do with administrator privileges?" << endl << "[0] Transaction history " << endl; }
	int no = no_error_range(lang_setting, 0, 2);
	if (no == 2) {
		if (lang_setting == true) { cout << "�ʱ� ȭ������ ���ư��ϴ�." << endl; }
		else { cout << "Returning to the initial screen." << endl; }
		return;
	}
	if (no == 1) {
		int replenish[4] = { 0,0,0,0 };
		if (this->lang_setting == 1) { cout << "������ 1000������ ���� �Է��� �ּ���." << endl; }
		if (this->lang_setting == 0) { cout << "Please enter the amount of 1,000 won bills to be replenished." << endl; }
		replenish[0] = no_error(lang_setting);
		if (this->lang_setting == 1) { cout << "������ 5000������ ���� �Է��� �ּ���." << endl; }
		if (this->lang_setting == 0) { cout << "Please enter the amount of 5,000 won bills to be replenished." << endl; }
		replenish[1] = no_error(lang_setting);
		if (this->lang_setting == 1) { cout << "������ 10000������ ���� �Է��� �ּ���." << endl; }
		if (this->lang_setting == 0) { cout << "Please enter the amount of 10,000 won bills to be replenished." << endl; }
		replenish[2] = no_error(lang_setting);
		if (this->lang_setting == 1) { cout << "������ 50000������ ���� �Է��� �ּ���." << endl; }
		if (this->lang_setting == 0) { cout << "Please enter the amount of 50,000 won bills to be replenished." << endl; }
		replenish[3] = no_error(lang_setting);
		add_cash(replenish[0], replenish[1], replenish[2], replenish[3]);
		return;
	}
	else if (no == 0) {
		if (this->lang_setting == 1) { cout << "�ŷ� ������ ����մϴ�." << endl << endl; }
		else if (this->lang_setting == 0) { cout << "Printing transaction histories." << endl << endl; }
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
	else {
		if (lang_setting == true) { cout << "�ʱ� ȭ������ ���ư��ϴ�." << endl; }
		else { cout << "Returning to the initial screen." << endl; }
		return;
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
	//vector<string>new_history = { TransactionID, CardNumber, TransactionTypes, sorf, Amount, Specific }; // TransactionID, CardNumber, TransactionTypes, Amount, TransactionSpecific Information
	//int len = static_cast<int>(rec.size());

	ofstream writeFromFile(this->transaction_histories, ios::app);
	writeFromFile << "TransactionID : " << rec[0] << "\n";
	writeFromFile << "CardNumber : " << rec[1] << "\n";
	writeFromFile << "TransactionTypes : " << rec[2] << "\n";
	writeFromFile << "Success or failure : " << rec[3] << "\n";
	writeFromFile << "Amount : " << rec[4] << "\n";
	writeFromFile << "Note : " << rec[5] << "\n";
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

void ATM::printNow() {
	for (int i = 0; i < (*blist).size(); i++) {
		for (int j = 0; j < (*blist)[i]->get_account().size(); j++) {
			cout << "Account[" << (*blist)[i]->get_account()[j]->getUserName() << "] : " << (*blist)[i]->get_account()[j]->checkFunds() << "/" << (*blist)[i]->get_account()[j]->getAccountNumber() << "/" << (*blist)[i]->get_account()[j]->getBankName() << endl;
		}
	}
	for (int i = 0; i < (*alist).size(); i++) {
		cout << "ATM " << "[" << i << "] " << "Primary Bank : " << (*alist)[i]->getPrimary()->getBankName() << " " << (*alist)[i]->getType() << " " << (*alist)[i]->getLangType() << endl;
		cout << "Remaing cash : " << 1000 * (*alist)[i]->get1000() + 5000 * (*alist)[i]->get5000() + 10000 * (*alist)[i]->get10000() + 50000 * (*alist)[i]->get50000() << " (1000 : " << (*alist)[i]->get1000() << ", 5000 : " << (*alist)[i]->get5000() << ", 10000 : " << (*alist)[i]->get10000() << ", 50000 : " << (*alist)[i]->get50000() << ")" << endl;
		// cout << "ATM [" << ATM_list[i]->getSerial() << "] Remaing cash : " << 1000 * ATM_list[i]->get1000() + 5000 * ATM_list[i]->get5000() + 10000 * ATM_list[i]->get10000() + 50000 * ATM_list[i]->get50000() << " (1000 : " << ATM_list[i]->get1000() << ", 5000 : " << ATM_list[i]->get5000() << ", 10000 : " << ATM_list[i]->get10000() << ", 50000 : " << ATM_list[i]->get50000() << ")" << endl;
	}
	cout << "printNow End!" << endl;
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