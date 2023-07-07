#include "version.h"

#define _OMNISCIA_VERSION_ 5020

unsigned long long get_game_version() {
    return _OMNISCIA_VERSION_;
}
std::string get_game_version_string() {
    return std::to_string(get_game_version());
}

