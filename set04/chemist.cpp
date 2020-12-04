#include <iostream>
#include <map>
#include <set>

void calculate(std::string &word, long long start, long long end
    , std::set<std::string> &table
    , std::map<std::pair<long long, long long>, bool> &dynamic) {
    if (dynamic.find(std::make_pair(start, end)) != dynamic.end()) {
        return;
    }

    if (start + 1 == end) {
        dynamic.emplace(std::make_pair(start, end)
            , table.find(word.substr(start, 1)) != table.end());
        return;
    }

    if (start + 2 == end 
        && table.find(word.substr(start, 2)) != table.end()) {
        dynamic.emplace(std::make_pair(start, end), true);
        return;
    }

    for (long long i = start + 1; i < std::min(start + 3, end); i++) {
        calculate(word, start, i, table, dynamic);
        calculate(word, i, end, table, dynamic);

        if (dynamic.find({start, i}) != dynamic.end() 
           && dynamic.find({i, end}) != dynamic.end() 
           && dynamic.at({start, i}) && dynamic.at({i, end})) {
            dynamic.emplace(std::make_pair(start, end), true);
            return;
        }
    }
    
    dynamic.emplace(std::make_pair(start, end), false);
}

int main(void) {
    long long t;
    std::cin >> t;
    std::set<std::string> table {"h", "he"
        , "li", "be", "b", "c", "n", "o", "f", "ne"
        , "na", "mg", "al", "si", "p", "s", "cl", "ar"
        , "k", "ca", "sc", "ti", "v", "cr", "mn", "fe", "co", "ni", "cu", "zn"
        , "ga", "ge", "as", "se", "br", "kr"
        , "rb", "sr", "y", "zr", "nb", "mo", "tc", "ru", "rh", "pd", "ag", "cd"
        , "in", "sn", "sb", "te", "i", "xe"
        , "cs", "ba", "hf", "ta", "w", "re", "os", "ir", "pt", "au", "hg"
        , "tl", "pb", "bi", "po", "at", "rn"
        , "fr", "ra", "rf", "db", "sg", "bh", "hs", "mt", "ds", "rg", "cn"
        , "fl", "lv"
        , "la", "ce", "pr", "nd", "pm", "sm", "eu", "gd", "tb", "dy", "ho", "er"
        , "tm", "yb", "lu"
        , "ac", "th", "pa", "u", "np", "pu", "am", "cm", "bk", "cf", "es", "fm"
        , "md", "no", "lr"};

    std::string word;
    std::getline(std::cin, word);
    for (long long i = 0; i < t; i++) {
        std::getline(std::cin, word);
        long long l = word.length();
        std::map<std::pair<long long, long long>, bool> dynamic;
        calculate(word, 0, l, table, dynamic);
        std::cout << (dynamic.at({0, l}) ? "YES" : "NO") << std::endl;
    }

    return 0;
}

