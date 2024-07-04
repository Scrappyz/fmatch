#pragma once

#include <string>
#include <vector>

namespace fnmatch {

    bool match(const std::string& pattern, const std::string& str)
    {
        int i = 0;
        int j = 0;
        while(i < pattern.size() && j < str.size()) {
            if(pattern[i] == '*') {
                i++;

                if(i >= pattern.size()) {
                    return true;
                }

                while(j < str.size() && pattern[i] != str[j]) {
                    j++;
                }

                if(j >= str.size()) {
                    return false;
                }
            } else if(pattern[i] != str[j]) {
                return false;
            } else {
                i++;
                j++;
            }
        }

        if(i < pattern.size() || j < str.size()) {
            return false;
        }

        return true;
    }
}