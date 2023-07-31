#include "controller.h"

s21::Controller::Controller(Model *model)
    : model_(model), x_value_is_set_(false) {}

s21::Controller::~Controller() {}

double s21::Controller::GetCalcResult() {
  return model_->get_calculated_value();
}

int s21::Controller::CheckCorrectnessOfExpression(
    std::string input_expression) {
  bool resultCheck = model_->GetPostfixNotation(input_expression);

  if (!resultCheck) return WRONG_EXPRESSION;

  bool x_in_expression = model_->get_x_is_in_expression();

  return (x_in_expression && !x_value_is_set_) ? NO_INPUT_X : OK;
}

int s21::Controller::PerformCalculations(double x) {
  bool no_calc_errors = model_->Calculations(x);

  return (no_calc_errors) ? OK : CALC_ERROR;
}

int s21::Controller::GenerateGraph(std::string graph_expression, double x_begin,
                                   double x_end, double y_begin, double y_end) {
  if (x_begin >= x_end || y_begin >= y_end) return INPUT_ERROR;

  if (!model_->GetPostfixNotation(graph_expression)) return WRONG_EXPRESSION;

  model_->ProcessGraph(x_begin, x_end);

  return OK;
}

std::vector<double> s21::Controller::GetXValuesVector() {
  return model_->get_x_graph_values();
}

std::vector<double> s21::Controller::GetYValuesVector() {
  return model_->get_y_graph_values();
}

void s21::Controller::set_x_value_is_set(bool x_is_set) {
  x_value_is_set_ = x_is_set;
}

void s21::Controller::Refresh() {
  x_value_is_set_ = false;

  model_->ClearAll();
}
