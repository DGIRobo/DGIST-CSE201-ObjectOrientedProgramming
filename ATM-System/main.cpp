#include <iostream>
#include <string>
#include <exception>

#include "Account.h"
#include "Bank.h"
#include "ATM.h"
#include "SingleBankATM.h"
#include "MultiBankATM.h"

using namespace std;

void printNow(vector<ATM*>& ATM_list, vector<Bank*>& bank_list) {

	for (int i = 0; i < bank_list.size(); i++) {
		for (int j = 0; j < bank_list[i]->get_account().size(); j++) {
			cout << "Account[" << (bank_list)[i]->get_account()[j]->getUserName() << "] : " << (bank_list)[i]->get_account()[j]->checkFunds() << "/" << (bank_list)[i]->get_account()[j]->getAccountNumber() << "/" << (bank_list)[i]->get_account()[j]->getBankName() << endl;
		}
	}
	for (int i = 0; i < (ATM_list).size(); i++) {
		cout << "ATM " << "[" << i << "] " << "Primary Bank : " << (ATM_list)[i]->getPrimary()->getBankName() << " " << (ATM_list)[i]->getType() << " " << (ATM_list)[i]->getLangType() << endl;
		cout << "Remaing cash : " << 1000 * (ATM_list)[i]->get1000() + 5000 * (ATM_list)[i]->get5000() + 10000 * (ATM_list)[i]->get10000() + 50000 * (ATM_list)[i]->get50000() << " (1000 : " << (ATM_list)[i]->get1000() << ", 5000 : " << (ATM_list)[i]->get5000() << ", 10000 : " << (ATM_list)[i]->get10000() << ", 50000 : " << (ATM_list)[i]->get50000() << ")" << endl;
	}

	cout << endl;
	cout << "Please re-enter here : ";
	return;
}

string Qsearch(vector<ATM*>& ATM_list, vector<Bank*>& bank_list) {
	string str;
	while (true) {
		cin >> str;
		if (str == "Q" || str == "q") {
			printNow(ATM_list, bank_list);
		}
		else {
			return str;
		}
	}
}

int no_error(vector<ATM*>& ATM_list, vector<Bank*>& bank_list, int language_setting) {
	int temp = 0;
	while (true) {

		string abc = "";
		// cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow(ATM_list, bank_list);
			}
			else {
				break;
			}
		}

		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[에러] 입력 오류가 발생했습니다. 다시 한 번 입력해 주세요." << endl;
				cout << "숫자를 입력해주세요 : ";
			}
			continue;
		}

		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp >= 0) { return temp; }
			else {
				if (language_setting == 1) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 2) {
					cout << "[에러] 범위 밖의 입력. 다시 한 번 입력해 주세요." << endl;
					cout << "숫자를 입력해주세요 : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 1) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[에러] 범위 밖의 입력. 다시 한 번 입력해 주세요." << endl;
				cout << "숫자를 입력해주세요 : ";
			}
			continue;
		}
	}
}

int no_error_range(vector<ATM*>& ATM_list, vector<Bank*>& bank_list, int language_setting, int min, int max) {
	int temp = 0;
	while (true) {

		string abc = "";
		// cin >> abc;
		while (true) {
			cin >> abc;
			if (abc == "Q" || abc == "q") {
				printNow(ATM_list, bank_list);
			}
			else {
				break;
			}
		}

		if (abc.find(".") != string::npos || abc.find("-") != string::npos || abc.find("\n") != string::npos) {
			if (language_setting == 1) {
				cout << "[Error] An input error has occurred. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[에러] 입력 오류가 발생했습니다. 다시 한 번 입력해 주세요." << endl;
				cout << "숫자를 입력해주세요 : ";
			}
			continue;
		}

		if (atoi(abc.c_str()) != 0 || abc.compare("0") == 0) {
			temp = stoi(abc);
			if (temp > min - 1 && temp < max + 1) { return temp; }
			else {
				if (language_setting == 1) {
					cout << "[Error] Input out of range. Please write again." << endl;
					cout << "Please Enter the Number : ";
				}
				if (language_setting == 2) {
					cout << "[에러] 범위 밖의 입력. 다시 한 번 입력해 주세요." << endl;
					cout << "숫자를 입력해주세요 : ";
				}
				continue;
			}
		}
		if (atoi(abc.c_str()) == 0 && abc.compare("0") != 0) {
			if (language_setting == 1) {
				cout << "[Error] Input out of range. Please write again." << endl;
				cout << "Please Enter the Number : ";
			}
			if (language_setting == 2) {
				cout << "[에러] 범위 밖의 입력. 다시 한 번 입력해 주세요." << endl;
				cout << "숫자를 입력해주세요 : ";
			}
			continue;
		}
	}
}

void BankMake(vector<ATM*>& ATM_list, vector<Bank*>& bank_list, int language_setting, vector<Bank*>* blist, vector<ATM*>* alist) {

	cout << "==================== < Bank Duplicate Session > ====================" << endl;
	string bank_name; string bank_name_save;

	while (true) {
		int dup = 0;

		if (language_setting == 1) { cout << "Please write bank name : "; }
		if (language_setting == 2) { cout << "은행명을 입력해주세요. : "; }

		cin >> bank_name;
		// Qsearch(ATM_list, bank_list, bank_name);

		bank_name_save = bank_name;

		for (int i = 0; i < bank_name.size(); i++) {
			bank_name[i] = tolower(bank_name[i]);
		}

		for (int j = 0; j < bank_list.size(); j++) {

			// string reference = bank_list[j].getBankName();
			string reference = bank_list[j]->getBankName();

			for (int k = 0; k < reference.size(); k++) {
				reference[k] = tolower(reference[k]);
			}
			if (reference == bank_name) {
				if (language_setting == 1) { cout << bank_name << " is already exiested!" << endl; }
				if (language_setting == 2) { cout << bank_name << " 은행은 이미 존재합니다!" << endl; }
				dup = 1;
			}
		}
		if (dup == 0) {
			// bank_list.push_back(Bank(bank_name_save));
			bank_list.push_back(new Bank(bank_name_save, blist, alist));
			cout << "==================== < Bank Duplicate Session End! > ====================" << endl;
			break;
		}
	}
}

void BankService(vector<ATM*>& ATM_list, vector<Bank*> bank_list, int language_setting) {

	cout << "==================== < Bank Service Session > ====================" << endl;

	if (bank_list.size() == 0) {
		if (language_setting == 1) { cout << "There is no bank. So bank service is not available." << endl; }
		if (language_setting == 2) { cout << "은행이 없어 은행 서비스를 수행할 수 없습니다." << endl; }
		return;
	}

	if (language_setting == 1) { cout << "Please choose Bank number that you want to make account for." << endl; }
	if (language_setting == 2) { cout << "계좌를 만들고 싶은 은행을 선택해주세요." << endl; }

	for (int i = 0; i < bank_list.size(); i++) {
		cout << "[" << i << "] " << bank_list[i]->getBankName() << " Bank" << endl;
	}
	cout << endl;

	if (language_setting == 1) { cout << "Bank number : "; }
	if (language_setting == 2) { cout << "은행 번호 : "; }

	int bank_choose = 0;
	bank_choose = no_error_range(ATM_list, bank_list, language_setting, 0, (int) bank_list.size() - 1);

	if (language_setting == 1) { cout << bank_list[bank_choose]->getBankName() << " bank is selected." << endl; }
	if (language_setting == 2) { cout << bank_list[bank_choose]->getBankName() << " 은행이 선택되었습니다." << endl; }

	if (language_setting == 1) {
		cout << "Please choose number that you want to get service." << endl;
		cout << "[1] Create Account" << endl;
		cout << "[2] Make Card" << endl;
		cout << "[3] Account history" << endl;
		cout << endl;
		cout << "Serive number : ";
	}
	if (language_setting == 2) {
		cout << "이용하고자 하는 서비스를 선택해주세요." << endl;
		cout << "[1] 계좌 개설" << endl;
		cout << "[2] 카드 생성" << endl;
		cout << "[3] 계좌 기록" << endl;
		cout << endl;
		cout << "서비스 번호 : ";
	}

	int service_choose = 0;
	// cin >> service_choose;
	service_choose = no_error_range(ATM_list, bank_list, language_setting, 1, 3);


	if (service_choose == 1) {
		bank_list[bank_choose]->create_account(language_setting);
	}
	if (service_choose == 2) {
		bank_list[bank_choose]->makeCard_session(language_setting);
	}
	if (service_choose == 3) {
		Account* input_account = bank_list[bank_choose]->search_account_number(language_setting);
		if (input_account == NULL) { return; }
		string input_password;
		int a = 3;
		while (true) {

			if (a == 0) {
				if (language_setting == 1) { cout << "You write wrong password 3 times. " << endl; }
				if (language_setting == 2) { cout << "비밀번호 3회 틀렸습니다." << endl; }
				cout << "==================== < Account History Session End! > ====================" << endl;
				return;
			}
			if (language_setting == 1) {
				cout << a << " attempts left." << endl;
				cout << "Password : ";
			}
			if (language_setting == 2) {
				cout << a << " 회 남음." << endl;
				cout << "비밀번호 : ";
			}

			// password is string!
			a--;
			//cin >> input_password;
			input_password = Qsearch(ATM_list, bank_list);
			//cout << input_password;

			if (input_account->getPassword() == input_password) {
				if (language_setting == 1) { cout << "Correct password." << endl; }
				if (language_setting == 2) { cout << "옳은 비밀번호." << endl; }
				cout << endl;
				input_account->printHistory();
				cout << "==================== < Account History Session End! > ====================" << endl;
				return;
			}
		}
	}

	cout << "==================== < Bank Service Session End! > ====================" << endl;
}

void ATMMake(vector<ATM*>& ATM_list, vector<Bank*>& bank_list, int* fee_list1[4], int* fee_list2[4], int language_setting, vector<Bank*>* blist, vector<ATM*>* alist) {
	cout << "==================== < ATM Duplicate Session > ====================" << endl;
	//input : primary bank name, serial number, type, language, initial fund
	//constant : 
	if (language_setting == 1) { cout << "Please choose Bank number that you want to make ATM for : " << endl; }
	if (language_setting == 2) { cout << "ATM을 설치할 은행을 선택하세요 : " << endl; }
	for (int i = 0; i < bank_list.size(); i++) {
		cout << "[" << i << "] " << bank_list[i]->getBankName() << " Bank" << endl;
	}

	int bank_choose = 0;
	// cin >> bank_choose;
	bank_choose = no_error_range(ATM_list, bank_list, language_setting, 0, (int) bank_list.size() - 1);

	if (bank_choose >= bank_list.size()) {
		if (language_setting == 1) { cout << "The corresponding bank does not exist." << endl; }
		if (language_setting == 2) { cout << "해당하는 은행이 존재하지 않습니다." << endl; }
		cout << "==================== < ATM Make Session End! > ====================" << endl;
		return;
	}
	if (language_setting == 1) { cout << bank_list[bank_choose]->getBankName() << " bank is selected." << endl; }
	if (language_setting == 2) { cout << bank_list[bank_choose]->getBankName() << " 은행이 선택되었습니다.." << endl; }

	string serial = "";
	for (int i = 0; i < 6 - to_string(ATM_list.size()).size(); i++) {
		serial += "0";
	}
	serial += to_string(ATM_list.size());
	if (language_setting == 1) { cout << "Serial number of ATM will be automatically issued. Serial number of this ATM is " << serial << "." << endl; }
	if (language_setting == 2) { cout << "ATM의 일련번호가 자동으로 발급됩니다. 본 ATM의 일련번호는 " << serial << "입니다." << endl; }

	if (language_setting == 1) { cout << "Please input ATM type." << endl << "[1] Single Bank ATM" << endl << "[2] Multi Bank ATM" << endl; }
	if (language_setting == 2) { cout << "ATM의 type을 입력하세요." << endl << "[1] Single Bank ATM" << endl << "[2] Multi Bank ATM" << endl; }

	int type = 0;
	// cin >> type;
	type = no_error_range(ATM_list, bank_list, language_setting, 1, 2);

	if (language_setting == 1) { cout << "Please input ATM language type." << endl << "[1] Unilingual ATM" << endl << "[2] Bilingual ATM" << endl; }
	if (language_setting == 2) { cout << "ATM의 언어 type을 선택해 주세요." << endl << "[1] Unilingual ATM" << endl << "[2] Bilingual ATM" << endl; }

	int language = 0;
	// cin >> language;
	language = no_error_range(ATM_list, bank_list, language_setting, 1, 2);

	int* fund[4] = { 0, };
	for (int i = 0; i < 4; i++) {
		fund[i] = new int(0);
	}
	if (language_setting == 1) { cout << "Please Enter the Amount of 1000 won bills." << endl; }
	if (language_setting == 2) { cout << "1000원권의 수를 입력해 주세요." << endl; }
	// cin >> *(fund[0]);
	*(fund[0]) = no_error(ATM_list, bank_list, language_setting);

	if (language_setting == 1) { cout << "Please Enter the Amount of 5000 won bills." << endl; }
	if (language_setting == 2) { cout << "5000원권의 수를 입력해 주세요." << endl; }
	// cin >> *(fund[1]);
	*(fund[1]) = no_error(ATM_list, bank_list, language_setting);

	if (language_setting == 1) { cout << "Please Enter the Amount of 10000 won bills." << endl; }
	if (language_setting == 2) { cout << "10000원권의 수를 입력해 주세요." << endl; }
	// cin >> *(fund[2]);
	*(fund[2]) = no_error(ATM_list, bank_list, language_setting);

	if (language_setting == 1) { cout << "Please Enter the Amount of 50000 won bills." << endl; }
	if (language_setting == 2) { cout << "50000원권의 수를 입력해 주세요." << endl; }
	// cin >> *(fund[3]);
	*(fund[3]) = no_error(ATM_list, bank_list, language_setting);

	switch (type) {
	case 1:
		//Single(bank_list[bank_choose].getBankName(), serial, language, fund, fee_list1);
		ATM_list.push_back(new Single(bank_list[bank_choose], serial, language, fund, fee_list1, blist, alist));
		cout << "==================== < ATM Duplicate Session End! > ====================" << endl;
		break;
	case 2:
		//Multi(bank_list[bank_choose].getBankName(), serial, language, fund, fee_list1, fee_list2);
		ATM_list.push_back(new Multi(bank_list[bank_choose], serial, language, fund, fee_list1, fee_list2, blist, alist));
		cout << "==================== < ATM Duplicate Session End! > ====================" << endl;
		break;
	default:
		break;
	}

	return;
}

void ATMService(vector<ATM*> ATM_list, vector<Bank*> bank_list, int language_setting) {
	cout << "==================== < ATM Service Session > ====================" << endl;

	if (ATM_list.size() == 0) {
		if (language_setting == 1) { cout << "There is no ATM existed." << endl; }
		if (language_setting == 2) { cout << "존재하는 ATM이 없습니다." << endl; }
		return;
	}

	if (language_setting == 1) { cout << "Please choose ATM number that you want to use for." << endl; }
	if (language_setting == 2) { cout << "거래를 진행하고 싶은 ATM을 선택해주세요." << endl; }

	for (int i = 0; i < ATM_list.size(); i++) {
		cout << "[" << i << "] ATM " << ATM_list[i]->getSerial() << " [Bank " << ATM_list[i]->getPrimary()->getBankName() << "/" << ATM_list[i]->getType() << "/" << ATM_list[i]->getLangType() << "]" << endl;
	}
	cout << endl;
	if (language_setting == 1) { cout << "ATM number : "; }
	if (language_setting == 2) { cout << "ATM 번호 : "; }

	int ATM_choose = 0;
	// cin >> ATM_choose;
	ATM_choose = no_error_range(ATM_list, bank_list, language_setting, 0, (int) ATM_list.size() - 1);

	//if (ATM_choose >= ATM_list.size()) {
	//	if (language_setting == 1) { cout << "The corresponding ATM does not exist." << endl; }
	//	if (language_setting == 2) { cout << "해당하는 ATM이 존재하지 않습니다." << endl; }
	//	cout << "==================== < ATM Service Session End! > ====================" << endl;
	//	return;
	//}

	if (language_setting == 1) { cout << ATM_list[ATM_choose]->getSerial() << " ATM is selected." << endl << "Connecting to ATM..." << endl; }
	if (language_setting == 2) { cout << ATM_list[ATM_choose]->getSerial() << " ATM이 선택되었습니다." << endl << "ATM에 접속합니다..." << endl; }

	ATM_list[ATM_choose]->session(bank_list);
	cout << "==================== < ATM Service Session End! > ====================" << endl;
	return;
}

Account* BankSearch(vector<ATM*>& ATM_list, vector<Bank*> bank_list, int language_setting) {
	cout << "==================== < Bank Search Session > ====================" << endl;
	if (language_setting == 1) {
		cout << "Please choose searach service number that you want." << endl;
		cout << "[1] By Account Number" << endl;
		cout << "[2] By Card Number" << endl;
		cout << endl;
		cout << "Search service number : ";
	}
	if (language_setting == 2) {
		cout << "원하는 조회 서비스의 번호를 골라주세요.." << endl;
		cout << "[1] 계좌 번호로" << endl;
		cout << "[2] 카드 번호로" << endl;
		cout << endl;
		cout << "Search service number : ";
	}

	int search_choose = 0;
	// cin >> search_choose;
	search_choose = no_error_range(ATM_list, bank_list, language_setting, 1, 2);

	while (true) {
		if (search_choose == 1) {
			string account_number;
			if (language_setting == 1) { cout << "Please write your account number : "; }
			if (language_setting == 2) { cout << "계좌번호를 입력해주세요. : "; }

			//cin >> account_number;
			account_number = Qsearch(ATM_list, bank_list);

			for (int i = 0; i < bank_list.size(); i++) {
				if (bank_list[i]->search_account_number_BankSearch(account_number, language_setting) != NULL) {
					cout << "==================== < Bank Search Session End! > ====================" << endl;
					return bank_list[i]->search_account_number_BankSearch(account_number, language_setting);
				}
			}
			if (language_setting == 1) { cout << "Account is not found." << endl; }
			if (language_setting == 2) { cout << "계좌를 찾을 수 없습니다." << endl; }
		}
		if (search_choose == 2) {
			string card_number;
			if (language_setting == 1) { cout << "Please write your card number : "; }
			if (language_setting == 2) { cout << "카드 번호를 입력해주세요. : "; }

			//cin >> card_number;
			card_number = Qsearch(ATM_list, bank_list);

			for (int i = 0; i < bank_list.size(); i++) {
				if (bank_list[i]->search_account_card_BankSearch(card_number, language_setting) != NULL) {
					cout << "==================== < Bank Search Session End! > ====================" << endl;
					return bank_list[i]->search_account_card_BankSearch(card_number, language_setting);
				}
			}
			if (language_setting == 1) { cout << "Account is not found." << endl; }
			if (language_setting == 2) { cout << "계좌를 찾을 수 없습니다." << endl; }
		}
	}
	cout << "==================== < Bank Search Session End! > ====================" << endl;
}

void feeConfig(vector<ATM*>& ATM_list, vector<Bank*> bank_list, int* fee_list1[4], int* fee_list2[4], int language_setting) {
	if (language_setting == 1) { cout << "Please Enter the deposit fee for primary bank." << endl; }
	if (language_setting == 2) { cout << "Primary bank 계좌에서의 입금 수수료를 입력해 주세요." << endl; }
	// cin >> *(fee_list1[0]);
	*(fee_list1[0]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the withdrawal fee for primary bank." << endl; }
	if (language_setting == 2) { cout << "Primary bank 계좌에서의 출금 수수료를 입력해 주세요." << endl; }
	// cin >> *(fee_list1[1]);
	*(fee_list1[1]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the account transfer fee between primary banks." << endl; }
	if (language_setting == 2) { cout << "Primary bank 계좌끼리의 송금 수수료를 입력해 주세요." << endl; }
	// cin >> *(fee_list1[2]);
	*(fee_list1[2]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the cash transfer fee." << endl; }
	if (language_setting == 2) { cout << "현금 송금 수수료를 입력해 주세요." << endl; }
	// cin >> *(fee_list1[3]);
	*(fee_list1[3]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the deposit fee for non-primary bank." << endl; }
	if (language_setting == 2) { cout << "Non-Primary bank 계좌에서의 입금 수수료를 입력해 주세요." << endl; }
	// cin >> *(fee_list2[0]);
	*(fee_list2[0]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the withdrawal fee for non-primary bank." << endl; }
	if (language_setting == 2) { cout << "Non-primary bank 계좌에서의 출금 수수료를 입력해 주세요." << endl; }
	// cin >> *(fee_list2[1]);
	*(fee_list2[1]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the account transfer fee between primary bank and non-primary banks." << endl; }
	if (language_setting == 2) { cout << "Primary bank 계좌와 non-primary bank 계좌 사이의 송금 수수료를 입력해 주세요." << endl; }
	// cin >> *(fee_list2[2]);
	*(fee_list2[2]) = no_error(ATM_list, bank_list, language_setting);
	if (language_setting == 1) { cout << "Please Enter the account transfer fee between non-primary banks." << endl; }
	if (language_setting == 2) { cout << "Non-primary bank 계좌끼리의 송금 수수료를 입력해 주세요." << endl; }
	// cin >> *(fee_list2[3]);
	*(fee_list2[3]) = no_error(ATM_list, bank_list, language_setting);
	return;
}

int LanguageService(vector<ATM*>& ATM_list, vector<Bank*> bank_list, int language_setting) {
	cout << "===========================<Language Change Session>===========================" << endl;
	if (language_setting == 1) {
		cout << "Select language" << endl;
		cout << "[1] English" << endl;
		cout << "[2] 한국어" << endl;
		cout << endl;
		cout << "Please Enter the Number: ";
	}
	if (language_setting == 2) {
		cout << "언어선택" << endl;
		cout << "[1] English" << endl;
		cout << "[2] 한국어" << endl;
		cout << endl;
		cout << "번호 입력 : ";
	}

	int setting = 0;
	// cin >> setting;
	setting = no_error_range(ATM_list, bank_list, language_setting, 1, 2);
	language_setting = setting;

	return language_setting;
}

void Admin(vector<ATM*> ATM_list, vector<Bank*> bank_list, int language_setting) {
	string admin_password = "admin";

	// \t
	if (language_setting == 1) {
		cout << "This is Admin session." << endl;
		cout << endl;
		cout << "Please Enter the password : ";
	}
	if (language_setting == 2) {
		cout << "관리자 세션입니다." << endl;
		cout << endl;
		cout << "비밀번호를 입력해주세요 : ";
	}
	string input_password;

	int a = 0;
	for (int i = 0; i < 3; i++) {

		//cin >> input_password;
		input_password = Qsearch(ATM_list, bank_list);

		if (admin_password == input_password) {
			if (language_setting == 1) { cout << "Admin confirmed." << endl; }
			if (language_setting == 2) { cout << "관리자 확인 완료." << endl; }
			a = 1;
			break;
		}
		if (a == 0) {
			if (language_setting == 1) { cout << 2 - i << " attempt left." << endl; }
			if (language_setting == 2) { cout << 2 - i << " 회 남음." << endl; }
		}
	}

	if (a == 0) {
		if (language_setting == 1) { cout << "You write wrong password 3 times." << endl; }
		if (language_setting == 2) { cout << "잘못된 비밀번호를 3회 입력하셨습니다." << endl; }
		return;
	}

	if (a == 1) {
		if (language_setting == 1) {
			cout << "Please Select the task you want to do." << endl;
			cout << "[1] Bank & Account Info" << endl;
			cout << "[2] ATM Info" << endl;
			cout << endl;
			cout << "Please Enter the Number : ";
		}
		if (language_setting == 2) {
			cout << "진행하고자 하는 업무를 선택하세요." << endl;
			cout << "[1] 은행 & 계좌 정보" << endl;
			cout << "[2] ATM 정보" << endl;
			cout << endl;
			cout << "숫자를 입력해주세요 : ";
		}
	}

	int choice = 0;
	// cin >> choice;
	choice = no_error_range(ATM_list, bank_list, language_setting, 1, 2);

	if (choice == 1) {
		if (language_setting == 1) {
			cout << "==================== < Bank & Account Info > ====================" << endl;
			for (int i = 0; i < bank_list.size(); i++) {
				cout << endl;
				cout << "Bank : " << bank_list[i]->getBankName() << endl;
				cout << endl;

				for (int j = 0; j < bank_list[i]->get_account().size(); j++) {
					cout << "Name : " << bank_list[i]->get_account()[j]->getUserName() << " ID : " << bank_list[i]->get_account()[j]->getAccountNumber() << " Password : " << bank_list[i]->get_account()[j]->getPassword() << " Available Fund : " << bank_list[i]->get_account()[j]->getAvailableFund() << endl;
					cout << "Card : ";
					for (int k = 0; k < bank_list[i]->get_account()[j]->getCardNumber().size(); k++) {
						cout << bank_list[i]->get_account()[j]->getCardNumber()[k] << "\t";
					}
					cout << endl;
				}
				cout << "========================================" << endl;
			}
			cout << "==================== < Bank & Account Info End!> ====================" << endl;
		}
		if (language_setting == 2) {
			cout << "==================== < Bank & Account Info > ====================" << endl;
			for (int i = 0; i < bank_list.size(); i++) {
				cout << endl;
				cout << "은행 : " << bank_list[i]->getBankName() << endl;
				cout << endl;

				for (int j = 0; j < bank_list[i]->get_account().size(); j++) {
					cout << "예금주 : " << bank_list[i]->get_account()[j]->getUserName() << " 계좌번호 : " << bank_list[i]->get_account()[j]->getAccountNumber() << " 비밀번호 : " << bank_list[i]->get_account()[j]->getPassword() << " 계좌잔고 : " << bank_list[i]->get_account()[j]->getAvailableFund() << endl;
					cout << "카드번호 : ";
					for (int k = 0; k < bank_list[i]->get_account()[j]->getCardNumber().size(); k++) {
						cout << bank_list[i]->get_account()[j]->getCardNumber()[k] << "\t";
					}
					cout << endl;
				}
				cout << "========================================" << endl;
			}
			cout << "==================== < Bank & Account Info End!> ====================" << endl;
		}
	}

	if (choice == 2) {
		if (language_setting == 1) {
			cout << "==================== < ATM Info > ====================" << endl;
			for (int i = 0; i < ATM_list.size(); i++) {
				cout << endl;
				cout << "ATM " << "[" << i << "] " << "Primary Bank : " << ATM_list[i]->getPrimary()->getBankName() << " " << ATM_list[i]->getType() << " " << ATM_list[i]->getLangType() << endl;
				cout << "Remaing cash : " << 1000 * ATM_list[i]->get1000() + 5000 * ATM_list[i]->get5000() + 10000 * ATM_list[i]->get10000() + 50000 * ATM_list[i]->get50000() << " (1000 : " << ATM_list[i]->get1000() << ", 5000 : " << ATM_list[i]->get5000() << ", 10000 : " << ATM_list[i]->get10000() << ", 50000 : " << ATM_list[i]->get50000() << ")" << endl;
			}
			cout << "==================== < ATM Info End!> ====================" << endl;
		}
		if (language_setting == 2) {
			cout << "==================== < ATM Info > ====================" << endl;
			for (int i = 0; i < ATM_list.size(); i++) {
				cout << endl;
				cout << "ATM " << "[" << i << "] " << "Primary Bank : " << ATM_list[i]->getPrimary()->getBankName() << " " << ATM_list[i]->getType() << " " << ATM_list[i]->getLangType() << endl;
				cout << "잔여현금 : " << 1000 * ATM_list[i]->get1000() + 5000 * ATM_list[i]->get5000() + 10000 * ATM_list[i]->get10000() + 50000 * ATM_list[i]->get50000() << " (1000 : " << ATM_list[i]->get1000() << ", 5000 : " << ATM_list[i]->get5000() << ", 10000 : " << ATM_list[i]->get10000() << ", 50000 : " << ATM_list[i]->get50000() << ")" << endl;
			}
			cout << "==================== < ATM Info End!> ====================" << endl;
		}
	}
}

int main() {
	vector<Bank*> bank_list;
	vector<ATM*> ATM_list;
	vector<Bank*>* blist = &bank_list;
	vector<ATM*>* alist = &ATM_list;

	int* fee1[4] = { 0, };
	int* fee2[4] = { 0, };
	for (int i = 0; i < 4; i++) {
		fee1[i] = new int(0);
	}
	for (int i = 0; i < 4; i++) {
		fee2[i] = new int(0);
	}

	bool onSession = true;
	int language_setting = 1; // 1: English, 2: Korean

	while (onSession) {
		cout << "===========================<Welcome to Bank System Service>===========================" << endl;
		if (language_setting == 1) {
			cout << "Please Select the task you want to do." << endl;
			cout << "[1] Make Bank" << endl;
			cout << "[2] Banking Service (Make Account or Make Card)" << endl;
			cout << "[3] Make ATM" << endl;
			cout << "[4] ATM Service (Deposit, Withdraw, etc...)" << endl;
			cout << "[5] Change Language Setting" << endl;
			cout << "[6] Shut Down the Bank System Service" << endl;
			cout << "[7] Fee Configuration" << endl;
			cout << "[8] Admin" << endl;
			cout << endl;

			cout << "Please Enter the Number : ";
		}
		if (language_setting == 2) {
			cout << "진행하고자 하는 업무를 선택하세요." << endl;
			cout << "[1] 은행 만들기" << endl;
			cout << "[2] 은행 서비스 (계좌 및 카드 생성)" << endl;
			cout << "[3] ATM 만들기" << endl;
			cout << "[4] ATM 서비스 (입금, 출금 등...)" << endl;
			cout << "[5] 언어 설정 변경" << endl;
			cout << "[6] Bank System Service 종료" << endl;
			cout << "[7] 수수료 설정" << endl;
			cout << "[8] 관리자" << endl;
			cout << endl;
			cout << "숫자를 입력해주세요 : ";
		}

		int session_chice = 0;
		session_chice = no_error_range(ATM_list, bank_list, language_setting, 1, 8);

		switch (session_chice) {
		case 1:
			BankMake(ATM_list, bank_list, language_setting, blist, alist);
			break;
		case 2:
			BankService(ATM_list, bank_list, language_setting);
			break;
		case 3:
			ATMMake(ATM_list, bank_list, fee1, fee2, language_setting, blist, alist);
			break;
		case 4:
			ATMService(ATM_list, bank_list, language_setting);
			break;
		case 5:
			language_setting = LanguageService(ATM_list, bank_list, language_setting);
			break;
		case 6:
			onSession = false;
			break;
		case 7:
			feeConfig(ATM_list, bank_list, fee1, fee2, language_setting);
			break;
		case 8:
			Admin(ATM_list, bank_list, language_setting);
		}
		cout << "===========================<End System Session>===========================" << endl;
	}

	cout << "===========================<End System>===========================" << endl;

	for (int i = 0; i < 4; i++) {
		delete fee1[i];
	}
	for (int i = 0; i < 4; i++) {
		delete fee2[i];
	}
	for (int i = 0; i < (int)bank_list.size(); i++) {
		delete bank_list[i];
	}
	for (int i = 0; i < (int)ATM_list.size(); i++) {
		delete ATM_list[i];
	}

	return 0;
}



