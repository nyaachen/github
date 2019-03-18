#include "puke.h"

PUKE::Card::Card() : c(PUKE::CARD_INVALID) {}
PUKE::Card::Card(Cardtype i) : c(i) {}
PUKE::Card::~Card() = default;

// 比较两张牌的大小
bool PUKE::Card::operator<(const Card &t) {
	return c < t.c;
}
bool PUKE::Card::operator<=(const Card &t) {
	return c <= t.c;
}
bool PUKE::Card::operator>(const Card &t) {
	return c > t.c;
}
bool PUKE::Card::operator>=(const Card &t) {
	return c >= t.c;
}
bool PUKE::Card::operator==(const Card &t) {
	return c == t.c;
}
bool PUKE::Card::operator!=(const Card &t) {
	return c != t.c;
}

std::istream &PUKE::operator>>(std::istream &is, PUKE::Card &t) {
	string t;
	is >> t;
	size_t i=0;
	while (i < 15) {
		if (t == PUKE::card_string[i]) {
			t.c = i;
			break;
		}
		else ++i;
	}
	if (i == 15) t.c = -1;
	return is;
}
std::ostream &PUKE::operator<<(std::ostream &os, const PUKE::Card &t);
