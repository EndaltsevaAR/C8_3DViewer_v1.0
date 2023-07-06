#ifndef S21_3D_VIEWER_H
#define S21_3D_VIEWER_H

#define MAX_LENGTH 255
#define MAX_POLYGON_LENGHT 125
#define OK 1
#define FAIL 0
#define NUMBER_COLS 4
#define NUMBER_COORD_XYZ 3
#define INIT_PART_SCREEN 0.4

// for tests
#define AFFIN_FAIL 2
#define s21_EPS 1e-7
#define s21_PI_2 1.57079632679489661923
#define s21_PI_4 0.78539816339744830962

// for qt
#define WIDTH 1000
#define HEIGHT 900
#define DEPTH 1

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Coord_matrix {
  double **coordinates;
  unsigned int rows;
  unsigned int cols;
  double scale_coefficient;
} coord_matrix;

typedef struct Poligon {
  unsigned int *vertexes;
  unsigned int number_vertexes;
} polygon;

typedef struct Obj_data {
  unsigned int number_vertex;
  unsigned int number_polygons;
  coord_matrix coordMatrix;
  polygon *polygons;
} obj_data;

int parsing_process_for_tests(const char *file_name);

int start(const char *file_name, obj_data *total_data);

int parse_file(const char *file_name, obj_data *total_data);

int find_info_for_init(unsigned int *number_vertexes,
                       unsigned int *number_poligons, const char *file_name);

int init_coord_matrix(coord_matrix *coordMatrix, unsigned int number_vertexes,
                      unsigned int number_for_cols);

int fill_matrixes(obj_data *total_data, const char *file_name);

int parseVertexes(char *line, coord_matrix *coordMatrix, unsigned int vertex_i);

int parsePolygon(char *line, polygon *polygons, unsigned int polygon_i);

// support function
void print_data(obj_data data);

int get_int(const char *token, unsigned int *number_str);

int is_string_number(char *token);

double min_two_doubles(double old_d, double new_d);

double max_two_doubles(double old_d, double new_d);

int check_polygons(obj_data *total_data);

// free functions

void free_coord_matrix(coord_matrix *coordMatrix);

void free_polygons(obj_data *total_data, unsigned int crash_number);

void free_results(obj_data *total_data);

// affine functions
int move_coordinate(coord_matrix *coordMatrix, double diffX, double diffY,
                    double diffZ);

int scale_coordinate(coord_matrix *coordMatrix, double diff);

int rotate_X(coord_matrix *coordMatrix, double angleX);

int rotate_Y(coord_matrix *coordMatrix, double angleY);

int rotate_Z(coord_matrix *coordMatrix, double angleZ);

// support for affine funstions
int init_move_matrix(coord_matrix *affin_matrix, double diffX, double diffY,
                     double diffZ);

int init_scale_matrix(coord_matrix *affin_matrix, double diffX, double diffY,
                      double diffZ);

int init_rotateX_matrix(coord_matrix *affin_matrix, double diffX);

int init_rotateY_matrix(coord_matrix *affin_matrix, double diffY);

int init_rotateZ_matrix(coord_matrix *affin_matrix, double diffZ);

int init_vector_matrix(coord_matrix *vector_matrix, coord_matrix *init_matrix,
                       unsigned int vector_i);

int s21_mult_matrix(coord_matrix *A, coord_matrix *B, coord_matrix *result);

// fuction for initialization to paint
void calculate_extrems(coord_matrix coordMatrix, double *extrems);

int preparation_to_init_draw(obj_data *total_data);

int move_to_center(obj_data *total_data, const double *extrems);

int scale_0_1(obj_data *total_data, double *extrems);

double calculate_scale_coefficient(const double *extrems);

double max_delta_coordinates(const double *deltas);

// functions for counting number of edges
int get_edges_number(polygon *polygons, unsigned int number_polygons);

int has_edge(const int *edges, int vertex_start, int vertex_end, int size);

#endif  // S21_3D_VIEWER_H