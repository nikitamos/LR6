#include <gtest/gtest.h>
#include <limits>
#include <solutions.h>

#include <algorithm>
#include <string>

#include "fuzztest/fuzztest.h"

namespace LR6 {
namespace testing {
using ::fuzztest::Arbitrary;
using ::fuzztest::InRange;
using ::fuzztest::Map;
using ::fuzztest::OneOf;
using ::fuzztest::InRegexp;

void ParsesCorrectStrings(u64 res) {
  Solution s;
  std::string str = std::to_string(res);
  ASSERT_EQ(s.ParseStrToUL(str.c_str()), res);
}
void ThrowsOnIncorrectStrings(std::string str) {
  Solution s;
  ASSERT_ANY_THROW(s.ParseStrToUL(str.c_str()));
}
void ThrowsOnTooLongInts(__uint128_t x) {
  Solution sol;
  std::string s;
  while (x != 0) {
    s += '0' + (x % 10);
    x /= 10;
  }
  std::reverse(s.begin(), s.end());
  ASSERT_ANY_THROW(sol.ParseStrToUL(s.c_str()));
}

FUZZ_TEST(ParseStrToUL, ParsesCorrectStrings).WithDomains(Arbitrary<u64>());
FUZZ_TEST(ParseStrToUL, ThrowsOnIncorrectStrings)
    .WithDomains(InRegexp("\\d{0,17}[ -/:-~][ -~]*"));

FUZZ_TEST(ParseStrToUL, ThrowsOnTooLongInts)
    .WithDomains(InRange(static_cast<__uint128_t>(std::numeric_limits<u64>::max()) + 1, std::numeric_limits<__uint128_t>::max()));

TEST(ParseStrToUL, ParsesEmptyString) {
  Solution s;
  const char* str = "";
  ASSERT_EQ(s.ParseStrToUL(str), 0);
}

TEST(ParseStrToUL, ParsesMax) {
  Solution s;
  auto str = std::to_string(std::numeric_limits<u64>::max());
  ASSERT_EQ(s.ParseStrToUL(str.c_str()), std::numeric_limits<u64>::max());
}

auto EvenSymmetricalString() {
  auto any_str = InRegexp("([ -}]){1,40}");
  return Map(
      [](std::string s) {
        std::string s2;
        s2.resize(s.size()+1);
        std::reverse_copy(s.begin(), s.end(), s2.begin());
        return s + s2;
      },
      any_str);
}
auto OddSymmetricalString() {
  auto any_str = InRegexp("([ -}]){1,40}");
  return Map(
      [](std::string s) {
        std::string s2;
        s2.resize(s.size());
        std::reverse_copy(s.begin(), s.end() - 1, s2.begin());
        return s + s2;
      },
      any_str);
}
auto AnyAsymmerticalString() {
  auto sym_str = OneOf(EvenSymmetricalString(), OddSymmetricalString());
  return Map(
      [] (std::string s) {
        s.shrink_to_fit();
        return '~' + s;
      },
      sym_str);
}

void NormalSymmetrical(std::string str) {
  Solution s;
  ASSERT_TRUE(s.IsStringSymmetrical(str.c_str()));
}
void NormalAsymmetrical(std::string str) {
  Solution s;
  ASSERT_FALSE(s.IsStringSymmetrical(str.c_str()));
}

FUZZ_TEST(IsStringSymmetrical, NormalSymmetrical)
    .WithDomains(OneOf(EvenSymmetricalString(), OddSymmetricalString()));
FUZZ_TEST(IsStringSymmetrical, NormalAsymmetrical)
    .WithDomains(AnyAsymmerticalString());
}  // namespace testing
}  // namespace LR6