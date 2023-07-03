#include "s21_viewer.h"
#include <stdlib.h>
/*
int main() {
    parsing_process();
    return 0;
}
*/
int parsing_process() {
    int is_ok = OK;
    char file_name[] = "simple_test_2_spaces.obj";  // строка для дебага
    obj_data total_data = {0};  // создание итоговой структуры

    is_ok = start(file_name, &total_data);

    if (is_ok) {
        free_results(&total_data);
    }

}

int start(const char *file_name, obj_data *total_data) {
    int is_ok = OK;
    is_ok = parse_file(file_name, total_data);

    if (is_ok) {
        is_ok = check_polygons(
                total_data);  // проверка, чтобы каждое значение вершины в полигонах
        // было строго больше 0 и в пределах количества вершин
        if (!is_ok) {
            free_results(
                    total_data);  // память уже выделена и заполнена, но в массиве для
            // построения есть некорректные данные, поэтому дальше
            // мы эти данные не пропустим, а память почистим
        }
    }
    if (is_ok) {
        print_data(*total_data); // функция для информативности в тестах
        is_ok = preparation_to_init_draw(total_data); // оцентровка и изменение масштаба к 0-1
    }

    if (is_ok) {
        printf("After center\n");
        print_data(*total_data);
    }

    return is_ok;
}

int parse_file(const char *file_name, obj_data *total_data) {
    unsigned int number_vertexes = 0, number_polygons = 0;
    int is_ok = OK;
    is_ok = find_info_for_init(&number_vertexes, &number_polygons,
                               file_name);  // первое прочтение файла

    if (is_ok) {
        coord_matrix coordMatrix = {0};  // инициализация матрицы координат вершин
        is_ok = init_coord_matrix(&coordMatrix, number_vertexes,
                                  NUMBER_COLS);  // внутри происходит выделение
        // памяти под матрицу координат
        if (is_ok) {
            //   obj_data total_data; //создание итоговой структуры
            total_data->number_vertex = number_vertexes;
            total_data->number_polygons = number_polygons;
            total_data->coordMatrix = coordMatrix;
            total_data->polygons =
                    (polygon *) calloc(total_data->number_polygons, sizeof(polygon));

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

int find_info_for_init(unsigned int *number_vertexes,
                       unsigned int *number_polygons, const char *file_name) {
    // история без вершин и полигонов будет восприниматься как ошибочная
    int is_ok = OK;
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Program can not open file.\n");
        is_ok = FAIL;
    }

    if (is_ok) {
        char line[MAX_LENGTH];  // Буфер для хранения строки
        while (fgets(line, sizeof(line), file)) {  // Считываем строку из файла
            line[strcspn(line, "\n")] = '\0';
            if (line[0] == 'v' && line[1] == ' ') { // vertex
                *number_vertexes += 1;
            } else if (line[0] == 'f' && line[1] == ' ') { //polygon
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

int init_coord_matrix(coord_matrix *coordMatrix, unsigned int number_vertexes,
                      unsigned int number_for_cols) {
    int is_ok = OK;
    coordMatrix->rows =
            number_vertexes + 1;  // нулевая строчка использоваться не будет
    coordMatrix->cols =
            number_for_cols;  // x,y,z - 3 координаты + w для аффинных преобразований
    coordMatrix->coordinates =
            (double **) calloc(coordMatrix->rows, sizeof(double *));
    if (coordMatrix->coordinates == NULL) {
        printf("Error with main calloc at init_coord_matrix function\n");
        is_ok = FAIL;
    } else {
        for (unsigned int i = 0; i < coordMatrix->rows && is_ok; ++i) {
            coordMatrix->coordinates[i] =
                    (double *) calloc(coordMatrix->cols, sizeof(double));
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

int fill_matrixes(obj_data *total_data, const char *file_name) {
    int is_ok = OK;
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Program can not open file second time.\n");
        is_ok = FAIL;
    }

    if (is_ok) {
        fseek(file, 0, SEEK_SET);  // открывает файл второй раз с начала
        char line[MAX_LENGTH] = {0};  // Буфер для хранения строки

        unsigned int vertex_i = 1; // нулевой не используется, т.к. отсчет в f начинвается с 1
        unsigned int polygon_i = 0;
        while (fgets(line, sizeof(line), file) &&
               is_ok) {  // Считываем строку из файла
            line[strcspn(line, "\n")] = '\0';
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

int parseVertexes(char *line, coord_matrix *coordMatrix, unsigned int vertex_i) {
    int is_ok = OK;
    char *token = strtok(line, " ");  // Разделитель - пробел

    int i = -1; // ++1 - на проверку выхода за границу
    double coordinates[NUMBER_COLS + 1] = {0};
    while (token != NULL && is_ok) {
        if (i == -1 && strcmp(token, "v") == 0) {
            ++i;
        } else {
            if (i > NUMBER_COORD_XYZ) {  // потому что сначала происходит проверка,
                // после 3х координат и w, ш будет равен 3
                printf("File is broken, too much coordinates for vertex\n");
                is_ok = FAIL;
            } else {
                if (!is_string_number(token)) {
                    is_ok = FAIL;
                } else if (i >= 0) {
                    coordinates[i] = atof(token);  //  проверкой на число - в is_string_number
                    if (i < NUMBER_COORD_XYZ) { // рассматриваем только координаты x,y,z
                        // заполнение и обновление массива минимумов и максимумов
                        if (vertex_i == 1) { // первоначальная инициализация значениями мин и макс в первой точке
                            coordMatrix->extrems[i * 2] = coordinates[i]; // минимум
                            coordMatrix->extrems[i * 2 + 1] = coordinates[i]; // максимум
                        } else { // работа с остальными точками
                            coordMatrix->extrems[i * 2] = min_two_doubles(coordMatrix->extrems[i * 2], coordinates[i]);
                            coordMatrix->extrems[i * 2 + 1] = max_two_doubles(coordMatrix->extrems[i * 2 + 1],
                                                                              coordinates[i]);
                        }
                    }
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
        if (coordinates[3] >
            0) {  // если w = 0, то аффинные преобразования не будут происходить
            coordMatrix->coordinates[vertex_i][3] = coordinates[3];
        } else {
            coordMatrix->coordinates[vertex_i][3] = 1;  // по дефолту w = 1;
        }
    }
    return is_ok;
}

int parsePolygon(char *line, polygon *polygons, unsigned int polygon_i) {
    int is_ok = OK;
    char *token = strtok(line, " ");  // Разделитель - пробел

    unsigned int vert_i =
            -1;  // -1 - чтобы шагнуть с первого токена, который будет "f" в 0 позицию

    unsigned int max_vertexes = MAX_POLYGON_LENGHT;
    unsigned int *vertexes =
            (unsigned int *) malloc(max_vertexes * sizeof(unsigned int));

    if (vertexes == NULL) {
        fprintf(stderr, "Failed to allocate memory for polygon %u.\n", polygon_i);
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

    if (vert_i < NUMBER_COORD_XYZ) {  // из двух точек не получится фигуры
        printf("File is broken, less than 2 pointers to polygon\n");
        is_ok = FAIL;
    }

    if (vert_i < MAX_POLYGON_LENGHT && is_ok) {
        unsigned int *new_vertexes =
                (unsigned int *) realloc(vertexes, vert_i * sizeof(unsigned int));
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
    printf("Extrems are \n");
    for (int i = 0; i < 6; ++i) {
        printf("%lf ", data.coordMatrix.extrems[i]);
    }
    printf("\n");
}

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
            char *numberStr = (char *) calloc(step + 1, sizeof(char));
            if (numberStr == NULL) {
                printf("Error with malloc at get_int function\n");
                is_ok = FAIL;
            } else {
                strncpy(numberStr, token, step);
                numberStr[step] = '\0';
                *number_str = atoi(numberStr);  // atoi защищен проверкой на digit выше
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

int is_string_number(char *token) {
    int is_number = OK;
    int have_dot = 0;
    char *p = token;

    if (strlen(token) > 1 && *p == '-') {
        ++p;
    }

    while (*p != '\0' && is_number) {
        if (!(isdigit(*p) ||
              (*p == '.' && !have_dot))) {  // только цифра и одна точка
            is_number = FAIL;
        }

        if (*p == '.' && !have_dot) {  // обработка двух точек в одном числе
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

void free_polygons(obj_data *total_data, unsigned int crash_number) {
    for (unsigned int i = 0; i < crash_number; ++i) {
        free(total_data->polygons[i].vertexes);
    }
}

void free_results(obj_data *total_data) {
    free_coord_matrix(&total_data->coordMatrix);
    free_polygons(total_data, total_data->number_polygons);
    free(total_data->polygons);
    total_data->number_polygons = 0;
    total_data->number_vertex = 0;
}

// афинные преобразования

//общий алгоритм
int affin_operation(coord_matrix *coordMatrix, double diffX, double diffY,
                    double diffZ, int type) {
    int status = OK;
    double scale_coeff = calculate_scale_coefficient(coordMatrix->extrems);
    diffX *= scale_coeff;
    diffY *= scale_coeff;
    diffZ *= scale_coeff;
    coord_matrix affin_matrix = {0};
    switch (type) {
        case 1:  // перемещение
            status = init_move_matrix(&affin_matrix, diffX, diffY, diffZ);
            break;
        case 2:  // scale
            status = init_scale_matrix(&affin_matrix, diffX, diffY, diffZ);
            break;
        case 3:  // rotateX
            status = init_rotateX_matrix(&affin_matrix, diffX);
            break;
        case 4:  // rotateY
            status = init_rotateY_matrix(&affin_matrix, diffY);
            break;
        default:  // rotateZ
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
            if (status ==
                OK) {  // в случае фейла фришить не надо, так как free зашит в init
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    coordMatrix->coordinates[i][j] = result_matrix.coordinates[j][0];
                }
                free_coord_matrix(&vector_matrix);
                free_coord_matrix(&result_matrix);
            }
        }
        recalculate_extrems(coordMatrix);
    }
    free_coord_matrix(&affin_matrix);
    return status;
}

// перемещения
int move_coordinate(coord_matrix *coordMatrix, double diffX, double diffY,
                    double diffZ) {
    return affin_operation(coordMatrix, diffX, diffY, diffZ, 1);
}

// scale
int scale_coordinate(coord_matrix *coordMatrix, double diffX, double diffY,
                     double diffZ) {  // проверить ввод 0 на фронте
    return affin_operation(coordMatrix, diffX, diffY, diffZ, 2);
}

// rotate X
int rotate_X(coord_matrix *coordMatrix,
             double angleX) {  // принимаем в радианах
    return affin_operation(coordMatrix, angleX, 0, 0, 3);
}

// rotate Y
int rotate_Y(coord_matrix *coordMatrix,
             double angleY) {  // принимаем в градусах
    return affin_operation(coordMatrix, 0, angleY, 0, 4);
}

// rotate Z
int rotate_Z(coord_matrix *coordMatrix,
             double angleZ) {  // принимаем в градусах
    return affin_operation(coordMatrix, 0, 0, angleZ, 5);
}

int s21_mult_matrix(coord_matrix *A, coord_matrix *B,
                    coord_matrix *result) {  // Умножение двух матриц
    int status = OK;

    // это проверка тут на всякий случай,
    if (A->cols != B->rows) {  // Число столбцов первой матрицы должно быть равно
        // числу строк второй матрицы
        status = AFFIN_FAIL;
    }

    if (status == OK) {
        result->rows = A->rows;
        result->cols = B->cols;
        status = init_coord_matrix(
                result, A->rows - 1,
                B->cols);  // rows-1 - потому что в init к row прибавляется один
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
    }
    return status;
}

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
    } else {
        is_ok = AFFIN_FAIL; // все ошибки аффинных преобразований не должны ломать систему
    }
    return is_ok;
}

int init_scale_matrix(coord_matrix *affin_matrix, double diffX, double diffY,
                      double diffZ) {
    int is_ok = OK;
    is_ok = init_coord_matrix(affin_matrix, NUMBER_COORD_XYZ, NUMBER_COLS);
    if (is_ok) {
        affin_matrix->coordinates[0][0] = diffX;
        affin_matrix->coordinates[1][1] = diffY;
        affin_matrix->coordinates[2][2] = diffZ;
        affin_matrix->coordinates[3][3] = 1;
    } else {
        is_ok = AFFIN_FAIL; // все ошибки аффинных преобразований не должны ломать систему
    }
    return is_ok;
}

int init_rotateX_matrix(coord_matrix *affin_matrix,
                        double diffX) {  // y ,z = 0. x в градусах
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

int init_rotateY_matrix(coord_matrix *affin_matrix,
                        double diffY) {
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

int init_rotateZ_matrix(coord_matrix *affin_matrix,
                        double diffZ) {
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

int init_vector_matrix(coord_matrix *vector_matrix, coord_matrix *init_matrix,
                       unsigned int vector_i) {
    int is_ok = OK;
    is_ok = init_coord_matrix(vector_matrix, NUMBER_COORD_XYZ, 1);
    for (unsigned int i = 0; i < NUMBER_COLS; ++i) {
        vector_matrix->coordinates[i][0] = init_matrix->coordinates[vector_i][i];
    }
    return is_ok;
}

int preparation_to_init_draw(obj_data *total_data) {
    int is_ok = OK;
    is_ok = move_to_center(total_data); // оцентровка
    if (is_ok) {
        is_ok = scale_0_1(total_data); // изменение масштабирования
    }
    return is_ok;
}

int move_to_center(obj_data *total_data) {    // оцентровка
    double shift_values[NUMBER_COORD_XYZ] = {
            0}; // поиск на сколько сдвигать каждую точку по каждой координате, чтобы фигура была оцентрирована
    for (int i = 0; i < NUMBER_COORD_XYZ; ++i) {
        shift_values[i] = total_data->coordMatrix.extrems[i * 2] + (total_data->coordMatrix.extrems[i * 2 + 1] - total_data->coordMatrix.extrems[i * 2]) / 2; // формула: min + (max - min)/2
    }
    return move_coordinate(&total_data->coordMatrix, -shift_values[0], -shift_values[1], -shift_values[2]);
}

int scale_0_1(obj_data *total_data) {    // изменение масштаба в диапапзон [0;1]
    double scale_coefficient = calculate_scale_coefficient(total_data->coordMatrix.extrems);
    return scale_coordinate(&total_data->coordMatrix, scale_coefficient, scale_coefficient, scale_coefficient);
}

void recalculate_extrems(coord_matrix *coordMatrix) {
    for (int i = 0; i < NUMBER_COORD_XYZ; ++i) {
        coordMatrix->extrems[i *
                             2] = coordMatrix->coordinates[1][i]; // нулевая строчка не используется, поэтому инициализация идет с 1 строчки
        coordMatrix->extrems[i * 2 + 1] = coordMatrix->coordinates[1][i];
    }
    for (int i = 2; i < coordMatrix->rows; ++i) {
        for (int j = 0; j < NUMBER_COORD_XYZ; ++j) {
            coordMatrix->extrems[j * 2] = min_two_doubles(coordMatrix->extrems[j * 2], coordMatrix->coordinates[i][j]);
            coordMatrix->extrems[j * 2 + 1] = max_two_doubles(coordMatrix->extrems[j * 2 + 1],
                                                              coordMatrix->coordinates[i][j]);
        }
    }
}

double calculate_scale_coefficient(const double *extrems) {
    double deltas[NUMBER_COORD_XYZ] = {0};
    for (int i = 0; i < NUMBER_COORD_XYZ; ++i) {
        deltas[i] = extrems[2 * i + 1] - extrems[2 * i];
    }
    double max_delta = max_delta_coordinates(deltas);
    return 2 * INIT_PART_SCREEN / max_delta;
}

double max_delta_coordinates(const double *deltas) {
    double max = deltas[0];
    for (int i = 1; i < NUMBER_COORD_XYZ; ++i) {
        if (deltas[i] > max) {
            max = deltas[i];
        }
    }
    return max;
}