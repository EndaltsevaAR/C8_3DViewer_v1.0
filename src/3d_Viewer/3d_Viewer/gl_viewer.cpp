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


