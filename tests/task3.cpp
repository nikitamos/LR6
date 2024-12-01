#include <gtest/gtest.h>
#include <solutions.h>
#include <string>

#include "fuzztest/fuzztest.h"

namespace LR6 {
namespace testing {
using ::fuzztest::internal_no_adl::InRegexp;
using ::fuzztest::Arbitrary;
using ::fuzztest::StringOf;
using ::fuzztest::PrintableAsciiString;

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

TEST(ParseStringToUL, ParsesEmptyString) {
  Solution s;
  const char* str = "";
  ASSERT_EQ(s.ParseStrToUL(str), 0);
}

auto EvenSymmetricalString(std::string s)  {
  
}
auto OddSymmetricalString(std::string s) {
  
}

}  // namespace testing
}  // namespace LR6