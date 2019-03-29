#include "song.h"

namespace KTV {
    namespace song {
        Song::Song();
        std::string &Song::title() {return _title;}
        std::string Song::title() const { return _title; }
        std::string &Song::artist() { return _artist; }
        std::string Song::artist() const { return _artist; }
        std::string &Song::pinyin() { return _pinyin; }
        std::string Song::pinyin() const { return _pinyin; }
        bool Song::include_title(const std::string &s) const {
            return s == _title;
        }
        bool Song::include_artist(const std::string &s) const {
            return s == _artist;
        }
        bool Song::include_pinyin(const std::string &s) const {
            return s == _pinyin;
        }
        bool Song::smaller_rate(const Song &s) const {
            double current_rate = operator[](RATESUM).getAttrib(current_rate) / operator[](RATEDTIMES).getAttrib(current_rate);
            double c_rate = s[RATESUM].getAttrib(c_rate) / s[RATEDTIMES].getAttrib(c_rate);
            return current_rate < c_rate;
        }
        bool Song::smaller_playedtimes(const Song &s) const {
            return replayedtime < s.replayedtime;
        }
    }
}