#include "calculation2.h"
void plus(double a, double b)
{
    printf ("a + b = %lf \n", a +b);
}

void minus(double a, double b)
{
    printf ("a - b = %lf \n", a - b);
}

void division(double a, double b)
{
    double raz;
    if(b == 0){
        printf("Деление на ноль запрещенно\n");
    }
    else{
        raz = a / b;
        printf("a / b = %lf \n", raz);
    }
}

void multiplication(double a, double b)
{
    printf ("a * b = %lf \n", a * b);
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
{   int x;
    double a, b;

    void (*operation[4])(double, double) = {plus, minus,division, multiplication};
    while (1)
    {
    printf("Введите два числа\n");
    scanf("%lf %lf", &a, &b);
    menu();
    scanf("%d", &x);

    if (x >= 1 && x <= 4) {
            operation[x - 1](a, b);
        } else {
            printf("Некорректный выбор\n");
        }
}
}