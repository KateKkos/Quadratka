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



enum TEST_ERRORS
{
    success,            //верны 2 корня
    failure_1,          //неверен 1ый корень, верен 2ой
    failure_2,          //неверен 2ой корень, верен 1ый
    total_failure       //неверны оба корня
};



struct test_data
{
    double a, b, c, x1_exp, x2_exp;
    int n_of_roots;
};

int do_correct_input(double* a, double* b, double* c);
int compare_double(double left_value, double right_value, char operation);
double sqrt_of_double(double num);
int solve_square(double a, double b, double c, double* x1, double* x2);
int solve_exactly_square(double a, double b, double c, double* x1, double* x2);
int solve_linear(double b, double c, double* x1);
int solve_and_check(double* x1, double* x2, double a, double b, double c);
int output_solutions(int sols_cnt, double x1, double x2);
void test_the_solver(void);
int test_this_values(struct test_data data, double* x1_test, double* x2_test);

int main ()
{
    printf("This is the square equation solver (ax^2 + bx + c = 0).\n\n");
    test_the_solver();


    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    int successed_input = -1;

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
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    int solutions_cnt_func = -2;

    if (compare_double(a, 0, 'e'))
    {
        printf("\nThis is the linear equation.\n");
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
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

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

        printf("\nPlease, enter the coefficients again. "
                                "They must be floating point numbers (# for exit): ");

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
    assert(isfinite(sols_cnt));
    assert(isfinite(x1));
    assert(isfinite(x2));

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
    assert(isfinite(b));
    assert(isfinite(c));

    int solutions_cnt_func = -2;

    if (compare_double(b, 0, 'n'))
    {
        *x1 = -c/b;
        solutions_cnt_func = 1;
    }
    else if (compare_double(b, 0, 'e') && compare_double(c, 0, 'n'))
    {
        *x1 = NAN;
        solutions_cnt_func = 0;
    }
    else if (compare_double(b, 0, 'e') && compare_double(c, 0, 'e'))
    {
        *x1 = NAN;
        solutions_cnt_func = -1;
    }

    return solutions_cnt_func;
}



int solve_and_check(double* x1, double* x2, double a, double b, double c)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

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
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(a != 0);

    int solutions_cnt_func = -2;

    double D = b*b - 4*a*c, sqrt_of_D = -1;
    if (!compare_double(D, 0, 'l'))
    {
        sqrt_of_D = sqrt_of_double(D);
    }

    if (compare_double(D, 0, 'm'))
    {
        *x1 = ( sqrt_of_D - b)/(2*a);
        *x2 = (-sqrt_of_D - b)/(2*a);
        solutions_cnt_func = 2;
    }
    else if (compare_double(D, 0, 'e'))
    {
        *x1 = -b/(2*a);
        *x2 = *x1;
        solutions_cnt_func = 1;
    }
    else if (compare_double(D, 0, 'l'))
    {
        *x1 = *x2 = NAN;
        solutions_cnt_func = 0;
    }

    return solutions_cnt_func;
}



double sqrt_of_double(double num)
{
    //printf("\n%f\n", num);
    assert(isfinite(num));
    assert(compare_double(num + 1e-5, 0, 'm') || compare_double(num + 1e-5, 0, 'e'));

    return sqrt(num);
}



int compare_double(double left_value, double right_value, char operation)
{
//    operation:
//              m - левое значение больше правого (more)
//              l - левое значение меньше правого (less)
//              e - значения равны (equal)
//              n - значения не равны (not equal)

    assert(operation == 'e' || operation == 'm' || operation == 'l' || operation == 'n');

    const double epsilon = 1e-5;
    double lft_p_e = left_value + epsilon, lft_m_e = left_value - epsilon;
    double rt_p_e = right_value + epsilon, rt_m_e = right_value - epsilon;


    if (isfinite(left_value) && isfinite(right_value))
    {
        if (operation == 'e')
        {
            if ((lft_p_e >=  rt_m_e && lft_p_e <= rt_p_e)  ||
                ( rt_p_e >= lft_m_e &&  rt_p_e <= lft_p_e))
            {
                return 1;
            }
            return 0;
        }
        else if (operation == 'n')
        {
            if (compare_double(left_value, right_value, 'm') ||
                compare_double(left_value, right_value, 'l'))
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
    }
    else
    {
        if (operation == 'e')
        {
            if (!(isfinite(left_value)) && !(isfinite(right_value)))
                {
                    return 1;
                }
            return 0;
        }
        return 0;
    }

    return 0;
}



void test_the_solver(void)
{
    const int n_of_tests = 10;
    int i = 0;

    struct test_data data[n_of_tests];
    data[0] = (struct test_data) { 7.1,  3.5, -2,    0.33871, -0.83166, 2};
    data[1] = (struct test_data) { 0,    0,    0,    NAN,      NAN,    -1};
    data[2] = (struct test_data) { 7.5,  4.3,  0,    0,       -0.57333, 2};
    data[3] = (struct test_data) { 8,    0,   -5,    0.79057, -0.79057, 2};
    data[4] = (struct test_data) { 0,    7,    3.5, -0.5,     -0.5,     1};
    data[5] = (struct test_data) { 0,    0,    5.5,  NAN,      NAN,     0};
    data[6] = (struct test_data) { 0,    7,    0,    0,        0,       1};
    data[7] = (struct test_data) {-7,    0,    0,    0,        0,       1};
    data[8] = (struct test_data) { 1e-5, 1e-5, 1e-5, NAN,      NAN,    -1};
    data[9] = (struct test_data) { 1,    0,    4,    NAN,      NAN,     0};


    for (i = 0; i < n_of_tests; i++)
    {
        double x1_test = 0, x2_test = 0;

        int result = test_this_values(data[i], &x1_test, &x2_test);

        switch (result)
        {
            case success: printf("Test %d is successed.\n", i+1);
                        break;
            case failure_1: printf("Test %d is failured: the 1st root is %.5f, but expected %f.\n",
                                    i+1, x1_test, data[i].x1_exp);
                        break;
            case failure_2: printf("Test %d is failured: the 2nd root is %.5f, but expected %f.\n",
                                    i+1, x2_test, data[i].x2_exp);
                        break;
            case total_failure:printf("Test %d is failured: the roots are %.5f and %.5f, but expected %f and %f.\n",
                                    i+1, x1_test, x2_test, data[i].x1_exp, data[i].x2_exp);
                        break;
            default: printf("Smth is wrong with \"test_this_value\" function.\n");
        }
    }
}




int test_this_values(struct test_data data, double* x1_test, double* x2_test)
{
    solve_square(data.a, data.b, data.c, x1_test, x2_test);

    if (compare_double(*x1_test, data.x1_exp, 'e')
                                            && compare_double(*x2_test, data.x2_exp, 'e'))
    {
        return success;
    }
    else if (compare_double(*x1_test, data.x1_exp, 'e')
                                            && !(compare_double(*x2_test, data.x2_exp, 'e')))
    {
        return failure_2;
    }
    else if (!(compare_double(*x1_test, data.x1_exp, 'e'))
                                            && compare_double(*x2_test, data.x2_exp, 'e'))
    {
        return failure_1;
    }
    else if (!(compare_double(*x1_test, data.x1_exp, 'e'))
                                            && !(compare_double(*x2_test, data.x2_exp, 'e')))
    {
        return total_failure;
    }

    return -1;
}

