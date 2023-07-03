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
  QString filename;
  QColor background_color;
  obj_data total_data;


 private:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  Ui::gl_viewer *ui;

};


#endif // GL_VIEWER_H
