#include "common.h"

namespace s21 {
std::list<std::vector<int>> s21::Common::Parser() {
  LOG_TRACE
  std::ifstream file("../emnist-letters-test.csv");
  int n = 0;
  if (file.is_open()) {
    std::vector<int> numbers;
    int number;
    std::string line;
    while (std::getline(file, line)) {
      std::vector<int> values;
      std::stringstream ss(line);
      std::string cell;
      while (std::getline(ss, cell, ',')) {
        std::stringstream(cell) >> number;
        values.push_back(number);
      }
      data_.push_back(values);
//      if (values[0] == 26) {
//        break;
//      }
      if (n == 1)
        break;
      n++;
    }
    file.close();
  } else {
    std::cout << "No such file";
  }
  return data_;
}
} // namespace s21

// cin