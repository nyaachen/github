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

std::ostream &PUKE::operator<<(std::ostream &os, const PUKE::Card &t) {
	if (t.c != PUKE::CARD_INVALID) os << PUKE::card_string[t.c];
	return os;
}


PUKE::CardsLinkedList::Node::Node() : c(PUKE::Card(PUKE::CARD_INVALID)), cnt(0) {}

PUKE::CardsLinkedList::Node::Node(const Card &card, size_t count) : c(card), cnt(count) {}

PUKE::CardsLinkedList::Node::~Node() = default;

PUKE::Card PUKE::CardsLinkedList::Node::getCard() const {
	return c;
}
PUKE::Card PUKE::CardsLinkedList::Node::setCard(const PUKE::Card &card) {
	c = card;
	return c;
}
size_t PUKE::CardsLinkedList::Node::getcnt() const {
	return cnt;
}
size_t PUKE::CardsLinkedList::Node::setcnt(size_t count) {
	cnt = count;
	return cnt;
}
