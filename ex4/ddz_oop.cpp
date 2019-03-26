// Please use UTF-8 encoding so that the comments can be displayed correctly.
// 标注TODO的是你需要完善的地方
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>

// #include "myddz.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
using std::string;
using std::cout;
using std::cin;
using std::endl;
namespace nyaachen {
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
		Card &insert(const string &s) {
			for (size_t i=0; i < 15; ++i) {
				if (s == CARD_STRING[i]) {
					++cnt[i];
					break;
				}
			}
			return *this;
		}
		Card() : cnt({0}) {}
		~Card() = default;
		int &operator[](size_t i) {
			return cnt[i];
		}
		int operator[](size_t i) const {
			return cnt[i];
		}
		Card operator-(const Card &c) const {
			Card tmp = *this;
			for (size_t i=0; i < 15; ++i) {
				tmp[i] -= c[i];
			}
			return tmp;
		}
		Card &operator-=(const Card &c) {
			for (size_t i=0; i < 15; ++i) {
				this->cnt[i] -= c[i];
			}
			return *this;
		}
		void clear() {
			cnt = std::array<int, 15> ({0});
		}
		bool is_empty() {
			for (size_t i=0; i < 15; ++i) {
				if (cnt[i] != 0) return false;
			}
			return true;
		}
		bool subset(const Card &c) const {
			for (size_t i=0; i < 15; ++i) {
				if (cnt[i] < c.cnt[i]) return false;
			}
			return true;
		}
	};

	std::vector<std::string> print(const Card &c) {
		std::vector<std::string> t;
		for (int i=14; i>=0; --i) {
			for (int j=0; j < c[i]; ++j) t.push_back(CARD_STRING[i]);
		}
		return t;
	}

	// 王炸是各有一张大小王，并且没有其他多余的牌
	bool is_wangzha(const Card &c) {
		bool others = true;
		for(size_t i=0; i < 13; ++i) {
			if (c[i] != 0) others = false;
		}
		return others && c[13]==1 && c[14]==1;
	}
	bool find_a_wangzha(const Card &myCard, const Card &targetCard, Card &result) {
		if (myCard[13] == 1 && myCard[14] == 1) {
			result[13] = 1;
			result[14] = 1;
			return true;
		}
		return false;
	}
	bool find_a_wangzha(const Card &myCard, Card &result) {
		if (myCard[13] == 1 && myCard[14] == 1) {
			result[13] = 1;
			result[14] = 1;
			return true;
		}
		return false;
	}
	// 炸弹是只有一种牌，并且有四张 标识是4的大小
	bool is_zhadan(const Card &c) {
		bool find = false;
		bool dup = false;
		for (size_t i=0; i < 13; ++i) {
			if(c[i] != 0) { // 有牌
				if (!find && c[i] == 4) find = true; // 第一次发现四张一样的牌
				else dup=true; // 要么不是第一次发现，要么不是四张
			}
		}
		return find && !dup;
	}
	bool find_a_zhadan(const Card &myCard, const Card &targetCard, Card &result) {
		size_t pos(0);
		for (size_t i=0; i < 13; ++i) {
			if (targetCard[i] != 0) {
				pos = i;
				break;
			}
		}
		for (size_t i=pos+1; i < 13; ++i) {
			if (myCard[i] == 4) {
				result[i] = 4;
				return true;
			}
		}
		return false;
	}
	bool find_a_zhadan(const Card &myCard, Card &result) {
		for (size_t i=0; i < 13; ++i) {
			if (myCard[i] == 4) {
				result[i] = 4;
				return true;
			}
		}
		return false;
	}
	// 四带二是有四张牌，并且带了两种1或2张的牌。不允许带的是俩王 标识是4的大小和带牌数量
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
	bool find_a_sidaier(const Card &myCard, const Card &targetCard, Card &result) {
		bool find_4(false);
		size_t pos_4(0);
		int cnt(0);
		for (size_t i=0; i < 13; ++i) {
			if (targetCard[i] != 0) {
				if (targetCard[i] == 4) {
					find_4 = true;
					pos_4 = i;
					if (cnt != 0) break;
				}
				else {
					cnt = targetCard[i];
					if (find_4) break;
				}
			}
		}
		find_4 = false;
		for (size_t i=pos_4+1; i < 13; ++i) {
			if (myCard[i] == 4) {
				find_4 = true;
				pos_4 = i;
				result[i] = 4;
				break;
			}
		}
		if (!find_4) return false;
		bool find1(false);
		for (size_t i=0; i < 13; ++i) {
			if (i != pos_4 && myCard[i] >= cnt) {
				result[i] = cnt;
				if (!find1) find1=true;
				else {
					if (result[13] == 1 && result[14] == 1) return false; // 带俩王
					return true;
				}
			}
		}
		return false;
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
	bool find_a_sandai(const Card &myCard, const Card &targetCard, Card &result) {
		size_t pos_3(0);
		int cnt(0);
		bool find_3(false);
		for (size_t i=0; i < 13; ++i) {
			if (targetCard[i] != 0) {
				if (targetCard[i] == 3) {
					pos_3 = i;
					find_3 = true;
					if (cnt != 0) break;
				}
				else {
					cnt = targetCard[i];
					if (find_3) break;
				}
			}
		}
		find_3 = false;
		for (size_t i=pos_3 +1; i < 15; ++i) {
			if (myCard[i] >= 3) {
				find_3 = true;
				pos_3 = i;
				result[i] = 3;
				break;
			}
		}
		if (!find_3) return false;
		if (cnt == 0) return true;
		for(size_t i=0; i < 13; ++i) {
			if (i != pos_3 && myCard[i] >= cnt) {
				result[i] = cnt;
				return true;
			}
		}
		return false;
	}
	// 顺子 是五张以上的连续牌
	bool is_shunzi(const Card &c) {
		bool conti(false), dup(false);
		int cnt(0);
		for (size_t i=0; i < 13; ++i) {
			if (c[i] != 0) {
				if (!conti && cnt != 0) dup=true;
				else {
					conti = true;
					++cnt;
				}
			}
			else conti = false;
		}
		return !dup && cnt>4;
	}
	bool find_a_shunzi(const Card &myCard, const Card &targetCard, Card &result) {
		size_t start(0);
		int cnt(0);
		for (size_t i=0; i < 13; ++i) {
			if (targetCard[i] != 0) {
				if (cnt == 0) start = i;
				++cnt;
			}
			else {
				if (cnt != 0) break;
			}
		}
		int cnt2(0);
		for (size_t i=start+1; i < 13; ++i) {
			if (myCard[i] > 0) {
				result[i] = 1;
				++cnt2;
				if (cnt2 == cnt) return true;
			}
			else {
				result.clear();
				cnt2 = 0;
			}
		}
		return false;
	}
	bool find_a_shunzi(const Card &myCard, Card &result) {
		int cnt(0);
		for (size_t i=0; i < 13; ++i) {
			if (myCard[i] > 0) {
				result[i] = 1;
				++cnt;
				if (cnt >= 5) return true;
			}
			else {
				result.clear();
				cnt = 0;
			}
		}
		return false;
	}
	// 对子 有一种牌有两张
	bool is_duizi(const Card &c) {
		bool find(false), dup(false);
		for (size_t i = 0; i < 13; ++i) {
			if (c[i] != 0) {
				if (!find && c[i] == 2) find=true;
				else dup=true;
			}
		}
		return find && !dup;
	}
	bool find_a_duizi(const Card &myCard, const Card &targetCard, Card &result) {
		size_t pos(0);
		for (size_t i=0; i < 13; ++i) {
			if (targetCard[i] != 0) {
				pos = i;
				break;
			}
		}
		for (size_t i=pos+1; i < 13; ++i) {
			if (myCard[i] >= 2) {
				result[i] = 2;
				return true;
			}
		}
		return false;
	}
	bool find_a_duizi(const Card &myCard, Card &result) {
		for (size_t i=0; i < 13; ++i) {
			if (myCard[i] >= 2) {
				result[i] = 2;
				return true;
			}
		}
		return false;
	}
	// 连对 连续三组以上的对子
	bool is_liandui(const Card &c) {
		bool conti(false), dup(false);
		int cnt(0);
		for (size_t i=0; i < 13; ++i) {
			if (c[i] != 0) {
				if (!conti && cnt != 0) dup = true;
				else if (c[i] != 2) dup = true;
				else {
					conti = true;
					++cnt;
				}
			}
			else conti=false;
		}
		return cnt > 2 && !dup;
	}
	bool find_a_liandui(const Card &myCard, const Card &targetCard, Card &result) {
		size_t pos(0);
		int cnt(0);
		for (size_t i=0; i < 13; ++i) {
			if (targetCard[i] != 0) {
				if (cnt != 0) pos = i;
				++cnt;
			}
			else if (cnt != 0) break;
		}
		int cnt2(0);
		for (size_t i=pos+1; i < 13; ++i) {
			if (myCard[i] >= 2) {
				result[i] = 2;
				++cnt2;
				if (cnt2 == cnt) return true;
			}
			else {
				result.clear();
				cnt2 = 0;
			}
		}
		return false;
	}
	// 飞机 飞机是三连续的多组三带 特征是三连数目和带牌数目
	bool is_feiji(const Card &c) {
		bool conti(false), dup(false);
		int cnt_3(0), cnt_dai(0), cnt(0);
		for (size_t i=0; i < 15; ++i) {
			if (c[i] != 0) {
				if (c[i] == 3) {
					if (!conti && cnt_3 != 0) dup = true;
					else {
						conti = true;
						++cnt_3;
					}
				}
				else {
					++cnt_dai;
					conti = false;
					if (cnt == 0) cnt = c[i];
					else if (c[i] != cnt) dup=true;
				}
			}
			else conti = false;
		}
		return !dup && cnt_3>1 && (cnt_dai==0 || cnt_dai == cnt_3);
	}
	bool find_a_feiji(const Card &myCard, const Card &targetCard, Card &result) {
		int cnt_3(0), cnt(0);
		size_t pos(0);
		for (size_t i=0; i < 15; ++i) {
			if(targetCard[i] == 3) {
				if (cnt_3 == 0) pos = i;
				++cnt_3;
			}
			else if (targetCard[i] != 0) {
				cnt = targetCard[i];
			}
		}
		bool find3(false), find(false);
		int t(0);
		for (size_t i=pos+1; i < 13; ++i) {
			if (myCard[i] >= 3) {
				if (t == 0) pos = i;
				result[i] = 3;
				++t;
				if (t == cnt_3) break;
			}
			else {
				t=0;
				result.clear();
			}
		}
		if (cnt == 0) return true;
		t=0;
		for (size_t i=0; i < 13; ++i) {
			if (!(i >= pos && i < pos + cnt_3)) {
				if (myCard[i] >= cnt) {
					result[i] = cnt;
					++t;
					if (t == cnt_3) return true;
				}
			}
		}
		return false;
	}
	// 单张
	bool is_danzhang(const Card &c) {
		bool find(false), dup(false);
		for (size_t i=0; i < 15; ++i) {
			if (c[i] == 1) {
				if (find) dup = true;
				else find=true;
			}
		}
		return find && !dup;
	}
	bool find_a_danzhang(const Card &myCard, const Card &targetCard, Card &result) {
		size_t pos(0);
		for (size_t i=0; i < 15; ++i) {
			if (targetCard[i] == 1) {
				pos = i;
				break;
			}
		}
		for (size_t i=pos+1; i < 15; ++i) {
			if (myCard[i] != 0) {
				result[i] = 1;
				return true;
			}
		}
		return false;
	}
	bool find_a_danzhang(const Card &myCard, Card &result) {
		for (size_t i=0; i < 15; ++i) {
			if (myCard[i] != 0) {
				result[i] = 1;
				return true;
			}
		}
		return false;
	}


	bool special_card(const Card &c) {
		return is_wangzha(c) || is_zhadan(c);
	}
	enum Cardtype{
		DANZHANG=1,
		SHUNZI,
		DUIZI,
		LIANDUI,
		SANDAI,
		FEIJI,
		SIDAIER,
		ZHADAN,
		WANGZHA,
		INVALID = -1
	};

	Cardtype find_cardtype(const Card &c) {
		if (is_wangzha(c)) return WANGZHA;
		if (is_zhadan(c)) return ZHADAN;
		if (is_sidaier(c)) return SIDAIER;
		if (is_feiji(c)) return FEIJI;
		if (is_sandai(c)) return SANDAI;
		if (is_liandui(c)) return LIANDUI;
		if (is_duizi(c)) return DUIZI;
		if (is_shunzi(c)) return SHUNZI;
		if (is_danzhang(c)) return DANZHANG;
		return INVALID;
	}

	bool cmpCards(const Card &myCard, const Card &targetCard, Card &result) {
		Cardtype t = find_cardtype(targetCard);
		bool ok(false);
		switch (t) {
			case DANZHANG:
			ok = find_a_danzhang(myCard, targetCard, result);
			break;
			case SHUNZI:
			ok = find_a_shunzi(myCard, targetCard, result);
			break;
			case DUIZI:
			ok = find_a_duizi(myCard, targetCard, result);
			break;
			case LIANDUI:
			ok = find_a_liandui(myCard, targetCard, result);
			break;
			case SANDAI:
			ok = find_a_sandai(myCard, targetCard, result);
			break;
			case FEIJI:
			ok = find_a_feiji(myCard, targetCard, result);
			break;
			case SIDAIER:
			ok = find_a_sidaier(myCard, targetCard, result);
			break;
			case ZHADAN:
			ok = find_a_zhadan(myCard, targetCard, result);
			if (!ok) {
				result.clear();
				return find_a_wangzha(myCard, targetCard, result);
			}
			break;
			case WANGZHA:
			return false;
			case INVALID:
			return false;
		}
		if (!ok) {
			result.clear();
			ok = find_a_zhadan(myCard, result);
			if (!ok)  {
				result.clear();
				return find_a_wangzha(myCard, targetCard, result);
			}
		}
		return ok;
	}
	bool freeCards(const Card &myCard, Card &result) {
		bool ok(false);
		ok = find_a_shunzi(myCard, result);
		if (!ok) {
			result.clear();
			ok = find_a_duizi(myCard, result);
			if (!ok) {
				result.clear();
				ok = find_a_zhadan(myCard, result);
				if (!ok) {
					result.clear();
					ok = find_a_wangzha(myCard, result);
					if (!ok) {
						result.clear();
						return find_a_danzhang(myCard, result);
					}
				}
			}
		}
		return ok;
	}
}

// end of myddz.h

using namespace std;


class Card : public string { // 继承自标准库字符串类
public:
    static const int N_CARD_VALUES; // 手牌种类数
    static const int N_CARD_SUITS; // 手牌花色数
    static const string CARD_VALUES[]; // 手牌种类对应的字符串
    static const string CARD_SUITS[]; // 手牌花色对应的字符串

    Card(const char* str) :string(str) {};
    Card() :string() {};
    Card(string str) :string(str) {};

    static vector<Card> get_new_deck();

    // 重载操作符，使得牌面可以比较大小
    bool operator <(const Card &other) const;
    bool operator >(const Card &other) const;
};


class DDZPlayer {
protected:
    string name;  // 玩家名
    int position;  // 你的位置编号，0为地主，1为地主下家，2为地主上家
    vector<Card> hand;  // 手牌

    int prePos;  //上一个出牌的人位置编号，-1表示还没有人出过牌
    vector<Card> prePlay;  // 上一个出牌的人出了什么牌？

    bool legal(vector<Card> cards);  // 判断当前打出cards是否合法
    void substractFromHand(vector<Card> cards);  // 从当前手牌中删去cards中的牌
public:
    DDZPlayer(string name);  // 构造函数，初始化玩家名
    string getName();
    virtual void draw(Card card);  // 将cards中的牌加入手牌
    virtual void draw(vector<Card> cards);  // 将cards中的牌加入手牌
    virtual void setPosition(int pos);  // 初始化用，决定地主后设置
    virtual void showHand();  // 打印手牌
    virtual void observed(int pos, vector<Card> cards);  // 观测到玩家出牌
    virtual vector<Card> play();  // 轮到自己时决定出什么牌
    bool leftNoCard();  // 返回是否打完了牌？
};


class DDZGame {
private:
    static int my_random (int i);  // 洗牌时用到的随机函数
    vector<DDZPlayer*> players;  // 保存三个玩家的指针
    void showCards(vector<Card> cards);  // 输出一组牌

public:
    DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3);  // 构造函数
    void run();  // 执行游戏流程
};


class DDZHumanPlayer: public DDZPlayer {
public:
    DDZHumanPlayer(string name) : DDZPlayer(name) {};
    vector<Card> play();
};

nyaachen::Card to_my_card(const vector<Card> &c) {
    nyaachen::Card t;
    for (string i : c) {
        t.insert(i);
    }
    return t;
}
vector<Card> to_std_card(const nyaachen::Card &c) {
    vector<Card> t;
    for (string i : nyaachen::print(c)) {
        t.push_back(i);
    }
    return t;
}
// ----------------------------------------------------------------------------

int main1() {
    srand(0x5942B);

    DDZPlayer p1("Alice"), p2("Bob"), p3("Charlie");
    DDZGame g(&p1, &p2, &p3);
    g.run();

    return 0;
}


int main() {
    string name;
    cout << "Please input your name:" << endl;
    getline(cin, name);

    srand(0x5942B);

    DDZPlayer p1("Alice"), p2("Bob");
    DDZHumanPlayer p3(name);
    DDZGame g(&p1, &p2, &p3);
    g.run();

    return 0;
}


bool Card::operator <(const Card &other) const {
    int a = -1, b = -1;
    for (int i = 0; i < N_CARD_VALUES; ++i) {
        if (*this == CARD_VALUES[i]) a = i;
        if (other == CARD_VALUES[i]) b = i;
    }
    return a < b;
}

bool Card::operator >(const Card &other) const {
    return other < *this;
}

DDZPlayer::DDZPlayer(string name): name(name) {
    // 玩家类的构造函数
    prePos = -1;
}

string DDZPlayer::getName() {
    return name;
}

bool DDZPlayer::legal(vector<Card> cards) {
	// 通过上家打出的牌prePlay和手牌hand判断cards作为打出牌是否合法
	// TODO：（第二题）请补全这个函数
	// 1判断是否是子集
	nyaachen::Card m(to_my_card(hand)), o(to_my_card(cards));
	if (!m.subset(o)) return false;
	// 如果出牌，判断是否是合法牌，是否能管上
	// 如果不出牌，是否是必须出牌
	if (cards.size() == 0) {
		return (prePos != position);
	}
	else {
		nyaachen::Card p(to_my_card(prePlay)), q;
		return (nyaachen::find_cardtype(o) != nyaachen::INVALID && (prePos == -1 || prePos == position || nyaachen::cmpCards(o, p, q)));
	}
	return true;
}

void DDZPlayer::substractFromHand(vector<Card> cards) {
    // 这个函数从hand中删除cards。假设cards中的牌hand可以拿得出来（否则会出错）。
    sort(hand.begin(), hand.end(), greater<Card>());
    sort(cards.begin(), cards.end(), greater<Card>());
    vector<Card>::iterator i = hand.begin(), k = cards.begin();
    for (vector<Card>::iterator j = hand.begin(); j != hand.end(); ++j) {
        if (k == cards.end() || *k != *j) *(i++) = *j;
        else if (k != cards.end()) ++k;
    }
    hand.erase(i, hand.end());
}

void DDZPlayer::showHand() {
    // 输出玩家名和手牌。
    cout << name << " holds: ";
    for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

void DDZPlayer::draw(Card card) {
    // 将card加入手牌
    hand.push_back(card);
    sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::draw(vector<Card> cards) {
    // 将cards中的牌加入手牌
    hand.insert(hand.end(), cards.begin(), cards.end());
    sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::setPosition(int pos) {
    position = pos;
}

void DDZPlayer::observed(int pos, vector<Card> cards) {
    // 将上一个出牌的人和出了什么牌记录下来。
    // 如果你想记录更多的信息供你的策略使用，可以改动这个函数。
    // 例如，记录已经有哪些牌被打出（记牌器），以推测场上是否可能还存在炸弹。
    if (cards.size() == 0) return;
    prePos = pos;
    prePlay = cards;
}

vector<Card> DDZPlayer::play() {
    // 轮到你出牌，返回打出的牌。
    // TODO：（第一题）请完善这个函数
    // 如果你使用不同的数据结构进行处理，你可以现将hand变量转换为你使用的结构，
    // 处理过后再将打出的牌转换为vector<Card>，存入card变量。
    vector<Card> cards;
    if (prePos == position || prePos == -1) {
        // 出任意牌
        nyaachen::Card m(to_my_card(hand)), t;
        nyaachen::freeCards(m, t);
        cards = to_std_card(t);
    } else {
        nyaachen::Card m(to_my_card(hand)), o(to_my_card(prePlay)), t;
        bool b = nyaachen::cmpCards(m,o,t);
        if (b) cards = to_std_card(t);
        // 位于prePos的玩家打出了prePlay的牌，你需要出什么牌？
    }

    // 你需要保证打出的牌是合法的
    // assert函数在参数为false的时候会使程序报错退出。
    // 这样做的好处是，如果你有没注意到的错误导致程序在此报错退出，
    // 你就知道是在出牌的合法性上出了问题，而不用排查程序的其他部分。
    assert(legal(cards));

    // 将打出的牌从手牌中删去
    substractFromHand(cards);
    return cards;
}

bool DDZPlayer::leftNoCard() {
    // 返回当前手牌为空
    return hand.empty();
}

const int Card::N_CARD_VALUES = 15;

const int Card::N_CARD_SUITS = 4;

const string Card::CARD_VALUES[] = {
    "3", "4", "5", "6",
    "7", "8", "9", "10",
    "J", "Q", "K", "A", "2",
    "joker", "JOKER"
};

const string Card::CARD_SUITS[] = {
    "Spades", "Hearts", "Diamonds", "Clubs"
};

vector<Card> Card::get_new_deck() {
    // 生成一副新牌
    vector<Card> deck;
    for (int i = 0; i < N_CARD_VALUES-2; ++i) {
        for (int j = 0; j < N_CARD_SUITS; ++j) {
            Card card(CARD_VALUES[i]); // 这里没有使用花色数组，使用花色数组直接用string类的加法加和
            // 由此可见，这个程序的卡牌的机器内表示是字符串
            deck.push_back(card);
        }
    }
    deck.push_back(Card(CARD_VALUES[13]));
    deck.push_back(Card(CARD_VALUES[14]));
    return deck; // 生成的是一副全新的、有序的牌
}

int DDZGame::my_random (int i) {
    return std::rand()%i;
}

DDZGame::DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3) {
    // 牌局类的构造函数，需要接受三个玩家作为参数
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
}

void DDZGame::showCards(vector<Card> cards) {
    sort(cards.begin(), cards.end(), greater<Card>());
    for (vector<Card>::iterator i = cards.begin(); i != cards.end(); ++i) {
        cout << *i << " ";
    }
    if (cards.size() == 0) cout << "YAO BU QI";
    cout << endl << endl;
}

void DDZGame::run() {
    // 斗地主游戏的主要流程

    // 取一副新牌并洗牌
    vector<Card> deck = Card::get_new_deck();
    random_shuffle(deck.begin(), deck.end(), my_random);

    // 每个玩家抽17张牌，留下三张底牌
    for (int i = 0; i < 54-3; ++i)
        players[i%3]->draw(deck[i]);

    // 随机选取地主，发给地主最后三张牌
    // * 你可以实现自己的叫地主流程，
    // * 你需要在DDZPlayer类里面加入相应的变量（存储其他玩家叫地主的情况）
    // * 和函数bool DDZPlayer::bid()（返回自己是否要叫地主）。
    // * 请参阅play()函数和叫地主的规则设计这个流程。
    int landlordPos = my_random(3);
    for (int i = 54-3; i < 54; ++i)
        players[landlordPos]->draw(deck[i]);
    for (int i = 0; i < 3; ++i)
        players[i]->setPosition((i + 3 - landlordPos) % 3); // 计算与地主的相对位置
    cout << players[landlordPos]->getName() << " is the landlord." << endl;


    int currentPlayer = landlordPos;
    while (true) {
        // 当前玩家打牌
        vector<Card> currentCards = players[currentPlayer]->play();
        cout << players[currentPlayer]->getName() << " plays:";
        showCards(currentCards);
        // 其他玩家看到了打出的牌。（并不是只有下家看到，上家也能看到）
        for (int i = 0; i < 3; ++i) {
            // 玩家看到的位置编号都是从地主为0开始的
            int relativePos = (currentPlayer + 3 - landlordPos) % 3;
            players[i]->observed(relativePos, currentCards);
        }

        // 如果刚出完牌的玩家没有牌了游戏结束
        if (players[currentPlayer]->leftNoCard()) {
            bool landlordwins = (currentPlayer == landlordPos);
            cout << (landlordwins ? "Landlord wins!" : "Farmers win!") << endl;
            break;
        }

        // 计算下一个玩家的下标
        currentPlayer = (currentPlayer + 1) % 3;
    }
}

vector<Card> DDZHumanPlayer::play() {
    vector<Card> cards;
    string s, c;
    while (true) {
        showHand();
        cout << "Please input the cards you want to play." << endl;
        getline(cin, s);
        istringstream iss(s);
        while (iss >> c) {
            cards.push_back(Card(c));
        }
        // 现在cards是一个vector<Card>，存储了用户输入的牌
        // 你需要检测输入的牌是持有的牌，并且合法。请完成legal函数。
        if (legal(cards)) {
            break;
        } else {
            cout << "Illegal cards. Input again." << endl;
            cards.clear();
        }
    }
    substractFromHand(cards);
    return cards;
}
