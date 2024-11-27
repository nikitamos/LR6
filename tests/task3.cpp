#include <gtest/gtest.h>

#include "fuzztest/fuzztest.h"

namespace LR6 {
namespace testing {
using ::fuzztest::internal_no_adl::InRegexp;

auto PushChars(std::string s, size_t count, std::string chr) {
  using namespace fuzztest;
  return
}

auto SymmetricalString(auto max_size) {
  auto size = ::fuzztest::InRange(0, max_size / 2);
  return ::fuzztest::FlatMap(
      [](size_t x) {
        return ::fuzztest::VectorOf(InRegexp("\\p{Cyrillic}")).WithSize(x);
      },
      size);
}

void PrintSth(const std::string &s) { std::cout << s << '\n'; }

FUZZ_TEST(UNTEST, PrintSth).WithDomains(SymmetricalString(40));

}  // namespace testing
}  // namespace LR6