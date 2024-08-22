#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int output_solutions(int sols_cnt, double x1, double x2);
int do_correct_input(double* a, double* b, double* c);
int solve_square(double a, double b, double c, double* x1, double* x2);
int solve_linear(double b, double c, double* x1);

int main ()
{
    double a = 0, b = 0, c = 0;
    int solutions_cnt = -1, successed_input = -1, successed_output = -1;

    printf("This is the square equation solver (ax^2 + bx + c = 0).\n\n");

    do
    {
        printf("Enter coefficients a, b and c in form \"a b c\" or # for exit: ");
        successed_input = do_correct_input(&a, &b, &c);

        if (successed_input == 0 || successed_input == 1 || successed_input == 4)
            return 0;
        else if (successed_input != 2 && successed_input != 3)
        {
            printf("\nSomething went wrong. Run the program again.\n");
            return 0;
        }

        double x1 = 0, x2 = 0;
        solutions_cnt = solve_square(a, b, c, &x1, &x2);
        successed_output = output_solutions(solutions_cnt, x1, x2);

        if (successed_output != 1)
        {
            printf("\nSomething went wrong. Run the program again.\n");
            return 0;
        }

        if (successed_input == 3)
        {
            printf("\nFinished with #.\n");
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

    double D = -1;
    int solutions_cnt_func = -2;

    if (a == 0)
    {
        solutions_cnt_func = solve_linear(b, c, x1);
        *x2 = *x1;
    }
    else
    {
        D = b*b - 4*a*c;
        if (D > 0)
        {
            *x1 = (sqrt(D) - b)/(2*a);
            *x2 = (-sqrt(D) - b)/(2*a);
            solutions_cnt_func = 2;
        }
        else if (D == 0)
        {
            *x1 = (sqrt(D) - b)/(2*a);
            *x2 = *x1;
            solutions_cnt_func = 1;
        }
        else
            solutions_cnt_func = 0;
    }

    return solutions_cnt_func;
}



int do_correct_input(double* a, double* b, double* c)
{
    //retrun 0 - ошибка ввода
    //return 1 - завершить программу
    //return 2 - ввод успешный, ожидается следующий ввод
    //return 3 - ввод успешный, завершение программы после обработки ввода
    //return 4 - ошибка в функции ввода

    assert(a != NULL && b != NULL && c != NULL);

    int ch = '$', scanf_success = 0;

    while (1)
    {
        scanf_success = scanf("%lf %lf %lf", a, b, c);

        if ((ch = getchar()) == EOF)
        {
            printf("\nInput error!\n");
            return 0;
        }
        else if (ch == '#' && scanf_success != 3)
        {
            printf("\nFinished with #.\n");
            return 1;
        }
        else if (ch == '#' && scanf_success == 3)
            return 3;
        else if (ch == '\n' && scanf_success == 3)
            return 2;

        printf("\nPlease, enter the coefficients again. They must be floating point numbers (# for exit): ");

        while ((ch = getchar()) != '\n')
        {
            if (ch == EOF)
            {
                  printf("\nInput error!\n");
                  return 0;
            }

            if (ch == '#')
            {
                printf("\nFinished with #.\n");
                return 1;
            }
        }
    }

    printf("\nError in function \"do_correct_input\".\n");
    return 4;
}



int output_solutions(int sols_cnt, double x1, double x2)
{
    int success = -1;

    switch (sols_cnt)
        {
            case 0: printf("The equation has no solutions.\n\n");
                success = 1;
                break;
            case 1: printf("The equation has 1 solution: %.2lf.\n\n", x1);
                success = 1;
                break;
            case 2: printf("The equation has 2 solutions: %.2lf and %.2lf.\n\n", x1, x2);
                success = 1;
                break;
            case -1: printf("The equation has an infinite number of solutions.\n\n");
                success = 1;
                break;
            default: success = 0;
        }

    return success;
}



int solve_linear(double b, double c, double* x1)
{
    assert(x1 != NULL);

    printf("\nThis is the linear equation.\n");
    int solutions_cnt_func = -2;

    if (b != 0 && c != 0)
    {
        *x1 = -c/b;
        solutions_cnt_func = 1;
    }
    else if (b != 0 && c == 0)
    {
        *x1 = 0;
        solutions_cnt_func = 1;
    }
    else if (b == 0 && c != 0)
        solutions_cnt_func = 0;
    else if (b == 0 && c == 0)
        solutions_cnt_func = -1;

    return solutions_cnt_func;
}



