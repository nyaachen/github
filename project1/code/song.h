#ifndef SONG_H_
#define SONG_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <stdexcept>

namespace KTV {
	namespace song {
		enum _song_attrib_type {
			STRING,
			DOUBLE,
			INT
		};
		const std::vector<std::string> _song_attrib_str {
			"std::string",
			"double",
			"int"
		};
		class Unexcepted_Attribute_type :public std::runtime_error {
		public:
			Unexcepted_Attribute_type(const std::string &a, const std::string &b);
		};
		class SongAttrib {
		private:
			_song_attrib_type Type;
			int ival;
			double dval;
			std::string sval;
		public:
			SongAttrib();
			SongAttrib(int i);
			SongAttrib(double d);
			SongAttrib(const std::string &s);
			SongAttrib &operator=(int i);
			SongAttrib &operator=(double d);
			SongAttrib &operator=(const std::string &s);
			int &i();
			double &d();
			std::string &str();
			operator int();
			operator double();
			operator std::string();
			std::string print() const;
		};
		class INVALID_KEY_ERROR : public std::out_of_range {
		public:
			INVALID_KEY_ERROR(const std::string &s);
		};
		const std::set<std::string> SONG_KEY {
			"id", // string
			"title", // string
			"artist", // string
			"pinyin", // string
			// below are item not printed
			"playedtimes", // int
			"ratedtimes", // int
			"ratesum", // double
			"replaystatus" // int
		};
		const std::string ID("id"), TITLE("title"), ARTIST("artist"), PINYIN("pinyin"),
						  PLAYEDTIMES("playedtimes"), RATEDTIMES("ratedtimes"), RATESUM("ratesum"),
						  REPLAYSTATUS("replaystatus");
		class Song : public std::map<std::string, SongAttrib> {
		public:
			Song();
			// 歌曲的访问
			std::string id() const;
			std::string &title();
			std::string title() const;
			std::string &artist();
			std::string artist() const;
			std::string &pinyin();
			std::string pinyin() const;
			SongAttrib &operator[](const std::string &s);
			SongAttrib operator[](const std::string &s) const;

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