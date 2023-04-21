#include "WordCounter.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;


WordCounter::WordCounter(){
}

void WordCounter::InputText(string atext){
    // remove leading and trailing spaces from a string
    auto start = atext.find_first_not_of(whitespace);
    auto end = atext.find_last_not_of(whitespace);
    
    text =  atext.substr(start, end - start + 1);
    len = text.length();
}

int WordCounter::GetWordCount(){
    int words = 1;
    for (int size = 0; text[size] != '\0' ; size++)
    {
        if (text[size] == ' ') words ++;
    }
    return words;
}

int WordCounter::GetCharacterCount(){
    int result = 0;
    for (auto x : text)
    {
        if ('A' <= x && x <= 'z' ) result ++;
    }
    return result;
}

int WordCounter::GetUniqueWordCount(){
    vector<string> v;
    istringstream ss(text);
    v.clear();
    while (getline(ss, buffer, ' '))
    {
        v.push_back(buffer);}
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    return v.size();
}

int WordCounter::GetWordCount_OneWord(const char* find_word){
    findword = find_word;
    int wordlen = findword.length();
    int count = 0;
    int i, j;
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < wordlen; j++)
        {
            if (text[i+j] != findword[j]) break;
        }
        if (j == wordlen) count++;
    }
    return count;
}

WordCounter::~WordCounter(){}


