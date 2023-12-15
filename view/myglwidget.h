#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl.h>

#include <QApplication>
#include <QColorDialog>
#include <QDebug>
#include <QDockWidget>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QWidget>
#include <QtOpenGL>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../controller/controller.h"
#include "../viewer_data.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit MyGLWidget(QWidget *parent = nullptr);
  ~MyGLWidget();

  int size_v, size_f;
  bool is_clicking, radio;
  int stipple, square;
  float size_line, size_point;

  void Parcer(QString fileName);
  void Move();
  void Rotate();
  void Projection(bool checked);
  void Scale();
  void CenterFigure();
  void Reduction();
  void LineType(int check_line);
  void ProjectionParallel();
  void ProjectionCenter();
  void LineWidth(double size);
  void PointType(int check_point);
  void PointSize(double size);
  void ColorLine(QColor color);
  void ColorPoint(QColor color);
  void ColorBackground(QColor color);
  void SaveSetting();
  void LoadSetting();
  void GifScreencast();

  s21::Coordinates GetCoordinates() { return dataCoordinates; }
  void SetCoordinates();

  /* сеттеры mainwindow */
  void SetScale(float num);
  void SetRotateOx(float num);
  void SetRotateOy(float num);
  void SetRotateOz(float num);
  void SetMove(float numX, float numY, float numZ);
  void SetController(s21::Controller &contr);

 private slots:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void paintFigure();
  void style();

 protected:
  s21::Coordinates dataCoordinates{};
  s21::Autosave save{};

 private:
  float xRot, yRot, zRot;  // насколько повернуть модель
  GLfloat red_line, green_line, blue_line;  // параметры цвета модели линий
  GLfloat red_point, green_point, blue_point;  // параметры цвета модели точек
  GLfloat red_backg, green_backg, blue_backg;  // параметры цвета бэкграунда
  QPoint mPos, mDelta;  // параметры движения мышки
  int glwidth, glheight;
  uint8_t image[640 * 2 * 480 * 2 * 4];
  s21::Controller *controller_;
};

#endif  // MYGLWIDGET_H
