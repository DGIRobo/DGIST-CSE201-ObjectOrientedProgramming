#include <iostream>
#include <string>

#include "Account.h"

using namespace std;

int main() {
	// Account Test Code
	Account a1("kakao", "lee", "abc");
	cout << a1.getBankName() << endl;
	cout << a1.getUserName() << endl;
	cout << a1.getPassword() << endl;
	a1.printHistory();
}