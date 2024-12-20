#include <solutions.h>

#include <exception>
#include <iostream>
#include <string>

int main() {
  LR6::Solution solution;
  const int kCaptionWidth = 33;
  int terminal_width = solution.GetTerminalWidth();
  if (terminal_width == -1) {
    terminal_width = 0;
    std::cout << LR6::kWarningFormat << "Не удалось получить ширину терминала\n"
              << LR6::kReset;
  }
  for (int i = 0; i < (terminal_width - kCaptionWidth) / 5; ++i) {
    putchar(' ');
  }

  std::cout << LR6::kCyan + LR6::kBold << "Лабораторная работа №6. "
            << LR6::EscapeSequence(LR6::kBold) << "Вариант 9" << '\n';
  std::cout << LR6::kReset << "Выполнил " << LR6::kBold << "Москалёв Никита\n\n";
  char* problem_no_str = new char[81];
  bool do_run = true;

  do {
    solution.PrintDescription();
    LR6::PrettyInput();
    solution.ReadLine(problem_no_str);
    int problem_num = 0;
    try {
      problem_num = std::stoi(problem_no_str);
    } catch (std::exception& e) {
      std::cerr << LR6::kErrorFormat << "Некорректный ввод!\n";
    }

    switch (problem_num) {
      case 0:
        do_run = false;
        break;
      case 1:
        solution.SolveProblem1();
        break;
      case 2:
        solution.SolveProblem2();
        break;
      case 3:
        solution.SolveProblem3();
        break;
      default:
        std::cerr << LR6::kErrorFormat
                  << "Неверный ввод или таска не выполнена\n";
    }
  } while (do_run);

  delete[] problem_no_str;
  return 0;
}