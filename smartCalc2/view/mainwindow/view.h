#ifndef CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_VIEW_VIEW_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_VIEW_VIEW_H_

#include <QMainWindow>

#include "../../controller/controller.h"
#include "../graphwindow/graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller *controller, QWidget *parent = nullptr);
  ~View();

 signals:
  void signal(QString graph_formula);

 private slots:
  void on_pushButton_clicked();

  void on_eraseButton_clicked();

  void on_graphButton_clicked();

 private:

  Controller *controller_;

  Ui::View *ui_;

  bool x_is_initialized_;

  GraphWindow *graph_window_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_SMARTCALC2_VIEW_VIEW_H_
