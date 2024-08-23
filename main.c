#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

enum INPUT_ERRORS
{
    input_error,                 // return 0 - ошибка ввода
    end_the_program,             // return 1 - завершить программу
    suc_input_next_input_exp,    // return 2 - ввод успешный, ожидается следующий ввод
    suc_input_end_the_program,   // return 3 - ввод успешный,
                                 // завершение программы после обработки ввода
    error_in_input_func          // return 4 - ошибка в функции ввода
};

int do_correct_input(double* a, double* b, double* c);
int compare_double(double left_value, double right_value, char operation);
double sqrt_of_double(double num);
int solve_square(double a, double b, double c, double* x1, double* x2);
int solve_exactly_square(double a, double b, double c, double* x1, double* x2);
int solve_linear(double b, double c, double* x1);
int solve_and_check(double* x1, double* x2, double a, double b, double c);
int output_solutions(int sols_cnt, double x1, double x2);

int main ()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    int successed_input = -1;

    printf("This is the square equation solver (ax^2 + bx + c = 0).\n\n");

    do
    {
        printf("Enter coefficients a, b and c in form \"a b c\" or # for exit: ");
        successed_input = do_correct_input(&a, &b, &c);

        switch (successed_input)
        {
            case input_error:
            case end_the_program:
            case error_in_input_func:
                return 0;

            case suc_input_next_input_exp:
                solve_and_check(&x1, &x2, a, b, c);
                break;

            case suc_input_end_the_program:
                solve_and_check(&x1, &x2, a, b, c);

                printf("\nFinished with #.\n");
                return 0;

            default:
                printf("\nSomething went wrong. Run the program again.\n");
                return 0;
        }
    }
    while (1);

    printf("\nThe program must not be here. Check the main function and run the program again.\n");
    return 0;
}



int solve_square(double a, double b, double c, double* x1, double* x2)
{
    assert(x1 != NULL && x2 != NULL);
    assert(isfinite(a) && isfinite (b) && isfinite(c));

    int solutions_cnt_func = -2;

    if (compare_double(a, 0, 'e'))
    {
        solutions_cnt_func = solve_linear(b, c, x1);
        *x2 = *x1;
    }
    else
    {
        solutions_cnt_func = solve_exactly_square(a, b, c, x1, x2);
    }

    return solutions_cnt_func;
}



int do_correct_input(double* a, double* b, double* c)
{
    assert(a != NULL && b != NULL && c != NULL);

    int ch = '$', scanf_success = 0;

    while (1)
    {
        scanf_success = scanf("%lf %lf %lf", a, b, c);

        if ((ch = getchar()) == EOF)
        {
            printf("\nInput error!\n");
            return input_error;
        }
        else if (ch == '#' && scanf_success != 3)
        {
            printf("\nFinished with #.\n");
            return end_the_program;
        }
        else if (ch == '#' && scanf_success == 3)
        {
            return suc_input_end_the_program;
        }
        else if (ch == '\n' && scanf_success == 3)
        {
            return suc_input_next_input_exp;
        }

        printf("\nPlease, enter the coefficients again. They must be floating point numbers (# for exit): ");

        while ((ch = getchar()) != '\n')
        {
            if (ch == EOF)
            {
                  printf("\nInput error!\n");
                  return input_error;
            }

            if (ch == '#')
            {
                printf("\nFinished with #.\n");
                return end_the_program;
            }
        }
    }

    printf("\nError in function \"do_correct_input\".\n");
    return error_in_input_func;
}



int output_solutions(int sols_cnt, double x1, double x2)
{
    assert(isfinite(sols_cnt) && isfinite(x1) && isfinite(x2));

    int success = 1;

    switch (sols_cnt)
        {
            case 0: printf("The equation has no solutions.\n\n");
                break;
            case 1: printf("The equation has 1 solution: %.2lf.\n\n", x1);
                break;
            case 2: printf("The equation has 2 solutions: %.2lf and %.2lf.\n\n", x1, x2);
                break;
            case -1: printf("The equation has an infinite number of solutions.\n\n");
                break;
            default: success = 0;
        }

    return success;
}



int solve_linear(double b, double c, double* x1)
{
    assert(x1 != NULL);
    assert(isfinite(b) && isfinite(c));

    printf("\nThis is the linear equation.\n");
    int solutions_cnt_func = -2;

    if (compare_double(b, 0, 'n'))
    {
        *x1 = -c/b;
        solutions_cnt_func = 1;
    }
    else if (compare_double(b, 0, 'e') && compare_double(c, 0, 'n'))
    {
        solutions_cnt_func = 0;
    }
    else if (compare_double(b, 0, 'e') && compare_double(c, 0, 'e'))
    {
        solutions_cnt_func = -1;
    }

    return solutions_cnt_func;
}



int solve_and_check(double* x1, double* x2, double a, double b, double c)
{
    assert(x1 != NULL && x2 != NULL);
    assert(isfinite(a) && isfinite (b) && isfinite(c));

    int solutions_cnt = -1, successed_output = -1;

    *x1 = 0, *x2 = 0;
    solutions_cnt = solve_square(a, b, c, x1, x2);
    successed_output = output_solutions(solutions_cnt, *x1, *x2);

    if (successed_output != 1)
    {
        printf("\nSomething went wrong. Run the program again.\n");
        return 0;
    }

    return 0;
}



int solve_exactly_square(double a, double b, double c, double* x1, double* x2)
{
    assert(x1 != NULL && x2 != NULL);
    assert(isfinite(a) && isfinite (b) && isfinite(c));

    int solutions_cnt_func = -2;

    double D = b*b - 4*a*c, sqrt_of_D = sqrt_of_double(D);

    if (compare_double(D, 0, 'm'))
    {
        *x1 = ( sqrt_of_D - b)/(2*a);
        *x2 = (-sqrt_of_D - b)/(2*a);
        solutions_cnt_func = 2;
    }
    else if (compare_double(D, 0, 'e'))
    {
        *x1 = (sqrt_of_D - b)/(2*a);
        *x2 = *x1;
        solutions_cnt_func = 1;
    }
    else
    {
        solutions_cnt_func = 0;
    }

    return solutions_cnt_func;
}



double sqrt_of_double(double num)
{
    assert(isfinite(num));

    return sqrt(num);
}



int compare_double(double left_value, double right_value, char operation)
{
//    operation:
//              m - левое значение больше правого (more)
//              l - левое значение меньше правого (less)
//              e - значения равны (equal)
//              n - значения не равны (not equal)

    assert(isfinite(left_value) && isfinite(right_value));
    assert(operation == 'e' || operation == 'm' || operation == 'l' || operation == 'n');

    double epsilon = 1e-6;
    double lft_p_e = left_value + epsilon, lft_m_e = left_value - epsilon;
    double rt_p_e = right_value + epsilon, rt_m_e = right_value - epsilon;

    if (operation == 'e')
    {
        if ((lft_p_e >= rt_m_e && lft_p_e <= rt_p_e) || (rt_p_e >= lft_m_e && rt_p_e <= lft_p_e))
        {
            return 1;
        }
        return 0;
    }
    else if (operation == 'n')
    {
        if (compare_double(left_value, right_value, 'm') || compare_double(left_value, right_value, 'l'))
        {
            return 1;
        }
        return 0;
    }
    else if (operation == 'm')
    {
        if (lft_m_e >= rt_p_e)
        {
            return 1;
        }
        return 0;
    }
    else if (operation == 'l')
    {
        if (lft_p_e <= rt_m_e)
        {
            return 1;
        }
        return 0;
    }

    return 0;
}



