#include "gl_viewer.h"
int start(const char *file_name, obj_data *total_data);

gl_viewer::gl_viewer(QWidget *parent) : QOpenGLWidget(parent) {
}

void gl_viewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    char file_name[] = "../../test_files_obj/cube.obj";  // строка для дебага
    start(file_name, &total_data);
    glBegin(GL_QUADS);
    glColor3d(1, 0, 0);
        for (unsigned int i = 0; i < total_data.number_polygons; i++)
        {
            polygon currentPolygon = total_data.polygons[i];
            for (unsigned int j = 0; j < currentPolygon.number_vertexes; j++)
            {
                unsigned int vertexIndex = currentPolygon.vertexes[j];
                double *vertex = total_data.coordMatrix.coordinates[vertexIndex];
                glVertex3d(vertex[0], vertex[1], vertex[2]);
            }
        }
        glEnd();

}

void gl_viewer::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
}

void gl_viewer::initializeGL() {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
