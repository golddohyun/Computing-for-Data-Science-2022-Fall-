#pragma once
#include <iostream>
using namespace std;

class WordCounter
{
private:
    string const whitespace = " \r\n\t\v\f";
    string text;
    string findword;
    string buffer;
    int len;

public:
    void InputText(string atext);
    int GetWordCount();
    int GetCharacterCount();
    int GetUniqueWordCount();
    int GetWordCount_OneWord(const char* find_word);
    WordCounter();
    ~WordCounter();
};
