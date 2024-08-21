#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void output_solutions(int sols_cnt, double* x1, double* x2, double* a, double* b, double* c);
void do_correct_input(double* a, double* b, double* c);
int solve_square(double a, double b, double c, double* x1, double* x2);

int main ()
{
    double a = 0, b = 0, c = 0;
    int solutions_cnt = 0;

    printf("This is the square equation solver (ax^2 + bx + c = 0).\n\n");
    printf("Enter coefficients a, b and c in form \"a b c\" or # for exit: ");
    do_correct_input(&a, &b, &c);

    while (1)
    {
        double x1, x2;
        solutions_cnt = solve_square(a, b, c, &x1, &x2);
        output_solutions(solutions_cnt, &x1, &x2, &a, &b, &c);

        printf("Enter coefficients a, b and c or # for exit: ");
        do_correct_input(&a, &b, &c);
    }

    printf("\nSuccessfully finished!\n");
    return 0;
}



int solve_square(double a, double b, double c, double* x1, double* x2)
{
    double D;
    int solutions_cnt_func;

    if (a == 0)
    {
        if (b != 0 && c != 0)
        {
            *x1 = -c/b;
            *x2 = *x1;
            solutions_cnt_func = 1;
        }
        else if (b != 0 && c == 0)
        {
            *x1 = 0;
            *x2 = *x1;
            solutions_cnt_func = 1;
        }
        else if (b == 0 && c != 0)
            solutions_cnt_func = 0;
        else if (b == 0 && c == 0)
            solutions_cnt_func = -1;
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



void do_correct_input(double* a, double* b, double* c)
{
    int ch;
    while (scanf("%lf %lf %lf", a, b, c) != 3)
    {
        if ((ch = getchar()) == EOF)
        {
            printf("\nInput error! Run the programm again 1.\n");
            exit(EXIT_FAILURE);
        }

        else if (ch == '#')
            {
                printf("\nSuccessfully finished!\n");
                exit(EXIT_SUCCESS);
            }

        printf("\nPlease, enter the coefficients again. They must be floating point numbers (# for exit): ");
        while ((ch = getchar()) != '\n')
        {
            if (ch == EOF)
            {
                  printf("\nInput error! Run the programm again 2.\n");
                  exit(EXIT_FAILURE);
            }

            if (ch == '#')
            {
                printf("\nSuccessfully finished!\n");
                exit(EXIT_SUCCESS);
            }

        }
    }
}



void output_solutions(int sols_cnt, double* x1, double* x2, double* a, double* b, double* c)
{
    switch (sols_cnt)
        {
            case 0: printf("The equation %.2lfx^2 + %.2lfx + %.2lf = 0 has no solutions.\n\n",
                        *a, *b, *c);
                break;
            case 1: printf("The equation %.2lfx^2 + %.2lfx + %.2lf = 0 has 1 solution: %.2lf.\n\n",
                        *a, *b, *c, *x1);
                break;
            case 2: printf("The equation %.2lfx^2 + %.2lfx + %.2lf = 0 has 2 solutions: %.2lf and %.2lf.\n\n",
                        *a, *b, *c, *x1, *x2);
                break;
            case -1: printf("The equation %.2lfx^2 + %.2lfx + %.2lf = 0 has an infinite number of solutions.\n\n",
                                    *a, *b, *c);

        }
}
