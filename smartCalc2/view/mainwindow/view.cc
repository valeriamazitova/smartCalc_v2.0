#include "view.h"

#include "ui_view.h"

s21::View::View(Controller *controller, QWidget *parent)
    : QMainWindow(parent), controller_(controller), ui_(new Ui::View) {
  setFixedSize(535, 920);
  ui_->setupUi(this);

  QString imagePath = ":/new/prefix1/nature.jpeg";
  QString styleSheet = QString("background-image: url(%1);").arg(imagePath);
  ui_->centralwidget->setStyleSheet(styleSheet);

  graph_window_ = new GraphWindow(nullptr, controller_);

  connect(this, &View::signal, graph_window_, &GraphWindow::slot);
}

s21::View::~View() {
    delete ui_;
    delete graph_window_;
}

void s21::View::on_pushButton_clicked() {
  controller_->Refresh();

  x_is_initialized_ = ui_->calculate_withx_check_box->isChecked();

  double x_value = 0.0;
  if (x_is_initialized_) {
    x_value = ui_->spinbox_x_value->value();

    controller_->set_x_value_is_set(true);
  }

  QString qstring_expression = ui_->expressionEdit->text();
  std::string expression_as_str = qstring_expression.toStdString();

  int no_errors = OK;

  if ((no_errors = controller_->CheckCorrectnessOfExpression(
           expression_as_str)) == OK &&
      (no_errors = controller_->PerformCalculations(x_value)) == OK) {
    double result = controller_->GetCalcResult();
    QString qstring_result = QString::number(result, 'g', 11);
    ui_->expressionEdit->setText("");
    ui_->expressionEdit->setText(qstring_result);

  } else if (no_errors == WRONG_EXPRESSION) {
    ui_->expressionEdit->setText("WrongInput");

  } else if (no_errors == NO_INPUT_X) {
    ui_->expressionEdit->setText("Please try again. Insert x.");

  } else if (no_errors == CALC_ERROR) {
    ui_->expressionEdit->setText("Calculation Error");
  }
}

void s21::View::on_eraseButton_clicked() { ui_->expressionEdit->setText(""); }

void s21::View::on_graphButton_clicked() {
  emit signal(ui_->expressionEdit->text());

  graph_window_->setModal(true);
  graph_window_->exec();
}
