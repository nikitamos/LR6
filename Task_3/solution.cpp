#include <limits>
#include <solutions.h>

#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <format>

namespace LR6 {
class ULParseError: public std::runtime_error {
  public:
  explicit ULParseError(int p): position_(p), std::runtime_error(std::format("Ошибка разбора на позиции {}", p)) {}
  int GetPosition() const {
    return position_;
  }
  private:
  int position_;
};
}  // namespace LR6

void LR6::Solution::SolveProblem3() {
  std::cout << kReset << "Размерность массива ";
  PrettyInput();
  char* buf = ReadLine();
  int n = 0;
  errno = 0;
  try {
    n = ParseStrToUL(buf);
  } catch (ULParseError& e) {
    std::cerr << kErrorFormat
                << "Ошибка разбора на позиции "
                << e.GetPosition() + 1 << ":\n"
                << kDefault << buf << '\n';
      for (int _ = 0; _ < e.GetPosition(); ++_) {
        std::cerr << ' ';
      }
      std::cerr << kPurple + kBold << "^ " << kRed + kBold << " здесь\n"
                << kReset;
      delete[] buf;
      return;
  }
  if (n == 0) {
    std::cout << kReset << "Для пустого массива справедливо всё что угодно\n";
    delete[] buf;
    return;
  }
  char** strings = new char*[n];
  for (size_t i = 0; i < n; ++i) {
    std::cout << kReset << "Строка " << kBold << i + 1 << ' ';
    PrettyInput();
    strings[i] = ReadLine();
  }
  std::cout << kReset << "Ниже будут выведены симметричные строки\n";
  for (size_t i = 0; i < n; ++i) {
    if (IsStringSymmetrical(strings[i])) {
      std::cout << kGreen + kBold << strings[i] << '\n';
    }
  }

  for (size_t i = 0; i < n; ++i) {
    delete[] strings[i];
    strings[i] = nullptr;
  }
  delete[] strings;
  strings = nullptr;
  delete[] buf;
  buf = nullptr;
}

bool LR6::Solution::IsStringSymmetrical(char* str) const {
  int length = 0;
  for (; str[length] != '\0'; ++length) {}
  for (int i = 0; i < length / 2;) {
    if ((str[i] & 0x80) == 0 && (str[length - i - 1] & 0x80) == 0) {  // ASCII
      if (str[i] != str[length - i - 1]) {
        return false;
      }
      ++i;
    } else {
      int a = GetCodepoint(str, i);
      int j = length - i;
      int b = GetCodepoint(str, j);
      if (a != b) {
        return false;
      }
    }
  }
  return true;
}

unsigned long LR6::Solution::ParseStrToUL(const char* str) {
  unsigned long result = 0;
  for (const char* c = str; *c != '\0'; ++c) {
    auto oldres = result;
    if ('0' <= *c && *c <= '9') {
      result *= 10;
      result += *c - '9';
      if (oldres > result) {
        throw ULParseError(c - str);
      }
    } else {
      throw ULParseError(c- str);
    }
  }
  return result;
}