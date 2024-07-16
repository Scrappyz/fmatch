#pragma once

#include <string>
#include <vector>
#include <unordered_set>

namespace fnmatch {

    namespace options {
        enum MatchOption {
            NormalizePath
        };
    }

    namespace _private_ {
        std::string normalizePath(const std::string& str);

        template<typename T>
        std::unordered_set<T> convertVectorToUnorderedSet(const std::vector<T>& v);
    }

    inline bool match(const std::string& str, const std::string& pattern, const std::unordered_set<int>& options = {})
    {
        std::string str_copy = str;
        std::string pattern_copy = pattern;

        if(options.count(options::NormalizePath) > 0) {
            str_copy = _private_::normalizePath(str);
            pattern_copy = _private_::normalizePath(pattern);
        }

        int i = 0;
        int j = 0;
        while(i < pattern_copy.size() && j < str_copy.size()) {
            if(pattern_copy[i] == '*') {
                i++;

                if(i >= pattern_copy.size()) {
                    return true;
                }

                while(j < str_copy.size() && pattern_copy[i] != str_copy[j]) {
                    j++;
                }

                if(j >= str_copy.size()) {
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

    inline bool match(const std::string& str, const std::string& pattern, const std::vector<int>& options)
    {
        std::unordered_set<int> s = _private_::convertVectorToUnorderedSet(options);
        return match(str, pattern, s);
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

        template<typename T>
        inline std::unordered_set<T> convertVectorToUnorderedSet(const std::vector<T>& v)
        {
            std::unordered_set<T> s;
            for(const auto& i : v) {
                s.insert(i);
            }

            return s;
        }
    }
}