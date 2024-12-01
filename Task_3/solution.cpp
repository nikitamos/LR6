#include <limits>
#include <solutions.h>

#include <cstdio>
#include <cstring>
#include <format>
#include <stdexcept>

namespace LR6 {
class ULParseError : public std::runtime_error {
 public:
  explicit ULParseError(int p)
      : position_(p),
        std::runtime_error(std::format("Ошибка разбора на позиции {}", p)) {}
  int GetPosition() const { return position_; }

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
    if (e.GetPosition() == strlen(buf)) {
      std::cerr << kErrorFormat << "Некорректный ввод\n";
      delete[] buf;
      return;
    }
    std::cerr << kErrorFormat << "Ошибка разбора на позиции "
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
  std::cout << n << '\n';
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

bool LR6::Solution::IsStringSymmetrical(const char* str) const {
  int length = 0;
  for (; str[length] != '\0'; ++length) {
  }
  for (int i = 0; i < length / 2;) {
    int a = GetCodepoint(str, i);
    int j = length - i;
    int b = GetCodepoint(str, j);
    if (a != b) {
      return false;
    }
  }
  return true;
}

LR6::u64 LR6::Solution::ParseStrToUL(const char* str) {
  __int128_t result = 0;
  for (const char* c = str; *c != '\0'; ++c) {
    if ('0' <= *c && *c <= '9') {
      result *= 10;
      result += *c - '0';
      if (result > static_cast<__uint128_t>(std::numeric_limits<u64>::max())) {
        throw ULParseError(c - str);
      }
    } else {
      throw ULParseError(c - str);
    }
  }
  return result;
}
