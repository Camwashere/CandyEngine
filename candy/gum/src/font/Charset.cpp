#include <gum/font/Charset.hpp>
#include <cstdio>
#include <string>
#include <vector>
namespace Candy::Gum
{
  static Charset CreateAsciiCharset() {
    Charset ascii;
    for (unicode_t cp = 0x20; cp < 0x7f; ++cp)
      ascii.Add(cp);
    return ascii;
  }
  const Charset Charset::ASCII = CreateAsciiCharset();
  void Charset::Add(unicode_t codePoint)
  {
    codepoints.insert(codePoint);
  }
  /// Removes a codepoint
  void Charset::Remove(unicode_t codePoint)
  {
    codepoints.erase(codePoint);
  }
  
  size_t Charset::Size() const
  {
    return codepoints.size();
  }
  bool Charset::Empty() const
  {
    return codepoints.empty();
  }
  std::set<unicode_t>::const_iterator Charset::begin() const
  {
    return codepoints.begin();
  }
  std::set<unicode_t>::const_iterator Charset::end() const
  {
    return codepoints.end();
  }
  
  
  
  
  static char EscapedChar(char c) {
    switch (c) {
      case '0':
        return '\0';
      case 'n': case 'N':
        return '\n';
      case 'r': case 'R':
        return '\r';
      case 's': case 'S':
        return ' ';
      case 't': case 'T':
        return '\t';
      case '\\': case '"': case '\'':
      default:
        return c;
    }
  }
  
  static int ReadWord(std::string &str, FILE *f) {
    while (true) {
      int c = fgetc(f);
      if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
        str.push_back((char) c);
      else
        return c;
    }
  }
  
  static bool ReadString(std::string &str, FILE *f, char terminator) {
    bool escape = false;
    while (true) {
      int c = fgetc(f);
      if (c < 0)
        return false;
      if (escape) {
        str.push_back(EscapedChar((char) c));
        escape = false;
      } else {
        if (c == terminator)
          return true;
        else if (c == '\\')
          escape = true;
        else
          str.push_back((char) c);
      }
    }
  }
  
  static bool ParseInt(int &i, const char *str) {
    i = 0;
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) { // hex
      str += 2;
      for (; *str; ++str) {
        if (*str >= '0' && *str <= '9') {
          i <<= 4;
          i += *str-'0';
        } else if (*str >= 'A' && *str <= 'F') {
          i <<= 4;
          i += *str-'A'+10;
        } else if (*str >= 'a' && *str <= 'f') {
          i <<= 4;
          i += *str-'a'+10;
        } else
          return false;
      }
    } else { // dec
      for (; *str; ++str) {
        if (*str >= '0' && *str <= '9') {
          i *= 10;
          i += *str-'0';
        } else
          return false;
      }
    }
    return true;
  }
  
  static std::string CombinePath(const char *basePath, const char *relPath) {
    if (relPath[0] == '/' || (relPath[0] && relPath[1] == ':')) // absolute path?
      return relPath;
    int lastSlash = -1;
    for (int i = 0; basePath[i]; ++i)
      if (basePath[i] == '/' || basePath[i] == '\\')
        lastSlash = i;
    if (lastSlash < 0)
      return relPath;
    return std::string(basePath, lastSlash+1)+relPath;
  }
  
  void utf8Decode(std::vector<unicode_t> &codepoints, const char *utf8String) {
    bool start = true;
    int rBytes = 0;
    unicode_t cp = 0;
    
    for (const char *c = utf8String; *c; ++c) {
      if (rBytes > 0) {
        --rBytes;
        if ((*c&0xc0) == 0x80)
          cp |= (*c&0x3f)<<(6*rBytes);
        // else error
      } else if (!(*c&0x80)) {
        cp = *c;
        rBytes = 0;
      } else if (*c&0x40) {
        int block;
        for (block = 0; ((unsigned char) *c<<block)&0x40 && block < 4; ++block);
        if (block < 4) {
          cp = (*c&(0x3f>>block))<<(6*block);
          rBytes = block;
        } else
          continue; // error
      } else
        continue; // error
      if (!rBytes) {
        if (!(start && cp == 0xfeff)) // BOM
          codepoints.push_back(cp);
        start = false;
      }
    }
  }
  /// Load character set from a text file with the correct syntax
  bool Charset::Load(const char *filename, bool disableCharLiterals) {
    
    if (FILE *f = fopen(filename, "rb")) {
      
      enum {
        CLEAR,
        TIGHT,
        RANGE_BRACKET,
        RANGE_START,
        RANGE_SEPARATOR,
        RANGE_END
      } state = CLEAR;
      
      std::string buffer;
      std::vector<unicode_t> unicodeBuffer;
      unicode_t rangeStart = 0;
      for (int c = fgetc(f), start = true; c >= 0; start = false) {
        switch (c) {
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': // number
            if (!(state == CLEAR || state == RANGE_BRACKET || state == RANGE_SEPARATOR))
              goto FAIL;
            buffer.push_back((char) c);
            c = ReadWord(buffer, f);
            {
              int cp;
              if (!ParseInt(cp, buffer.c_str()))
                goto FAIL;
              switch (state) {
                case CLEAR:
                  if (cp >= 0)
                    Add((unicode_t) cp);
                  state = TIGHT;
                  break;
                case RANGE_BRACKET:
                  rangeStart = (unicode_t) cp;
                  state = RANGE_START;
                  break;
                case RANGE_SEPARATOR:
                  for (unicode_t u = rangeStart; (int) u <= cp; ++u)
                    Add(u);
                  state = RANGE_END;
                  break;
                default:;
              }
            }
            buffer.clear();
            continue; // next character already read
          case '\'': // single UTF-8 character
            if (!(state == CLEAR || state == RANGE_BRACKET || state == RANGE_SEPARATOR) || disableCharLiterals)
              goto FAIL;
            if (!ReadString(buffer, f, '\''))
              goto FAIL;
            utf8Decode(unicodeBuffer, buffer.c_str());
            if (unicodeBuffer.size() == 1) {
              switch (state) {
                case CLEAR:
                  if (unicodeBuffer[0] > 0)
                    Add(unicodeBuffer[0]);
                  state = TIGHT;
                  break;
                case RANGE_BRACKET:
                  rangeStart = unicodeBuffer[0];
                  state = RANGE_START;
                  break;
                case RANGE_SEPARATOR:
                  for (unicode_t u = rangeStart; u <= unicodeBuffer[0]; ++u)
                    Add(u);
                  state = RANGE_END;
                  break;
                default:;
              }
            } else
              goto FAIL;
            unicodeBuffer.clear();
            buffer.clear();
            break;
          case '"': // string of UTF-8 characters
            if (state != CLEAR || disableCharLiterals)
              goto FAIL;
            if (!ReadString(buffer, f, '"'))
              goto FAIL;
            utf8Decode(unicodeBuffer, buffer.c_str());
            for (unicode_t cp : unicodeBuffer)
              Add(cp);
            unicodeBuffer.clear();
            buffer.clear();
            state = TIGHT;
            break;
          case '[': // character range start
            if (state != CLEAR)
              goto FAIL;
            state = RANGE_BRACKET;
            break;
          case ']': // character range end
            if (state == RANGE_END)
              state = TIGHT;
            else
              goto FAIL;
            break;
          case '@': // annotation
            if (state != CLEAR)
              goto FAIL;
            c = ReadWord(buffer, f);
            if (buffer == "include") {
              while (c == ' ' || c == '\t' || c == '\n' || c == '\r')
                c = fgetc(f);
              if (c != '"')
                goto FAIL;
              buffer.clear();
              if (!ReadString(buffer, f, '"'))
                goto FAIL;
              Load(CombinePath(filename, buffer.c_str()).c_str());
              state = TIGHT;
            } else
              goto FAIL;
            buffer.clear();
            break;
          case ',': case ';': // separator
            if (!(state == CLEAR || state == TIGHT)) {
              if (state == RANGE_START)
                state = RANGE_SEPARATOR;
              else
                goto FAIL;
            } // else treat as whitespace
          case ' ': case '\n': case '\r': case '\t': // whitespace
            if (state == TIGHT)
              state = CLEAR;
            break;
          case 0xef: // UTF-8 byte order mark
            if (start) {
              if (!(fgetc(f) == 0xbb && fgetc(f) == 0xbf))
                goto FAIL;
              break;
            }
          default: // unexpected character
            goto FAIL;
        }
        c = fgetc(f);
      }
      
      fclose(f);
      return state == CLEAR || state == TIGHT;
      
      FAIL:
      fclose(f);
      return false;
    }
    
    return false;
  }
}