#ifndef CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_CONTROLLER_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

#define OK 0
#define WRONG_EXPRESSION 1
#define NO_INPUT_X 2
#define INPUT_ERROR 3
#define CALC_ERROR 4

namespace s21 {
class Controller {
 public:
  Controller(Model *model);
  ~Controller();

  double GetCalcResult();

  int CheckCorrectnessOfExpression(std::string input_expression);

  int PerformCalculations(double x);

  int GenerateGraph(std::string graph_expression, double x_begin, double x_end,
                    double y_begin, double y_end);

  std::vector<double> GetXValuesVector();

  std::vector<double> GetYValuesVector();

  void set_x_value_is_set(bool x_is_set);

  void Refresh();

 private:
  Model *model_;

  bool x_value_is_set_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_CONTROLLER_CONTROLLER_H_
