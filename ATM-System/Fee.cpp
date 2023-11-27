#include "Fee.h"

Fee::Fee(int a, int b, int c, int d, int e, int f, int g, int h) {
	primary_deposit_fee = a;
	primary_withdrawal_fee = b;
	primary_transfer_fee = c;
	non_deposit_fee = d;
	non_withdrawal_fee = e;
	non_primary_transfer_fee = f;
	non_non_transfer_fee = g;
	cash_transfer_fee = h;
}

int Fee::getPD() {
	return primary_deposit_fee;
}
int Fee::getPW() {
	return primary_withdrawal_fee;
}
int Fee::getPPT() {
	return primary_transfer_fee;
}
int Fee::getND() {
	return non_deposit_fee;
}
int Fee::getNW() {
	return non_withdrawal_fee;
}
int Fee::getPNT() {
	return non_primary_transfer_fee;
}

int Fee::getNNT() {
	return non_non_transfer_fee;
}
int Fee::CT() {
	return cash_transfer_fee;
}