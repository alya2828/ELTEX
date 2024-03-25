#include "calculation.h"

double plus(double a, double b)
{
    return a + b;
}

double minus(double a, double b)
{
    return a - b;
}

double *division(double a, double b, double *result)
{
    if (b == 0)
        return NULL;

    *result = a / b;
    return result;
}

double multiplication(double a, double b)
{
    return a * b;
}

void menu()
{
    printf("Меню \n");
    printf("1 - Сложение\n");
    printf("2 - Вычетание\n");
    printf("3 - Деление\n");
    printf("4 - умножение\n");
}

int main()
{
    int x;
    double a, b, result;
    while (1)
    {
        printf("Введите два числа\n");
        scanf("%lf %lf", &a, &b);
        menu();
        printf("Выберите дейстие\n");
        scanf("%d", &x);
        {
            switch (x)
            {
            case 1:
                printf(" Результат сложения= %g\n", plus(a, b));
                break;
            case 2:
                printf(" Результат вычетания= %g\n", minus(a, b));
                break;
            case 3:
                if (division(a, b, &result) == NULL)
                {
                    printf("На ноль делить нельзя\n");
                    break;
                }
                printf(" Результат деления= %g\n", *division(a, b, &result));
                break;
            case 4:
                printf(" Результат умножения= %g\n", multiplication(a, b));
                break;
            default:
                break;
            }
        }
    }
}