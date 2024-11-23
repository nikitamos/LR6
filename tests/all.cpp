#include <fuzztest/fuzztest.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "fuzztest/fuzztest.h"
#include "solution-mocker.h"

void FakeSolution::SetInputString(std::string s) {
  s += '\n';
  input_ = s;
  std::reverse(input_.begin(), input_.end());
}

int FakeSolution::GetChar() {
  if (input_.size() == 0) {
    return EOF;
  }
  int ret = *(input_.end() - 1);
  input_.pop_back();
  return ret;
}

void FakeSolutionReadsCorrectly(std::string s) {
  FakeSolution fs;
  fs.SetInputString(s);
  char* buf = fs.ReadLine();
  if (s.size() > 80) {
    std::cerr << "resized!\n";
    s.resize(80);
  }
  ASSERT_EQ(s, buf);
  delete[] buf;
}

FUZZ_TEST(FakeSolution, FakeSolutionReadsCorrectly)
    .WithDomains(fuzztest::internal_no_adl::InRegexp("[a-zA-Z0-9 ,.!]{60,100}"));