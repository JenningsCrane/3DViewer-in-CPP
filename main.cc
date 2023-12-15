#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller &controller = s21::Controller::getInstance(&model);
  // controller = &controller->getInstance(&model);
  s21::MainWindow view(controller);
  view.show();
  return a.exec();
}
