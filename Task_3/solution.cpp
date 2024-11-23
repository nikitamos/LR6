#include <solutions.h>

#include <cstdio>
#include <cstring>

void LR6::Solution::SolveProblem3() {
  std::cout << kReset << "Размерность массива ";
  PrettyInput();
  char* buf = ReadLine();
  errno = 0;
  size_t n = std::strtoul(buf, nullptr, 10);
  if (errno != 0) {
    std::cerr << kErrorFormat << "Ошибка обработки ввода: " << strerror(errno)
              << '\n';
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
  int length = strlen(str);
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