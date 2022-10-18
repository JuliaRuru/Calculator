#ifndef SRC_CALCULATOR_H_
#define SRC_CALCULATOR_H_

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LEN 255
#define NUM_OF_OPER 18
#define MAS_OPER_CONST {{'-', 2}, {'+', 2}, {'*', 3}, \
{'/', 3}, {'(', 1}, {')', 1}, {'s', 4}, {'S', 4}, {'c', 4}, \
{'C', 4}, {'^', 4}, {'q', 4}, {'l', 4}, {'L', 4}, {'m', 3}, \
{'T', 4}, {'t', 4}, {'$', 5}}

typedef struct polyn {
    char oper;
    int prioritet;
} polyn;

int check_formula(char str[]);
int check_x(char str[]);
int is_incorrect(char str[]);
int double_sym(char str[]);
int bad_braces(char str[]);
int double_sym(char str[]);
int bad_dots(char str[]);
void change_str(char str[]);
void edit_str(char str[], char sub_str[], char sub_str_result[]);
double pars(char formula[]);
char get_oper(char **str);
int get_number(char **str, double *num);
int is_valid_sym(char c);
int is_number(char c);
int is_func(char c);
int is_operator(char c);
int not_last_sym(char c);
int not_first_sym(char c);
void push_stack_oper(char oper, char mas_oper[], double mas_num[], int *len, int *len_num);
int check_stack(char oper, char mas_oper[], double mas_num[], int *len, int *len_num);
void push_stack_num(double oper, double mas_num[], int *len);
int result_oper(char oper, char mas_oper[], double mas_num[], int *len, int *len_num);
void edit_stack(char mas_oper[], double mas_num[], int *len_num, int *len);
void edit_stack_trig(char mas_oper[], int *len);
double get_result(char formula[], char x[]);

#endif  // SRC_CALCULATOR_H_
