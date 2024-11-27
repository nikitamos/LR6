#include <solutions.h>

#include <cctype>
#include <cstring>

void LR6::Solution::SolveProblem1() {
  std::cout << kReset
            << "Введите строку, состоящую из цифр, разделенных пробелами\n";
  PrettyInput();
  char* buf = this->ReadLine();
  std::cout << kReset;

  size_t number_count = 0;
  int length = std::strlen(buf);
  bool in_number = false;
  for (int i = 0; i < length; ++i) {
    if (std::isdigit(buf[i])) {
      if (!in_number) {
        in_number = true;
        ++number_count;
      }
    } else if (std::isspace(buf[i])) {
      in_number = false;
    } else {
      std::cerr << kErrorFormat
                << "Встречен символ, который не является цифрой или пробелом "
                   "на позиции "
                << i + 1 << ":\n"
                << kDefault << buf << '\n';
      for (int _ = 0; _ < i; ++_) {
        std::cerr << ' ';
      }
      std::cerr << kPurple + kBold << "^ " << kRed + kBold << " здесь\n"
                << kReset;
      delete[] buf;
      return;
    }
  }

  char** numbers = new char*[number_count](nullptr);
  for (int n = 0, j = 0; j < length && n < number_count; ++j) {
    if (std::isdigit(buf[j]) != 0) {
      if (numbers[n] == nullptr) {
        numbers[n] = buf + j;
      }
    } else {
      buf[j] = '\0';
      if (numbers[n] != nullptr) {
        ++n;
      }
    }
  }

  SortNumberArray(const_cast<const char**>(numbers), number_count);
  std::cout << kGreen << "Отсортированные числа: " << kGreen + kBold;
  for (size_t i = 0; i < number_count; ++i) {
    std::cout << numbers[i] << ", ";
  }
  std::cout << kReset << '\n';

  delete[] buf;
  delete[] numbers;
  buf = nullptr;
  numbers = nullptr;
}

void LR6::Solution::SortNumberArray(const char** numbers, size_t length) {
  for (size_t i = 0; i <= length / 2; ++i) {
    SiftDown(numbers, length, length / 2 - i);
  }

  do {
    std::swap(numbers[0], numbers[length - 1]);
    SiftDown(numbers, length - 1, 0);
    --length;
  } while (length != 0);
}

void LR6::Solution::SiftDown(const char** numbers, size_t length,
                             size_t index) const {
  if (index * 2 + 1 >= length) {
    return;
  }
  size_t target = 2 * index + 1;
  if (target + 1 < length &&
      GreaterOrEqual(numbers[target + 1], numbers[target])) {
    target += 1;
  }
  if (GreaterOrEqual(numbers[index], numbers[target])) {
    return;
  }
  std::swap(numbers[index], numbers[target]);
  SiftDown(numbers, length, target);
}

bool LR6::Solution::GreaterOrEqual(const char* first,
                                   const char* second) const {
  int len1 = strlen(first);
  int len2 = strlen(second);
  if (len1 != len2) {
    return len1 > len2;
  }
  size_t i = 0;
  for (; i < len1 && first[i] == second[i]; ++i) {
  }
  if (i == len1) {
    return true;
  }
  return first[i] > second[i];
}