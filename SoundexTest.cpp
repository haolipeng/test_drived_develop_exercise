//
// Created by Administrator on 2020\1\31 0031.
//
#include "Soundex.h"

//google mock允许定义fixture类，我们可以在这个类中为相关的测试声明函数和数据
//去除了测试中重复的Soundex类实例
class SoundexEncoding : public testing::Test{
public:
    Soundex soundex;
};


//为了使用自定义的fixture的成员，要使用TEST_F
/*只有一个字母*/
TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
    ASSERT_THAT(soundex.encode("A"), testing::Eq("A000"));
    ASSERT_THAT(soundex.encode("I"), testing::Eq("I000"));
}

/*测试字符转换表*/
TEST_F(SoundexEncoding, ReplaceConsonantWithAppropriateDigit)
{
    /*
     * {'b',"1"},{'f',"1"},{'p',"1"},{'v',"1"},
        {'c',"2"},{'g',"2"},{'j',"2"},{'k',"2"},{'q',"2"},{'s',"2"},{'x',"2"},{'z',"2"},
        {'d',"3"},{'t',"3"},
        {'l',"4"},
        {'m',"4"},{'n',"4"},
        {'r',"6"},
    */
    ASSERT_THAT(soundex.encode("Ab"), testing::Eq("A100"));
    ASSERT_THAT(soundex.encode("Ac"), testing::Eq("A200"));
    ASSERT_THAT(soundex.encode("Ad"), testing::Eq("A300"));
    ASSERT_THAT(soundex.encode("Ax"), testing::Eq("A200"));
}

/*测试忽略非字符*/
TEST_F(SoundexEncoding, IgnoresNonAlphabetics)
{
    ASSERT_THAT(soundex.encode("A#"),testing::Eq("A000"));
}

/*测试在转换表中替换多个字符到数字*/
TEST_F(SoundexEncoding, ReplaceMultipleConsonantWithDigits)
{
    ASSERT_THAT(soundex.encode("Acdl"),testing::Eq("A234"));
    ASSERT_THAT(soundex.encode("acdl"),testing::Eq("A234"));
}

/*测试字符串编码后长度为4*/
TEST_F(SoundexEncoding, LimitsLengthToFourCharacters)
{
    ASSERT_THAT(soundex.encode("Dcdlb").length(), testing::Eq(4));
    ASSERT_THAT(soundex.encode("123").length(), testing::Eq(4));
}

/*测试元音对soundex的影响*/
TEST_F(SoundexEncoding, IgnoresVowelLikeLetters)
{
    ASSERT_THAT(soundex.encode("BaAeEiIoOuUhHyYcdl"), testing::Eq("B234"));
}

TEST_F(SoundexEncoding, CombineDuplicateEncodings)
{
    ASSERT_THAT(soundex.encodedDigit('b'), testing::Eq(soundex.encodedDigit('f')));
    ASSERT_THAT(soundex.encodedDigit('c'), testing::Eq(soundex.encodedDigit('g')));
    ASSERT_THAT(soundex.encodedDigit('d'), testing::Eq(soundex.encodedDigit('t')));

    ASSERT_THAT(soundex.encode("abfcgdt"),testing::Eq("A123"));
}

/*首字母变为大写*/
TEST_F(SoundexEncoding, UppercaseFirstLetter)
{
    ASSERT_THAT(soundex.encode("abcd"), testing::StartsWith("A"));
}

/*忽略大小写*/
TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants)
{
    ASSERT_THAT(soundex.encode("BCDL"), testing::Eq(soundex.encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombineMultipleDuplicateCode)
{
    ASSERT_THAT(soundex.encode("Bbcd"), testing::Eq("B230"));
}

/*测试元音的影响*/
TEST_F(SoundexEncoding, CombineDuplicateEncodingByVowels)
{
    ASSERT_THAT(soundex.encode("Jbob"), testing::Eq("J110"));
}
