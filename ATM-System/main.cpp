#include <iostream>
#include <string>

#include "Account.h"
#include "Bank.h"
#include "ATM.h"

using namespace std;

int main() {
	// Account Test Code
	Bank Kakao("kakao");
	Account a1(&Kakao, "lee", "abc");
	cout << a1.getBankName() << endl;
	cout << a1.getUserName() << endl;
	cout << a1.getPassword() << endl;
	a1.printHistory();
}