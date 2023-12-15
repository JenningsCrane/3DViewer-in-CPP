#include "myglwidget.h"

#include <chrono>
#include <cstdint>
#include <thread>

#include "../gif_library/gif.hpp"

void glClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

void glCheckError(const char* callStr, int line) {
  uint32_t error;
  while ((error = glGetError()) != GL_NO_ERROR) {
    qDebug() << "[OpenGL Error] (" << error << "): \"" << callStr << "\" at "
             << line;
  }
}

#define GlCall(call) \
  glClearError();    \
  call;              \
  glCheckError(#call, __LINE__)

MyGLWidget::MyGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  SetCoordinates();
  radio = 1;
  stipple = 0, square = 0;
  size_line = 1.0, size_point = 0.0;
  red_line = 1, green_line = 1, blue_line = 1;
  red_point = 1, green_point = 1, blue_point = 1;
  red_backg = 0, green_backg = 0, blue_backg = 0;

  xRot = 0;
  yRot = 0;
  zRot = 0;
  setMouseTracking(true);
}

MyGLWidget::~MyGLWidget() {
  if (!controller_->get_polygons().empty())
    controller_->get_polygons().resize(0);
  if (!controller_->get_vertexes().empty())
    controller_->get_vertexes().resize(0);
}

void MyGLWidget::SetController(s21::Controller& contr) { controller_ = &contr; }

void MyGLWidget::SetCoordinates() {
  dataCoordinates.min_x = -1.0;
  dataCoordinates.max_x = 1.0;

  dataCoordinates.min_y = -1.0;
  dataCoordinates.max_y = 1.0;

  dataCoordinates.min_z = -1.0;
  dataCoordinates.max_z = 1.0;
}

void MyGLWidget::initializeGL() { initializeOpenGLFunctions(); }

void MyGLWidget::resizeGL(int w, int h) {
  glwidth = w;
  glheight = h;
  GlCall(glViewport(0, 0, w, h));
}

void MyGLWidget::paintGL() {
  GlCall(glClear(GL_COLOR_BUFFER_BIT));
  GlCall(glClearColor(red_backg, green_backg, blue_backg, 0));
  GlCall(glMatrixMode(GL_PROJECTION));
  GlCall(glLoadIdentity());
  if (radio)
    ProjectionCenter();
  else
    ProjectionParallel();
  GlCall(glMatrixMode(GL_MODELVIEW));
  GlCall(glLoadIdentity());
  GlCall(glRotatef(xRot, 1.0, 0.0, 0.0));
  GlCall(glRotatef(yRot, 0.0, 1.0, 0.0));
  GlCall(glRotatef(zRot, 0.0, 0.0, 1.0));
  paintFigure();
  GlCall(glReadPixels(320, 320, 640, 480, GL_RGBA, GL_UNSIGNED_BYTE, image));
}

void MyGLWidget::GifScreencast() {
  QString exePath = QCoreApplication::applicationDirPath();
  QDir dir(exePath);
  auto fileName = "gif_image.gif";
  int delay = 100;
  GifWriter g;
  GifBegin(&g, dir.filePath(fileName).toStdString().c_str(), 640, 480, delay);
  for (int timer = 0; timer <= 5000; timer += delay) {
    GifWriteFrame(&g, image, 640, 480, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
  GifEnd(&g);
}

void MyGLWidget::paintFigure() {
  if (!controller_->get_polygons().empty() &&
      !controller_->get_vertexes().empty()) {
    style();
    GlCall(glEnableClientState(GL_VERTEX_ARRAY));
    GlCall(glVertexPointer(3, GL_FLOAT, 0, controller_->get_vertexes().data()));
    GlCall(glColor3f(red_line, green_line, blue_line));
    if (stipple != 2) {
      GlCall(glDrawElements(GL_LINES, controller_->get_polygons().size(),
                            GL_UNSIGNED_INT,
                            controller_->get_polygons().data()));
    }

    GlCall(glColor3f(red_point, green_point, blue_point));
    if (square != 2) {
      GlCall(glDrawArrays(GL_POINTS, 0, controller_->GetQuantityVertexes()));
    }
    GlCall(glDisableClientState(GL_VERTEX_ARRAY));
  }
}

void MyGLWidget::Parcer(QString fileName) {
  try {
    controller_->OpenFile(fileName.toStdString());
  } catch (const std::exception& e) {
    QMessageBox::critical(this, "ОШИБКА", e.what());
  }
}

void MyGLWidget::mousePressEvent(QMouseEvent*) { is_clicking = true; }

void MyGLWidget::mouseReleaseEvent(QMouseEvent*) { is_clicking = false; }

void MyGLWidget::mouseMoveEvent(QMouseEvent* mo) {
  mDelta = mo->pos() - mPos;
  mPos = mo->pos();
  if (is_clicking) {
    xRot += 1 / M_PI * mDelta.y();
    yRot += 1 / M_PI * mDelta.x();
  }
  update();
  mDelta = QPoint();
}

/*--- Аффинные преобразования ---*/

/* Перемещение */
void MyGLWidget::Move() {
  if (!controller_->get_polygons().empty() &&
      !controller_->get_vertexes().empty()) {
    dataCoordinates.state = s21::Affine::kTranslate;
    controller_->OtherMethods(dataCoordinates);
  }
  update();
}

/* вращение */

void MyGLWidget::Rotate() {
  if (!controller_->get_polygons().empty() &&
      !controller_->get_vertexes().empty()) {
    controller_->AffineRotate(dataCoordinates);
  }
  update();
}

/* Скейл */
void MyGLWidget::Scale() {
  if (!controller_->get_polygons().empty() &&
      !controller_->get_vertexes().empty()) {
    dataCoordinates.state = s21::Affine::kScale;
    controller_->OtherMethods(dataCoordinates);
  }
  update();
}

/* Центрирование фигуры*/
void MyGLWidget::CenterFigure() {
  if (!controller_->get_polygons().empty() &&
      !controller_->get_vertexes().empty()) {
    dataCoordinates.state = s21::Affine::kCenter;
    controller_->OtherMethods(dataCoordinates);
    Reduction();
  }
  update();
}

/* Уменьшение фигуры */
void MyGLWidget::Reduction() {
  if (!controller_->get_polygons().empty() &&
      !controller_->get_vertexes().empty()) {
    dataCoordinates.state = s21::Affine::kObjectReduct;
    controller_->OtherMethods(dataCoordinates);
  }
}

/*--- Проекция ---*/

/* Центральная проекция */
void MyGLWidget::ProjectionCenter() {
  if (!controller_->get_polygons().empty() &&
      !controller_->get_vertexes().empty()) {
    float fov = 30.0 * M_PI / 180;
    float heapHeight = dataCoordinates.max_y / (2 * tan(fov / 2));

    float ratio = glwidth / glheight;

    GlCall(glFrustum(dataCoordinates.min_x * ratio,
                     dataCoordinates.max_x * ratio, dataCoordinates.min_y,
                     dataCoordinates.max_y, heapHeight,
                     dataCoordinates.max_z * 100));
    GlCall(glTranslatef(0, 0, -heapHeight * 3));
  }
  update();
}

/* Параллельная проекция */
void MyGLWidget::ProjectionParallel() {
  if (!controller_->get_polygons().empty() &&
      !controller_->get_vertexes().empty()) {
    float ratio = glwidth / glheight;

    GlCall(glOrtho(dataCoordinates.min_x * 1.5f * ratio,
                   dataCoordinates.max_x * 1.5f * ratio,
                   dataCoordinates.min_y * 1.5f, dataCoordinates.max_y * 1.5f,
                   dataCoordinates.min_z * 3.5f, dataCoordinates.max_z * 3.5f));
    GlCall(glTranslatef(0, 0, -0.5));
  }
  update();
}

/* Значения кнопок */
void MyGLWidget::Projection(bool checked) { radio = checked; }

void MyGLWidget::LineType(int check_line) { stipple = check_line; }

void MyGLWidget::LineWidth(double size) { size_line = size; }

void MyGLWidget::PointType(int check_point) { square = check_point; }

void MyGLWidget::PointSize(double size) { size_point = size; }

void MyGLWidget::ColorLine(QColor color) {
  red_line = color.redF();
  green_line = color.greenF();
  blue_line = color.blueF();
  update();
}

void MyGLWidget::ColorPoint(QColor color) {
  red_point = color.redF();
  green_point = color.greenF();
  blue_point = color.blueF();
  update();
}

void MyGLWidget::ColorBackground(QColor color) {
  red_backg = color.redF();
  green_backg = color.greenF();
  blue_backg = color.blueF();
  update();
}

/*--- Cтили ---*/
void MyGLWidget::style() {
  if (stipple == 1) {
    GlCall(glEnable(GL_LINE_STIPPLE));
    GlCall(glLineStipple(1, 10));
  } else if (!stipple) {
    GlCall(glDisable(GL_LINE_STIPPLE));
  }

  if (square == 1) {
    GlCall(glEnable(GL_POINT_SMOOTH));
  } else if (!square) {
    GlCall(glDisable(GL_POINT_SMOOTH));
  }

  GlCall(glLineWidth(size_line));
  GlCall(glPointSize(size_point));
}

void MyGLWidget::SaveSetting() {
  save.red_backg = red_backg;
  save.green_backg = green_backg;
  save.blue_backg = blue_backg;
  save.red_line = red_line;
  save.green_line = green_line;
  save.blue_line = blue_line;
  save.red_point = red_point;
  save.green_point = green_point;
  save.blue_point = blue_point;
  save.radio = radio;
  save.size_line = size_line;
  save.size_point = size_point;
  save.square = square;
  save.stipple = stipple;
  controller_->AutosaveWriting(save);
}

void MyGLWidget::LoadSetting() {
  controller_->AutoSaveReading(save);
  red_backg = save.red_backg;
  green_backg = save.green_backg;
  blue_backg = save.blue_backg;
  red_line = save.red_line;
  green_line = save.green_line;
  blue_line = save.blue_line;
  red_point = save.red_point;
  green_point = save.green_point;
  blue_point = save.blue_point;
  radio = save.radio;
  size_line = save.size_line;
  size_point = save.size_point;
  square = save.square;
  stipple = save.stipple;
}

/* сеттеры mainwindow */

void MyGLWidget::SetScale(float num) { dataCoordinates.scale_value = num; }

void MyGLWidget::SetRotateOx(float num) {
  dataCoordinates.rotate_value_x = num;
  dataCoordinates.state = s21::Affine::kRotateX;
}

void MyGLWidget::SetRotateOy(float num) {
  dataCoordinates.rotate_value_y = num;
  dataCoordinates.state = s21::Affine::kRotateY;
}

void MyGLWidget::SetRotateOz(float num) {
  dataCoordinates.rotate_value_z = num;
  dataCoordinates.state = s21::Affine::kRotateZ;
}

void MyGLWidget::SetMove(float numX, float numY, float numZ) {
  dataCoordinates.move_value_x = numX;
  dataCoordinates.move_value_y = numY;
  dataCoordinates.move_value_z = numZ;
}
