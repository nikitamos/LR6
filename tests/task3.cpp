#include <algorithm>
#include <gtest/gtest.h>
#include <solutions.h>
#include <string>

#include "fuzztest/fuzztest.h"

namespace LR6 {
namespace testing {
using ::fuzztest::internal_no_adl::InRegexp;
using ::fuzztest::Arbitrary;
using ::fuzztest::OneOf;
using ::fuzztest::PrintableAsciiString;
using ::fuzztest::PrintableAsciiChar;
using ::fuzztest::Map;
using ::fuzztest::FlatMap;
using ::fuzztest::InRange;

void ParsesCorrectStrings(u64 res) {
  Solution s;
  std::string str = std::to_string(res);
  ASSERT_EQ(s.ParseStrToUL(str.c_str()), res);
}
void ThrowsOnIncorrectStrings(std::string str) {

  Solution s;
  ASSERT_ANY_THROW(s.ParseStrToUL(str.c_str()));
}
auto ThrowsOnTooLongInts = &ThrowsOnIncorrectStrings;

FUZZ_TEST(ParseStrToUL, ParsesCorrectStrings).WithDomains(Arbitrary<u64>());
FUZZ_TEST(ParseStrToUL, ThrowsOnIncorrectStrings)
  .WithDomains(InRegexp("\\d{0,17}[ -/:-~][ -~]*"));

FUZZ_TEST(ParseStrToUL, ThrowsOnTooLongInts)
  .WithDomains(InRegexp("\\d{19,64}"));

TEST(ParseStrToUL, ParsesEmptyString) {
  Solution s;
  const char* str = "";
  ASSERT_EQ(s.ParseStrToUL(str), 0);
}

auto EvenSymmetricalString()  {
  auto any_str = PrintableAsciiString().WithMinSize(1).WithMaxSize(40);//InRegexp("([ -~]){1,40}");
  return Map([] (std::string s) {
    std::string s2;
    s2.resize(s.size());
    std::reverse_copy(s.begin(), s.end(), s2.begin());
    return s + s2;
  }, any_str);
}
auto OddSymmetricalString() {
  auto any_str = PrintableAsciiString().WithMinSize(1).WithMaxSize(40);//InRegexp("([ -~]){1,40}");
  return Map([] (std::string s) {
    std::string s2;
    s2.resize(s.size());
    std::reverse_copy(s.begin(), s.end()-1, s2.begin());
    return s + s2;
  }, any_str); 
}
auto AnyAsymmerticalString() {
  auto sym_str = OneOf(EvenSymmetricalString(), OddSymmetricalString());
  return FlatMap(
    [](std::string s) {
      return Map(
        [s] (size_t p, char c) {
          std::string s2 = s;
          s2.insert(p, 1, c);
          return s;
        },
        InRange(static_cast<size_t>(0), s.size()-1),
        PrintableAsciiChar()
      );
    },
    sym_str
  );
}

void NormalSymmetrical(std::string str) {
  Solution s;
  ASSERT_TRUE(s.IsStringSymmetrical(str.c_str()));
}

FUZZ_TEST(IsStringSymmetrical, NormalSymmetrical).WithDomains(OneOf(EvenSymmetricalString(), OddSymmetricalString()));

}  // namespace testing
}  // namespace LR6