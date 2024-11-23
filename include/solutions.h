#pragma once
#include <iostream>

namespace LR6 {
class Solution {
 public:
  void SolveProblem1();
  void SolveProblem2();
  void SolveProblem3();
  void PrintDescription();
  char* ReadLine(char* reuse = nullptr);
  int GetTerminalWidth();
  void SortNumberArray(char** numbers, size_t &length);
  [[deprecated]]
  void SetBufferSize(size_t new_size);
  int GetCodepoint(const char* chr, int& index) const;
  bool GreaterOrEqual(char* first, char* second) const;

 private:
  virtual int GetChar();
  enum Answer { kVowel, kConsonant, kNone };
  void SiftDown(char** numbers, size_t length, size_t index) const;
  Answer GetLetterType(int);
  bool IsStringSymmetrical(char* str)const;
  size_t buf_size_ = 81;
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