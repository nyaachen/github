#include "song.h"

namespace KTV {
    namespace song {
        SongAttrib::SongAttrib() : Type(INT), ival(0), dval(0), sval("") {}
        SongAttrib::SongAttrib(int i) : Type(INT), ival(i), dval(0), sval("") {}
        SongAttrib::SongAttrib() : Type(INT), ival(0), dval(0), sval("") {}
        SongAttrib::SongAttrib() : Type(INT), ival(0), dval(0), sval("") {}
        int &SongAttrib::getAttrib(int i) { return ival;}
        int SongAttrib::getAttrib(int i) const { return ival;}
        double &SongAttrib::getAttrib(double d) { return dval;}
        double SongAttrib::getAttrib(double d) const { return dval;}
        std::string &SongAttrib::getAttrib(const std::string &s) { return sval;}
        std::string SongAttrib::getAttrib(const std::string &s) const { return sval;}

        Song::Song() : std::map<std::string, SongAttrib> () {}
        SongAttrib &Song::operator[](const std::string &s) {
            if (SONG_KEY.find(s) == SONG_KEY.end()) {
                throw INVALID_KEY_ERROR(s);
            }
            return std::map<std::string, SongAttrib>::operator[](s);
        }
        SongAttrib Song::operator[](const std::string &s) const {
            return at(s);
        }
        bool Song::include_title(const std::string &s) const {
            return s == operator[](TITLE).getAttrib(s);
        }
        bool Song::include_artist(const std::string &s) const {
            return s == operator[](ARTIST).getAttrib(s);
        }
        bool Song::include_pinyin(const std::string &s) const {
            return s == operator[](PINYIN).getAttrib(s);
        }

    }
}