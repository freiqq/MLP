#ifndef S21_MLP_MLP_
#define S21_MLP_MLP_

#define LOG_INIT                                                               \
  FILE *fp_init = fopen("../Logs/logs.txt", "w");                              \
  fclose(fp_init);

#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "../Logs/TraceLogger.h"

namespace s21 {
class Common {
public:
  Common() {}
  std::list<std::vector<int>> Parser();

private:
  std::list<std::vector<int>> data_;
};
} // namespace s21

#endif // S21_MLP_MLP_