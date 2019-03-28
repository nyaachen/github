#ifndef SONG_H_
#define SONG_H_
#include <vector>
#include <string>
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
			_song_attrib_type value_type() const;
			int &getAttrib(int i);
			int getAttrib(int i) const;
			double &getAttrib(double d);
			double getAttrib(double d) const;
			std::string &getAttrib(const std::string &s);
			std::string getAttrib(const std::string &s) const;
		};
		class INVALID_KEY_ERROR : public std::out_of_range {
		public:
			INVALID_KEY_ERROR(const std::string &s) : out_of_range("Illegal Key Value " + s + " ! Check your program code !") {}
		};
		const std::set<std::string> SONG_KEY {
			"ID",
			"title",
			"artist",
			"pinyin",
			"playedtimes", // int
			"ratedtimes", // int
			"ratesum", // double
			"replaystatus" // int
		};
		const std::string ID("ID"), TITLE("title"), ARTIST("artist"), PINYIN("pinyin"),
						  PLAYEDTIMES("playedtimes"), RATEDTIMES("ratedtimes"), RATESUM("ratesum"),
						  REPLAYSTATUS("replaystatus");
		class Song : public std::map<std::string, SongAttrib> {
		public:
			Song();
			// 歌曲的访问
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