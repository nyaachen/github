#include <iostream>
#include <string>
#include <vector>
#include <array>
using std::string;
using std::cout;
using std::cin;
using std::endl;

const std::array<string, 15> CARD_STRING(
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
	std::array<int,15> cnt;
public:
	Card() : cnt({0}) {}
	~Card();
	int &operator[](size_t i) {
		return cnt[i];
	}
	int operator[](size_t i) const {
		return cnt[i];
	}
};

void print(const Card &c) {
	for (int i=14; i>0; --i) {
		if (c[i]) cout << CARD_STRING[i] << " ";
	}
	cout << endl;
}

// 王炸是各有一张大小王，并且没有其他多余的牌
bool is_wangzha(const Card &c) {
	bool others = true;
	for(size_t i=0; i < 13; ++i) {
		if (c[i] != 0) others = false;
	}
	return others && c[13]==1 && c[14]==1;
}
// 炸弹是只有一种牌，并且有四张 标识是4的大小
bool is_zhadan(const Card &c) {
	bool find = false;
	bool dup = false;
	for (size_t i=0; i < 15; ++i) {
		if(c[i] != 0) { // 有牌
			if (!find && c[i] == 4) find = true; // 第一次发现四张一样的牌
			else dup=true; // 要么不是第一次发现，要么不是四张
		}
	}
	return find && !dup;
}
// 四带二是有四张牌，并且带了两种1或2张的牌。不允许带俩王 标识是4的大小和带牌数量
bool is_sidaier(const Card &c) {
	bool find_4 = false;
	bool dup = false;
	bool first(false), second(false);
	int cnt(0);
	for (size_t i=0; i < 13; ++i) {
		if (c[i] != 0) {
			if (c[i] == 4) find_4 = true;
			else {
				if (!first) {
					first = true;
					cnt = c[i];
				}
				else if (!second && c[i] == cnt) {
					second = true;
				}
				else {
					dup = true;
				}
			}
		}
	}
	return find_4 && first && second && !dup;
}
// 三带 三带是一个三加上可选的一个带牌，标识是3的大小和带牌数量
bool is_sandai(const Card &c) {
	bool find(false), dup(false);
	int cnt(0);
	for (size_t i=0; i < 13; ++i) {
		if (c[i] != 0) {
			if (!find && c[i] == 3) find = true;
			else if (cnt == 0) cnt = c[i];
			else dup = true;
		}
	}
	return find && !dup;
}
// 顺子 是五张以上的连续牌
bool is_shunzi(const Card &c) 

// 对子
// 连对
// 飞机 飞机是三连续的多组三带 特征是三连数目和带牌数目

bool special_card(const Card &c) {
	return is_wangzha(c) || is_zhadan(c);
}
bool cmpCards(const Card &myCard, const Card &targetCard, Card &result) {
	if (!special_card(targetCard)) {

	}
}
