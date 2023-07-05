#include "gl_viewer.h"
int start(const char *file_name, obj_data *total_data);
void free_results(obj_data *total_data);

gl_viewer::gl_viewer(QWidget *parent) : QOpenGLWidget(parent) {
}

void gl_viewer::paintGL() {
    glClearColor(background_color.redF(), background_color.greenF(),
                 background_color.blueF(), background_color.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (is_file_loaded) {
        if (vert_type != NOTHING) {
            paint_vertex();
        }
        paint_object();
    }
}

void gl_viewer::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
}

void gl_viewer::destroy_viewer() {
   if(destroy_status) {
       free_results(&total_data);
   }
   destroy_status = false;
}

void gl_viewer::paint_object() {
  glLineWidth(edge_depth);

  if (!is_edge_solid) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1010);
  }
  for (unsigned int i = 0; i < total_data.number_polygons; i++) {
      polygon currentPolygon = total_data.polygons[i];
      for (unsigned int j = 0; j < currentPolygon.number_vertexes; j++) {
        glBegin(GL_LINE_LOOP);
        glColor3d(edge_color.redF(), edge_color.greenF(), edge_color.blueF());
        unsigned int vertexIndex = currentPolygon.vertexes[j];
        double *vertex = total_data.coordMatrix.coordinates[vertexIndex];
        glVertex3d(vertex[0], vertex[1], vertex[2]);
    }
    glEnd();
  }
  if (!is_edge_solid) glDisable(GL_LINE_STIPPLE);
}

void gl_viewer::paint_vertex() {
  if (vert_type == CIRLCE) glEnable(GL_POINT_SMOOTH);
  glPointSize(vertex_depth);

  for (unsigned int i = 0; i < total_data.number_polygons; i++) {
      polygon currentPolygon = total_data.polygons[i];
      for (unsigned int j = 0; j < currentPolygon.number_vertexes; j++) {
        glBegin(GL_POINTS);
        glColor3d(vertex_color.redF(), vertex_color.greenF(), vertex_color.blueF());
        unsigned int vertexIndex = currentPolygon.vertexes[j];
        double *vertex = total_data.coordMatrix.coordinates[vertexIndex];
        glVertex3d(vertex[0], vertex[1], vertex[2]);
      }
      glEnd();
  }
  if (vert_type == CIRLCE) glDisable(GL_POINT_SMOOTH);
}


