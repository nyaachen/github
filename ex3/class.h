#ifndef PUKE_H
#define PUKE_H

#include <iostream>
#include <array>
#include <string>

namespace DouDiZhu {
	// 卡牌类型的机内表示
	enum Cardtype {
		CARD_3,
		CARD_4,
		CARD_5,
		CARD_6,
		CARD_7,
		CARD_8,
		CARD_9,
		CARD_10,
		CARD_J,
		CARD_Q,
		CARD_K,
		CARD_A,
		CARD_2,
		CARD_joker,
		CARD_JOKER
	};
	// 卡牌类型的字符串表示
	const std::array<std::string, 15> card_string(
		{
			"3",
			"4",
			"5",
			"6",
			"7",
			"8",
			"9",
			"10",
			"J",
			"Q",
			"K",
			"A",
			"2",
			"joker",
			"JOKER"
		});

	class Card {
	private:
		Cardtype c;
	public:
		Card(Cardtype i) : c(i) {}
		~Card();

		// 比较两张牌的大小
		bool operator<(const Card &t) {
			return c < t.c;
		}
		bool operator<=(const Card &t) {
			return c <= t.c;
		}
		bool operator>(const Card &t) {
			return c > t.c;
		}
		bool operator>=(const Card &t) {
			return c >= t.c;
		}
		bool operator==(const Card &t) {
			return c == t.c;
		}
		bool operator!=(const Card &t) {
			return c != t.c;
		}

		// 输入与输出
		friend std::istream &operator>>(std::istream &is, Card &c);
		friend std::ostream &operator<<(std::ostream &os, const Card &c);
	};

} // 名称空间结束

#endif
