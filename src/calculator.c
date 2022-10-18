#include "calculator.h"

int check_formula(char str[]) {
    int error = 1;                      //  0 - OK, 1 - error
    change_str(str);
    if (is_incorrect(str) == 0 && bad_braces(str) == 0 &&
        bad_dots(str) == 0 && double_sym(str) == 0) {
        error = 0;
    }
    return error;
}

int check_x(char str[]) {
    int error = 1;                      //  0 - OK, 1 - error
    change_str(str);
    edit_str(str, "-", "");
    if (bad_dots(str) == 0) {
        error = 0;
        int i = 0, number = 0;
        while (str[i] != '\0') {
            if ((str[i] == ')') || str[i] == 'x' || is_func(str[i])) error++;
            else if (is_number(str[i])) number++;
            else if (!is_valid_sym(str[i])) error++;
            i++;
            if (error > 0) {
                break;
            }
        }
        if (number == 0) error++;
    }
    return error;
}

int is_valid_sym(char c) {
    int res;
    if (c == 'x' || is_number(c) || is_func(c) || is_operator(c) || not_first_sym(c) || not_last_sym(c)) {
        res = 1;
    } else {
        res = 0;
    }
    return res;
}

int double_sym(char str[]) {
    int error = 0;
    char sub_str[10] = {'\0'};
    strcpy(sub_str, "--");
    error += strstr(str, sub_str) ? 1 : 0;
    strcpy(sub_str, "++");
    error += strstr(str, sub_str) ? 1 : 0;
    strcpy(sub_str, "^^");
    error += strstr(str, sub_str) ? 1 : 0;
    strcpy(sub_str, "**");
    error += strstr(str, sub_str) ? 1 : 0;
    strcpy(sub_str, "//");
    error += strstr(str, sub_str) ? 1 : 0;
    strcpy(sub_str, "()");
    error += strstr(str, sub_str) ? 1 : 0;
    return error;
}

int bad_braces(char str[]) {
    int error = 0;
    int x = 0;
    for (unsigned long i = 0; i < strlen(str); i++) {
        if (str[i] == '(') x++;
        if (str[i] == ')') x--;
    }
    if (x != 0) {
        error++;
    }
    return error;
}

int bad_dots(char str[]) {            //  0 = OK, 1 = bad_dots, 2 = no_digits, 3 = 2 + 1
    int res = 0;
    char *point = str;
    double num = 0.;
    int number_check = get_number(&point, &num);
    if (number_check == 2) {
        res = 1;
    }
    return res;
}

int is_incorrect(char str[]) {
    int error = 0, i = 0, number = 0;
    while (str[i] != '\0') {
        if ((str[i] == ')') && is_number(str[i+1])) error++;        //  )x, )5
        else if ((str[i+1] == '(') && is_number(str[i])) error++;   //  x(, 5(
        else if ((str[i] == 'x') && is_number(str[i+1])) error++;   //  xx, x5
        else if ((str[i+1] == 'x') && is_number(str[i])) error++;   //  xx, 5x
        else if (is_number(str[i]) && is_func(str[i+1])) error++;   //  xsin, 5sin
        else if (not_first_sym(str[0]) || ((str[i] == '(') && not_first_sym(str[i+1]))) error++;
        else if (not_last_sym(str[i]) && str[i+1] == '\0') error++;   //  not last sym последний
        else if (not_last_sym(str[i]) && str[i+1] == ')') error++;   //  not last sym)
        else if (is_number(str[i])) number++;
        else if (!is_valid_sym(str[i])) error++;
        i++;
        if (error > 0) {
            break;
        }
    }
    if (number == 0) error++;
    return error;
}

void change_str(char str[]) {
    edit_str(str, " ", "");
    edit_str(str, "asin", "S");
    edit_str(str, "acos", "C");
    edit_str(str, "atan", "T");
    edit_str(str, "sin", "s");
    edit_str(str, "cos", "c");
    edit_str(str, "tan", "t");
    edit_str(str, "sqrt", "q");
    edit_str(str, "ln", "l");
    edit_str(str, "log", "L");
    edit_str(str, "mod", "m");
}

void edit_str(char str[], char sub_str[], char sub_str_result[]) {
    char buffer[MAX_LEN] = {'\0'};
    while (strstr(str, sub_str)) {
        memset(buffer, 0, strlen(buffer));
        strncpy(buffer, str, strlen(str) - strlen(strstr(str, sub_str)) );
        strcat(buffer, sub_str_result);
        strcat(buffer, strstr(str, sub_str) + strlen(sub_str));
        strcpy(str, buffer);
    }
}

double get_result(char formula[], char x[]) {
    char result_copy[MAX_LEN];
    strcpy(result_copy, formula);
    double result = 0;
    edit_str(result_copy, "x", x);
    edit_str(result_copy, "X", x);
    result = pars(result_copy);
    return result;
}

double pars(char formula[]) {
    change_str(formula);
    char *point = formula;
    double num = 0.;
    char mas_oper[MAX_LEN] = {'\0'};
    double mas_num[MAX_LEN] = {0};
    int len_oper = 0, len_num = 0, minus = 0;
    while (strlen(point) > 0) {
        int chec_num = get_number(&point, &num);
        if (chec_num != 0) {
            if (chec_num != 2) {
                push_stack_num(num, mas_num, &len_num);
                if (minus == 1) {
                    push_stack_oper(')', mas_oper, mas_num, &len_oper, &len_num);
                    minus = 0;
                }
            } else {
                point = NULL;
                mas_num[0] = NAN;
                break;
            }
        }
        char opr = get_oper(&point);
        if (opr != '\0') {
            if ((opr == '+' || opr == '-') && chec_num == 0) {
                push_stack_num(-1, mas_num, &len_num);
                push_stack_oper('(', mas_oper, mas_num, &len_oper, &len_num);
                push_stack_oper('*', mas_oper, mas_num, &len_oper, &len_num);
                minus = 1;
            } else {
                push_stack_oper(opr, mas_oper, mas_num, &len_oper, &len_num);
            }
        }
    }
    if (*point == '\0') {
        for (int c = len_oper; c >= 1; c--) {
            result_oper(mas_oper[c - 1], mas_oper, mas_num, &c, &len_num);
        }
    }
    return mas_num[0];
}

char get_oper(char **str) {
    char res = '\0';
    polyn mas_oper_const[] = MAS_OPER_CONST;
    for (int i = 0; i < NUM_OF_OPER; i++) {
        if (** str == mas_oper_const[i].oper) {
            res = mas_oper_const[i].oper;
            (*str)++;
            i =  NUM_OF_OPER;
        }
    }
    return res;
}

int get_number(char **str, double *res) {
    *res = 0;
    double x = 10;
    int flag = is_number(**str);       //  есть число = 1
    while (is_number(**str)) {
        if (**str == '.') {
            if (x == 10) {
                x = 0.1;
            } else {
                flag = 2;                  //  некорректные . = 2
            }
        } else {
            if (x != 10) {
                *res = *res + x * (**str-'0');
                x = x / 10;
            } else {
                *res = *res * x + (**str-'0');
            }
        }
        (*str)++;
    }
    return flag;
}

int is_number(char c) {
    int res;
    if ((c >= '0' && c <= '9') || c == '.' || c == 'x')
        res = 1;
    else
        res = 0;
    return res;
}

int is_func(char c) {
    int res;
    if (c == 's' || c == 'S' || c == 'c' || c == 'C' ||
         c == 't' || c == 'T' || c == 'l' || c == 'L' || c == 'q') {
        res = 1;
    } else {
        res = 0;
    }
    return res;
}

int not_first_sym(char c) {
    int res;
    if (c == '*' || c == '/' || c == 'm' || c == ')' || c == '^') {
        res = 1;
    } else {
        res = 0;
    }
    return res;
}

int not_last_sym(char c) {
    int res;
    if (c == '(' || c == '.' || is_operator(c)) {
        res = 1;
    } else {
        res = 0;
    }
    return res;
}

int is_operator(char c) {
    int res;
    if (c == '+' || c == '-' || c == '*' || c == '/' ||
        c == '^' || c == 'm') {
        res = 1;
    } else {
        res = 0;
    }
    return res;
}

void push_stack_oper(char oper, char mas_oper[], double mas_num[], int *len, int *len_num) {
    if (oper == '(') {
        mas_oper[*len] = oper;
        *len += 1;
    } else {
        check_stack(oper, mas_oper, mas_num, len, len_num);
    }
}

int check_stack(char oper, char mas_oper[], double mas_num[], int *len, int *len_num) {
    int res = 0;
    polyn mas_oper_const[] = MAS_OPER_CONST;
    if (*len != 0) {
        int pr1 = 0, pr2 = 0;
        for (int i = 0; i < NUM_OF_OPER; i++) {
            if (mas_oper_const[i].oper == oper) pr1 = mas_oper_const[i].prioritet;
            if (mas_oper_const[i].oper == mas_oper[*len-1]) pr2 =  mas_oper_const[i].prioritet;
        }
        if (pr2 >= pr1 && oper != ')' && mas_oper[*len -1] != '(') {
            result_oper(oper, mas_oper, mas_num, len, len_num);
        } else if (oper == ')') {
            if (mas_oper[*len - 1] != '(') {
                result_oper(oper, mas_oper, mas_num, len, len_num);
            } else {
                mas_oper[*len - 1] = '\0';
                *len -= 1;
            }
        } else {
            mas_oper[*len] = oper;
            *len += 1;
        }
    } else {
        mas_oper[*len] = oper;
        *len += 1;
    }
    return res;
}

void push_stack_num(double oper, double mas_num[], int *len) {
    mas_num[*len] = oper;
    *len += 1;
}

int result_oper(char oper, char mas_oper[], double mas_num[], int *len, int *len_num) {
    int res = 0;
    switch (mas_oper[*len - 1]) {
        case '+':
            mas_num[*len_num - 2] = mas_num[*len_num - 2] + mas_num[*len_num - 1];
            edit_stack(mas_oper, mas_num, len_num, len);
            break;
        case '-':
            mas_num[*len_num - 2] = mas_num[*len_num - 2] - mas_num[*len_num - 1];
            edit_stack(mas_oper, mas_num, len_num, len);
            break;
        case '*':
            mas_num[*len_num - 2] = mas_num[*len_num - 2] * mas_num[*len_num - 1];
            edit_stack(mas_oper, mas_num, len_num, len);
            break;
        case '$':
            mas_num[*len_num - 2] = mas_num[*len_num - 2] * mas_num[*len_num - 1];
            edit_stack(mas_oper, mas_num, len_num, len);
            break;
        case '/':
            mas_num[*len_num - 2] = mas_num[*len_num - 2] / mas_num[*len_num - 1];
            edit_stack(mas_oper, mas_num, len_num, len);
            break;
        case 'm':
            mas_num[*len_num - 2] = fmod(mas_num[*len_num - 2], mas_num[*len_num - 1]);
            edit_stack(mas_oper, mas_num, len_num, len);
            break;
        case 'c':
            mas_num[*len_num - 1] = cos(mas_num[*len_num - 1]);
            edit_stack_trig(mas_oper, len);
            break;
        case 's':
            mas_num[*len_num - 1] = sin(mas_num[*len_num - 1]);
            edit_stack_trig(mas_oper, len);
            break;
        case '^':
            mas_num[*len_num - 2] = pow(mas_num[*len_num - 2], mas_num[*len_num - 1]);
            edit_stack(mas_oper, mas_num, len_num, len);
            break;
        case 't':
            mas_num[*len_num - 1] = tan(mas_num[*len_num - 1]);
            edit_stack_trig(mas_oper, len);
            break;
        case 'C':
            mas_num[*len_num - 1] = acos(mas_num[*len_num - 1]);
            edit_stack_trig(mas_oper, len);
            break;
        case 'S':
            mas_num[*len_num - 1] = asin(mas_num[*len_num - 1]);
            edit_stack_trig(mas_oper, len);
            break;
        case 'T':
            mas_num[*len_num - 1] = atan(mas_num[*len_num - 1]);
            edit_stack_trig(mas_oper, len);
            break;
        case 'q':
            mas_num[*len_num - 1] = sqrt(mas_num[*len_num - 1]);
            edit_stack_trig(mas_oper, len);
            break;
        case 'L':
            mas_num[*len_num - 1] = log10(mas_num[*len_num - 1]);
            edit_stack_trig(mas_oper, len);
            break;
        case 'l':
            mas_num[*len_num - 1] = log(mas_num[*len_num - 1]);
            edit_stack_trig(mas_oper, len);
            break;
        default:
            res = 1;
            break;
    }
    if (res == 0) push_stack_oper(oper, mas_oper, mas_num, len, len_num);
    return res;
}

void edit_stack(char mas_oper[], double mas_num[], int *len_num, int *len) {
    *len_num -= 1;
    mas_num[*len_num] = 0;
    mas_oper[*len - 1] = mas_oper[*len];
    mas_oper[*len] = '\0';
    *len -= 1;
}

void edit_stack_trig(char mas_oper[], int *len) {
    mas_oper[*len - 1] = mas_oper[*len];
    mas_oper[*len] = '\0';
    *len -= 1;
}
