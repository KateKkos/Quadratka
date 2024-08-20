#include <stdio.h>
#include <math.h>

int squareSolve(double a, double b, double c, double* x1, double* x2);
int main ()
{
    double a, b, c;
    int solutions_cnt;
    a = b = c = 0;

    printf("This is the square equation solver (ax^2 + bx + c = 0).\n");
    printf("Enter coefficients a, b and c in form \"a b c\" or \"0 0 0\" for exit: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    while (!(a == 0 && b == 0 && c == 0))
    {
        double x1, x2;
        solutions_cnt = squareSolve(a, b, c, &x1, &x2);
        switch (solutions_cnt)
        {
            case 0: printf("The equation has no solutions.\n\n");
                break;
            case 1: printf("The equation has 1 solution: %.2lf.\n\n", x1);
                break;
            case 2: printf("The equation has 2 solutions: %.2lf and %.2lf.\n\n", x1, x2);
                break;
        }

        printf("Enter coefficients a, b and c or \"0 0 0\" for exit: ");
        scanf("%lf %lf %lf", &a, &b, &c);
    }

    printf("Finished!\n");
    return 0;
}

int squareSolve(double a, double b, double c, double* x1, double* x2)
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
