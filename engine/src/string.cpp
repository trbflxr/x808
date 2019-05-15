//
// Created by FLXR on 7/4/2018.
//

#include <cstring>
#include <libgen.h>
#include <xe/string.hpp>

#ifdef XE_PLATFORM_WINDOWS
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef WIN32_EXTRA_LEAN
    #define WIN32_EXTRA_LEAN
  #endif
  #include <windows.h>
#endif

namespace xe {

  const char *findToken(const char *str, const string &token) {
    const char *t = str;
    while ((t = strstr(t, token.data()))) {
      bool left = str == t || isspace(t[-1]);
      bool right = !t[token.size()] || isspace(t[token.size()]);

      if (left && right) return t;

      t += token.size();
    }
    return nullptr;
  }

  const char *findToken(const string &str, const string &token) {
    return findToken(str.data(), token);
  }

  const char *findChar(const char *str, char ch) {
    return strchr(str, ch);
  }

  string getBlock(const char *str, const char **outPosition) {
    const char *end = strstr(str, "}");
    if (!end) return string(str);

    if (outPosition) *outPosition = end;

    uint length = end - str + 1;
    return string(str, length);
  }

  string getBlock(const string &str, uint offset) {
    const char *s = str.data() + offset;
    return getBlock(s);
  }

  string getWord(const char *str, const char **outPosition) {
    size_t length = strlen(str);

    string res = str;

    for (size_t i = 0; i < length; ++i) {
      if (str[i] == 95) continue; //underscore
      if (str[i] < 48 || str[i] > 57) { //numbers
        if (str[i] < 65 || str[i] > 90) { //cap letters
          if (str[i] < 97 || str[i] > 122) { //letters
            res = string(str, i);

            if (outPosition) *outPosition = str + i;

            break;
          }
        }
      }
    }

    return res;
  }

  string getFileName(const string &str, bool includeExt) {
    string temp = str;
    char *s = basename(temp.data());

    size_t size = strlen(s);

    if (!includeExt) {
      int32 lastDot = -1;

      for (size_t i = 0; i < size; ++i) {
        if (s[i] == '.') {
          lastDot = static_cast<int32>(i);
        }
      }

      if (lastDot != -1) {
        s[lastDot] = '\0';
      }
    }

    return s;
  }

  string getFileExt(const string &str) {
    const char *dot = strrchr(str.c_str(), '.');
    if (!dot || dot == str) return "";
    return string(dot + 1);
  }

  string getStatement(const char *str, const char **outPosition) {
    const char *end = strstr(str, ";");
    if (!end) return string(str);

    if (outPosition) *outPosition = end;

    uint length = end - str + 1;
    return string(str, length);
  }

  std::vector<string> tokenize(const string &str) {
    return splitString(str, " \t\n");
  }

  std::vector<string> splitString(const string &str, const string &delimiters) {
    size_t start = 0;
    size_t end = str.find_first_of(delimiters);

    std::vector<string> result;

    while (end <= string::npos) {
      string token = str.substr(start, end - start);
      if (!token.empty())
        result.push_back(token);

      if (end == string::npos) break;

      start = end + 1;
      end = str.find_first_of(delimiters, start);
    }

    return result;
  }

  std::vector<string> splitString(const string &str, char delimiter) {
    return splitString(str, string(1, delimiter));
  }

  std::vector<string> getLines(const string &str) {
    return splitString(str, "\n");
  }

  bool startsWith(const string &str, const string &start) {
    return str.find(start) == 0;
  }

  void replaceAll(string &src, const string &oldVal, const string &newVal) {
    size_t start = 0;
    while ((start = src.find(oldVal, start)) != std::string::npos) {
      src.replace(start, oldVal.length(), newVal);
      start += newVal.length();
    }
  }

#ifdef XE_PLATFORM_WINDOWS

  std::wstring toWstring(const string &str) {
    return toWstring(str.c_str());
  }

  std::wstring toWstring(const char *str) {
    int32 size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    std::wstring buffer(static_cast<size_t>(size), L'\0');

    MultiByteToWideChar(CP_UTF8, 0, str, -1, buffer.data(), size);

    return buffer;
  }

  string toString(const std::wstring &str) {
    int32 size = static_cast<int32>(str.size()) * 2;

    string buffer(size, '\0');

    WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, &buffer[0], size, nullptr, nullptr);

    return buffer;
  }

#endif

  void wcharToUTF8(const uint &wchar, uint &utf8) {
    char *c = (char *) &utf8;

    if (wchar < 0x80) {
      utf8 = wchar;
    } else if (wchar < 0x800) {
      c[0] = static_cast<char>((wchar >> 6) | 0xC0);
      c[1] = static_cast<char>((wchar & 0x3F) | 0x80);
    } else if (wchar < 0x10000) {
      c[0] = static_cast<char>((wchar >> 12) | 0xE0);
      c[1] = static_cast<char>(((wchar >> 6) & 0x3F) | 0x80);
      c[2] = static_cast<char>((wchar & 0x3F) | 0x80);
    } else if (wchar < 0x110000) {
      c[0] = static_cast<char>((wchar >> 18) | 0xF0);
      c[1] = static_cast<char>(((wchar >> 12) & 0x3F) | 0x80);
      c[2] = static_cast<char>(((wchar >> 6) & 0x3F) | 0x80);
      c[3] = static_cast<char>((wchar & 0x3F) | 0x80);
    }
  }

}