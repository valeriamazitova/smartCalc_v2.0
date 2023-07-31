#include "graphwindow.h"

#include "ui_graphwindow.h"

s21::GraphWindow::GraphWindow(QWidget *parent, Controller *controller)
    : QDialog(parent), ui_(new Ui::GraphWindow), graph_controller_(controller) {
  ui_->setupUi(this);
}

s21::GraphWindow::~GraphWindow() {
  delete ui_;
}

void s21::GraphWindow::on_buildButton_clicked() {
  graph_controller_->Refresh();

  double x_start = ui_->x_begin->value();
  double x_end = ui_->x_end->value();

  double y_start = ui_->y_begin->value();
  double y_end = ui_->y_end->value();

  int status = graph_controller_->GenerateGraph(
      ui_->expression_label->text().toStdString(), x_start, x_end, y_start, y_end);

  if (status == OK) {
    ui_->status_label->setText("Status bar: OK. Graph is printed.");

    std::vector<double> x_values = graph_controller_->GetXValuesVector();

    std::vector<double> y_values = graph_controller_->GetYValuesVector();

    QVector<double> qVector_x_values(x_values.begin(), x_values.end());

    QVector<double> qVector_y_values(y_values.begin(), y_values.end());

    ui_->widget->clearGraphs();

    ui_->widget->addGraph();

    ui_->widget->graph(0)->setData(qVector_x_values, qVector_y_values);

    ui_->widget->xAxis->setRange(x_start, x_end);

    ui_->widget->yAxis->setRange(y_start, y_end);

    ui_->widget->replot();

  } else if (status == WRONG_EXPRESSION) {
    ui_->status_label->setText("Status bar: Expression parsing error (!!!)");

  } else if (status == INPUT_ERROR) {
    ui_->status_label->setText(
        "Status bar: Wrong input arguments: x_begin should be less than "
        "x_end,\n y_begin should be less than y_end.");
  }
}

void s21::GraphWindow::slot(QString graph_formula) {
  ui_->expression_label->setText(graph_formula);

  ui_->status_label->setText("Status bar: ");
}
