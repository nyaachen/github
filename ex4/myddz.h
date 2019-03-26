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
