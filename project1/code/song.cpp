#include "song.h"

namespace KTV {
    namespace song {

        Unexcepted_Attribute_type::Unexcepted_Attribute_type(const std::string &a, const std::string &b) : std::runtime_error("Wrong Attribute type! The element have type "+ a + " but you tried type " + b + ". Please check your code!") {}

        SongAttrib::SongAttrib() : Type(INT), ival(0), dval(0), sval("") {}
        SongAttrib::SongAttrib(int i) : Type(INT), ival(i), dval(0), sval("") {}
        SongAttrib::SongAttrib(double d) : Type(DOUBLE), ival(0), dval(d), sval("") {}
        SongAttrib::SongAttrib(const std::string &s) : Type(STRING), ival(0), dval(0), sval(s) {}
        SongAttrib &SongAttrib::operator=(int i) {
            Type = INT;
            ival = i;
        }
        SongAttrib &SongAttrib::operator=(double d) {
            Type = DOUBLE;
            dval = d;
        }
        SongAttrib &SongAttrib::operator=(const std::string &s) {
            Type = STRING;
            sval = s;
        }
        int &SongAttrib::i() {
            if (Type != INT)
                throw Unexcepted_Attribute_type(_song_attrib_str[Type], _song_attrib_str[INT]);
            return ival;
        }
        double &SongAttrib::d() {
            if (Type != DOUBLE)
                throw Unexcepted_Attribute_type(_song_attrib_str[Type], _song_attrib_str[DOUBLE]);
            return dval;
        }
        std::string &SongAttrib::str() {
            if (Type != STRING)
                throw Unexcepted_Attribute_type(_song_attrib_str[Type], _song_attrib_str[STRING]);
            return sval;
        }
        SongAttrib::operator int() {} {
            if (Type != INT)
                throw Unexcepted_Attribute_type(_song_attrib_str[Type], _song_attrib_str[INT]);
            return ival;
        }
        SongAttrib::operator double() {
            if (Type != DOUBLE)
                throw Unexcepted_Attribute_type(_song_attrib_str[Type], _song_attrib_str[DOUBLE]);
            return dval;
        }
        SongAttrib::operator std::string() {
            if (Type != STRING)
                throw Unexcepted_Attribute_type(_song_attrib_str[Type], _song_attrib_str[STRING]);
            return sval;
        }
        std::string SongAttrib::print() const {
            std::string r;
            std::ostringstream os;
            switch (Type) {
            case INT:
                os << ival << std::flush;
                r = os.str();
                break;
            case DOUBLE:
                os << dval << std::flush;
                r = os.str();
                break;
            case STRING:
                r = sval;
                break;
            }
            return r;
        }

        INVALID_KEY_ERROR::INVALID_KEY_ERROR(const std::string &s) : out_of_range("Illegal Key Value " + s + " ! Check your program code !") {}

        Song::Song() : std::map<std::string, SongAttrib> () {}

        std::string Song::id() const;
        std::string &Song::title();
        std::string Song::title() const;
        std::string &Song::artist();
        std::string Song::artist() const;
        std::string &Song::pinyin();
        std::string Song::pinyin() const;
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
            return s == reinterpret_cast<std::string>(operator[](TITLE));
        }
        bool Song::include_artist(const std::string &s) const {
            return s == operator[](ARTIST).getAttrib(s);
        }
        bool Song::include_pinyin(const std::string &s) const {
            return s == operator[](PINYIN).getAttrib(s);
        }
        bool Song::smaller_rate(const Song &s) const {
            double current_rate = operator[](RATESUM).getAttrib(current_rate) / operator[](RATEDTIMES).getAttrib(current_rate);
            double c_rate = s[RATESUM].getAttrib(c_rate) / s[RATEDTIMES].getAttrib(c_rate);
            return current_rate < c_rate;
        }
        bool Song::smaller_playedtimes(const Song &s) const {
            int count = operator[](PLAYEDTIMES).getAttrib(count);
            return count < s[PLAYEDTIMES].getAttrib(count);
        }
    }
}