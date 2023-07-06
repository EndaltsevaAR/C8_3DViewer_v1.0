#include "s21_viewer.h"

#include <stdlib.h>

/*
int main() {
    char file_name[] = "simple_test_1_spaces.txt";
    int status = parsing_process_for_tests(file_name);
    return 0;
}
*/

int parsing_process_for_tests(const char *file_name) {
  int is_ok = OK;
  obj_data total_data = {0};
  is_ok = start(file_name, &total_data);
  if (is_ok) {
    free_results(&total_data);
  }
  return is_ok;
}

int start(const char *file_name, obj_data *total_data) {
  int is_ok = OK;
  is_ok = parse_file(file_name, total_data);
  if (is_ok) {
    is_ok = check_polygons(total_data);
    if (!is_ok) {
      free_results(total_data);
    }
  }
  if (is_ok) {
    is_ok = preparation_to_init_draw(total_data);
  }
  return is_ok;
}

/*
This function processes the incoming file and populates the structures with the
necessary information. There is two readings of file: 1) to count number of
vertexes and polygons, 2) to fill them
*/
int parse_file(const char *file_name, obj_data *total_data) {
  unsigned int number_vertexes = 0, number_polygons = 0;
  int is_ok = OK;
  is_ok = find_info_for_init(&number_vertexes, &number_polygons, file_name);
  if (is_ok) {
    coord_matrix coordMatrix = {0};
    is_ok = init_coord_matrix(&coordMatrix, number_vertexes, NUMBER_COLS);
    if (is_ok) {
      total_data->number_vertex = number_vertexes;
      total_data->number_polygons = number_polygons;
      total_data->coordMatrix = coordMatrix;
      total_data->polygons =
          (polygon *)calloc(total_data->number_polygons, sizeof(polygon));

      if (total_data->polygons == NULL) {
        printf("Error with calloc for polygons at parse_file funct\n");
        free_coord_matrix(&total_data->coordMatrix);
        is_ok = FAIL;
      } else {
        is_ok = fill_matrixes(total_data, file_name);
        if (!is_ok) {
          free(total_data->polygons);
          free_coord_matrix(&total_data->coordMatrix);
        }
      }
    }
  }
  return is_ok;
}

// There is function for first reading of file to find common data
int find_info_for_init(unsigned int *number_vertexes,
                       unsigned int *number_polygons, const char *file_name) {
  int is_ok = OK;
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Program can not open file.\n");
    is_ok = FAIL;
  }

  if (is_ok) {
    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
      line[strcspn(line, "\n")] = '\0';
      line[strcspn(line, "\t")] = '\0';
      line[strcspn(line, "\r")] = '\0';
      if (line[0] == 'v' && line[1] == ' ') {
        *number_vertexes += 1;
      } else if (line[0] == 'f' && line[1] == ' ') {
        *number_polygons += 1;
      }
    }
    fclose(file);
  }
  if (is_ok && (*number_vertexes < 1 || *number_polygons < 1)) {
    printf("There is vertexes and/or polygons, it is nothing to draw!\n");
    is_ok = FAIL;
  }
  return is_ok;
}

/*
There is function for initialization matrix of coordinate. There is memory
allocation for matrix. CoordMatrix have empty 0 row, because at the polygons
count starts from 1
*/
int init_coord_matrix(coord_matrix *coordMatrix, unsigned int number_vertexes,
                      unsigned int number_for_cols) {
  int is_ok = OK;
  coordMatrix->scale_coefficient = 1.0;
  coordMatrix->rows = number_vertexes + 1;
  coordMatrix->cols = number_for_cols;
  coordMatrix->coordinates =
      (double **)calloc(coordMatrix->rows, sizeof(double *));
  if (coordMatrix->coordinates == NULL) {
    printf("Error with main calloc at init_coord_matrix function\n");
    is_ok = FAIL;
  } else {
    for (unsigned int i = 0; i < coordMatrix->rows && is_ok; ++i) {
      coordMatrix->coordinates[i] =
          (double *)calloc(coordMatrix->cols, sizeof(double));
      if (coordMatrix->coordinates[i] == NULL) {
        printf("Error with calloc at init_coord_matrix function\n");
        is_ok = FAIL;
        for (unsigned int j = 0; j < i; ++j) {
          free(coordMatrix->coordinates[j]);
          coordMatrix->coordinates[j] = NULL;
        }
        free(coordMatrix->coordinates);
        coordMatrix->coordinates = NULL;
      }
    }
  }
  return is_ok;
}

// There is functon for second reading of file to fill info about figure
int fill_matrixes(obj_data *total_data, const char *file_name) {
  int is_ok = OK;
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Program can not open file second time.\n");
    is_ok = FAIL;
  }
  if (is_ok) {
    fseek(file, 0, SEEK_SET);
    char line[MAX_LENGTH] = {0};
    unsigned int vertex_i = 1;
    unsigned int polygon_i = 0;
    while (fgets(line, sizeof(line), file) && is_ok) {
      line[strcspn(line, "\n")] = '\0';
      line[strcspn(line, "\t")] = '\0';
      line[strcspn(line, "\r")] = '\0';
      if (line[0] == 'v' && line[1] == ' ') {
        is_ok = parseVertexes(line, &total_data->coordMatrix, vertex_i);
        ++vertex_i;
      } else if (line[0] == 'f' && line[1] == ' ') {
        is_ok = parsePolygon(line, &total_data->polygons[polygon_i], polygon_i);
        if (!is_ok) {
          free_polygons(total_data, polygon_i);
        }
        polygon_i += 1;
      }
    }
    fclose(file);
  }
  return is_ok;
}

// There is function to parse lines about vertexes, first token is v letter
int parseVertexes(char *line, coord_matrix *coordMatrix,
                  unsigned int vertex_i) {
  int is_ok = OK;
  char *token = strtok(line, " ");

  int i = -1;
  double coordinates[NUMBER_COLS + 1] = {0};
  while (token != NULL && is_ok) {
    if (i == -1 && strcmp(token, "v") == 0) {
      ++i;
    } else {
      if (i > NUMBER_COORD_XYZ) {
        printf("File is broken, too much coordinates for vertex\n");
        is_ok = FAIL;
      } else {
        if (!is_string_number(token)) {
          is_ok = FAIL;
        } else if (i >= 0) {
          coordinates[i] = atof(token);
          ++i;
        }
      }
    }
    token = strtok(NULL, " ");
  }

  if (i < NUMBER_COORD_XYZ && is_ok) {
    printf("There is less than 3 coordinates!\n");
    is_ok = FAIL;
  }

  if (is_ok) {
    coordMatrix->coordinates[vertex_i][0] = coordinates[0];
    coordMatrix->coordinates[vertex_i][1] = coordinates[1];
    coordMatrix->coordinates[vertex_i][2] = coordinates[2];
    if (coordinates[3] > 0) {
      coordMatrix->coordinates[vertex_i][3] = coordinates[3];
    } else {
      coordMatrix->coordinates[vertex_i][3] = 1;
    }
  }
  return is_ok;
}

// There is function to parse lines about polygons, first token is f letter
int parsePolygon(char *line, polygon *polygons, unsigned int polygon_i) {
  int is_ok = OK;
  char *token = strtok(line, " ");
  unsigned int vert_i = -1;

  unsigned int max_vertexes = MAX_POLYGON_LENGHT;
  unsigned int *vertexes =
      (unsigned int *)malloc(max_vertexes * sizeof(unsigned int));

  if (vertexes == NULL) {
    printf("Failed to allocate memory for polygon %u.\n", polygon_i);
    is_ok = FAIL;
  }
  while (token != NULL && is_ok) {
    if (strcmp(token, "f") == 0) {
      ++vert_i;
    } else {
      unsigned int number_str = 0;
      is_ok = get_int(token, &number_str);
      if (is_ok) {
        vertexes[vert_i++] = number_str;
      }
    }
    token = strtok(NULL, " ");
  }

  if (vert_i < NUMBER_COORD_XYZ) {
    printf("File is broken, less than 2 pointers to polygon\n");
    is_ok = FAIL;
  }

  if (vert_i < MAX_POLYGON_LENGHT && is_ok) {
    unsigned int *new_vertexes =
        (unsigned int *)realloc(vertexes, vert_i * sizeof(unsigned int));
    if (new_vertexes == NULL) {
      printf("Failed to reallocate memory for polygon %u.\n", polygon_i);
      is_ok = FAIL;
    } else {
      vertexes = new_vertexes;
    }
  }
  if (!is_ok) {
    free(vertexes);
  } else {
    polygons->vertexes = vertexes;
    polygons->number_vertexes = vert_i;
  }
  return is_ok;
}

// There is support function to print data
void print_data(obj_data data) {
  printf("%d is number vertexes\n", data.number_vertex);
  printf("%d is number polygons\n", data.number_polygons);
  printf("Printing matrix coordinates of vertexes...\n");
  for (unsigned int i = 1; i <= data.number_vertex; ++i) {
    printf("x is %lf, y is %lf, z is %lf\n", data.coordMatrix.coordinates[i][0],
           data.coordMatrix.coordinates[i][1],
           data.coordMatrix.coordinates[i][2]);
  }
  printf("Printing polygon's scheme...\n");
  for (unsigned int i = 0; i < data.number_polygons; ++i) {
    for (unsigned int j = 0; j < data.polygons->number_vertexes; ++j) {
      printf("%d ", data.polygons[i].vertexes[j]);
    }
    printf("\n");
  }
  printf("\n");
}

// There is support function to transform string token to int value
int get_int(const char *token, unsigned int *number_str) {
  int is_ok = OK;
  int step = 0;

  while (token[step] != '\0' && token[step] != '/' && is_ok) {
    if (!isdigit(token[step])) {
      printf("Not correct view of coordinate\n");
      is_ok = FAIL;
    } else {
      ++step;
    }
  }
  if (is_ok) {
    if (step > 0) {
      char *numberStr = (char *)calloc(step + 1, sizeof(char));
      if (numberStr == NULL) {
        printf("Error with malloc at get_int function\n");
        is_ok = FAIL;
      } else {
        strncpy(numberStr, token, step);
        numberStr[step] = '\0';
        *number_str = atoi(numberStr);
        free(numberStr);
      }
    } else {
      printf("There is no vertex's number at get_int function\n");
      is_ok = FAIL;
    }
  }
  if (is_ok && *number_str == 0) {
    printf("Vertexes parse_file counted from 1, not from 0\n");
    is_ok = FAIL;
  }
  return is_ok;
}

// This function check that token is double number. First letter can be minus,
// token can consist only one dot, and can not contain any of letter
int is_string_number(char *token) {
  int is_number = OK;
  int have_dot = 0;
  char *p = token;

  if (strlen(token) > 1 && *p == '-') {
    ++p;
  }

  while (*p != '\0' && is_number) {
    if (!(isdigit(*p) || (*p == '.' && !have_dot))) {
      is_number = FAIL;
    }

    if (*p == '.' && !have_dot) {
      have_dot = 1;
    }
    ++p;
  }
  return is_number;
}

double min_two_doubles(double old_d, double new_d) {
  if (new_d < old_d) {
    old_d = new_d;
  }
  return old_d;
}

double max_two_doubles(double old_d, double new_d) {
  if (new_d > old_d) {
    old_d = new_d;
  }
  return old_d;
}

// This function checks that there is no index greater than the number of
// vertexes.
int check_polygons(obj_data *total_data) {
  int is_ok = OK;
  for (unsigned int i = 0; i < total_data->number_polygons && is_ok; ++i) {
    for (unsigned int j = 0;
         j < total_data->polygons[i].number_vertexes && is_ok; ++j) {
      if (total_data->polygons[i].vertexes[j] == 0 ||
          total_data->polygons[i].vertexes[j] > total_data->number_vertex) {
        printf("Wrong number of vertex at the check_polygons function.\n");
        is_ok = FAIL;
      }
    }
  }
  return is_ok;
}

// There is support function to free matrix with information about coordinates
// of all vertexes
void free_coord_matrix(coord_matrix *coordMatrix) {
  if (coordMatrix != NULL) {
    for (unsigned int i = 0; i < coordMatrix->rows; ++i) {
      free(coordMatrix->coordinates[i]);
    }
    free(coordMatrix->coordinates);
    coordMatrix->rows = 0;
    coordMatrix->cols = 0;
  }
}

// There is support function to free matrix with information about vertex's
// indexes
void free_polygons(obj_data *total_data, unsigned int crash_number) {
  for (unsigned int i = 0; i < crash_number; ++i) {
    free(total_data->polygons[i].vertexes);
  }
}

// There is support function to free structure Obj_data
void free_results(obj_data *total_data) {
  free_coord_matrix(&total_data->coordMatrix);
  free_polygons(total_data, total_data->number_polygons);
  free(total_data->polygons);
  total_data->number_polygons = 0;
  total_data->number_vertex = 0;
}

// affine functions

// There is common algorithm of affine transformations
int affin_operation(coord_matrix *coordMatrix, double diffX, double diffY,
                    double diffZ, int type) {
  int status = OK;
  coord_matrix affin_matrix = {0};
  switch (type) {
    case 1:
      status = init_move_matrix(&affin_matrix, diffX, diffY, diffZ);
      break;
    case 2:
      status = init_scale_matrix(&affin_matrix, diffX, diffY, diffZ);
      break;
    case 3:
      status = init_rotateX_matrix(&affin_matrix, diffX);
      break;
    case 4:
      status = init_rotateY_matrix(&affin_matrix, diffY);
      break;
    default:
      status = init_rotateZ_matrix(&affin_matrix, diffZ);
  }

  if (status == OK) {
    for (unsigned int i = 1; i < coordMatrix->rows; ++i) {
      coord_matrix vector_matrix = {0};
      coord_matrix result_matrix = {0};

      status = init_vector_matrix(&vector_matrix, coordMatrix, i);

      if (status == OK) {
        status = s21_mult_matrix(&affin_matrix, &vector_matrix, &result_matrix);
      }
      if (status == OK) {
        for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
          coordMatrix->coordinates[i][j] = result_matrix.coordinates[j][0];
        }
        free_coord_matrix(&vector_matrix);
        free_coord_matrix(&result_matrix);
      }
    }
    free_coord_matrix(&affin_matrix);
  }

  return status;
}

// There is function for move transformations
int move_coordinate(coord_matrix *coordMatrix, double diffX, double diffY,
                    double diffZ) {
  diffX *= coordMatrix->scale_coefficient;
  diffY *= coordMatrix->scale_coefficient;
  diffZ *= coordMatrix->scale_coefficient;
  return affin_operation(coordMatrix, diffX, diffY, diffZ, 1);
}

// There is function for scale transformations
int scale_coordinate(coord_matrix *coordMatrix, double diff) {
  coordMatrix->scale_coefficient *= diff;
  return affin_operation(coordMatrix, diff, diff, diff, 2);
}

// There is function for rotate transformations by X at the rad
int rotate_X(coord_matrix *coordMatrix, double angleX) {
  return affin_operation(coordMatrix, angleX, 0, 0, 3);
}

// There is function for rotate transformations by Y at the rad
int rotate_Y(coord_matrix *coordMatrix, double angleY) {
  return affin_operation(coordMatrix, 0, angleY, 0, 4);
}

// There is function for rotate transformations by Z at the rad
int rotate_Z(coord_matrix *coordMatrix, double angleZ) {
  return affin_operation(coordMatrix, 0, 0, angleZ, 5);
}

// There is support function to multiply two matrix
int s21_mult_matrix(coord_matrix *A, coord_matrix *B, coord_matrix *result) {
  int status = OK;
  result->rows = A->rows;
  result->cols = B->cols;
  status = init_coord_matrix(result, A->rows - 1, B->cols);

  if (status == OK) {
    for (unsigned int y = 0; y < result->rows; ++y) {
      for (unsigned int x = 0; x < result->cols; ++x) {
        result->coordinates[y][x] = 0;
        for (unsigned int k = 0; k < A->cols; ++k) {
          result->coordinates[y][x] +=
              A->coordinates[y][k] * B->coordinates[k][x];
        }
      }
    }
  }
  return status;
}

// There is support function to initialization Translation matrix
int init_move_matrix(coord_matrix *affin_matrix, double diffX, double diffY,
                     double diffZ) {
  int is_ok = OK;
  is_ok = init_coord_matrix(affin_matrix, NUMBER_COORD_XYZ, NUMBER_COLS);
  if (is_ok) {
    for (unsigned int i = 0; i < NUMBER_COLS; ++i) {
      affin_matrix->coordinates[i][i] = 1;
    }
    affin_matrix->coordinates[0][3] = diffX;
    affin_matrix->coordinates[0][3] = diffX;
    affin_matrix->coordinates[1][3] = diffY;
    affin_matrix->coordinates[2][3] = diffZ;
  }
  return is_ok;
}

// There is support function to initialization Scaling matrix
int init_scale_matrix(coord_matrix *affin_matrix, double diffX, double diffY,
                      double diffZ) {
  int is_ok = OK;
  is_ok = init_coord_matrix(affin_matrix, NUMBER_COORD_XYZ, NUMBER_COLS);
  if (is_ok) {
    affin_matrix->coordinates[0][0] = diffX;
    affin_matrix->coordinates[1][1] = diffY;
    affin_matrix->coordinates[2][2] = diffZ;
    affin_matrix->coordinates[3][3] = 1;
  }
  return is_ok;
}

// There is support function to initialization Rotation matrix by X
int init_rotateX_matrix(coord_matrix *affin_matrix, double diffX) {
  int is_ok = OK;
  is_ok = init_coord_matrix(affin_matrix, NUMBER_COORD_XYZ, NUMBER_COLS);
  if (is_ok) {
    affin_matrix->coordinates[0][0] = 1;
    affin_matrix->coordinates[1][1] = cos(diffX);
    affin_matrix->coordinates[1][2] = -sin(diffX);
    affin_matrix->coordinates[2][1] = sin(diffX);
    affin_matrix->coordinates[2][2] = cos(diffX);
    affin_matrix->coordinates[3][3] = 1;
  }
  return is_ok;
}

// There is support function to initialization Rotation matrix by Y
int init_rotateY_matrix(coord_matrix *affin_matrix, double diffY) {
  int is_ok = OK;
  is_ok = init_coord_matrix(affin_matrix, NUMBER_COORD_XYZ, NUMBER_COLS);
  if (is_ok) {
    affin_matrix->coordinates[0][0] = cos(diffY);
    affin_matrix->coordinates[0][2] = sin(diffY);
    affin_matrix->coordinates[2][0] = -sin(diffY);
    affin_matrix->coordinates[2][2] = cos(diffY);
    affin_matrix->coordinates[1][1] = 1;
    affin_matrix->coordinates[3][3] = 1;
  }
  return is_ok;
}

// There is support function to initialization Rotation matrix by Z
int init_rotateZ_matrix(coord_matrix *affin_matrix, double diffZ) {
  int is_ok = OK;
  is_ok = init_coord_matrix(affin_matrix, NUMBER_COORD_XYZ, NUMBER_COLS);
  if (is_ok) {
    affin_matrix->coordinates[0][0] = cos(diffZ);
    affin_matrix->coordinates[0][1] = -sin(diffZ);
    affin_matrix->coordinates[1][0] = sin(diffZ);
    affin_matrix->coordinates[1][1] = cos(diffZ);
    affin_matrix->coordinates[2][2] = 1;
    affin_matrix->coordinates[3][3] = 1;
  }
  return is_ok;
}

// There is support function to initialization Vector matrix of coordinates
int init_vector_matrix(coord_matrix *vector_matrix, coord_matrix *init_matrix,
                       unsigned int vector_i) {
  int is_ok = OK;
  is_ok = init_coord_matrix(vector_matrix, NUMBER_COORD_XYZ, 1);
  for (unsigned int i = 0; i < NUMBER_COLS; ++i) {
    vector_matrix->coordinates[i][0] = init_matrix->coordinates[vector_i][i];
  }
  return is_ok;
}

// There is support function to transformation matrix to field [-1;1] by each
// coordinates
int preparation_to_init_draw(obj_data *total_data) {
  int is_ok = OK;
  double extrems[6] = {0};
  calculate_extrems(total_data->coordMatrix, extrems);
  is_ok = move_to_center(total_data, extrems);
  if (is_ok) {
    is_ok = scale_0_1(total_data, extrems);
  }
  return is_ok;
}

// There is support function to calculate matrix of extrems
void calculate_extrems(coord_matrix coordMatrix, double *extrems) {
  for (unsigned int i = 0; i < NUMBER_COORD_XYZ; ++i) {
    extrems[i * 2] = coordMatrix.coordinates[1][i];
    extrems[i * 2 + 1] = coordMatrix.coordinates[1][i];
  }
  for (unsigned int i = 2; i < coordMatrix.rows; ++i) {
    for (int j = 0; j < NUMBER_COORD_XYZ; ++j) {
      extrems[j * 2] =
          min_two_doubles(extrems[j * 2], coordMatrix.coordinates[i][j]);
      extrems[j * 2 + 1] =
          max_two_doubles(extrems[j * 2 + 1], coordMatrix.coordinates[i][j]);
    }
  }
}

/*
There is support function to move object to condition when center of coordinate
is center of figure too. It is done by formula at each direction: min + (max -
min)/2
*/
int move_to_center(obj_data *total_data, const double *extrems) {
  double shift_values[NUMBER_COORD_XYZ] = {0};
  for (unsigned int i = 0; i < NUMBER_COORD_XYZ; ++i) {
    shift_values[i] =
        extrems[i * 2] + (extrems[i * 2 + 1] - extrems[i * 2]) / 2;
  }
  return move_coordinate(&total_data->coordMatrix, -shift_values[0],
                         -shift_values[1], -shift_values[2]);
}

// There is support function to resize object to field [-1;1] by each
// coordinates
int scale_0_1(obj_data *total_data, double *extrems) {
  return scale_coordinate(&total_data->coordMatrix,
                          calculate_scale_coefficient(extrems));
}

// There is support function to calculate coefficient to resize object
double calculate_scale_coefficient(const double *extrems) {
  double deltas[NUMBER_COORD_XYZ] = {0};
  for (unsigned int i = 0; i < NUMBER_COORD_XYZ; ++i) {
    deltas[i] = extrems[2 * i + 1] - extrems[2 * i];
  }
  double max_delta = max_delta_coordinates(deltas);
  return 2 * INIT_PART_SCREEN / max_delta;
}

// There is support function to calculate max differents of coordinate direction
double max_delta_coordinates(const double *deltas) {
  double max = deltas[0];
  for (unsigned int i = 1; i < NUMBER_COORD_XYZ; ++i) {
    if (deltas[i] > max) {
      max = deltas[i];
    }
  }
  return max;
}

/*
There is support function to calculate number of edges
It is created matrix of unique combinations of two vertex numbers (first is min
of them, second - is max of them); Circle of all polygons: each vertex with
neighbour and last with first
*/
int get_edges_number(polygon *polygons, unsigned int number_polygons) {
  int answer = 0;
  int size = 4;
  int *edges = (int *)calloc(size * 2, sizeof(int));
  if (edges == NULL) {
    printf("Error with calloc at the get_edge\n");
    return 0;
  }
  for (unsigned int i = 0; i < number_polygons; ++i) {
    for (unsigned int j = 0; j < polygons[i].number_vertexes; ++j) {
      int start, end;
      if (j == polygons[i].number_vertexes - 1) {
        start = (int)polygons[i].vertexes[j];
        end = (int)polygons[i].vertexes[0];
      } else {
        start = (int)polygons[i].vertexes[j];
        end = (int)polygons[i].vertexes[j + 1];
      }

      int vertex_start = (start < end) ? start : end;
      int vertex_end = (start > end) ? start : end;

      if (has_edge(edges, vertex_start, vertex_end, answer * 2)) {
        if (answer * 2 == size) {
          size *= 2;
          int *new_edges = (int *)realloc(edges, size * 2 * sizeof(int));
          if (new_edges == NULL) {
            printf("Error with realloc at the get_edge\n");
            free(edges);
            return 0;
          }
          edges = new_edges;
        }
        edges[2 * answer] = vertex_start;
        edges[2 * answer + 1] = vertex_end;
        ++answer;
      }
    }
  }
  free(edges);
  return answer;
}

// There is support function to get_edges_number function
int has_edge(const int *edges, int vertex_start, int vertex_end, int size) {
  int has_edge = OK;
  for (int i = 0; i < size - 1 && has_edge; i += 2) {
    if (edges[i] == vertex_start && edges[i + 1] == vertex_end) {
      has_edge = FAIL;
    }
  }
  return has_edge;
}