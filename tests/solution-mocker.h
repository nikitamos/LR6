#include <solutions.h>

class FakeSolution: public LR6::Solution {
public:
  FakeSolution() : LR6::Solution() {}
  void SetInputString(std::string s);
  virtual int GetChar() override;
private:
  std::string input_;
};