#include "Bank.h"

int Bank::static_bank_counter = 0;

using namespace std;

int Bank:: no_error(int language_setting) {
	while (true) {
		int temp;
		cin >> temp;
		if (cin.fail()) {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";

			}
			if (language_setting == 2) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			if (temp >= 0) { return temp; }
			else {
				if (language_setting == 1) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";

				}
				if (language_setting == 2) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
			}
		}
	}
}

int Bank::no_error_range(int language_setting, int min, int max) {
	while (true) {
		int temp;
		cin >> temp;
		if (cin.fail()) {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";

			}
			if (language_setting == 2) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "���ڸ� �Է����ּ��� : ";
			}
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			if (temp > min - 1 && temp < max + 1) { return temp; }
			else {
				if (language_setting == 1) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";

				}
				if (language_setting == 2) {
					cout << "[����] ���� ���� �Է�. �ٽ� �� �� �Է��� �ּ���." << endl;
					cout << "���ڸ� �Է����ּ��� : ";
				}
			}
		}
	}
}

Bank::Bank(string name) {
	this->bank_name = name;
	static_bank_counter += 1;
	this->bank_id = static_bank_counter;
	cout << this->getBankName() << " Bank is created." << endl;
}

Bank::~Bank() {
	cout << this->bank_name << " Bank is eliminated." << endl;
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

void Bank::makeCard_session(int language_setting) {
	cout << "==================== < Card Create Session > ====================" << endl;

	if (accounts.size() == 0) {
		if (language_setting == 1) { cout << "There is no account. So making card is not available." << endl; }
		if (language_setting == 2) { cout << "���࿡ �����ϴ� ���°� ���� ī�� ������ ������ �� �����ϴ�." << endl; }
		return;
	}
	
	int c = 0;
	Account* account = search_account_number(language_setting);

	if (account == NULL) { c = 1; }

	if (c == 0) {
		string input_password;
		if (language_setting == 1) { cout << "To make card, please write password." << endl; }
		if (language_setting == 2) { cout << "ī�带 ����� ���� ��й�ȣ�� �Է����ּ���." << endl; }

		int a = 3;
		while (true) {

			if (a == 0) {
				if (language_setting == 1) { cout << "You write wrong password 4 times. " << endl; }
				if (language_setting == 2) { cout << "��й�ȣ 4ȸ Ʋ�Ƚ��ϴ�." << endl; }
				cout << "==================== < Card Create Session End! > ====================" << endl;
				break;
			}
			if (language_setting == 1) {
				cout << a << " attempts left." << endl;
				cout << "Password : ";
			}
			if (language_setting == 2) {
				cout << a << " ȸ ����." << endl;
				cout << "��й�ȣ : ";
			}

			cin >> input_password;
			a--;
			if (account->getPassword() == input_password) {
				if (language_setting == 1) { cout << "Correct password." << endl; }
				if (language_setting == 2) { cout << "���� ��й�ȣ." << endl; }

				string now_created_card_number;
				now_created_card_number = account->makeCard();
				if (language_setting == 1) {
					cout << "Card is created." << endl;
					cout << "Card Number : " << now_created_card_number << endl;
					cout << "This is card number list that connected to your account." << endl;
				}
				if (language_setting == 2) {
					cout << "ī�尡 �����Ǿ����ϴ�." << endl;
					cout << "ī�� ��ȣ : " << now_created_card_number << endl;
					cout << "���¿� ����� ī�� ��ȣ ����Դϴ�." << endl;
				}

				vector <string > card_list = account->getCardNumber();
				for (int i = 0; i < card_list.size(); i++) {
					cout << card_list[i] << endl;
				}
				break;
			}
		}
	}
	cout << "==================== < Card Create Session End! > ====================" << endl;
}

void Bank::create_account(int language_setting) {
	cout << "==================== < Account Create Session > ====================" << endl;
	string input_user_name;
	string account_number;
	string input_password;
	if (language_setting == 1) {
		cout << this->getBankName() << "Bank. To create account. please write name, password and initial fund." << endl;
		cout << "Name : ";
		cin >> input_user_name;
		cout << "Password : ";
		cin >> input_password;
		cout << "Initial fund : ";
	}
	if (language_setting == 2) {
		cout << this->getBankName() << "����. ���¸� �����ϱ� ���� �̸�, ����, �ʱ� �ڱ��� �Է����ּ���." << endl;
		cout << "������ : ";
		cin >> input_user_name;
		cout << "��й�ȣ : ";
		cin >> input_password;
		cout << "�ʱ��ڱ� : ";
	}

	int initial_fund;
	// cin >> initial_fund;
	initial_fund = no_error(language_setting);

	Account* new_account = new Account(this, input_user_name, input_password, initial_fund);
	accounts.push_back(new_account);

	if (language_setting == 1) {
		cout << "Account is created." << endl;
		cout << "Bank : " << new_account->getBankName() << endl;
		cout << "Owner : " << new_account->getUserName() << endl;
		cout << "Account number : " << new_account->getAccountNumber() << endl;
		cout << "Password : " << new_account->getPassword() << endl;
		cout << "Available fund : " << new_account->getAvailableFund() << endl;
		cout << "Do you want to make card? [Agree Y / Disagree N] : ";
	}
	if (language_setting == 2) {
		cout << "���°� �����Ǿ����ϴ�." << endl;
		cout << "���� : " << new_account->getBankName() << endl;
		cout << "������ : " << new_account->getUserName() << endl;
		cout << "���¹�ȣ : " << new_account->getAccountNumber() << endl;
		cout << "��й�ȣ : " << new_account->getPassword() << endl;
		cout << "�����ܰ� : " << new_account->getAvailableFund() << endl;
		cout << "ī�带 �����Ͻðڽ��ϱ�? [���� Y / ���� N] : ";
	}

	string agreement;
	// cin >> agreement;
	while (true) {
		cin >> agreement;
		if (agreement != "n" && agreement != "N" && agreement != "y" && agreement != "Y") {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "[Agree Y / Disagree N] : ";
			}
			if (language_setting == 2) {
				cout << "[����] �Է� ������ �߻��߽��ϴ�. �ٽ� �� �� �Է��� �ּ���." << endl;
				cout << "[���� Y / ���� N] : ";
			}
		}
		else { break; }
	}

	if (agreement == "n" || agreement == "N"){ cout << "==================== < Card Create Session End! > ====================" << endl; }
	if (agreement == "y" || agreement == "Y") {
		cout << "==================== < Card Create Session > ====================" << endl;
		string now_created_card_number;
		now_created_card_number = new_account->makeCard();

		if (language_setting == 1) {
			cout << "Card is created." << endl;
			cout << "Card number : " << now_created_card_number << endl;
			cout << "This is card number list that connected to your account." << endl;
		}
		if (language_setting == 2) {
			cout << "ī�尡 �����Ǿ����ϴ�." << endl;
			cout << "ī�� ��ȣ : " << now_created_card_number << endl;
			cout << "���¿� ����� ī�� ��ȣ ����Դϴ�." << endl;
		}
		vector <string> card_list = new_account->getCardNumber();
		for (int i = 0; i < card_list.size(); i++) {
			cout << card_list[i] << endl;
		}
		cout << "==================== < Card Create Session End! > ====================" << endl;
	}
	cout << "==================== < Account Create Session End! > ====================" << endl;
	//return new_account;
}

Account* Bank::search_account_number(int language_setting) {
	cout << "==================== < Account Number Search Session > ====================" << endl;
	vector<Account*> accounts_list = get_account();

	int a = 3;

	while (a > -1){
		if (language_setting == 1) {
			cout << this->getBankName() << " Bank. Please write account number." << endl;
			cout << "Account number : ";
		}
		if (language_setting == 2) {
			cout << this->getBankName() << " ����. ���¹�ȣ�� �Է����ּ���." << endl;
			cout << "���¹�ȣ : ";
		}

		string input_account_number;
		cin >> input_account_number;
		for (int i = 0; i < accounts_list.size(); i++) {
			if (accounts_list[i]->getAccountNumber() == input_account_number) {
				if (language_setting == 1) {
					cout << this->getBankName() << " Bank find your account." << endl;
					cout << "Bank : " << accounts_list[i]->getBankName() << endl;
					cout << "Owner : " << accounts_list[i]->getUserName() << endl;
					cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
				}
				if (language_setting == 2) {
					cout << this->getBankName() << " ������ ���¸� ã�ҽ��ϴ�." << endl;
					cout << "���� : " << accounts_list[i]->getBankName() << endl;
					cout << "������ : " << accounts_list[i]->getUserName() << endl;
					cout << "���¹�ȣ : " << accounts_list[i]->getAccountNumber() << endl;
				}

				cout << "==================== < Account Number Search Session End! > ====================" << endl;
				return accounts_list[i];
			}
		}
		if (a == 0) {
			if (language_setting == 1) { cout << this->getBankName() << " Bank cannot find your account." << endl; }
			if (language_setting == 2) { cout << this->getBankName() << " ������ ���¸� ã�� ���߽��ϴ�." << endl; }
			break;
		}
		if (language_setting == 1) {
			cout << this->getBankName() << " Bank cannot find your account." << endl;
			cout << a << " attempt left." << endl;
		}
		if (language_setting == 2) {
			cout << this->getBankName() << " ������ ���¸� ã�� ���߽��ϴ�." << endl;
			cout << a << " ȸ ���ҽ��ϴ�." << endl;
		}
		a--;
	}
	if (language_setting == 1) { cout << "You write wrong account number 4 times." << endl; }
	if (language_setting == 2) { cout << "�߸��� ���� ��ȣ�� 4ȸ �Է��߽��ϴ�." << endl; }
	cout << "==================== < Account Number Search Session End! > ====================" << endl;
	return NULL;
}

Account* Bank::search_account_number_BankSearch(string input_account, int language_setting) {
	vector<Account*> accounts_list = get_account();
	string input_account_number = input_account;
	for (int i = 0; i < accounts_list.size(); i++) {
		if (accounts_list[i]->getAccountNumber() == input_account_number) {
			if (language_setting == 1) {
				cout << this->getBankName() << " Bank find your account." << endl;
				cout << "Bank : " << accounts_list[i]->getBankName() << endl;
				cout << "Owner : " << accounts_list[i]->getUserName() << endl;
				cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
			}
			if (language_setting == 2) {
				cout << this->getBankName() << " ������ ���¸� ã�ҽ��ϴ�." << endl;
				cout << "���� : " << accounts_list[i]->getBankName() << endl;
				cout << "������ : " << accounts_list[i]->getUserName() << endl;
				cout << "���¹�ȣ : " << accounts_list[i]->getAccountNumber() << endl;
			}
			return accounts_list[i];
		}
	}
	// cout << this->getBankName() << "Bank cannot find your account." << endl;
	return NULL;
}

Account* Bank::search_account_card(int language_setting) {
	cout << "==================== < Account Card Search Session > ====================" << endl;
	vector<Account*> accounts_list = get_account();
	if (language_setting == 1) { cout << this->getBankName() << " Bank. Please write card number." << endl; }
	if (language_setting == 2) { cout << this->getBankName() << " ����. ī�� ��ȣ�� �Է����ּ���." << endl; }
	string input_card_number;
	if (language_setting == 1) {
		cout << "Card number : ";
		cin >> input_card_number;
	}
	if (language_setting == 2) {
		cout << "ī�� ��ȣ : ";
		cin >> input_card_number;
	}
	for (int i = 0; i < accounts_list.size(); i++) {
		vector<string> card_list = accounts_list[i]->getCardNumber();
		for (int j = 0; j < card_list.size(); j++) {
			if (card_list[j] == input_card_number) {
				if (language_setting == 1) {
					cout << this->getBankName() << " Bank find your account." << endl;
					cout << "Bank : " << accounts_list[i]->getBankName() << endl;
					cout << "Owner : " << accounts_list[i]->getUserName() << endl;
					cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
				}
				if (language_setting == 2) {
					cout << this->getBankName() << " ������ ���¸� ã�ҽ��ϴ�." << endl;
					cout << "���� : " << accounts_list[i]->getBankName() << endl;
					cout << "������ : " << accounts_list[i]->getUserName() << endl;
					cout << "���¹�ȣ : " << accounts_list[i]->getAccountNumber() << endl;
				}
				cout << "==================== < Account Card Search Session End! > ====================" << endl;
				return accounts_list[i];
			}
		}
	}
	if (language_setting == 1) { cout << this->getBankName() << " Bank cannot find your account." << endl; }
	if (language_setting == 2) { cout << this->getBankName() << " ������ ���¸� ã�� ���߽��ϴ�." << endl; }
	cout << "==================== < Account Card Search Session End! > ====================" << endl;
	return NULL;
}

Account* Bank::search_account_card_BankSearch(string input_card, int language_setting) {
	vector<Account*> accounts_list = get_account();
	string input_card_number = input_card;
	for (int i = 0; i < accounts_list.size(); i++) {
		vector<string> card_list = accounts_list[i]->getCardNumber();
		for (int j = 0; j < card_list.size(); j++) {
			if (card_list[j] == input_card_number) {
				if (language_setting == 1) {
					cout << this->getBankName() << " Bank find your account." << endl;
					cout << "Bank : " << accounts_list[i]->getBankName() << endl;
					cout << "Owner : " << accounts_list[i]->getUserName() << endl;
					cout << "Account : " << accounts_list[i]->getAccountNumber() << endl;
				}
				if (language_setting == 2) {
					cout << this->getBankName() << " ������ ���¸� ã�ҽ��ϴ�." << endl;
					cout << "���� : " << accounts_list[i]->getBankName() << endl;
					cout << "������ : " << accounts_list[i]->getUserName() << endl;
					cout << "���¹�ȣ : " << accounts_list[i]->getAccountNumber() << endl;
				}

				return accounts_list[i];
			}
		}
	}
	// cout << this->getBankName() << "Bank cannot find your account." << endl;
	return NULL;
}

vector<Account*> Bank::get_account() {
	return accounts;
}