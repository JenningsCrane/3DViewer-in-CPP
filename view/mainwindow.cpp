
#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionFile_triggered() {
  QString fileDialog = QFileDialog::getOpenFileName(
      this, QDir::homePath(), tr("Object Files (*.obj);;All Files (*)"),
      tr("Object Files (*.obj)"));
  if (fileDialog != "") ui->label_file_name->setText(QFileInfo(fileDialog).fileName());
  ui->openGLWidget->parcer(fileDialog);
  ui->label_value_v->setText(QString::number(ui->openGLWidget->size_v / 3));
  ui->label_value_f->setText(QString::number(ui->openGLWidget->size_f / 2));
}

void MainWindow::on_push_button_center_clicked() {
  ui->openGLWidget->centerFigure();
  ui->double_spin_box_translate_ox->setValue(0.0);
  ui->double_spin_box_translate_oy->setValue(0.0);
  ui->double_spin_box_translate_oz->setValue(0.0);
  ui->double_spin_box_rotation_ox->setValue(0.0);
  ui->double_spin_box_rotation_oy->setValue(0.0);
  ui->double_spin_box_rotation_oz->setValue(0.0);
  ui->double_spin_box_scale->setValue(0.0);
}

void MainWindow::on_double_spin_box_translate_ox_valueChanged() {
  ui->openGLWidget->move(ui->double_spin_box_translate_ox->value(),
                         ui->double_spin_box_translate_oy->value(),
                         ui->double_spin_box_translate_oz->value());
}

void MainWindow::on_double_spin_box_translate_oy_valueChanged() {
  ui->openGLWidget->move(ui->double_spin_box_translate_ox->value(),
                         ui->double_spin_box_translate_oy->value(),
                         ui->double_spin_box_translate_oz->value());
}

void MainWindow::on_double_spin_box_translate_oz_valueChanged() {
  ui->openGLWidget->move(ui->double_spin_box_translate_ox->value(),
                         ui->double_spin_box_translate_oy->value(),
                         ui->double_spin_box_translate_oz->value());
}

void MainWindow::on_double_spin_box_rotation_ox_valueChanged() {
  ui->openGLWidget->rotateOx(ui->double_spin_box_rotation_ox->value());
}

void MainWindow::on_double_spin_box_rotation_oy_valueChanged() {
  ui->openGLWidget->rotateOy(ui->double_spin_box_rotation_oy->value());
}

void MainWindow::on_double_spin_box_rotation_oz_valueChanged() {
  ui->openGLWidget->rotateOz(ui->double_spin_box_rotation_oz->value());
}

void MainWindow::on_double_spin_box_scale_valueChanged() {
  ui->openGLWidget->scaleXYZ(ui->double_spin_box_scale->value());
}

void MainWindow::on_radio_button_perspective_toggled(bool checked) {
  if (checked) {
    ui->radio_button_parallel->setChecked(0);
    ui->openGLWidget->projection(1);
  }
}

void MainWindow::on_radio_button_parallel_toggled(bool checked) {
  if (checked) {
    ui->radio_button_perspective->setChecked(0);
    ui->openGLWidget->projection(0);
  }
}

void MainWindow::on_radio_button_line_clicked() {
  if (ui->radio_button_line->isChecked()) {
    ui->radio_button_stipple->setChecked(0);
    ui->radio_button_disable->setChecked(0);
    ui->openGLWidget->line_type(0);
  }
}

void MainWindow::on_radio_button_stipple_clicked() {
  if (ui->radio_button_stipple->isChecked()) {
    ui->radio_button_line->setChecked(0);
    ui->radio_button_disable->setChecked(0);
    ui->openGLWidget->line_type(1);
  }
}

void MainWindow::on_radio_button_disable_clicked() {
  if (ui->radio_button_disable->isChecked()) {
    ui->radio_button_line->setChecked(0);
    ui->radio_button_stipple->setChecked(0);
    ui->openGLWidget->line_type(2);
  }
}

void MainWindow::on_push_button_color_lines_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) ui->openGLWidget->colorLine(color);
}

void MainWindow::on_double_spin_box_lines_width_valueChanged(double arg1) {
  ui->openGLWidget->line_width(arg1);
}

void MainWindow::on_double_spin_box_point_size_valueChanged(double arg1) {
  ui->openGLWidget->point_size(arg1);
}

void MainWindow::on_radio_button_square_clicked() {
  if (ui->radio_button_square->isChecked()) {
    ui->radio_button_circle->setChecked(0);
    ui->radio_button_point_disable->setChecked(0);
    ui->openGLWidget->point_type(0);
  }
}

void MainWindow::on_radio_button_circle_clicked() {
  if (ui->radio_button_circle->isChecked()) {
    ui->radio_button_square->setChecked(0);
    ui->radio_button_point_disable->setChecked(0);
    ui->openGLWidget->point_type(1);
  }
}

void MainWindow::on_radio_button_point_disable_clicked() {
  if (ui->radio_button_point_disable->isChecked()) {
    ui->radio_button_square->setChecked(0);
    ui->radio_button_circle->setChecked(0);
    ui->openGLWidget->point_type(2);
  }
}

void MainWindow::on_push_button_color_point_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) ui->openGLWidget->colorPoint(color);
}

void MainWindow::on_push_button_color_background_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) ui->openGLWidget->colorBackground(color);
}

void MainWindow::on_push_button_save_setting_clicked() { ui->openGLWidget->saveSetting(); }

void MainWindow::on_push_button_load_setting_clicked() {
  ui->openGLWidget->loadSetting();
  ui->double_spin_box_lines_width->setValue(ui->openGLWidget->size_line);
  ui->double_spin_box_point_size->setValue(ui->openGLWidget->size_point);
  if (!ui->openGLWidget->radio) {
    ui->radio_button_perspective->setChecked(0);
    ui->radio_button_parallel->setChecked(1);
  } else if (ui->openGLWidget->radio) {
    ui->radio_button_perspective->setChecked(1);
    ui->radio_button_parallel->setChecked(0);
  }

  if (ui->openGLWidget->stipple == 0) {
    ui->radio_button_line->setChecked(1);
    ui->radio_button_stipple->setChecked(0);
    ui->radio_button_disable->setChecked(0);
  } else if (ui->openGLWidget->stipple == 1) {
    ui->radio_button_line->setChecked(0);
    ui->radio_button_stipple->setChecked(1);
    ui->radio_button_disable->setChecked(0);
  } else if (ui->openGLWidget->stipple == 2) {
    ui->radio_button_line->setChecked(0);
    ui->radio_button_stipple->setChecked(0);
    ui->radio_button_disable->setChecked(1);
  }

  if (ui->openGLWidget->square == 0) {
    ui->radio_button_square->setChecked(1);
    ui->radio_button_circle->setChecked(0);
    ui->radio_button_point_disable->setChecked(0);
  } else if (ui->openGLWidget->square == 1) {
    ui->radio_button_square->setChecked(0);
    ui->radio_button_circle->setChecked(1);
    ui->radio_button_point_disable->setChecked(0);
  } else if (ui->openGLWidget->square == 2) {
    ui->radio_button_square->setChecked(0);
    ui->radio_button_circle->setChecked(0);
    ui->radio_button_point_disable->setChecked(1);
  }
}

void MainWindow::on_screenshot_clicked() {
  QString exePath = QCoreApplication::applicationDirPath();
  QDir dir(exePath);
  QString screenshotName = "../../../screen/screenshot";
  screenshotName +=
      QDateTime::currentDateTime().toString("dd.MM.yyyy_HH:mm:ss");
  if (ui->radio_button_bmp->isChecked()) {
    screenshotName += ".bmp";
  } else if (ui->radio_button_jpeg->isChecked()) {
    screenshotName += ".jpeg";
  }
  ui->openGLWidget->grab().save(dir.filePath(screenshotName));
}

void MainWindow::on_gif_screencast_clicked() {
  std::thread cast_gif(&MyGLWidget::gifScreencast, ui->openGLWidget);
  cast_gif.detach();
}

void MainWindow::on_radio_button_bmp_clicked() {
  if (ui->radio_button_bmp->isChecked()) ui->radio_button_jpeg->setChecked(0);
}

void MainWindow::on_radio_button_jpeg_clicked() {
  if (ui->radio_button_jpeg->isChecked()) ui->radio_button_bmp->setChecked(0);
}
