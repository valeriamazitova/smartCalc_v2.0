#include <gtest/gtest.h>

#include "smartCalc2/controller/controller.h"
#include "smartCalc2/model/model.h"

constexpr double ACCURACY = 1e-6;

class SmartCalculatorTest : public ::testing::Test {
 protected:
  s21::Model model;
  std::unique_ptr<s21::Controller> controller;

  void SetUp() {
    controller = std::unique_ptr<s21::Controller>(new s21::Controller(&model));
  }

  void TearDown() { controller->Refresh(); }
};

TEST_F(SmartCalculatorTest, WrongInputTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("InputExpression"),
            WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, AdditionTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("3+2"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 5);
}

TEST_F(SmartCalculatorTest, AdditionTest2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("6+(-5)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 1);
}

TEST_F(SmartCalculatorTest, AdditionTest3) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("0+0"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 0);
}

TEST_F(SmartCalculatorTest, SinTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("sin(0)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 0);
}

TEST_F(SmartCalculatorTest, CosTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("cos(5)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  ASSERT_TRUE(fabs(controller->GetCalcResult() - 0.283662) < ACCURACY);
}

TEST_F(SmartCalculatorTest, CalcTest1) {
  controller->set_x_value_is_set(true);
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("tan(x)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 0);
}

TEST_F(SmartCalculatorTest, CalcTest2) {
  controller->set_x_value_is_set(true);
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(2*x+4)/(x-3)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  ASSERT_TRUE(fabs(controller->GetCalcResult() - (-1.33333334)) < ACCURACY);
}

TEST_F(SmartCalculatorTest, BracketsTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(1+5)/2"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 3);
}

TEST_F(SmartCalculatorTest, BracketsTest2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(1+2)*4+3"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 15);
}

TEST_F(SmartCalculatorTest, BracketsTest3) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("2/(3+2)*5"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 2);
}

TEST_F(SmartCalculatorTest, WrongBracketsTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("sin(90"),
            WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, WrongBracketsTest2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("((4+7)-11*(14/2)"),
            WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, WrongBracketsTest3) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(((()))"),
            WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, AdditionTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("2+3"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 5);
}

TEST_F(SmartCalculatorTest, SubtractionTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("5-3"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 2);
}

TEST_F(SmartCalculatorTest, MultiplicationTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("2*3"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 6);
}

TEST_F(SmartCalculatorTest, DivisionTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("6/3"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 2);
}

TEST_F(SmartCalculatorTest, ComplexExpressionTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("2 + (3 * 4) / (5 - 1)"),
            OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 5);
}

TEST_F(SmartCalculatorTest, BracketsTest4) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(2+3)*4"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 20);
}

TEST_F(SmartCalculatorTest, BracketsTest5) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(5-2)/3"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 1);
}

TEST_F(SmartCalculatorTest, DivisionByZeroTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1/0"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, InvalidExpressionTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("2+3+*"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, PowerRaisingTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("2^2^3"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 256);
}

TEST_F(SmartCalculatorTest, PowerRaisingTest2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(2^2^3 - 200) / 2"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 28);
}

TEST_F(SmartCalculatorTest, PowerRaisingTest3) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("3^2^2"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 81);
}

TEST_F(SmartCalculatorTest, CaclDoubles1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1.1 + 2.0 + 12.0 + 11.8"),
            OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_DOUBLE_EQ(controller->GetCalcResult(), 26.9);
}

TEST_F(SmartCalculatorTest, CaclDoubles2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1.5 * 2.5 * 3.5"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_DOUBLE_EQ(controller->GetCalcResult(), 13.125);
}

TEST_F(SmartCalculatorTest, CaclDoubles3) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(2.3 + 4.7) * 1.5"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_DOUBLE_EQ(controller->GetCalcResult(), 10.5);
}

TEST_F(SmartCalculatorTest, CaclDoubles4) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1.7 / 2.5"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_DOUBLE_EQ(controller->GetCalcResult(), 0.68);
}

TEST_F(SmartCalculatorTest, CaclDoubles5) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1.44^(0.5)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_DOUBLE_EQ(controller->GetCalcResult(), 1.2);
}

TEST_F(SmartCalculatorTest, CaclDoubles6) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1.44^(0.5)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_DOUBLE_EQ(controller->GetCalcResult(), 1.2);
}

TEST_F(SmartCalculatorTest, SinTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("sin(0.5)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 0.47942554, ACCURACY);
}

TEST_F(SmartCalculatorTest, CosTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("cos(1.0)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 0.54030231, ACCURACY);
}

TEST_F(SmartCalculatorTest, TanTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("tan(0.75)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 0.93159646, ACCURACY);
}

TEST_F(SmartCalculatorTest, ASinTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("asin(0.3)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 0.30469265, ACCURACY);
}

TEST_F(SmartCalculatorTest, ACosTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("acos(0.8)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 0.64350111, ACCURACY);
}

TEST_F(SmartCalculatorTest, ATanTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("atan(1.5)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 0.98279372, ACCURACY);
}

TEST_F(SmartCalculatorTest, SqrtTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("sqrt(9.0)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 3.0);
}

TEST_F(SmartCalculatorTest, ModTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("10mod(3)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 1.0);
}

TEST_F(SmartCalculatorTest, LnTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("ln(2.71828)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 1.0, ACCURACY);
}

TEST_F(SmartCalculatorTest, LogTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("log(1000.0)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 3.0, ACCURACY);
}

TEST_F(SmartCalculatorTest, UnaryPlusTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("+5"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 5);
}

TEST_F(SmartCalculatorTest, UnaryMinusTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("-7"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), -7);
}

TEST_F(SmartCalculatorTest, CombinedUnaryTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("-(+4)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), -4);
}

TEST_F(SmartCalculatorTest, ComplexTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("2 + 3 * (4 - 1)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 11);
}

TEST_F(SmartCalculatorTest, ComplexTest2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(5 + 2)^2 - sqrt(36)"),
            OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 43);
}

TEST_F(SmartCalculatorTest, ComplexTest3) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("sin(1/6) * cos(1/4)"),
            OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 0.16073882368, ACCURACY);
}

TEST_F(SmartCalculatorTest, ComplexTest4) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("log(100) + ln((1/7)^2)"),
            OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), -1.89182029811, ACCURACY);
}

TEST_F(SmartCalculatorTest, ComplexTest5) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("sin(0.5)^2 + cos(0.5)^2"),
            OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 1);
}

TEST_F(SmartCalculatorTest, ExponentTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1.23E"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 1.23);
}

TEST_F(SmartCalculatorTest, ExponentTest2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("4.76E10"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 47600000000);
}

TEST_F(SmartCalculatorTest, ExponentTest3) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("9.87E-4"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_EQ(controller->GetCalcResult(), 0.000987);
}

TEST_F(SmartCalculatorTest, ExponentTest4) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1.23E+4.87E"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, ExponentTest5) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1.23E-2+4.56E-2"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);
  EXPECT_NEAR(controller->GetCalcResult(), 0.0579, ACCURACY);
}

TEST_F(SmartCalculatorTest, WrongExpressionTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("https://21-school.ru/"),
            WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, WrongExpressionTest2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("{abcdf}"),
            WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, WrongExpressionTest3) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("."), WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, WrongExpressionTest4) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("--2"), WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, WrongExpressionTest5) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("7*3-4)"),
            WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, WrongExpressionTest6) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("++++++++1"),
            WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, WrongExpressionTest7) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("sin()(2)"),
            WRONG_EXPRESSION);
}

TEST_F(SmartCalculatorTest, CalcErrorTest1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("(+1 2 )"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, CalcErrorTest2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("sqrt(-81)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, CalcErrorTest3) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("log(-1000)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, CalcErrorTest4) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("ln(-1)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, CalcErrorTest5) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("asin(5)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, CalcErrorTest6) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("acos(10)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, CalcErrorTest7) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("3mod0"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, CalcErrorTest8) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("1.2.3+4.6"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), CALC_ERROR);
}

TEST_F(SmartCalculatorTest, NoInputXTest) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("tan(x)"), NO_INPUT_X);
}

TEST_F(SmartCalculatorTest, CorrectTestCase1) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("+(+1)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);

  EXPECT_EQ(controller->GetCalcResult(), 1);
}

TEST_F(SmartCalculatorTest, CorrectTestCase2) {
  EXPECT_EQ(controller->CheckCorrectnessOfExpression("-(-1)"), OK);

  EXPECT_EQ(controller->PerformCalculations(0.0), OK);

  EXPECT_EQ(controller->GetCalcResult(), 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}