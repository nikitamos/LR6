#include <gtest/gtest.h>
#include "solutions.h"

namespace LR6 {
namespace testing {

TEST(GetCodepoint, Ascii) {
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

TEST(GetCodepoint, 1Ascii) {
  Solution s;
  const char kX = 'x';
  int i = 0;
  ASSERT_EQ(s.GetCodepoint(&kX, i), kX);
}

TEST(GetCodepoint, 1Cyrillic) {
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


TEST(CountLetters, AllLatin) {
  Solution s;
  const char* latin = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
  Solution::LetterCount expected = {.consonants = 40, .vowels=12};
  ASSERT_EQ(s.CountLetters(latin, 52), expected);
}

TEST(CountLetters, AllCyrillic) {
  Solution s;
  const char* cyrillic = "ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
  Solution::LetterCount expected = {.consonants = 46, .vowels=20};
  ASSERT_EQ(s.CountLetters(cyrillic, strlen(cyrillic)), expected);
}

}  // namespace testing
}  // namespace LR6