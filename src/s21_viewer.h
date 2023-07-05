#ifndef S21_3D_VIEWER_H
#define S21_3D_VIEWER_H

#define MAX_LENGTH 255
#define MAX_POLYGON_LENGHT 125
#define OK 1
#define FAIL 0
#define AFFIN_FAIL 2
#define NUMBER_COLS 4
#define NUMBER_COORD_XYZ 3
#define INIT_PART_SCREEN 0.4

// for tests
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
    unsigned int rows;  // так как в f вершины начинаются с 1, то row будет
    // number_vertex + 1 и нулевая строчка будет пустая
    unsigned int cols;  // always 3: x, y and z
    double scale_coefficient;
} coord_matrix;

typedef struct Poligon {
    unsigned int *vertexes;  // массив номеров вершин в одном полигоне, которые
    // будут соединяться в одну фигуру
    unsigned int number_vertexes;  //количество вершин в фигуре
} polygon;

typedef struct Obj_data {
    unsigned int number_vertex;    // количество вершин
    unsigned int number_polygons;  // количество полигонов
    coord_matrix coordMatrix;
    polygon *polygons;  // количество полигонов - number_vertexes+1
} obj_data;

// общий алгоритм
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

// вспомогательные функции
void print_data(obj_data data);

int get_int(const char *token, unsigned int *number_str);

int is_string_number(char *token);

double min_two_doubles(double old_d, double new_d);

double max_two_doubles(double old_d, double new_d);

int check_polygons(obj_data *total_data);

// функции очистки памяти

void free_coord_matrix(coord_matrix *coordMatrix);
void free_polygons(obj_data *total_data, unsigned int crash_number);
void free_results(obj_data *total_data);

// афинные преобразования
// перемещения
int move_coordinate(coord_matrix *coordMatrix, double diffX, double diffY, double diffZ);

// scale
int scale_coordinate(coord_matrix *coordMatrix, double diff);

// rotate
int rotate_X(coord_matrix *coordMatrix, double angleX);
int rotate_Y(coord_matrix *coordMatrix, double angleY);
int rotate_Z(coord_matrix *coordMatrix, double angleZ);

// работа с матрицами
// вспомогательные матрицы
int init_move_matrix(coord_matrix *affin_matrix, double diffX, double diffY,
                     double diffZ);  // перемещения
int init_scale_matrix(coord_matrix *affin_matrix, double diffX, double diffY,
                      double diffZ);  // масштабирования
int init_rotateX_matrix(coord_matrix *affin_matrix,
                        double diffX);  // поворот по х
int init_rotateY_matrix(coord_matrix *affin_matrix,
                        double diffY);  // поворот по y
int init_rotateZ_matrix(coord_matrix *affin_matrix,
                        double diffZ);  // поворот по Z

int init_vector_matrix(coord_matrix *vector_matrix, coord_matrix *init_matrix,
                       unsigned int vector_i);

int s21_mult_matrix(coord_matrix *A, coord_matrix *B,
                    coord_matrix *result);  // Умножение двух матриц


// оцентровка и изменение к масштабу [0;1]
void calculate_extrems(coord_matrix coordMatrix, double *extrems);
int preparation_to_init_draw(obj_data *total_data); // оцентровка и изменение масштаба к 0-1
int move_to_center(obj_data *total_data, const double *extrems);
int scale_0_1(obj_data *total_data, double *extrems);    // изменение масштаба в диапапзон [0;1]
double calculate_scale_coefficient(const double *extrems);
double max_delta_coordinates(const double *deltas);

int get_edges_number(polygon *polygons, unsigned int number_polygons);
int has_edge(const int *edges, int vertex_start, int vertex_end, int size);

#endif  // S21_3D_VIEWER_H