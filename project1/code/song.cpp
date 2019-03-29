#include "song.h"
#include <numeric>

namespace KTV {
    namespace song {
        Song::Song(); // TODO
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
            double avg1 = std::accumulate(rates.cbegin(), rates.cend(), 0);
            double avg2 = std::accumulate(s.rates.cbegin(), s.rates.cend(), 0);
            return avg1 < avg2;
        }
        bool Song::smaller_playedtimes(const Song &s) const {
            return replayedtime < s.replayedtime;
        }
        bool Song::smaller_id(const Song &s) const; // TODO
        bool Song::smaller_pinyin(const Song &s) const {
            return _title < s._title;
        }
    }
}