#pragma once
#include <string>
#include <iostream>

namespace Candy
{
    class String
    {
    
    public:
        static char ToUpper(char c);
        static const char* ToUpper(const char* str);
        static std::string ToUpper(const std::string& str);
        static String ToUpper(const String& str);
        
        static char ToLower(char c);
        static const char* ToLower(const char* str);
        static std::string ToLower(const std::string& str);
        static String ToLower(const String& str);
        
        static bool IsUpper(char c);
        static bool IsLower(char c);
        static bool IsAlpha(char c);
        
        static String Number(int n, int base=10);
        static String Number(unsigned int n, int base=10);
        static String Number(double n, char format='g', int precision=4);
    private:
        std::string data;
    
    public:
        String();
        String(char c);
        String(std::string str);
        String(const char* str);
        String(String const &other);
    
    public:
        bool operator==(const String& other)const;
        bool operator!=(const String& other)const;
        
        char& operator[](std::size_t index);
        const char operator[](std::size_t index)const;
        
        
        void operator+=(char other);
        void operator+=(const char* other);
        void operator+=(const String& other);
        void operator+=(const std::string& other);
        
        
        
        explicit operator std::string()const;
        explicit operator const char*()const;
    
    public:
        bool IsEmpty()const;
        bool IsNotEmpty()const;
        std::size_t Size()const;
        char GetFirst()const;
        char GetLast()const;
        std::size_t LastIndex()const;
        
        String Substr(std::size_t start)const;
        String Substr(std::size_t start, std::size_t end)const;
        String SubstrRight(std::size_t index)const;
        String SubstrLeft(std::size_t index)const;
    
    public:
        void Append(char c);
        void Append(const char* str);
        void Append(const std::string& str);
        void Append(const String& str);
        
        void Prepend(char c);
        void Prepend(const char* str);
        void Prepend(const std::string& str);
        void Prepend(const String& str);
        
        void Insert(std::size_t index, char c);
        void Insert(std::size_t index, const char* str);
        void Insert(std::size_t index, const std::string& str);
        void Insert(std::size_t index, const String& str);
        
        std::size_t RemoveAll(char charsToRemove);
        std::size_t RemoveAll(const char* charsToRemove);
        std::size_t RemoveAll(const std::string& charsToRemove);
        std::size_t RemoveAll(const String& charsToRemove);
        
        std::size_t RemoveSequence(char sequenceToRemove);
        std::size_t RemoveSequence(const char* sequenceToRemove);
        std::size_t RemoveSequence(const std::string& sequenceToRemove);
        std::size_t RemoveSequence(const String& sequenceToRemove);
        
        char RemoveChar(std::size_t index);
        char RemoveStart();
        char RemoveEnd();
        
        void Capitalize();
        void Upper();
        void Lower();
        void ReverseCase();
        void Reverse();
        void Clear();
    
    public:
        String Capitalized()const;
        String ToUpper()const;
        String ToLower()const;
        String ToReverseCase()const;
        String ToReverse()const;
        
        
        int ToInt()const;
        char ToChar()const;
        const char* ToCharStr()const;
        const std::string& ToStdString()const;
    };
}

Candy::String operator + (const Candy::String& left, const Candy::String& right);
Candy::String operator + (const Candy::String& left, char right);
std::ostream& operator << (std::ostream& ostream, const Candy::String& str);

namespace std {
    template <typename T> struct hash;
    template<>
    struct hash<Candy::String>
    {
        std::size_t operator()(const Candy::String& str) const
        {
            hash<std::string> hasher;
            return hasher(str.ToStdString());
            
        }
    };
    
}