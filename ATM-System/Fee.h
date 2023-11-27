#pragma once
#include <string>
#include <vector>

class Fee {
private:
	int primary_deposit_fee = 0;
	int primary_withdrawal_fee = 0;
	int primary_transfer_fee = 0;
	int non_deposit_fee = 0;
	int non_withdrawal_fee = 0;
	int non_primary_transfer_fee = 0;
	int non_non_transfer_fee = 0;
	int cash_transfer_fee = 0;
protected:
public:
	Fee(int a, int b, int c, int d, int e, int f, int g, int h);
	~Fee();
};