#ifndef PUKE_H
#define PUKE_H

#include <iostream>
#include <array>
#include <string>

namespace PUKE {
	// 卡牌类型的机内表示
	enum Cardtype {
		CARD_3 = 0,
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
		CARD_JOKER,
		CARD_INVALID = -1
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
	// TODO : 潜在的重复定义bug
	class Card {
	private:
		Cardtype c;
	public:
		Card();
		Card(Cardtype i);
		~Card();

		// 比较两张牌的大小
		bool operator<(const Card &t);
		bool operator<=(const Card &t);
		bool operator>(const Card &t);
		bool operator>=(const Card &t);
		bool operator==(const Card &t);
		bool operator!=(const Card &t);

		// 输入与输出
		friend std::istream &operator>>(std::istream &is, Card &t);
		friend std::ostream &operator<<(std::ostream &os, const Card &t);
	};
	// 类Card的友元声明
	std::istream &operator>>(std::istream &is, Card &t);
	std::ostream &operator<<(std::ostream &os, const Card &t);

	// 一组卡牌的机内表示
	namespace CardsLinkedList {
		class Node {
		private:
			Card c;
			size_t cnt;
		public:
			Node();
			Node(const Card &card, size_t count);
			~Node();
			Card getCard() const;
			Card setCard(const Card &card);
			size_t getcnt() const;
			size_t setcnt(size_t count);
		}
	}

	class Cards {
	private:
		std::array<CardsLinkedList::Node, 15> cardsarray;
	public:
		Cards();
		~Cards();

	}
} // 名称空间结束

#endif
