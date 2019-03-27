#include <vector>
#include <string>

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
			int &getAttrib(int i);
			int getAttrib(int i) const;
			double &getAttrib(double d);
			double getAttrib(double d) const;
			std::string &getAttrib(const std::string &s);
			std::string getAttrib(const std::string &s) const;
		};
		const std::vector<string> SONG_KEY {
			"ID",
			"title",
			"artist",
			"pinyin",
			"playedtimes",
			"ratedtimes",
			"ratesum",
			"replaystatus"
		};
		class Song : public std::vector<SongAttrib> {
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

// Test for different condition
#include <iostream>
using namespace std;

int main() {
	return 0;
}
