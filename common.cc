#include <asm-generic/ioctls.h>
#include <solutions.h>
#include <sys/ioctl.h>

#include <cstdio>
#include <iostream>

std::ostream& LR6::operator<<(std::ostream& stream, LR6::EscapeSequence seq) {
#ifdef ENABLE_COLOR
  constexpr const size_t kStyleIndex = 2;
  constexpr const size_t kColorIndex = 5;
  char escape[8] = "\e[X;3Xm";
  escape[kColorIndex] = '0' + seq.color;
  escape[kStyleIndex] = '0' + seq.style;
  return stream << escape;
#else
  return stream;
#endif
}

std::ostream& LR6::operator<<(std::ostream& stream, LR6::Color color) {
#ifdef ENABLE_COLOR
  return stream << LR6::EscapeSequence(color);
#else
  return stream;
#endif
}
std::ostream& LR6::operator<<(std::ostream& stream, LR6::Style style) {
#ifdef ENABLE_COLOR
  return stream << EscapeSequence(style);
#else
  return stream;
#endif
}

char* LR6::Solution::ReadLine(char* reuse) const {
  if (reuse == nullptr) {
    try {
      reuse = new char[buf_size_ + 1];
    } catch (std::bad_alloc& e) {
      std::cout << kErrorFormat << "Не удалось выделить память\n";
      return nullptr;
    }
  }

  for (size_t i = 0; i < buf_size_; ++i) {
    int c = getchar();
    switch (c) {
      case EOF:
        std::cerr << kErrorFormat << "Поток ввода закрыт.\n";
      case '\r':
      case '\n':
        reuse[i] = '\0';
        return reuse;
      default:
        reuse[i] = c;
    }
  }
  std::cout << kWarningFormat << "Учитываются только " << buf_size_
            << " байт\n";
  std::cin.clear();
  reuse[buf_size_] = '\0';
  return reuse;
}

void LR6::Solution::PrintDescription() {
  std::cout << kReset << kYellow + kBold << "Задача 1: " << kReset << kCyan
            << "считывает строку чисел, разделенных пробелами и выводит их в "
               "порядке возрастания\n"
            << kYellow + kBold << "Задача 2: " << kReset << kCyan
            << "Определяет, каких букв больше во введенной строке: гласных или "
               "согласных\n"
            << kYellow + kBold << "Задача 3: " << kReset << kCyan
            << "Находит симметричные строки во введенном массиве строк\n"
            << kReset;
}

int LR6::Solution::GetTerminalWidth() {
  struct winsize window_size;
  if (ioctl(0, TIOCGWINSZ, &window_size) != 0) {
    return -1;
  }
  return window_size.ws_col;
}

void LR6::Solution::SetBufferSize(size_t new_size) { buf_size_ = new_size; }
int LR6::Solution::GetChar() const {
  return getchar();
}