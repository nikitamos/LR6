#include <gtest/gtest.h>
#include <fuzztest/fuzztest.h>
#include <fuzztest/domain.h>
#include "fuzztest/fuzztest.h"
#include "solutions.h"

namespace LR6 {
namespace testing {

TEST(GetCodepoint, AsciiString) {
  Solution s;
  const char kChars[] = "213498dksajfjUJGfbJ"; 
  size_t size = sizeof(kChars);
  int i=0;
  for (; i<size;) {
    int j=i;
    ASSERT_EQ(s.GetCodepoint(kChars, i), kChars[j]);
  }
  ASSERT_EQ(kChars[i-1], '\0');
}

TEST(GetCodepoint, AsciiChar) {
  Solution s;
  const char kX = 'x';
  int i = 0;
  ASSERT_EQ(s.GetCodepoint(&kX, i), kX);
}

TEST(GetCodepoint, CyrillicChar) {
  Solution s;
  const char *str = "я";
  int i = 0;
  ASSERT_EQ(s.GetCodepoint(str, i), 0x044F);
}

TEST(GetCodepoint, CyrillicString) {
  Solution s;
  const int kLetters = 5;
  const char *str = "ФКСиС";
  const int kCorrect[kLetters] = {0x0424, 0x041A, 0x0421, 0x0438, 0x0421};
  int sym = 0;
  for (int i=0; i<kLetters; ++i) {
    int next = sym;
    ASSERT_EQ(s.GetCodepoint(str, next), kCorrect[i]);
    ASSERT_EQ(next-sym, 2);
    sym = next;
  }
}

TEST(GetCodepoint, LongCodepoint) {
  Solution s;
  const char* str = "𝄞";
  int index = 0;
  ASSERT_EQ(s.GetCodepoint(str, index), 0x01D11E);
}

TEST(GetCodepoint, TwoByteUtf8) {
  Solution s;
  const char* str = "\u0700";
  int index = 0;
  ASSERT_EQ(s.GetCodepoint(str, index), 0x0700);
}


TEST(CountLetters, AllLatin) {
  Solution s;
  const char latin[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
  Solution::LetterCount expected = {.consonants = 40, .vowels=12};
  ASSERT_EQ(s.CountLetters(latin, 52), expected);
}

TEST(CountLetters, AllCyrillic) {
  Solution s;
  const char* cyrillic = "ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
  Solution::LetterCount expected = {.consonants = 42, .vowels=20};
  ASSERT_EQ(s.CountLetters(cyrillic, strlen(cyrillic)), expected);
}

TEST(CountLetters, LatinAndCyrillic) {
  Solution s;
  const char str[] = "бгуирbsuir";
  const int kLen = sizeof(str) - 1;
  Solution::LetterCount expected = {6, 4};
}

TEST(CountLetters, NoLetters) {
  Solution s;
  const char str[] = "274&(* 23) 2 2 }  [42 + 58 = 100]";
  const int kLen = sizeof(str) - 1;
  Solution::LetterCount expected = {0, 0};
  ASSERT_EQ(s.CountLetters(str, kLen), expected);
}

TEST(CountLetters, All) {
  Solution s;
  const char str[] = "ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ"
                    "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
  Solution::LetterCount expected {82, 32};
  const int kLen = sizeof(str)-1;
  ASSERT_EQ(s.CountLetters(str, kLen), expected);
}

TEST(CountLetters, EmptyString) {
  Solution s;
  const char str[] = "";
  Solution::LetterCount expected {0, 0};
  const int kLen = sizeof(str)-1;
  ASSERT_EQ(s.CountLetters(str, kLen), expected);
}

TEST(CountLetters, NoLettersNoAscii) {
  Solution s;
  const char str[] = "∑∏∜";
  Solution::LetterCount expected {0, 0};
  const int kLen = sizeof(str)-1;
  ASSERT_EQ(s.CountLetters(str, kLen), expected);
}

TEST(CountLetters, NormalLettersAmongWideUTF8) {
  Solution s;
  const char str[] = "⥁Дз⍍ы🔔нь┇";
  Solution::LetterCount expected {3, 1};
  const int kLen = sizeof(str)-1;
  ASSERT_EQ(s.CountLetters(str, kLen), expected); 
}

TEST(CountLetters, SoftHardSigns) {
  Solution s;
  const char str[] = "ьъЬЪ";
  const int kLen = sizeof(str) - 1;
  Solution::LetterCount expected {0, 0};
  ASSERT_EQ(s.CountLetters(str, kLen), expected);
}

TEST(CountLetters, Substring) {
  Solution s;
  const char str[] = "keyboard";
  const int kLen = 4;
  Solution::LetterCount expected {2, 2};
  ASSERT_EQ(s.CountLetters(str, kLen), expected);
}

}  // namespace testing
}  // namespace LR6