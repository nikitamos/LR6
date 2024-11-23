#include <fuzztest/fuzztest.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <solutions.h>

#include <format>
#include <string>
#include <vector>

using LR6::Solution;

namespace LR6 {
namespace testing {
namespace task1 {
static constinit Solution s;

void NormalStringNumbers(const std::string& a, const std::string& b) {
  ASSERT_EQ(s.GreaterOrEqual(a.c_str(), b.c_str()),
            std::stoul(a) >= std::stoul(b));
}

FUZZ_TEST(GreaterOrEqual, NormalStringNumbers)
    .WithDomains(fuzztest::internal_no_adl::InRegexp("[1-9]\\d{0,16}"),
                 fuzztest::internal_no_adl::InRegexp("[1-9]\\d{0,16}"));

TEST(GreaterOrEqual, EmptyStrings) {
  Solution s;
  const char* s1 = "";
  const char* s2 = "";
  ASSERT_TRUE(s.GreaterOrEqual(s1, s2));
}

MATCHER_P(NonDecreasingArray, size, "") {
  for (size_t i = 0; i < size - 1; ++i) {
    if (!s.GreaterOrEqual(arg[i + 1], arg[i])) {
      *result_listener << std::format("Elment ({}) is less than ({}): {} < {}",
                                      i + 1, i, arg[i + 1], arg[i]);
      return false;
    }
  }
  return true;
}

TEST(SortArray, Descending) {
  Solution s;
  const size_t kSize = 10;
  const char* array[kSize] = {"268214583475696384609874956215",
                              "54768435247498142",
                              "243857",
                              "455",
                              "167",
                              "167",
                              "8",
                              "7",
                              "6",
                              "0"};
  s.SortNumberArray(array, kSize);
  ASSERT_THAT(array, NonDecreasingArray(kSize));
}
// TODO(): imnplement the test
TEST(SortArray, Empty) {
}

void Arbitrary(const std::vector<std::string>& inp) {
  if (inp.size() == 0) { return; }
  const char** array = new const char*[inp.size()];
  for (size_t i = 0; i < inp.size(); ++i) {
    array[i] = inp[i].c_str();
  }
  s.SortNumberArray(array, inp.size());
  ASSERT_THAT(array, NonDecreasingArray(inp.size()));
  delete[] array;
}

FUZZ_TEST(SortArray, Arbitrary)
    .WithDomains(fuzztest::VectorOf(
        fuzztest::internal_no_adl::InRegexp("\\[1-9]\\d{0,12}")));
}  // namespace task1
}  // namespace testing
}  // namespace LR6