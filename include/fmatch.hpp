#pragma once

#include <string>
#include <vector>

namespace fmatch {

    namespace _private_ {
        std::string normalizePath(const std::string& str);
        void trimEnd(std::string& str, char ch);
    }

    inline char pathSeparator()
    {
        #if defined(_WIN32)
            return '\\';
        #elif defined(unix) || defined(__MACH__)
            return '/';
        #endif

        return '\0';
    }

    inline bool isPathSeparator(char ch, bool for_current_os = true)
    {
        if(!for_current_os && (ch == '\\' || ch == '/')) {
            return true;
        }

        return ch == pathSeparator();
    }

    inline bool match(const std::string& str, const std::string& pattern)
    {
        std::string str_copy = _private_::normalizePath(str);
        std::string pattern_copy = _private_::normalizePath(pattern);

        _private_::trimEnd(str_copy, pathSeparator());
        _private_::trimEnd(pattern_copy, pathSeparator());

        if(str_copy.size() < pattern_copy.size()) {
            return false;
        }

        std::vector<int> str_separator_pos = _private_::getSeparatorPosition(str_copy);
        std::vector<int> pattern_separator_pos = _private_::getSeparatorPosition(pattern_copy);

        int i = 0;
        int j = 0;
        bool fast_forward = false;
        while(i < pattern_copy.size() && j < str_copy.size()) {
            if(pattern_copy[i] == '*') {
                i++;
                
                // Ends with "*"
                if(i >= pattern_copy.size()) {
                    while(j < str_copy.size() && pattern_copy[i] != str_copy[j] && str_copy[j] != pathSeparator()) {
                        j++;
                    }

                    if(str_copy[j] == pathSeparator()) {
                        return false;
                    }

                    return true;
                }

                // Has "**"
                if(pattern_copy[i] == '*') {
                    i++;

                    while(i < pattern_copy.size() && isPathSeparator(pattern_copy[i])) {
                        i++;
                    }

                    // Ends with "**"
                    if(i >= pattern_copy.size()) {
                        return true;
                    }
                    
                    while(j < str_copy.size() && pattern_copy[i] != str_copy[j]) {
                        j++;
                    }

                    if(j >= str_copy.size()) {
                        return false;
                    }

                    

                    return true;
                }

                // Has "*" between some characters
                while(j < str_copy.size() && pattern_copy[i] != str_copy[j] && str_copy[j] != pathSeparator()) {
                    j++;
                }

                if(j >= str_copy.size() || str_copy[j] == pathSeparator()) {
                    return false;
                }
            } else if(pattern_copy[i] != '?' && pattern_copy[i] != str_copy[j]) {
                return false;
            } else {
                i++;
                j++;
            }
        }

        if(i < pattern_copy.size() || j < str_copy.size()) {
            return false;
        }

        return true;
    }

    namespace _private_ {
        inline std::string normalizePath(const std::string& str)
        {
            std::string s = str;

            for(int i = 0; i < s.size(); i++) {
                if(isPathSeparator(s[i], false)) {
                    s[i] = pathSeparator();
                }
            }

            return s;
        }

        inline void trimEnd(std::string& str, char ch)
        {
            if(str.empty()) {
                return;
            }

            while(str.back() == ch) {
                str.pop_back();
            }
        }

        inline std::vector<int> getSeparatorPosition(const std::string& str)
        {
            std::vector<int> v;
            for(int i = 0; i < str.size(); i++) {
                if(isPathSeparator(str[i])) {
                    v.push_back(i);
                }
            }

            return v;
        }
    }
}