#ifndef GL_VIEWER_H
#define GL_VIEWER_H

#include <QDebug>
#include <QFileInfo>
#include <QOpenGLWidget>
#include <QtWidgets/QWidget>
#include <QWidget>
#include <QOpenGLFunctions>

extern "C" {
#include "../../s21_viewer.h"
}

namespace Ui {
class gl_viewer;
}

class gl_viewer : public QOpenGLWidget {
  Q_OBJECT

 public:
  gl_viewer(QWidget *parent = nullptr);

  QColor background_color;


 private:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  Ui::gl_viewer *ui;
  obj_data total_data;
};


#endif // GL_VIEWER_H
