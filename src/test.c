#include <check.h>
#include "s21_viewer.h"

// good tests

START_TEST(s21_simple_good_test_file_2_spaces) {
    printf("Test simple_good_test_file_2_spaces\n");
    char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, OK);
}

END_TEST

START_TEST(s21_simple_good_test_file_1_spaces) {
    printf("Test good file name\n");
    char file_name[] = "test_files_obj/simple_test_1_spaces.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, OK);
}

END_TEST

START_TEST(s21_4_coordinates) {
    printf("Test good 4_coordinates\n");
    char file_name[] = "test_files_obj/forth_coordinate.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, OK);
}

END_TEST

START_TEST(s21_polygons_types) {
    printf("Test good polygons_types\n");
    char file_name[] = "test_files_obj/polygons_types.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, OK);
}

END_TEST

// bad tests

START_TEST(s21_bad_file_name) {
    printf("Test bad file name\n");
    char file_name[] = "potato.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_bad_file_dir) {
    printf("Test bad file directory\n");
    char file_name[] = "simple_test_2_spaces.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_2_coordinates) {
    printf("Test bad 2_coordinates\n");
    char file_name[] = "test_files_obj/two_coordinates.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_5_coordinates) {
    printf("Test bad 5_coordinates\n");
    char file_name[] = "test_files_obj/five_coordinates.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_2_coordinates_for_polygon) {
    printf("Test bad f2_coordinates_for_polygon\n");
    char file_name[] = "test_files_obj/two_coord_for_polygon.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_empty_vertexes) {
    printf("Test bad empty_vertexes\n");
    char file_name[] = "test_files_obj/empty_vertexes.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_empty_polygons) {
    printf("Test bad empty_polygons\n");
    char file_name[] = "test_files_obj/empty_polygons.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_empty_file) {
    printf("Test bad empty_file\n");
    char file_name[] = "test_files_obj/empty.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_not_correct_vertex_coordinate) {
    printf("Test bad vertex coordinate is not correct\n");
    char file_name[] = "test_files_obj/not_correct_vertex_coordinate.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_not_correct_vertex_at_polygon) {
    printf("Test bad vertex number at the polygon is not correct\n");
    char file_name[] = "test_files_obj/not_correct_vertex_for_polygon.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_negative_vertex_at_polygon) {
    printf("Test bad vertex number at the polygon is negative\n");
    char file_name[] = "test_files_obj/negative_vertex_for_polygon.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_zero_vertex_at_polygon) {
    printf("Test bad vertex number at the polygon is zero\n");
    char file_name[] = "test_files_obj/zero_vertex_for_polygon.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_no_vertex_at_polygon) {
    printf("Test bad vertex number at the polygon is missing\n");
    char file_name[] = "test_files_obj/miss_vertex_for_polygon.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

// check_polygons tests

START_TEST(s21_check_negative) {
    printf("Test check vertex number as negative\n");
    char file_name[] = "test_files_obj/check_negative.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_check_0) {
    printf("Test check vertex number as negative\n");
    char file_name[] = "test_files_obj/check_0.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_check_big) {
    printf("Test check vertex number as negative\n");
    char file_name[] = "test_files_obj/check_big.obj";
    int status = start(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

// moving tests

START_TEST(s21_move_xyz_m10_10) {
    for (unsigned int type = 0; type < 3; ++type) {
        for (double diff = -10; diff <= 10; diff += 5) {
            int is_ok = OK;
            printf("Test check moving for  coord by 5\n");
            char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
            obj_data total_data = {0};  //создание итоговой структуры
            parse_file(file_name, &total_data);
            coord_matrix test_result = {0};
            init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
            for (unsigned int i = 0; i < test_result.rows; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    if (j == type) {
                        test_result.coordinates[i][j] =
                                total_data.coordMatrix.coordinates[i][j] +
                                diff;  // тест, на то, что все сдвинется именно по х на 5
                    } else {
                        test_result.coordinates[i][j] =
                                total_data.coordMatrix.coordinates[i][j];
                    }
                }
            }

            switch (type) {
                case 0:
                    is_ok = move_coordinate(&total_data.coordMatrix, diff, 0,
                                            0);  // по х на diff
                    break;
                case 1:
                    is_ok = move_coordinate(&total_data.coordMatrix, 0, diff,
                                            0);  // по y на diff
                    break;
                case 2:
                    is_ok = move_coordinate(&total_data.coordMatrix, 0, 0,
                                            diff);  // по x на diff
                    break;
            }
            if (!is_ok) {
                printf("We can not do this transformation!\n");
            }

            printf("After moving\n");
            print_data(total_data);

            ck_assert_int_eq(is_ok, OK);
            for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    ck_assert_ldouble_eq_tol(total_data.coordMatrix.coordinates[i][j],
                                             test_result.coordinates[i][j], s21_EPS);
                }
            }
            free_coord_matrix(&test_result);
            free_results(&total_data);

            printf("\n");
        }
    }
}

END_TEST

START_TEST(s21_scale_xyz_m11_11) {
    for (unsigned int type = 0; type < 3; ++type) {  // 0 - x, 1 - y, 2 - z
        for (double diff = -11; diff <= 11; diff += 5) {
            int is_ok = OK;
            printf("Test check scaling for x coord by 5\n");
            char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
            obj_data total_data = {0};  //создание итоговой структуры
            parse_file(file_name, &total_data);

            coord_matrix test_result = {0};
            init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
            for (unsigned int i = 0; i < test_result.rows; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    if (j == type) {
                        test_result.coordinates[i][j] =
                                total_data.coordMatrix.coordinates[i][j] *
                                diff;  // тест, на то, что все увеличится именно по х на 5
                    } else {
                        test_result.coordinates[i][j] =
                                total_data.coordMatrix.coordinates[i][j];
                    }
                }
            }

            switch (type) {
                case 0:
                    is_ok = scale_coordinate(
                            &total_data.coordMatrix, diff, 1,
                            1);  // по х на diff  // в масштабировании если не изменяется
                    // координата, то передавать надо 1, а не 0
                    break;
                case 1:
                    is_ok = scale_coordinate(&total_data.coordMatrix, 1, diff,
                                             1);  // по y на diff
                    break;
                case 2:
                    is_ok = scale_coordinate(&total_data.coordMatrix, 1, 1,
                                             diff);  // по x на diff
                    break;
            }
            if (!is_ok) {
                printf("We can not do this transformation!\n");
            }
            printf("After moving\n");
            print_data(total_data);

            ck_assert_int_eq(is_ok, OK);
            for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    ck_assert_ldouble_eq_tol(total_data.coordMatrix.coordinates[i][j],
                                             test_result.coordinates[i][j], s21_EPS);
                }
            }
            free_coord_matrix(&test_result);
            free_results(&total_data);

            printf("\n");
        }
    }
}

END_TEST

START_TEST(s21_rotate_X) {
    for (double diff = -s21_PI_2; diff <= s21_PI_2; diff += s21_PI_4) {
        int is_ok = OK;
        printf("Test rotate for x coord by 15\n");
        printf("angle is %lf\n", diff);
        char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
        obj_data total_data = {0};  //создание итоговой структуры
        parse_file(file_name, &total_data);

        coord_matrix test_result = {0};
        init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
        for (unsigned int i = 1; i < test_result.rows; ++i) {
            test_result.coordinates[i][0] = total_data.coordMatrix.coordinates[i][0];
            test_result.coordinates[i][1] =
                    total_data.coordMatrix.coordinates[i][1] * cos(diff) -
                    total_data.coordMatrix.coordinates[i][2] * sin(diff);
            test_result.coordinates[i][2] =
                    total_data.coordMatrix.coordinates[i][1] * sin(diff) +
                    total_data.coordMatrix.coordinates[i][2] * cos(diff);
        }

        is_ok = rotate_X(&total_data.coordMatrix, diff);

        if (!is_ok) {
            printf("We can not do this transformation!\n");
        }
        printf("After moving\n");
        print_data(total_data);

        ck_assert_int_eq(is_ok, OK);
        for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
            for (unsigned int j = 0; j < NUMBER_COLS - 1; ++j) {
                ck_assert_ldouble_eq_tol(total_data.coordMatrix.coordinates[i][j],
                                         test_result.coordinates[i][j], s21_EPS);
            }
        }
        free_coord_matrix(&test_result);
        free_results(&total_data);

        printf("\n");
    }
}

END_TEST

START_TEST(s21_rotate_Y) {
    for (double diff = -s21_PI_2; diff <= s21_PI_2; diff += s21_PI_4) {
        int is_ok = OK;
        printf("Test rotate for x coord by 15\n");
        printf("angle is %lf\n", diff);
        char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
        obj_data total_data = {0};  //создание итоговой структуры
        parse_file(file_name, &total_data);

        coord_matrix test_result = {0};
        init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
        for (unsigned int i = 1; i < test_result.rows; ++i) {
            test_result.coordinates[i][0] =
                    total_data.coordMatrix.coordinates[i][0] * cos(diff) +
                    total_data.coordMatrix.coordinates[i][2] * sin(diff);
            test_result.coordinates[i][1] = total_data.coordMatrix.coordinates[i][1];
            test_result.coordinates[i][2] =
                    -total_data.coordMatrix.coordinates[i][0] * sin(diff) +
                    total_data.coordMatrix.coordinates[i][2] * cos(diff);
        }

        is_ok = rotate_Y(&total_data.coordMatrix, diff);

        if (!is_ok) {
            printf("We can not do this transformation!\n");
        }
        printf("After moving\n");
        print_data(total_data);

        ck_assert_int_eq(is_ok, OK);
        for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
            for (unsigned int j = 0; j < NUMBER_COLS - 1; ++j) {
                ck_assert_ldouble_eq_tol(total_data.coordMatrix.coordinates[i][j],
                                         test_result.coordinates[i][j], s21_EPS);
            }
        }
        free_coord_matrix(&test_result);
        free_results(&total_data);

        printf("\n");
    }
}

END_TEST

START_TEST(s21_rotate_Z) {
    for (double diff = -s21_PI_2; diff <= s21_PI_2; diff += s21_PI_4) {
        int is_ok = OK;
        printf("Test rotate for x coord by 15\n");
        printf("angle is %lf\n", diff);
        char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
        obj_data total_data = {0};  //создание итоговой структуры
        parse_file(file_name, &total_data);

        coord_matrix test_result = {0};
        init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
        for (unsigned int i = 1; i < test_result.rows; ++i) {
            test_result.coordinates[i][0] =
                    total_data.coordMatrix.coordinates[i][0] * cos(diff) -
                    total_data.coordMatrix.coordinates[i][1] * sin(diff);
            test_result.coordinates[i][1] =
                    total_data.coordMatrix.coordinates[i][0] * sin(diff) +
                    total_data.coordMatrix.coordinates[i][1] * cos(diff);
            test_result.coordinates[i][2] = total_data.coordMatrix.coordinates[i][2];
        }

        is_ok = rotate_Z(&total_data.coordMatrix, diff);

        if (!is_ok) {
            printf("We can not do this transformation!\n");
        }
        printf("After moving\n");
        print_data(total_data);

        ck_assert_int_eq(is_ok, OK);
        for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
            for (unsigned int j = 0; j < NUMBER_COLS - 1; ++j) {
                ck_assert_ldouble_eq_tol(total_data.coordMatrix.coordinates[i][j],
                                         test_result.coordinates[i][j], s21_EPS);
            }
        }
        free_coord_matrix(&test_result);
        free_results(&total_data);

        printf("\n");
    }
}

END_TEST

START_TEST(s21_move_scale_xyz_m11_11) {
    for (unsigned int type = 0; type < 3; ++type) {
        for (double diff = -11; diff <= 11; diff += 5) {
            int is_ok = OK;
            printf("Test check moving and scale for  coord by 5\n");
            char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
            obj_data total_data = {0};  //создание итоговой структуры
            parse_file(file_name, &total_data);

            coord_matrix test_result = {0};
            init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
            for (unsigned int i = 0; i < test_result.rows; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    if (j == type) {
                        test_result.coordinates[i][j] =
                                (total_data.coordMatrix.coordinates[i][j] + diff) *
                                diff;  // тест, на то, что все сдвинется именно по х на 5
                    } else {
                        test_result.coordinates[i][j] =
                                total_data.coordMatrix.coordinates[i][j];
                    }
                }
            }
            int move_ok = OK;
            int scale_ok = OK;
            switch (type) {
                case 0:
                    move_ok = move_coordinate(&total_data.coordMatrix, diff, 0,
                                              0);  // по х на diff
                    scale_ok = scale_coordinate(&total_data.coordMatrix, diff, 1,
                                                1);  // по х на diff
                    break;
                case 1:
                    move_ok = move_coordinate(&total_data.coordMatrix, 0, diff,
                                              0);  // по y на diff
                    scale_ok = scale_coordinate(&total_data.coordMatrix, 1, diff,
                                                1);  // по y на diff
                    break;
                case 2:
                    move_ok = move_coordinate(&total_data.coordMatrix, 0, 0,
                                              diff);  // по x на diff
                    scale_ok = scale_coordinate(&total_data.coordMatrix, 1, 1,
                                                diff);  // по x на diff
                    break;
            }
            if (move_ok != OK || scale_ok != OK) {
                is_ok = AFFIN_FAIL;
                printf("We can not do this transformation!\n");
            }

            printf("After moving\n");
            print_data(total_data);

            ck_assert_int_eq(is_ok, OK);
            for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    ck_assert_ldouble_eq_tol(total_data.coordMatrix.coordinates[i][j],
                                             test_result.coordinates[i][j], s21_EPS);
                }
            }
            free_coord_matrix(&test_result);
            free_results(&total_data);

            printf("\n");
        }
    }
}

END_TEST

START_TEST(s21_scale_move_xyz_m11_11) {
    for (unsigned int type = 0; type < 3; ++type) {
        for (double diff = -11; diff <= 11; diff += 5) {
            int is_ok = OK;
            printf("Test check moving and scale for  coord by 5\n");
            char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
            obj_data total_data = {0};  //создание итоговой структуры
            parse_file(file_name, &total_data);

            coord_matrix test_result = {0};
            init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
            for (unsigned int i = 0; i < test_result.rows; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    if (j == type) {
                        test_result.coordinates[i][j] =
                                total_data.coordMatrix.coordinates[i][j] * diff +
                                diff;  // тест, на то, что все сдвинется именно по х на 5
                    } else {
                        test_result.coordinates[i][j] =
                                total_data.coordMatrix.coordinates[i][j];
                    }
                }
            }
            int move_ok = OK;
            int scale_ok = OK;
            switch (type) {
                case 0:
                    scale_ok = scale_coordinate(&total_data.coordMatrix, diff, 1,
                                                1);  // по х на diff
                    move_ok = move_coordinate(&total_data.coordMatrix, diff, 0,
                                              0);  // по х на diff
                    break;
                case 1:
                    scale_ok = scale_coordinate(&total_data.coordMatrix, 1, diff,
                                                1);  // по y на diff
                    move_ok = move_coordinate(&total_data.coordMatrix, 0, diff,
                                              0);  // по y на diff
                    break;
                case 2:
                    scale_ok = scale_coordinate(&total_data.coordMatrix, 1, 1,
                                                diff);  // по x на diff
                    move_ok = move_coordinate(&total_data.coordMatrix, 0, 0,
                                              diff);  // по x на diff
                    break;
            }
            if (move_ok != OK || scale_ok != OK) {
                is_ok = AFFIN_FAIL;
                printf("We can not do this transformation!\n");
            }

            printf("After moving\n");
            print_data(total_data);

            ck_assert_int_eq(is_ok, OK);
            for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    ck_assert_ldouble_eq_tol(total_data.coordMatrix.coordinates[i][j],
                                             test_result.coordinates[i][j], s21_EPS);
                }
            }
            free_coord_matrix(&test_result);
            free_results(&total_data);
            printf("\n");
        }
    }
}

END_TEST

START_TEST(s21_rotate_XYZ) {  // без проверки значений
    for (double diff = -s21_PI_2; diff <= s21_PI_2; diff += s21_PI_4) {
        int is_ok = OK;
        printf("Test rotate for x,y,z coord by 15\n");
        printf("angle is %lf\n", diff);
        char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
        obj_data total_data = {0};  //создание итоговой структуры
        parse_file(file_name, &total_data);
        print_data(total_data);

        int rot_x = rotate_X(&total_data.coordMatrix, diff);
        int rot_y = rotate_Y(&total_data.coordMatrix, diff);
        int rot_z = rotate_Z(&total_data.coordMatrix, diff);


        if (rot_x != OK || rot_y != OK || rot_z != OK) {
            is_ok = AFFIN_FAIL;
            printf("We can not do this transformation!\n");
        }
        printf("After moving\n");
        print_data(total_data);

        ck_assert_int_eq(is_ok, OK);
        free_results(&total_data);
        printf("\n");
    }
}

END_TEST

// тесты оцентровки
START_TEST(s21_move_to_center_1) {  // перенос к центру координат
    char file_name[] = "test_files_obj/simple_test_2_spaces.obj";
    int is_ok = OK;
    obj_data total_data = {0};  // создание итоговой структуры
    is_ok = parse_file(file_name, &total_data);
    print_data(total_data);

    if (is_ok) {
        is_ok = check_polygons(
                &total_data);  // проверка, чтобы каждое значение вершины в полигонах
        // было строго больше 0 и в пределах количества вершин
        if (!is_ok) {
            free_results(
                    &total_data);  // память уже выделена и заполнена, но в массиве для
            // построения есть некорректные данные, поэтому дальше
            // мы эти данные не пропустим, а память почистим
        }
    }

    is_ok = move_to_center(&total_data);
    if (is_ok) {
        printf("After center\n");
        print_data(total_data);
    }

    ck_assert_int_eq(is_ok, OK);
    for (int i = 0; i < NUMBER_COORD_XYZ; ++i) { // проверяем что максимумы и минимумы фигуры зеркальны осям
        ck_assert_ldouble_eq_tol(fabs(total_data.coordMatrix.extrems[2*i]), fabs(total_data.coordMatrix.extrems[2*i+1]), s21_EPS);
    }

    if (is_ok) {
        free_results(&total_data);
    }
}

END_TEST



START_TEST(s21_move_to_center_cub) {  // перенос к центру координат
    char file_name[] = "test_files_obj/simple_cub.obj";
    int is_ok = OK;
    obj_data total_data = {0};  // создание итоговой структуры
    is_ok = parse_file(file_name, &total_data);
    print_data(total_data);

    if (is_ok) {
        is_ok = check_polygons(
                &total_data);  // проверка, чтобы каждое значение вершины в полигонах
        // было строго больше 0 и в пределах количества вершин
        if (!is_ok) {
            free_results(
                    &total_data);  // память уже выделена и заполнена, но в массиве для
            // построения есть некорректные данные, поэтому дальше
            // мы эти данные не пропустим, а память почистим
        }
    }

    is_ok = preparation_to_init_draw(&total_data);

    if (is_ok) {
        printf("After center\n");
        print_data(total_data);
    }

    ck_assert_int_eq(is_ok, OK);
    for (int i = 0; i < NUMBER_COORD_XYZ; ++i) { // проверяем что максимумы и минимумы фигуры зеркальны осям
        ck_assert_ldouble_eq_tol(fabs(total_data.coordMatrix.extrems[2*i]), fabs(total_data.coordMatrix.extrems[2*i+1]), s21_EPS);
        ck_assert_int_eq(fabs(total_data.coordMatrix.extrems[2*i]) < 1, 1); //
        ck_assert_int_eq(fabs(total_data.coordMatrix.extrems[2*i + 1]) < 1, 1);
    }

    if (is_ok) {
        free_results(&total_data);
    }
}

END_TEST




int main(void) {
    setlocale(LC_ALL, "en_US.UTF-8");
    int number_failed;
    Suite *s = suite_create("s21_viewer");

    TCase *s21_viewer_h = tcase_create("s21_viewer_h");
    SRunner *sr = srunner_create(s);
    suite_add_tcase(s, s21_viewer_h);

    // good tests
    tcase_add_test(s21_viewer_h, s21_simple_good_test_file_2_spaces);
    tcase_add_test(s21_viewer_h, s21_simple_good_test_file_1_spaces);
    tcase_add_test(s21_viewer_h, s21_4_coordinates);
    tcase_add_test(s21_viewer_h, s21_polygons_types);

    // bad tests
    tcase_add_test(s21_viewer_h, s21_bad_file_name);
    tcase_add_test(s21_viewer_h, s21_bad_file_dir);
    tcase_add_test(s21_viewer_h, s21_2_coordinates);
    tcase_add_test(s21_viewer_h, s21_5_coordinates);
    tcase_add_test(s21_viewer_h, s21_2_coordinates_for_polygon);
    tcase_add_test(s21_viewer_h, s21_empty_vertexes);
    tcase_add_test(s21_viewer_h, s21_empty_polygons);
    tcase_add_test(s21_viewer_h, s21_empty_file);
    tcase_add_test(s21_viewer_h, s21_not_correct_vertex_coordinate);
    tcase_add_test(s21_viewer_h, s21_not_correct_vertex_at_polygon);
    tcase_add_test(s21_viewer_h, s21_negative_vertex_at_polygon);
    tcase_add_test(s21_viewer_h, s21_zero_vertex_at_polygon);
    tcase_add_test(s21_viewer_h, s21_no_vertex_at_polygon);

    // check_polygons tests
    tcase_add_test(s21_viewer_h, s21_check_negative);
    tcase_add_test(s21_viewer_h, s21_check_0);
    tcase_add_test(s21_viewer_h, s21_check_big);

    // affine test
    tcase_add_test(s21_viewer_h, s21_move_xyz_m10_10);
    tcase_add_test(s21_viewer_h, s21_scale_xyz_m11_11);
    tcase_add_test(s21_viewer_h, s21_rotate_X);
    tcase_add_test(s21_viewer_h, s21_rotate_Y);
    tcase_add_test(s21_viewer_h, s21_rotate_Z);
    tcase_add_test(s21_viewer_h, s21_move_scale_xyz_m11_11);
    tcase_add_test(s21_viewer_h, s21_scale_move_xyz_m11_11);
    tcase_add_test(s21_viewer_h, s21_rotate_XYZ);

    // тесты оцентровки
    tcase_add_test(s21_viewer_h, s21_move_to_center_1);
    tcase_add_test(s21_viewer_h, s21_move_to_center_cub);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_ENV);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}