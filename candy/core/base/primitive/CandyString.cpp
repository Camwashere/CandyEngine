#include "CandyString.hpp"
#include <cctype>
#include <utility>
#include <algorithm>
#include <sstream>
#include <iomanip>
namespace Candy
{
    
    
    String::String() = default;
    String::String(char c)  {
        data.append(1, c);
    }
    
    String::String(std::string  str) : data(std::move(str)) {
    
    }
    
    
    String::String(const char *str) : data(str) {
    
    }
    
    String::String(String const &other) = default;
    
    char String::ToUpper(char c)
    {
        return std::toupper(c);
    }
    const char* String::ToUpper(const char* str){
        return String(str).ToUpper().ToCharStr();
    }
    std::string String::ToUpper(const std::string& str)
    {
        return String(str).ToUpper().data;
    }
    String String::ToUpper(const String& str)
    {
        return str.ToUpper();
    }
    
    char String::ToLower(char c)
    {
        return std::tolower(c);
    }
    const char* String::ToLower(const char* str)
    {
        return String(str).ToLower().ToCharStr();
    }
    std::string String::ToLower(const std::string& str)
    {
        return String(str).ToLower().data;
    }
    String String::ToLower(const String& str)
    {
        return String(str).ToLower();
    }
    
    bool String::IsUpper(char c)
    {
        return std::isupper(c);
    }
    bool String::IsLower(char c)
    {
        return std::islower(c);
    }
    bool IsAlpha(char c)
    {
        return std::isalpha(c);
    }
    
    const char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    String String::Number(int n, int base)
    {
        String result;
        bool negative=false;
        if (n < 0) {
            negative = true;
            n = -n;
        }
        do {
            result += digits[n % base];
            n /= base;
        } while (n > 0);
        if (negative) {
            result += '-';
        }
        result.Reverse();
        return result;
    }
    String String::Number(unsigned int n, int base)
    {
        String result;
        
        do {
            result += digits[n % base];
            n /= base;
        } while (n > 0);
        result.Reverse();
        return result;
    }
    String String::Number(double n, char format, int precision)
    {
        std::ostringstream oss;
        oss << std::setprecision(precision) << std::fixed;
        if (format == 'e' || format == 'E') {
            oss << std::scientific;
        }
        oss << n;
        return oss.str();
    }
    
    bool String::operator==(const String &other) const {
        return data==other.data;
    }
    
    bool String::operator!=(const String &other) const {
        return data!=other.data;
    }
    
    char &String::operator[](std::size_t index) {
        return data[index];
    }
    
    const char String::operator[](std::size_t index) const {
        return data[index];
    }
    
    
    
    void String::operator+=(char other) {
        Append(other);
    }
    
    void String::operator+=(const char *other) {
        Append(other);
    }
    
    void String::operator+=(const String &other) {
        Append(other);
    }
    
    void String::operator+=(const std::string &other) {
        Append(other);
    }
    
    
    
    String operator + (const String& left, const String& right)
    {
        String value = left;
        value.Append(right);
        return value;
    }
    String operator + (const String& left, char right)
    {
        String value = left;
        value.Append(right);
        return value;
    }
    std::ostream& operator << (std::ostream& ostream, const String& str)
    {
        ostream << str.ToCharStr();
        return ostream;
    }
    
    String::operator std::string() const {
        return data;
    }
    
    String::operator const char *() const {
        return data.c_str();
    }
    
    bool String::IsEmpty() const {
        return data.empty();
    }
    
    bool String::IsNotEmpty() const {
        return !data.empty();
    }
    
    std::size_t String::Size() const {
        return data.size();
    }
    
    char String::GetFirst() const {
        return data[0];
    }
    
    char String::GetLast() const {
        return data[data.size()-1];
    }
    std::size_t String::LastIndex()const
    {
        return Size()-1;
    }
    
    String String::Substr(std::size_t start) const{
        return {data.substr(start)};
    }
    
    String String::Substr(std::size_t start, std::size_t end) const{
        return {data.substr(start, end)};
    }
    String String::SubstrRight(std::size_t index)const
    {
        return {data.substr(index, Size())};
        
    }
    String String::SubstrLeft(std::size_t index)const
    {
        return {data.substr(0, index)};
        
    }
    
    void String::Append(char c) {
        
        data.append(1, c);
    }
    
    void String::Append(const char *str) {
        data.append(str);
    }
    
    void String::Append(const std::string &str) {
        data.append(str);
    }
    
    void String::Append(const String &str) {
        data.append(str.data);
    }
    
    void String::Prepend(char c) {
        data.insert(0, 1, c);
        
    }
    
    void String::Prepend(const char *str) {
        data.insert(0, str);
    }
    
    void String::Prepend(const std::string &str) {
        data.insert(0, str);
    }
    
    void String::Prepend(const String &str) {
        data.insert(0, str.data);
    }
    
    void String::Insert(std::size_t index, char c) {
        data.insert(index, 1, c);
    }
    
    void String::Insert(std::size_t index, const char *str) {
        data.insert(index, str);
    }
    
    void String::Insert(std::size_t index, const std::string &str) {
        data.insert(index, str);
    }
    
    void String::Insert(std::size_t index, const String &str) {
        data.insert(index, str.data);
    }
    
    std::size_t String::RemoveAll(char charsToRemove) {
        std::size_t count=0;
        std::string oldData = data;
        data.clear();
        for (char i : oldData)
        {
            if (i==charsToRemove)
            {
                count++;
            }
            else
            {
                Append(i);
            }
        }
        return count;
    }
    
    std::size_t String::RemoveAll(const char *charsToRemove) {
        std::size_t count=0;
        std::string oldData = data;
        std::string removalChars(charsToRemove);
        data.clear();
        
        for (char i : oldData)
        {
            bool good=true;
            for (char c : removalChars)
            {
                if (i==c)
                {
                    count++;
                    good=false;
                    break;
                }
            }
            if (good)
            {
                Append(i);
            }
            
        }
        return count;
    }
    
    std::size_t String::RemoveAll(const std::string &charsToRemove) {
        std::size_t count=0;
        std::string oldData = data;
        data.clear();
        
        for (char i : oldData)
        {
            bool good=true;
            for (char c : charsToRemove)
            {
                if (i==c)
                {
                    count++;
                    good=false;
                    break;
                }
            }
            if (good)
            {
                Append(i);
            }
            
        }
        return count;
    }
    
    std::size_t String::RemoveAll(const String &charsToRemove) {
        std::size_t count=0;
        std::string oldData = data;
        data.clear();
        
        for (char i : oldData)
        {
            bool good=true;
            for (int c=0; c<charsToRemove.Size(); c++)
            {
                if (i==charsToRemove[c])
                {
                    count++;
                    good=false;
                    break;
                }
            }
            if (good)
            {
                Append(i);
            }
            
        }
        return count;
    }
    
    std::size_t String::RemoveSequence(char sequenceToRemove) {
        return RemoveAll(sequenceToRemove);
    }
    
    std::size_t String::RemoveSequence(const char *sequenceToRemove) {
        std::size_t count=0;
        std::string oldData = data;
        std::string removalChars(sequenceToRemove);
        String tempString;
        Clear();
        std::size_t removalCheckIndex=0;
        
        for (int i=0; i<oldData.size(); i++)
        {
            if (oldData[i] == removalChars[removalCheckIndex])
            {
                tempString.Append(removalChars[removalCheckIndex]);
                removalCheckIndex++;
                if (removalCheckIndex==removalChars.size())
                {
                    removalCheckIndex=0;
                    tempString.Clear();
                    count++;
                }
                
            }
            else
            {
                if (removalCheckIndex > 0)
                {
                    Append(tempString);
                    tempString.Clear();
                }
                removalCheckIndex=0;
            }
        }
        return count;
    }
    
    std::size_t String::RemoveSequence(const std::string &removalChars) {
        std::size_t count=0;
        std::string oldData = data;
        String tempString;
        Clear();
        std::size_t removalCheckIndex=0;
        
        for (int i=0; i<oldData.size(); i++)
        {
            if (oldData[i] == removalChars[removalCheckIndex])
            {
                tempString.Append(removalChars[removalCheckIndex]);
                removalCheckIndex++;
                if (removalCheckIndex==removalChars.size())
                {
                    removalCheckIndex=0;
                    tempString.Clear();
                    count++;
                }
                
            }
            else
            {
                if (removalCheckIndex > 0)
                {
                    Append(tempString);
                    tempString.Clear();
                }
                removalCheckIndex=0;
            }
        }
        return count;
    }
    
    std::size_t String::RemoveSequence(const String &removalChars) {
        std::size_t count=0;
        std::string oldData = data;
        String tempString;
        Clear();
        std::size_t removalCheckIndex=0;
        
        for (int i=0; i<oldData.size(); i++)
        {
            if (oldData[i] == removalChars[removalCheckIndex])
            {
                tempString.Append(removalChars[removalCheckIndex]);
                removalCheckIndex++;
                if (removalCheckIndex==removalChars.Size())
                {
                    removalCheckIndex=0;
                    tempString.Clear();
                    count++;
                }
                
            }
            else
            {
                if (removalCheckIndex > 0)
                {
                    Append(tempString);
                    tempString.Clear();
                }
                removalCheckIndex=0;
            }
        }
        return count;
    }
    
    char String::RemoveChar(std::size_t index) {
        std::string oldData = data;
        data.clear();
        for (int i=0; i<oldData.size(); i++)
        {
            if (i!=index)
            {
                Append(oldData[i]);
            }
        }
        return oldData[index];
    }
    
    
    
    char String::RemoveStart() {
        return RemoveChar(0);
    }
    
    char String::RemoveEnd() {
        return RemoveChar(Size()-1);
    }
    
    void String::Capitalize() {
        if (data[0])
        {
            data[0] = ToUpper(data[0]);
        }
        if (data.size()>1)
        {
            for (int i=1; 1<data.size(); i++)
            {
                data[i] = ToUpper(data[i]);
            }
        }
        
    }
    
    void String::Upper() {
        for (char & i : data)
        {
            i = ToUpper(i);
        }
    }
    
    void String::Lower() {
        for (int i=0; i<data.size(); i++)
        {
            data[i] = ToLower(data[i]);
        }
    }
    
    void String::ReverseCase() {
        for (int i=0; i<data.size(); i++)
        {
            if (std::islower(data[i]))
            {
                data[i] = ToUpper(data[i]);
            }
            else if (std::isupper(data[i]))
            {
                data[i] = ToLower(data[i]);
            }
        }
        
    }
    
    void String::Reverse() {
        String newData;
        for (int i=LastIndex(); i>0; --i)
        {
            newData.Append(data[i]);
        }
        data = newData.data;
    }
    
    void String::Clear(){
        data.clear();
    }
    
    String String::Capitalized()const
    {
        String value;
        if (data[0])
        {
            value.Append(ToUpper(data[0]));
        }
        if (data.size()>1)
        {
            for (int i=1; 1<data.size(); i++)
            {
                value.Append(ToUpper(data[i]));
            }
        }
        return value;
    }
    String String::ToUpper()const
    {
        String value;
        for (char i : data)
        {
            value.Append(ToUpper(i));
        }
        return value;
    }
    String String::ToLower()const
    {
        String value;
        for (int i=0; i<data.size(); i++)
        {
            value.Append(ToLower(data[i]));
        }
        return value;
    }
    String String::ToReverseCase()const
    {
        String value;
        for (int i=0; i<data.size(); i++)
        {
            if (IsLower(data[i]))
            {
                value.Append(ToUpper(data[i]));
            }
            else if (IsUpper(data[i]))
            {
                value.Append(ToLower(data[i]));
            }
        }
        return value;
    }
    String String::ToReverse()const
    {
        String newData;
        for (int i=LastIndex(); i>=0; --i)
        {
            newData.Append(data[i]);
        }
        return newData;
    }
    
    int String::ToInt()const
    {
        int result = 0;
        bool negative = false;
        std::size_t i = 0;
        if (data[i] == '-') {
            negative = true;
            i++;
        }
        for (; i < Size(); i++) {
            char c = data[i];
            if (c < '0' || c > '9') {
                throw std::invalid_argument("Invalid input string");
            }
            result = result * 10 + (c - '0');
        }
        return negative ? -result : result;
        
    }
    
    char String::ToChar()const
    {
        return data[0];
    }
    const char* String::ToCharStr()const
    {
        return data.c_str();
    }
    const std::string& String::ToStdString()const
    {
        return data;
    }
    
    
    
}