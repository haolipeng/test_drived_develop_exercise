//
// Created by Administrator on 2020\1\31 0031.
//

#ifndef TDD_STUDY_SOUNDEX_H
#define TDD_STUDY_SOUNDEX_H

#include <string>
//#include <c++/4.8.2/string>
#include "gmock/gmock.h"
#include <unordered_map>
#include <c++/4.8.2/string>
#include <c++/4.8.2/cstddef>

//分成几个步骤来实现
//一个字母的情况
//第一个字母后，用数字替代辅音
//测试字母-数字转换表


//暂时放到一个文件中
class Soundex{
public:
    /*
     * 编码（外部调用接口）*/
    std::string encode(std::string word) {
        //首字母大写
        std::string upperLetter = std::string(1,toupper(word.front()));

        //除去首字母的其他字符串
        std::string encoding = encodedDigits(word);
        std::string encodingLetter = encoding.substr(1);
        return zeroPad(std::string(upperLetter + encodingLetter), MaxCodeLength);
    }

    /*字符串长度不足4，进行补零
     * param text:已编码的字符串
     * param toLength:补零的长度
     * */
    std::string zeroPad(std::string text, size_t toLength){
        size_t zeroNeeded = toLength - text.length();
        return text + std::string(zeroNeeded,'0');
    }

    /*对全部字符串编码
     * param text:输入字符串
     * param toLength:补零的长度
     * */
    std::string encodedDigits(std::string& word){
        std::string encoding;

        //1.首字母处理
        encodeHead(encoding, word);

        //2.剩余字母处理
        encodeTail(encoding, word);

        //3.返回编码后字符串
        return encoding;
    }

    std::string encodedDigit(char letter) const {
        const std::unordered_map<char, std::string > encodings {
                {'b',"1"},{'f',"1"},{'p',"1"},{'v',"1"},
                {'c',"2"},{'g',"2"},{'j',"2"},{'k',"2"},{'q',"2"},{'s',"2"},{'x',"2"},{'z',"2"},
                {'d',"3"},{'t',"3"},
                {'l',"4"},
                {'m',"4"},{'n',"4"},
                {'r',"6"},
        };

        //统一转换成小写字母
        char lowerLetter = (char)tolower(letter);
        auto ite = encodings.find(lowerLetter);
        if(ite == encodings.end())
        {
            return NotADigit;
        }
        return ite->second;
    }

private:
    /*判断是否是元音*/
    bool isVowel(char letter) {
        return std::string("aeiouy").find(tolower(letter)) != std::string::npos;
    }

    /*首字母编码*/
    void encodeHead(std::string& encoding,std::string word)
    {
        encoding += encodedDigit(word.front());
    }

    /*剩余字符串编码*/
    void encodeTail(std::string& encoding,std::string word)
    {
        size_t length = word.length();
        for (int i = 1; i < length; ++i) {
            //已编码字符串长度等于MaxCodeLength
            if(encoding.length() == MaxCodeLength)
                break;

            std::string digit = encodedDigit(word[i]);
            //1.当前解析的字符和上次解析的字符不相同
            //2.或者当前解析的字符的前一个字符是元音
            if(digit != NotADigit && (digit != lastDigit(encoding) || isVowel(word[i-1])))
                encoding += digit;
        }
    }

    /*获取编码后字符串最后一个字符*/
    std::string lastDigit(const std::string& encoding)
    {
        if(encoding.empty())
            return NotADigit;

        return std::string(1,encoding.back());
    }

    const std::string NotADigit{"*"};
    static const size_t MaxCodeLength{4};
};

#endif //TDD_STUDY_SOUNDEX_H
