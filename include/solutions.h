#pragma once
#include <iostream>

namespace LR6 {
class Solution {
 public:
  char* ReadLine(char* reuse = nullptr);
  void PrintDescription();
  int GetTerminalWidth();
  
  void SolveProblem1();
  /**
    * Compares the strings lexicographically.
    */
  bool GreaterOrEqual(const char* first, const char* second) const;
  /**
    * Sorts the array of strings in non-decreasing order
    */
  void SortNumberArray(char const** numbers, size_t length);

  void SolveProblem2();

  void SolveProblem3();

  
  [[deprecated]]
  void SetBufferSize(size_t new_size);
  /**
    * Returns the Unicode Codepoint of the character at position 
    * `chr[index]` and advances `index` by number of bytes in the
    * string that represent the codepoint
    */
  int GetCodepoint(const char* chr, int& index) const;

 private:
  virtual int GetChar();
  enum Answer { kVowel, kConsonant, kNone };
  void SiftDown(const char** numbers, size_t length, size_t index) const;
  Answer GetLetterType(int);
  bool IsStringSymmetrical(char* str)const;
  size_t buf_size_ = 80;
  static const char* author;
};

enum Color {
  kBlack = 0,
  kRed = 1,
  kGreen = 2,
  kYellow = 3,
  kBlue = 4,
  kPurple = 5,
  kCyan = 6,
  kWhite = 7,
  kDefault = 9
};
enum Style { kNormal = 0, kDim = 2, kBold = 1 };

struct EscapeSequence {
  Color color;
  Style style;
  constexpr explicit EscapeSequence(Color color, Style style = kNormal)
      : color(color), style(style) {}
  constexpr explicit EscapeSequence(Style style)
      : color(kDefault), style(style) {}
};

constexpr EscapeSequence operator+(Color color, Style style) {
  return EscapeSequence(color, style);
}
constexpr EscapeSequence operator+(Style style, Color color) {
  return EscapeSequence(color, style);
}
static const constinit EscapeSequence kErrorFormat = kRed + kBold;
static const constinit EscapeSequence kReset(kDefault + kNormal);
static const constinit EscapeSequence kWarningFormat = kYellow + kDim;

std::ostream& operator<<(std::ostream& stream, EscapeSequence seq);
std::ostream& operator<<(std::ostream& stream, Color color);
std::ostream& operator<<(std::ostream& stream, Style style);

inline std::istream& PrettyInput() {
  // Отвергрнутыя стрѣлки: ↦
  std::cout << kPurple + kBold << "↠ " << kReset << kGreen + kDim;
  return std::cin;
}

}  // namespace LR6