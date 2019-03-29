#ifndef SONG_H_
#define SONG_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

namespace KTV {
	namespace song {
		class Song {
		private:
			std::string _title, _artist, _pinyin; // 三大基本属性。以下为额外属性
			int id;
			int replayedtime;
			int replaystatus;
			std::vector<double> rates;
			// 用于播放列表的链接指针
			Song *playlistprev, *playlistnext;
		public:
			Song(); // TODO 更多的构造函数
			// 歌曲的访问之固定属性
			std::string &title();
			std::string title() const;
			std::string &artist();
			std::string artist() const;
			std::string &pinyin();
			std::string pinyin() const;
			// 歌曲的访问之扩展属性
			// TODO

			// 歌曲的检索
			bool include_title(const std::string &s) const;
			bool include_artist(const std::string &s) const;
			bool include_pinyin(const std::string &s) const;
			// 歌曲的排序
			bool smaller_rate(const Song &s) const;
			bool smaller_playedtimes(const Song &s) const;
			bool smaller_id(const Song &s) const;
			bool smaller_pinyin(const Song &s) const;
		};
	}
}


#endif