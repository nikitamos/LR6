#include <fuzztest/fuzztest.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

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

void ReadsNormalStrings(std::string s) {
  FakeSolution fs;
  fs.SetInputString(s);
  char* buf = fs.ReadLine();

  ASSERT_EQ(s, buf);
  delete[] buf;
}

void ReadsLongStrings(std::string s) {
  FakeSolution fs;
  fs.SetInputString(s);
  char* buf = fs.ReadLine();
  if (s.size() > 80) {
    s.resize(80);
  }
  ASSERT_EQ(s, buf);
  delete[] buf;
}
const auto ReadsNormalCyrillicStrings = ReadsNormalStrings;
const auto ReadsLongCyrillicStrings = ReadsLongStrings;

FUZZ_TEST(FakeSolution, ReadsNormalStrings)
    .WithDomains(fuzztest::internal_no_adl::InRegexp("[a-zA-Z0-9 ,.!]{1,80}"));

FUZZ_TEST(FakeSolution, ReadsLongStrings)
    .WithDomains(
        fuzztest::internal_no_adl::InRegexp("[a-zA-Z0-9 ,.!]{81,160}"));

FUZZ_TEST(FakeSolution, ReadsNormalCyrillicStrings)
    .WithDomains(fuzztest::internal_no_adl::InRegexp("[а-яА-Я]{1,40}"));

FUZZ_TEST(FakeSolution, ReadsLongCyrillicStrings)
    .WithDomains(fuzztest::internal_no_adl::InRegexp("[а-яА-Я]{41,80}"));

TEST(FakeSolution, ReadsEmptyStrings) {
  FakeSolution fs;
  fs.SetInputString("");
  char* buf = fs.ReadLine();
  ASSERT_STREQ(buf, "");
  delete[] buf;
}
