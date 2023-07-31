#include "model.h"

s21::Model::Model() : calculated_value_(0), x_is_in_expression_(false) {}

s21::Model::~Model() {}

bool s21::Model::GetPostfixNotation(std::string input_expression) {
  bool no_error_found = true;

  std::list<Node> signs_list_;

  char last_scanned_char = CHR_NONE;

  for (std::string::iterator it = input_expression.begin();
       it != input_expression.end() && no_error_found; it++) {
    RemoveSpaces(it);
    if (isdigit(*it) || *it == '.') {
      no_error_found = GetDoubleFromString(it);
    } else if (CharIsASign(*it)) {
      no_error_found = AddSignToList(signs_list_, *it, last_scanned_char);
    } else if (*it == OPEN_BKT) {
      no_error_found = OpenBktCase(it, signs_list_);
    } else if (*it == CLOSE_BKT) {
      no_error_found = ReturnToOpenBkt(signs_list_);
    } else if (*it == 'x') {
      notation_list_.push_back(Node(0, true, CHR_NONE));
      x_is_in_expression_ = true;
    } else if (isalpha(*it)) {
      no_error_found = ReadFunctionName(it, signs_list_);
    } else {
      no_error_found = false;
    }
    last_scanned_char = *it;
  }

  if (no_error_found) {
    while (!signs_list_.empty() &&
           (last_scanned_char = signs_list_.back().get_sign()) != OPEN_BKT) {
      notation_list_.push_back(Node(0, false, last_scanned_char));
      signs_list_.pop_back();
    }
    if (last_scanned_char == OPEN_BKT) {
      no_error_found = false;
    }
  }

  return no_error_found;
}

void s21::Model::RemoveSpaces(std::string::iterator &i) {
  while (*i == ' ') *i++;
}

bool s21::Model::GetDoubleFromString(std::string::iterator &i) {
  bool no_error = true;

  if (*i == '.') {
    i++;
    if (EndOfString(*i)) {
      no_error = false;
    }
  }
  double val = 0;
  int count_symbols_read = 0;
  int sscanf_result = sscanf(&i[0], "%le %n", &val, &count_symbols_read);
  i += count_symbols_read - 1;

  if (*i == ' ') i--;

  i++;
  if (!(*i == 'E' || *i == 'e')) i--;

  notation_list_.push_back(Node(val, false, CHR_NONE));

  return (sscanf_result == 1) && no_error;
}

bool s21::Model::AddSignToList(std::list<Node> &list_of_signs, char sign,
                               char last_c) {
  bool no_error = true;

  if (!isnumber(last_c) && last_c != 'x' && last_c != CLOSE_BKT) {
    if (sign == MINUS) {
      sign = UNAR_MINUS;
    } else if (sign == PLUS) {
      sign = UNAR_PLUS;
    }
  }
  if (list_of_signs.empty()) {
    list_of_signs.push_back(Node(0, false, sign));
  } else {
    char prev_sign = list_of_signs.back().get_sign();

    if (GetSignPriority(sign) > GetSignPriority(prev_sign)) {
      list_of_signs.push_back(Node(0, false, sign));
    } else {
      if (sign == POWER && prev_sign == sign) {
        list_of_signs.push_back(Node(0, false, sign));
      } else if ((sign == UNAR_PLUS || sign == UNAR_MINUS) &&
                 prev_sign == sign) {
        no_error = false;
      } else {
        char last_added_sign = list_of_signs.back().get_sign();
        while (!list_of_signs.empty() &&
               GetSignPriority(sign) <= GetSignPriority(last_added_sign)) {
          list_of_signs.pop_back();
          notation_list_.push_back(Node(0, false, last_added_sign));
          last_added_sign = list_of_signs.back().get_sign();
        }
        list_of_signs.push_back(Node(0, false, sign));
      }
    }
  }
  return no_error;
}

bool s21::Model::OpenBktCase(std::string::iterator &i,
                             std::list<Node> &list_of_signs) {
  bool no_error = true;
  i++;
  if (*i == CLOSE_BKT) {
    no_error = false;
  } else {
    i--;
    list_of_signs.push_back(Node(0, false, *i));
  }
  return no_error;
}

bool s21::Model::ReturnToOpenBkt(std::list<Node> &list_of_signs) {
  bool no_error = true;

  char sign = CHR_NONE;

  while (!list_of_signs.empty() &&
         (sign = list_of_signs.back().get_sign()) != OPEN_BKT) {
    notation_list_.push_back(Node(0, false, sign));
    list_of_signs.pop_back();
  }
  if (sign != OPEN_BKT) {
    no_error = false;
  } else {
    list_of_signs.pop_back();
  }

  return no_error;
}

bool s21::Model::ReadFunctionName(std::string::iterator &i,
                                  std::list<Node> &list_of_signs) {
  bool stat = true;  // no errors

  std::string func_name;

  while (isalpha(*i)) {
    func_name += *i;
    i++;
  }
  if (func_name == "sin") {
    stat = AddSignToList(list_of_signs, SIN, CHR_NONE);
  } else if (func_name == "cos") {
    stat = AddSignToList(list_of_signs, COS, CHR_NONE);
  } else if (func_name == "tan") {
    stat = AddSignToList(list_of_signs, TAN, CHR_NONE);
  } else if (func_name == "sqrt") {
    stat = AddSignToList(list_of_signs, SQRT, CHR_NONE);
  } else if (func_name == "ln") {
    stat = AddSignToList(list_of_signs, LN, CHR_NONE);
  } else if (func_name == "log") {
    stat = AddSignToList(list_of_signs, LOG, CHR_NONE);
  } else if (func_name == "mod") {
    stat = AddSignToList(list_of_signs, MOD, CHR_NONE);
  } else if (func_name == "asin") {
    stat = AddSignToList(list_of_signs, ASIN, CHR_NONE);
  } else if (func_name == "acos") {
    stat = AddSignToList(list_of_signs, ACOS, CHR_NONE);
  } else if (func_name == "atan") {
    stat = AddSignToList(list_of_signs, ATAN, CHR_NONE);
  } else {
    stat = false;
  }
  i--;
  return stat;
}

bool s21::Model::Calculations(double x) {
  bool no_errors = false;

  std::deque<double> values_container;

  int signs_amount = AmountOfSignsInList();
  int values_amount = notation_list_.size() - signs_amount;

  char sign = CHR_NONE;

  if (!notation_list_.empty() &&
      ((signs_amount >= 1 && values_amount >= 1) || values_amount == 1)) {
    no_errors = true;
  }

  notation_list_.reverse();
  std::list<Node>::reverse_iterator list_iter = notation_list_.rbegin();

  while (no_errors && list_iter != notation_list_.rend()) {
    if (list_iter->get_is_x()) {
      values_container.push_back(x);
    }
    if (NodeIsAValue(*list_iter)) {
      values_container.push_back(list_iter->get_value());
    }
    if (RepresentsAnOperation(list_iter->get_sign())) {
      sign = list_iter->get_sign();
      if (SignIsAnUnaryOperation(sign)) {
        no_errors = UnaryOperationCalculations(values_container, sign);
      } else if (SignIsABinaryOperation(sign)) {
        no_errors = BinaryOperationCalculations(values_container, sign);
      }
    }
    list_iter++;
  }
  if (values_container.size() > 1) {
    no_errors = false;
  }
  if (no_errors) {
    calculated_value_ = values_container.back();
  }
  return no_errors;
}

int s21::Model::AmountOfSignsInList() {
  int signs_count = 0;
  for (const Node &node : notation_list_) {
    if (RepresentsAnOperation(node.get_sign())) {
      signs_count++;
    }
  }
  return signs_count;
}

bool s21::Model::NodeIsAValue(Node node) {
  return !(node.get_is_x() || node.get_sign() != CHR_NONE);
}

bool s21::Model::UnaryOperationCalculations(
    std::deque<double> &values_container, char sign) {
  if (values_container.empty()) return false;

  double value = values_container.back();
  values_container.pop_back();

  double result = 0.0;
  bool no_errors = true;

  switch (sign) {
    case UNAR_PLUS:
      result = value;
      break;
    case UNAR_MINUS:
      result = -value;
      break;
    case SIN:
      result = sin(value);
      break;
    case COS:
      result = cos(value);
      break;
    case TAN:
      result = tan(value);
      break;
    case SQRT:
      if (value >= 0)
        result = sqrt(value);
      else
        no_errors = false;
      break;
    case LN:
      if (value > 0)
        result = log(value);
      else
        no_errors = false;
      break;
    case LOG:
      if (value > 0)
        result = log10(value);
      else
        no_errors = false;
      break;
    case ASIN:
      if (value >= -1 && value <= 1)
        result = asin(value);
      else
        no_errors = false;
      break;
    case ACOS:
      if (value >= -1 && value <= 1)
        result = acos(value);
      else
        no_errors = false;
      break;
    case ATAN:
      result = atan(value);
      break;
    default:
      no_errors = false;
      break;
  }

  if (no_errors) values_container.push_back(result);
  return no_errors;
}

bool s21::Model::BinaryOperationCalculations(
    std::deque<double> &values_container, char sign) {
  if (values_container.size() < 2) return false;

  bool no_errors = true;

  double b = values_container.back();
  values_container.pop_back();
  double a = values_container.back();
  values_container.pop_back();

  double result = 0.0;

  switch (sign) {
    case MINUS:
      result = a - b;
      break;
    case PLUS:
      result = a + b;
      break;
    case DIVIDE:
      if (b != 0)
        result = a / b;
      else
        no_errors = false;
      break;
    case MULTIPLY:
      result = a * b;
      break;
    case POWER:
      result = pow(a, b);
      break;
    case MOD:
      if (b != 0)
        result = fmod(a, b);
      else
        no_errors = false;
      break;
    default:
      no_errors = false;
      break;
  }
  if (no_errors) values_container.push_back(result);
  return no_errors;
}

bool s21::Model::RepresentsAnOperation(char c) {
  return (c == POWER || c == PLUS || c == UNAR_MINUS || c == UNAR_PLUS ||
          c == MINUS || c == MULTIPLY || c == DIVIDE || c == SIN || c == COS ||
          c == TAN || c == SQRT || c == LN || c == LOG || c == MOD ||
          c == ASIN || c == ACOS || c == ATAN);
}

bool s21::Model::EndOfString(char c) { return (c == '\n' || c == '\0'); }

bool s21::Model::CharIsASign(char c) {
  return (c == PLUS || c == MINUS || c == MULTIPLY || c == DIVIDE ||
          c == POWER);
}

int s21::Model::GetSignPriority(char c) {
  int lvl = -1;
  if (c == SIN || c == COS || c == TAN || c == SQRT || c == LN || c == LOG ||
      c == ASIN || c == ACOS || c == ATAN)
    lvl = 4;
  else if (c == POWER)
    lvl = 3;
  else if (c == UNAR_MINUS || c == UNAR_PLUS)
    lvl = 2;
  else if (c == MULTIPLY || c == DIVIDE || c == MOD)
    lvl = 1;
  else if (c == PLUS || c == MINUS)
    lvl = 0;
  return lvl;
}

bool s21::Model::SignIsAnUnaryOperation(char sign) {
  return (sign == UNAR_MINUS || sign == UNAR_PLUS || sign == SIN ||
          sign == COS || sign == TAN || sign == SQRT || sign == LN ||
          sign == LOG || sign == ASIN || sign == ACOS || sign == ATAN);
}

bool s21::Model::SignIsABinaryOperation(char sign) {
  return (sign == MINUS || sign == PLUS || sign == DIVIDE || sign == MULTIPLY ||
          sign == POWER || sign == MOD);
}

double s21::Model::get_calculated_value() { return calculated_value_; }

void s21::Model::ProcessGraph(double x_begin, double x_end) {
  double h = 0.0099;

  int N = ((x_end - x_begin) / h) + 1;

  std::vector<double> x(N);
  std::vector<double> y(N);

  int count_not_inserted_values = 0;

  int i = 0;
  for (double X = x_begin; X <= x_end; X += h) {
    if (Calculations(X)) {
      x[i] = X;
      y[i] = get_calculated_value();

      i++;
    } else
      count_not_inserted_values++;
  }

  x.resize(N - count_not_inserted_values);
  y.resize(N - count_not_inserted_values);

  x_graph_values_ = x;
  y_graph_values_ = y;
}

std::vector<double> s21::Model::get_x_graph_values() { return x_graph_values_; }

std::vector<double> s21::Model::get_y_graph_values() { return y_graph_values_; }

bool s21::Model::get_x_is_in_expression() { return x_is_in_expression_; }

void s21::Model::ClearAll() {
  notation_list_.clear();

  calculated_value_ = 0;

  x_graph_values_.clear();
  y_graph_values_.clear();

  x_is_in_expression_ = false;
}
