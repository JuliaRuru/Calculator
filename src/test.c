#include "calculator.h"
#include <check.h>
#define EPS 1e-7

START_TEST(test1) {
        char arr[255] = "10/10*10*1*0.18-123";
        ck_assert_int_eq(check_formula(arr), 0);
        ck_assert_double_eq_tol(pars(arr), -121.20000000, EPS);
}
END_TEST

START_TEST(test2) {
    char arr[255] = "cos(x+1)";
    char x[255] = "-10";
    char arr1[255] = "cos(-10+1)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), -0.91113026, EPS);
    ck_assert_double_eq_tol(pars(arr1), -0.91113026, EPS);
}
END_TEST

START_TEST(test3) {
    char arr[255] = "sin(x-1)";
    char x[255] = "-10";
    char arr1[255] = "sin(-10-1)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 0.99999021, EPS);
    ck_assert_double_eq_tol(pars(arr1), 0.99999021, EPS);
}
END_TEST

START_TEST(test4) {
    char arr[255] = "tan(x*-1)";
    char x[255] = "-10";
    char arr1[255] = "tan(-10*-1)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 0.64836083, EPS);
    ck_assert_double_eq_tol(pars(arr1), 0.64836083, EPS);
}
END_TEST

START_TEST(test5) {
    char arr[255] = "acos(x)^2";
    char x[255] = "0";
    char arr1[255] = "acos(0)^2";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 2.4674011, EPS);
    ck_assert_double_eq_tol(pars(arr1), 2.4674011, EPS);
}
END_TEST

START_TEST(test6) {
    char arr[255] = "asin(x/2)";
    char x[255] = "-0.1";
    char arr1[255] = "asin(-0.1/2)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), -0.05002086, EPS);
    ck_assert_double_eq_tol(pars(arr1), -0.05002086, EPS);
}
END_TEST

START_TEST(test7) {
    char arr[255] = "xmod3";
    char x[255] = "-17";
    char arr1[255] = "-17mod3";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), -2, EPS);
    ck_assert_double_eq_tol(pars(arr1), -2, EPS);
}
END_TEST

START_TEST(test8) {
    char arr[255] = "sqrt(x*12)";
    char x[255] = "5";
    char arr1[255] = "sqrt(5*12)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 7.7459667, EPS);
    ck_assert_double_eq_tol(pars(arr1), 7.7459667, EPS);
}
END_TEST

START_TEST(test9) {
    char arr[255] = "ln(x)";
    char x[255] = "5";
    char arr1[255] = "ln(5)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 1.6094379, EPS);
    ck_assert_double_eq_tol(pars(arr1), 1.6094379, EPS);
}
END_TEST

START_TEST(test10) {
    char arr[255] = "log(x)";
    char x[255] = "5";
    char arr1[255] = "log(5)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 0.6989700, EPS);
    ck_assert_double_eq_tol(pars(arr1), 0.6989700, EPS);
}
END_TEST

START_TEST(test11) {
    char arr[255] = "-cos(x)";
    char x[255] = "-10";
    char arr1[255] = "-cos(-10)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 0.8390715, EPS);
    ck_assert_double_eq_tol(pars(arr1), 0.8390715, EPS);
}
END_TEST

START_TEST(test12) {
    char arr[255] = "sin(x)";
    char x[255] = "5";
    char arr1[255] = "sin(5)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), -0.95892427, EPS);
    ck_assert_double_eq_tol(pars(arr1), -0.95892427, EPS);
}
END_TEST

START_TEST(test13) {
    char arr[255] = "-tan(x*-37)";
    char x[255] = "-10";
    char arr1[255] = "-tan(-10*-37)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 0.85594117, EPS);
    ck_assert_double_eq_tol(pars(arr1), 0.85594117, EPS);
}
END_TEST

START_TEST(test14) {
    char arr[255] = "-acos(x-3*(x+2))";
    char x[255] = "-10";
    char arr1[255] = "-acos(-10-3*(-10+2))";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_float_nan(get_result(arr, x));
    ck_assert_float_nan(pars(arr1));
}
END_TEST

START_TEST(test15) {
    char arr[255] = "-asin(x)";
    char x[255] = "100";
    char arr1[255] = "-asin(100)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_float_nan(get_result(arr, x));
    ck_assert_float_nan(pars(arr1));
}
END_TEST

START_TEST(test16) {
    char arr[255] = "-atan(x)";
    char x[255] = "-10";
    char arr1[255] = "-atan(-10)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 1.47112767, EPS);
    ck_assert_double_eq_tol(pars(arr1), 1.47112767, EPS);
}
END_TEST

START_TEST(test17) {
    char arr[255] = "-sqrt(x)";
    char x[255] = "0";
    char arr1[255] = "-sqrt(0)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), 0, EPS);
    ck_assert_double_eq_tol(pars(arr1), 0, EPS);
}
END_TEST

START_TEST(test18) {
    char arr[255] = "-ln(-x)";
    char x[255] = "10";
    char arr1[255] = "-ln(-10)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_float_nan(get_result(arr, x));
    ck_assert_float_nan(pars(arr1));
}
END_TEST

START_TEST(test19) {
    char arr[255] = "-log(x)";
    char x[255] = "5";
    char arr1[255] = "-log(5)";
    ck_assert_int_eq(check_formula(arr), 0);
    ck_assert_int_eq(check_formula(arr1), 0);
    ck_assert_double_eq_tol(get_result(arr, x), -0.6989700043360189, EPS);
    ck_assert_double_eq_tol(pars(arr1), -0.6989700043360189, EPS);
}
END_TEST

START_TEST(error1) {
    char arr[255] = "129()";
    ck_assert_int_ne(check_formula(arr), 0);
}
END_TEST

START_TEST(error2) {
    char arr[255] = "**";
    ck_assert_int_ne(check_formula(arr), 0);
}
END_TEST

START_TEST(error3) {
    char arr[255] = "++";
    ck_assert_int_ne(check_formula(arr), 0);
}
END_TEST

START_TEST(error4) {
    char arr[255] = "2.2.2";
    ck_assert_int_ne(check_formula(arr), 0);
}
END_TEST

START_TEST(error5) {
    char arr[255] = "^^";
    ck_assert_int_ne(check_formula(arr), 0);
}
END_TEST

START_TEST(error6) {
    char arr[255] = "Hello world";
    ck_assert_int_ne(check_formula(arr), 0);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("All targets");
    SRunner *sr = srunner_create(s1);
    int nf;

    TCase *tc1_1 = tcase_create("All targets");
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test1);
    tcase_add_test(tc1_1, test2);
    tcase_add_test(tc1_1, test3);
    tcase_add_test(tc1_1, test4);
    tcase_add_test(tc1_1, test5);
    tcase_add_test(tc1_1, test6);
    tcase_add_test(tc1_1, test7);
    tcase_add_test(tc1_1, test8);
    tcase_add_test(tc1_1, test9);
    tcase_add_test(tc1_1, test10);
    tcase_add_test(tc1_1, test11);
    tcase_add_test(tc1_1, test12);
    tcase_add_test(tc1_1, test13);
    tcase_add_test(tc1_1, test14);
    tcase_add_test(tc1_1, test15);
    tcase_add_test(tc1_1, test16);
    tcase_add_test(tc1_1, test17);
    tcase_add_test(tc1_1, test18);
    tcase_add_test(tc1_1, test19);
    tcase_add_test(tc1_1, error1);
    tcase_add_test(tc1_1, error2);
    tcase_add_test(tc1_1, error3);
    tcase_add_test(tc1_1, error4);
    tcase_add_test(tc1_1, error5);
    tcase_add_test(tc1_1, error6);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
