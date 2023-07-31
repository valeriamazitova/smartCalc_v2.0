#include <QApplication>

#include "view/mainwindow/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller);

  view.show();
  return a.exec();
}
