#pragma once

#include <string>
#include <vector>

namespace fmatch {

    namespace _private_ {
        std::string normalizePath(const std::string& str);
        std::vector<std::string> pathToList(const std::string& path);
        int numberOfPaths(const std::string& str, bool any_separator = false);
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

    inline bool isPathSeparator(char ch, bool any_separator = false)
    {
        if(any_separator && (ch == '\\' || ch == '/')) {
            return true;
        }

        return ch == pathSeparator();
    }

    inline bool match(const std::string& str, const std::string& pattern)
    {
        std::string str_copy = _private_::normalizePath(str);
        std::string pattern_copy = _private_::normalizePath(pattern);

        int max_str_path = _private_::numberOfPaths(str_copy);
        int max_pattern_path = _private_::numberOfPaths(pattern_copy);

        int i = 0;
        int j = 0;
        int path_i = 1;
        int path_j = 1;
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
                    
                    // Skip path separators in pattern
                    while(i < pattern_copy.size() && isPathSeparator(pattern_copy[i])) {
                        i++;
                    }

                    // Ends with "**"
                    if(i >= pattern_copy.size()) {
                        return true;
                    }

                    // Skip "*"
                    while(i < pattern_copy.size() && pattern_copy[i] == '*') {
                        i++;
                    }
                    
                    // Skip str iterator to match pattern character
                    while(j < str_copy.size() && pattern_copy[i] != str_copy[j]) {
                        j++;
                    }

                    // If str iterator reaches the end, it means no match was found
                    if(j >= str_copy.size() || pattern_copy[i-1] == pathSeparator() && j > 0 && str_copy[j-1] != pattern_copy[i-1]) {
                        return false;
                    }

                    // Return to main loop
                    continue;
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

        if(i == pattern_copy.size()-1 && pattern_copy[i] == '*') {
            return true;
        }

        // Did not reach the end of their respective strings
        if(i < pattern_copy.size() || j < str_copy.size()) {
            return false;
        }

        return true;
    }

    namespace _private_ {
        inline std::string normalizePath(const std::string& str)
        {
            std::string s;

            if(str.empty()) {
                return s;
            }

            for(int i = 0; i < str.size(); i++) {
                if(isPathSeparator(str[i], true)) {
                    s.push_back(pathSeparator());
                    while(isPathSeparator(str[i], true)) {
                        i++;
                    }
                    i--;
                    continue;
                }
                s.push_back(str[i]);
            }

            while(!s.empty() && s.back() == pathSeparator()) {
                s.pop_back();
            }

            return s;
        }

        inline std::vector<std::string> pathToList(const std::string& path)
        {
            std::vector<std::string> v;
            std::string temp;
            for(int i = 0; i < path.size(); i++) {
                if(isPathSeparator(path[i], true)) {
                    if(!temp.empty()) {
                        v.push_back(temp);
                        temp.clear();
                    }

                    while(i < path.size() && isPathSeparator(path[i], true)) {
                        i++;
                    }

                    if(i >= path.size()) {
                        break;
                    }
                }

                temp.push_back(path[i]);
            }

            if(!temp.empty()) {
                v.push_back(temp);
            }

            return v;
        }

        int numberOfPaths(const std::string& str, bool any_separator)
        {
            if(str.empty()) {
                return 0;
            }

            int num_paths = 1;
            for(int i = 0; i < str.size(); i++) {
                if(isPathSeparator(str[i], any_separator)) {
                    while(i < str.size() && isPathSeparator(str[i], any_separator)) {
                        i++;
                    }

                    if(i < str.size() && !isPathSeparator(str[i], any_separator)) {
                        num_paths++;
                    }

                    i--;
                }
            }

            return num_paths;
        }
    }
}