#ifndef CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_GRAPHWINDOW_GRAPHWINDOW_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_GRAPHWINDOW_GRAPHWINDOW_H_

#include <QDialog>
#include <QVector>
#include <vector>

#include "../../controller/controller.h"

namespace Ui {
class GraphWindow;
}

namespace s21 {
class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit GraphWindow(QWidget *parent = nullptr,
                       Controller *controller = nullptr);
  ~GraphWindow();

 public slots:
  void slot(QString graph_formula);

 private slots:
  void on_buildButton_clicked();

 private:
  Ui::GraphWindow *ui_;

  Controller *graph_controller_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_GRAPHWINDOW_GRAPHWINDOW_H_
