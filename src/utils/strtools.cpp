#include "strtools.h"

std::string parse_id(std::string s) {
    std::regex ws_re("\\s+");
    std::vector<std::string> v(std::sregex_token_iterator(s.begin(), s.end(), ws_re, -1), std::sregex_token_iterator());
    return v[1];
}

std::string parse_text(std::string s) {
    std::regex ws_re("\\s+");
    std::vector<std::string> v(std::sregex_token_iterator(s.begin(), s.end(), ws_re, -1), std::sregex_token_iterator());
    return v[2];
}