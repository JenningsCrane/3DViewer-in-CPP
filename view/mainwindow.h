#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller/controller.h"
#include "myglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller &contra, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionFile_triggered();
  void on_push_button_center_clicked();
  void on_double_spin_box_translate_ox_valueChanged();
  void on_double_spin_box_translate_oy_valueChanged();
  void on_double_spin_box_translate_oz_valueChanged();
  void on_double_spin_box_rotation_ox_valueChanged();
  void on_double_spin_box_rotation_oy_valueChanged();
  void on_double_spin_box_rotation_oz_valueChanged();
  void on_double_spin_box_scale_valueChanged();
  void on_radio_button_perspective_toggled(bool checked);
  void on_radio_button_parallel_toggled(bool checked);
  void on_radio_button_line_clicked();
  void on_radio_button_stipple_clicked();
  void on_radio_button_disable_clicked();
  void on_double_spin_box_lines_width_valueChanged(double arg1);
  void on_double_spin_box_point_size_valueChanged(double arg1);
  void on_push_button_color_lines_clicked();
  void on_radio_button_square_clicked();
  void on_radio_button_circle_clicked();
  void on_radio_button_point_disable_clicked();
  void on_push_button_color_point_clicked();
  void on_push_button_color_background_clicked();

  void on_screenshot_clicked();

  void on_gif_screencast_clicked();

  void on_radio_button_bmp_clicked();

  void on_radio_button_jpeg_clicked();

  void on_push_button_save_setting_clicked();

  void on_push_button_load_setting_clicked();

 private:
  Ui::MainWindow *ui;
  virtual void wheelEvent(QWheelEvent *event);
  s21::Controller &controller;
};

}  // namespace s21

#endif  // MAINWINDOW_H
