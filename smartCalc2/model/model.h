#ifndef CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_MODEL_MODEL_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_MODEL_MODEL_H_

#include <cmath>
#include <deque>
#include <list>
#include <string>
#include <vector>

namespace s21 {
class Model {
 public:
  enum Operation {
    POWER = '^',
    PLUS = '+',
    UNAR_MINUS = '~',
    UNAR_PLUS = '#',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    SIN = 's',
    COS = 'c',
    TAN = 't',
    SQRT = '1',
    LN = '2',
    LOG = '3',
    MOD = '4',
    ASIN = '5',
    ACOS = '6',
    ATAN = '7',
    OPEN_BKT = '(',
    CLOSE_BKT = ')',
    CHR_NONE = '\0'
  };

  class Node {
   public:
    Node() : value_(0), is_x_(false), sign_(CHR_NONE) {}

    Node(double value, bool is_x, char sign)
        : value_(value), is_x_(is_x), sign_(sign) {}

    double get_value() const { return value_; }

    bool get_is_x() const { return is_x_; }

    char get_sign() const { return sign_; }

   private:
    double value_;
    bool is_x_;
    char sign_;
  };

  Model();
  ~Model();

  //    public methods
  bool GetPostfixNotation(std::string input_expression);

  bool Calculations(double x);

  double get_calculated_value();

  void ProcessGraph(double x_begin, double x_end);

  std::vector<double> get_x_graph_values();

  std::vector<double> get_y_graph_values();

  bool get_x_is_in_expression();

  void ClearAll();

 private:
  std::list<Node> notation_list_;

  double calculated_value_;

  std::vector<double> x_graph_values_;
  std::vector<double> y_graph_values_;

  bool x_is_in_expression_;

  static void RemoveSpaces(std::string::iterator &i);

  bool GetDoubleFromString(std::string::iterator &i);

  bool AddSignToList(std::list<Node> &signs_list, char sign, char last_c);

  bool OpenBktCase(std::string::iterator &i, std::list<Node> &list_of_signs);

  bool ReturnToOpenBkt(std::list<Node> &list_of_signs);

  bool ReadFunctionName(std::string::iterator &i,
                        std::list<Node> &list_of_signs);

  int AmountOfSignsInList();

  static bool NodeIsAValue(Node node);

  static bool UnaryOperationCalculations(std::deque<double> &values_container,
                                         char sign);

  static bool BinaryOperationCalculations(std::deque<double> &values_container,
                                          char sign);

  static bool RepresentsAnOperation(char c);

  static bool EndOfString(char c);

  static bool CharIsASign(char c);

  int GetSignPriority(char c);

  bool SignIsAnUnaryOperation(char sign);

  bool SignIsABinaryOperation(char sign);

  //  bool DotIsSuitableForGraph(double y, double y_begin, double y_end);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_MODEL_MODEL_H_
