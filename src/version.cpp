#include "version.h"

#define _OMNISCIA_VERSION_ 4381

unsigned long long get_game_version() {
    return _OMNISCIA_VERSION_;
}
std::string get_game_version_string() {
    return boost::lexical_cast<std::string>(get_game_version());
}

