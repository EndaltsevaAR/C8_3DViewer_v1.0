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

enum vertex_type {
    CIRLCE,
    SQUARE,
    NOTHING
};

enum error_type {
    IS_OK,
    FILE_ERROR,
    PARSER_ERROR
};

class gl_viewer : public QOpenGLWidget {
  Q_OBJECT

 public:
  gl_viewer(QWidget *parent = nullptr);

  QString filename;
  obj_data total_data;

  double vertex_depth;
  double edge_depth;

  bool is_projection_ortho;
  bool is_edge_solid;
  enum vertex_type vert_type;
  bool destroy_status = false;
  bool is_file_loaded = false;

  QColor background_color;
  QColor vertex_color;
  QColor edge_color;

  void destroy_viewer();

 private:
  void paintGL();
  void paint_object();
  void paint_vertex();

  Ui::gl_viewer *ui;
};


#endif // GL_VIEWER_H
