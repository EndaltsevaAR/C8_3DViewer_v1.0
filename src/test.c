#include <check.h>
#include "s21_viewer.h"

// good tests

END_TEST

START_TEST(s21_simple_good_test_file_2_spaces) {
    printf("Test simple_good_test_file_2_spaces\n");
    char file_name[] = "test_files_obj/simple_test_2_spaces.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, OK);
}

END_TEST

START_TEST(s21_simple_good_test_file_1_spaces) {
    printf("Test good file name\n");
    char file_name[] = "test_files_obj/simple_test_1_spaces.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, OK);
}

END_TEST

START_TEST(s21_4_coordinates) {
    printf("Test good 4_coordinates\n");
    char file_name[] = "test_files_obj/forth_coordinate.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, OK);
}

END_TEST

START_TEST(s21_polygons_types) {
    printf("Test good polygons_types\n");
    char file_name[] = "test_files_obj/polygons_types.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, OK);
}

END_TEST

// bad tests

START_TEST(s21_bad_file_name) {
    printf("Test bad file name\n");
    char file_name[] = "potato.obj";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_bad_file_dir) {
    printf("Test bad file directory\n");
    char file_name[] = "simple_test_2_spaces.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_2_coordinates) {
    printf("Test bad 2_coordinates\n");
    char file_name[] = "test_files_obj/two_coordinates.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_5_coordinates) {
    printf("Test bad 5_coordinates\n");
    char file_name[] = "test_files_obj/five_coordinates.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_2_coordinates_for_polygon) {
    printf("Test bad f2_coordinates_for_polygon\n");
    char file_name[] = "test_files_obj/two_coord_for_polygon.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_empty_vertexes) {
    printf("Test bad empty_vertexes\n");
    char file_name[] = "test_files_obj/empty_vertexes.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_empty_polygons) {
    printf("Test bad empty_polygons\n");
    char file_name[] = "test_files_obj/empty_polygons.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_empty_file) {
    printf("Test bad empty_file\n");
    char file_name[] = "test_files_obj/empty.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_not_correct_vertex_coordinate) {
    printf("Test bad vertex coordinate is not correct\n");
    char file_name[] = "test_files_obj/not_correct_vertex_coordinate.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_not_correct_vertex_at_polygon) {
    printf("Test bad vertex number at the polygon is not correct\n");
    char file_name[] = "test_files_obj/not_correct_vertex_for_polygon.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_negative_vertex_at_polygon) {
    printf("Test bad vertex number at the polygon is negative\n");
    char file_name[] = "test_files_obj/negative_vertex_for_polygon.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_zero_vertex_at_polygon) {
    printf("Test bad vertex number at the polygon is zero\n");
    char file_name[] = "test_files_obj/zero_vertex_for_polygon.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_no_vertex_at_polygon) {
    printf("Test bad vertex number at the polygon is missing\n");
    char file_name[] = "test_files_obj/miss_vertex_for_polygon.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

// check_polygons tests

START_TEST(s21_check_negative) {
    printf("Test check vertex number as negative\n");
    char file_name[] = "test_files_obj/check_negative.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_check_0) {
    printf("Test check vertex number as negative\n");
    char file_name[] = "test_files_obj/check_0.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

START_TEST(s21_check_big) {
    printf("Test check vertex number at the polygon is too much\n");
    char file_name[] = "test_files_obj/check_big.txt";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, FAIL);
}

END_TEST

// moving tests

START_TEST(s21_move_xyz_m10_10) {
    // type is type of coordinate (x, y, z), diff is step
    for (unsigned int type = 0; type < 3; ++type) {
        for (double diff = -10; diff <= 10; diff += 5) {
            int is_ok = OK;
            printf("Test check moving for  coord by 5\n");
            char file_name[] = "test_files_obj/simple_cub.txt";
            obj_data total_data = {0};
            is_ok = start(file_name, &total_data);
            if (!is_ok) {
                ck_assert_int_eq(is_ok, OK);
                continue;
            }
            coord_matrix test_result = {0};
            is_ok = init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
            if (!is_ok) {
                free_results(&total_data);
                ck_assert_int_eq(is_ok, OK);
                continue;
            }
            double coefficient = total_data.coordMatrix.scale_coefficient;
            for (unsigned int i = 0; i < test_result.rows; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    if (j == type) {
                        test_result.coordinates[i][j] = total_data.coordMatrix.coordinates[i][j] + diff * coefficient;
                    } else {
                        test_result.coordinates[i][j] = total_data.coordMatrix.coordinates[i][j];
                    }
                }
            }

            switch (type) {
                case 0:
                    is_ok = move_coordinate(&total_data.coordMatrix, diff, 0, 0);

                    break;
                case 1:
                    is_ok = move_coordinate(&total_data.coordMatrix, 0, diff, 0);
                    break;
                case 2:
                    is_ok = move_coordinate(&total_data.coordMatrix, 0, 0, diff);
                    break;
            }
            if (!is_ok) {
                printf("We can not do this transformation!\n");
            }

            printf("After moving\n");
            print_data(total_data);
            ck_assert_int_eq(is_ok, OK);
            for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
                for (unsigned int j = 0; j < NUMBER_COORD_XYZ; ++j) {
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
    for (double diff = -11; diff <= 11; diff += 5) {
        int is_ok = OK;
        printf("Test check scaling for x coord by 5\n");
        char file_name[] = "test_files_obj/simple_cub.txt";
        obj_data total_data = {0};
        is_ok = parse_file(file_name, &total_data);
        if (!is_ok) {
            ck_assert_int_eq(is_ok, OK);
            continue;
        }
        print_data(total_data);
        coord_matrix test_result = {0};
        is_ok = init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
        if (!is_ok) {
            free_results(&total_data);
            ck_assert_int_eq(is_ok, OK);
            continue;
        }
        for (unsigned int i = 0; i < test_result.rows; ++i) {
            for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                test_result.coordinates[i][j] = total_data.coordMatrix.coordinates[i][j] * diff;
            }
        }
        is_ok = scale_coordinate(&total_data.coordMatrix, diff);
        if (!is_ok) {
            printf("We can not do this transformation!\n");
        }
        printf("After scaling\n");
        print_data(total_data);
        ck_assert_int_eq(is_ok, OK);
        for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
            for (unsigned int j = 0; j < NUMBER_COORD_XYZ; ++j) {
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

START_TEST(s21_rotate_X) {
    for (double diff = -s21_PI_2; diff <= s21_PI_2; diff += s21_PI_4) {
        int is_ok = OK;
        printf("Test rotate for x coord by 15\n");
        char file_name[] = "test_files_obj/simple_test_2_spaces.txt";
        obj_data total_data = {0};
        is_ok = parse_file(file_name, &total_data);
        if (!is_ok) {
            ck_assert_int_eq(is_ok, OK);
            continue;
        }
        coord_matrix test_result = {0};
        is_ok = init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
        if (!is_ok) {
            free_results(&total_data);
            ck_assert_int_eq(is_ok, OK);
            continue;
        }
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
            for (unsigned int j = 0; j < NUMBER_COORD_XYZ; ++j) {
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
        char file_name[] = "test_files_obj/simple_test_2_spaces.txt";
        obj_data total_data = {0};
        is_ok = parse_file(file_name, &total_data);
        if (!is_ok) {
            ck_assert_int_eq(is_ok, OK);
            continue;
        }
        coord_matrix test_result = {0};
        is_ok = init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
        if (!is_ok) {
            free_results(&total_data);
            ck_assert_int_eq(is_ok, OK);
            continue;
        }
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
            for (unsigned int j = 0; j < NUMBER_COORD_XYZ; ++j) {
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
        char file_name[] = "test_files_obj/simple_test_2_spaces.txt";
        obj_data total_data = {0};
        is_ok = parse_file(file_name, &total_data);
        if (!is_ok) {
            ck_assert_int_eq(is_ok, OK);
            continue;
        }
        coord_matrix test_result = {0};
        is_ok = init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
        if (!is_ok) {
            free_results(&total_data);
            ck_assert_int_eq(is_ok, OK);
            continue;
        }
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
            for (unsigned int j = 0; j < NUMBER_COORD_XYZ; ++j) {
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
    // type is type of coordinate (x, y, z), diff is step
    for (unsigned int type = 0; type < 3; ++type) {
        for (double diff = -11; diff <= 11; diff += 5) {
            int is_ok = OK;
            printf("Test check moving and scale for  coord by 5\n");
            char file_name[] = "test_files_obj/simple_test_2_spaces.txt";
            obj_data total_data = {0};
            is_ok = parse_file(file_name, &total_data);
            if (!is_ok) {
                ck_assert_int_eq(is_ok, OK);
                continue;
            }
            coord_matrix test_result = {0};
            is_ok = init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
            if (!is_ok) {
                free_results(&total_data);
                ck_assert_int_eq(is_ok, OK);
                continue;
            }
            double coefficient = total_data.coordMatrix.scale_coefficient;
            for (unsigned int i = 0; i < test_result.rows; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    if (j == type) {
                        test_result.coordinates[i][j] =
                                (total_data.coordMatrix.coordinates[i][j] + coefficient * diff) * diff;
                    } else {
                        test_result.coordinates[i][j] = total_data.coordMatrix.coordinates[i][j] * diff;
                    }
                }
            }
            int move_ok = OK;
            int scale_ok = OK;
            switch (type) {
                case 0:
                    move_ok = move_coordinate(&total_data.coordMatrix, diff, 0, 0);
                    break;
                case 1:
                    move_ok = move_coordinate(&total_data.coordMatrix, 0, diff, 0);
                    break;
                case 2:
                    move_ok = move_coordinate(&total_data.coordMatrix, 0, 0, diff);
                    break;
            }
            scale_ok = scale_coordinate(&total_data.coordMatrix, diff);
            if (move_ok != OK || scale_ok != OK) {
                is_ok = AFFIN_FAIL;
                printf("We can not do this transformation!\n");
            }

            printf("After moving\n");
            print_data(total_data);

            ck_assert_int_eq(is_ok, OK);
            for (unsigned int i = 1; i < total_data.number_vertex; ++i) {
                for (unsigned int j = 0; j < NUMBER_COORD_XYZ; ++j) {
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
    // type is type of coordinate (x, y, z), diff is step
    for (unsigned int type = 0; type < 3; ++type) {
        for (double diff = -11; diff <= 11; diff += 5) {
            int is_ok = OK;
            printf("Test check moving and scale for  coord by 5\n");
            char file_name[] = "test_files_obj/simple_cub.txt";
            obj_data total_data = {0};
            is_ok = parse_file(file_name, &total_data);
            if (!is_ok) {
                ck_assert_int_eq(is_ok, OK);
                continue;
            }
            print_data(total_data);
            coord_matrix test_result = {0};
            is_ok = init_coord_matrix(&test_result, total_data.number_vertex, NUMBER_COLS);
            if (!is_ok) {
                free_results(&total_data);
                ck_assert_int_eq(is_ok, OK);
                continue;
            }
            double coefficient = total_data.coordMatrix.scale_coefficient;
            for (unsigned int i = 0; i < test_result.rows; ++i) {
                for (unsigned int j = 0; j < NUMBER_COLS; ++j) {
                    if (j == type) {
                        test_result.coordinates[i][j] =
                                (total_data.coordMatrix.coordinates[i][j] + diff * coefficient) * diff;
                    } else {
                        test_result.coordinates[i][j] =
                                total_data.coordMatrix.coordinates[i][j] * diff;
                    }
                }
            }
            int move_ok = OK;
            int scale_ok = OK;
            scale_ok = scale_coordinate(&total_data.coordMatrix, diff);
            switch (type) {
                case 0:
                    move_ok = move_coordinate(&total_data.coordMatrix, diff, 0, 0);
                    break;
                case 1:
                    move_ok = move_coordinate(&total_data.coordMatrix, 0, diff, 0);
                    break;
                case 2:
                    move_ok = move_coordinate(&total_data.coordMatrix, 0, 0, diff);
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
                for (unsigned int j = 0; j < NUMBER_COORD_XYZ; ++j) {
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
        char file_name[] = "test_files_obj/simple_test_2_spaces.txt";
        obj_data total_data = {0};
        is_ok = parse_file(file_name, &total_data);
        if (!is_ok) {
            ck_assert_int_eq(is_ok, OK);
            continue;
        }
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

// tests for paint to the center

START_TEST(s21_move_to_center_1) {
    char file_name[] = "test_files_obj/simple_cub.txt";
    int is_ok = OK;
    obj_data total_data = {0};
    is_ok = parse_file(file_name, &total_data);
    if (!is_ok) {
        free_results(&total_data);
    } else {
        print_data(total_data);
        is_ok = check_polygons(&total_data);
        if (!is_ok) {
            free_results(&total_data);
        } else {
            double extrems[6] = {0};
            calculate_extrems(total_data.coordMatrix, extrems);
            is_ok = move_to_center(&total_data, extrems);
            if (!is_ok) {
                free_results(&total_data);
            } else {
                printf("After center\n");
                print_data(total_data);
                calculate_extrems(total_data.coordMatrix, extrems);
                for (int i = 0; i < NUMBER_COORD_XYZ; ++i) {
                    ck_assert_ldouble_eq_tol(fabs(extrems[2 * i]), fabs(extrems[2 * i + 1]), s21_EPS);
                }
                free_results(&total_data);
            }
        }
    }
    ck_assert_int_eq(is_ok, OK);
}

END_TEST


START_TEST(s21_move_to_center_cub) { 
    char file_name[] = "test_files_obj/simple_cub.txt";
    int is_ok = OK;
    obj_data total_data = {0};
    is_ok = parse_file(file_name, &total_data);
    print_data(total_data);
    if (is_ok) {
        is_ok = check_polygons(&total_data);
        if (!is_ok) {
            free_results(&total_data);
        }
        is_ok = preparation_to_init_draw(&total_data);
        if (is_ok) {
            printf("After center\n");
            print_data(total_data);
            free_results(&total_data);
        }
        ck_assert_int_eq(is_ok, OK);
    }
}

END_TEST

// tests for counting numbers of edges

START_TEST(s21_edge_number) {  
    char file_name[] = "test_files_obj/simple_cub.txt";
    int is_ok = OK;
    obj_data total_data = {0};
    is_ok = parse_file(file_name, &total_data);
    if (is_ok) {
        int edge_number = get_edges_number(total_data.polygons, total_data.number_polygons);
        ck_assert_int_eq(edge_number, 4);
        free_results(&total_data);
    }
    ck_assert_int_eq(is_ok, OK);
}

END_TEST

START_TEST(s21_edge_number_3d) {  
    char file_name[] = "test_files_obj/cube.txt";
    int is_ok = OK;
    obj_data total_data = {0};
    is_ok = parse_file(file_name, &total_data);
    if (is_ok) {
        int edge_number = get_edges_number(total_data.polygons, total_data.number_polygons);
        ck_assert_int_eq(edge_number, 18);
        free_results(&total_data);
    }
    ck_assert_int_eq(is_ok, OK);
}

/*
START_TEST(s21_simple_good_big_file) {
    printf("Test s21_simple_good_big_file\n");
    char file_name[] = "test_files_obj/good_man.obj";
    int status = parsing_process_for_tests(file_name);
    printf("\n");
    ck_assert_int_eq(status, OK);
}

START_TEST(s21_edge_number_big_3d) {  
    char file_name[] = "test_files_obj/good_cat.obj";
    int is_ok = OK;
    obj_data total_data = {0};  
    is_ok = parse_file(file_name, &total_data);

    int edge_number = get_edges_number(total_data.polygons, total_data.number_polygons);
    ck_assert_int_eq(is_ok, OK);
    ck_assert_int_eq(edge_number, 3199);

    if (is_ok) {
        free_results(&total_data);
    }
}
END_TEST
*/

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

    // affine tests
    tcase_add_test(s21_viewer_h, s21_move_xyz_m10_10);
    tcase_add_test(s21_viewer_h, s21_scale_xyz_m11_11);
    tcase_add_test(s21_viewer_h, s21_rotate_X);
    tcase_add_test(s21_viewer_h, s21_rotate_Y);
    tcase_add_test(s21_viewer_h, s21_rotate_Z);
    tcase_add_test(s21_viewer_h, s21_move_scale_xyz_m11_11);
    tcase_add_test(s21_viewer_h, s21_scale_move_xyz_m11_11);
    tcase_add_test(s21_viewer_h, s21_rotate_XYZ);

    // tests of paint to the center
    tcase_add_test(s21_viewer_h, s21_move_to_center_1);
    tcase_add_test(s21_viewer_h, s21_move_to_center_cub);

    // tests number of edges
    tcase_add_test(s21_viewer_h, s21_edge_number);
    tcase_add_test(s21_viewer_h, s21_edge_number_3d);

    // tests with heavy sources. There is needed download .obj file manually
    //  tcase_add_test(s21_viewer_h, s21_simple_good_man);
    //  tcase_add_test(s21_viewer_h, s21_edge_number_big_3d);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_ENV);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}