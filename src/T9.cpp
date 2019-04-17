#include "T9.h"

float similar(const std::string & lhs, const std::string & rhs) {
    unsigned res = 0;
    std::multiset<char> lhs_set;
    for(const auto & item : lhs)
        lhs_set.insert(item);
    std::multiset<char> rhs_set;
    for(const auto & item : rhs)
        rhs_set.insert(item);
    for(auto item : rhs_set) {
        auto it = lhs_set.find(item);
        if (it != lhs_set.end()) {
            lhs_set.erase(it);
            res++;
        }
    }
    return res / (float)rhs_set.size();
}
