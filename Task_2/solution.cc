#include <solutions.h>

#include <cctype>
#include <cstring>

void LR6::Solution::SolveProblem2() {
  std::cout << kReset << "Введите строку";
  PrettyInput();
  char* buf = ReadLine();
  int length = std::strlen(buf);
  int consonants = 0;
  int vowels = 0;

  for (int i = 0; i < length;) {
    int cp = GetCodepoint(buf, i);
    switch (GetLetterType(cp)) {
      case Answer::kVowel:
        ++vowels;
        break;
      case Answer::kConsonant:
        ++consonants;
        break;
      case Answer::kNone:
        break;
    }
  }
  std::cout << "гласных: " << vowels << ", согласных: " << consonants << '\n';
  delete[] buf;
}

int LR6::Solution::GetCodepoint(const char* chr, int& index) const {
  int code = 0;
  int octets = 0;
  if ((0x80 & chr[index]) == 0x00) {
    code = chr[index];
  } else if ((0xF0 & chr[index]) == 0xF0) {
    code = 0x07 & chr[index];
    octets = 3;
  } else if ((0xE0 & chr[index]) == 0xE0) {
    code = 0x0f & chr[index];
    octets = 2;
  } else if ((0xC0 & chr[index]) == 0xC0) {
    code = 0x1f & chr[index];
    octets = 1;
  }
  for (int i = 1; i <= octets; ++i) {
    code <<= 6;
    code |= chr[index + i] & 0x3F;
  }
  index += octets + 1;
  return code;
}

LR6::Solution::Answer LR6::Solution::GetLetterType(int codepoint) {
  switch (codepoint) {
#include <Task2_VowelTable.inc>
    return Answer::kVowel;
#include <Task2_ConsonantTable.inc>
    return Answer::kConsonant;
    default:
      return Answer::kNone;
  }
}