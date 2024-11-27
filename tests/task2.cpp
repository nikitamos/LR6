#include <fuzztest/fuzztest.h>
#include <gtest/gtest.h>

#include "solutions.h"

namespace LR6 {
namespace testing {

TEST(GetCodepoint, AsciiString) {
  Solution s;
  const char kChars[] = "213498dksajfjUJGfbJ";
  size_t size = sizeof(kChars);
  int i = 0;
  for (; i < size;) {
    int j = i;
    ASSERT_EQ(s.GetCodepoint(kChars, i), kChars[j]);
  }
  ASSERT_EQ(kChars[i - 1], '\0');
}

TEST(GetCodepoint, AsciiChar) {
  Solution s;
  const char kX = 'x';
  int i = 0;
  ASSERT_EQ(s.GetCodepoint(&kX, i), kX);
}

TEST(GetCodepoint, CyrillicChar) {
  Solution s;
  const char kStr[] = "я";
  int i = 0;
  ASSERT_EQ(s.GetCodepoint(kStr, i), 0x044F);
}

TEST(GetCodepoint, CyrillicString) {
  Solution s;
  const int kLetters = 5;
  const char kStr[] = "ФКСиС";
  const int kCorrect[kLetters] = {0x0424, 0x041A, 0x0421, 0x0438, 0x0421};
  int sym = 0;
  for (int i = 0; i < kLetters; ++i) {
    int next = sym;
    ASSERT_EQ(s.GetCodepoint(kStr, next), kCorrect[i]);
    ASSERT_EQ(next - sym, 2);
    sym = next;
  }
}

TEST(GetCodepoint, MixedString) {
  Solution s;
  const int kLetters = 4;
  const char kStr[] = "GЫGъ";
  const int kCorrect[kLetters] = {'G', 0x042B, 'G', 0x044A};
  int sym = 0;
  for (int i = 0; i < kLetters; ++i) {
    int next = sym;
    ASSERT_EQ(s.GetCodepoint(kStr, next), kCorrect[i]);
    sym = next;
  }
}

TEST(GetCodepoint, MixedString2) {
  Solution s;
  const int kLetters = 3;
  const char kStr[] = "Y🎓я";
  const int kCorrect[kLetters] = {'Y', 0x01F393, 0x044F};
  int sym = 0;
  for (int i = 0; i < kLetters; ++i) {
    int next = sym;
    ASSERT_EQ(s.GetCodepoint(kStr, next), kCorrect[i]);
    sym = next;
  }
}

TEST(GetCodepoint, FourByteUtf8) {
  Solution s;
  const char kStr[] = "𝄞";
  int index = 0;
  ASSERT_EQ(s.GetCodepoint(kStr, index), 0x01D11E);
}

TEST(GetCodepoint, TwoByteUtf8) {
  Solution s;
  const char kStr[] = "\u0700";
  int index = 0;
  ASSERT_EQ(s.GetCodepoint(kStr, index), 0x0700);
}

TEST(GetCodepoint, ThreeByteUtf8) {
  Solution s;
  const char kStr[] = "ᨡ";
  int index = 0;
  ASSERT_EQ(s.GetCodepoint(kStr, index), 0x1A21);
}

TEST(GetCodepoint, EmptyString) {
  Solution s;
  const char kStr[] = "";
  int index = 0;
  ASSERT_EQ(s.GetCodepoint(kStr, index), '\0');
}

TEST(CountLetters, AllLatin) {
  Solution s;
  const char kLatin[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
  Solution::LetterCount expected = {.consonants = 40, .vowels = 12};
  ASSERT_EQ(s.CountLetters(kLatin, 52), expected);
}

TEST(CountLetters, AllCyrillic) {
  Solution s;
  const char* cyrillic =
      "ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
  Solution::LetterCount expected = {.consonants = 42, .vowels = 20};
  ASSERT_EQ(s.CountLetters(cyrillic, strlen(cyrillic)), expected);
}

TEST(CountLetters, LatinAndCyrillic) {
  Solution s;
  const char kStr[] = "бгуирbsuir";
  const int kLen = sizeof(kStr) - 1;
  Solution::LetterCount expected = {6, 4};
}

TEST(CountLetters, NoLetters) {
  Solution s;
  const char kStr[] = "274&(* 23) 2 2 }  [42 + 58 = 100]";
  const int kLen = sizeof(kStr) - 1;
  Solution::LetterCount expected = {0, 0};
  ASSERT_EQ(s.CountLetters(kStr, kLen), expected);
}

TEST(CountLetters, All) {
  Solution s;
  const char kStr[] =
      "ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ"
      "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
  Solution::LetterCount expected{82, 32};
  const int kLen = sizeof(kStr) - 1;
  ASSERT_EQ(s.CountLetters(kStr, kLen), expected);
}

TEST(CountLetters, EmptyString) {
  Solution s;
  const char kStr[] = "";
  Solution::LetterCount expected{0, 0};
  const int kLen = sizeof(kStr) - 1;
  ASSERT_EQ(s.CountLetters(kStr, kLen), expected);
}

TEST(CountLetters, NoLettersNoAscii) {
  Solution s;
  const char kStr[] = "∑∏∜";
  Solution::LetterCount expected{0, 0};
  const int kLen = sizeof(kStr) - 1;
  ASSERT_EQ(s.CountLetters(kStr, kLen), expected);
}

TEST(CountLetters, NormalLettersAmongWideUTF8) {
  Solution s;
  const char kStr[] = "⥁Дз⍍ы🔔нь┇";
  Solution::LetterCount expected{3, 1};
  const int kLen = sizeof(kStr) - 1;
  ASSERT_EQ(s.CountLetters(kStr, kLen), expected);
}

TEST(CountLetters, SoftHardSigns) {
  Solution s;
  const char kStr[] = "ьъЬЪ";
  const int kLen = sizeof(kStr) - 1;
  Solution::LetterCount expected{0, 0};
  ASSERT_EQ(s.CountLetters(kStr, kLen), expected);
}

TEST(CountLetters, SubString) {
  Solution s;
  const char kStr[] = "keyboard";
  const int kLen = 4;
  Solution::LetterCount expected{2, 2};
  ASSERT_EQ(s.CountLetters(kStr, kLen), expected);
}

}  // namespace testing
}  // namespace LR6