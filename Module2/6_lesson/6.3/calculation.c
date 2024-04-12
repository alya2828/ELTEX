#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


int main(int argc, char **argv) {

    void *plus_lib = dlopen("./plus.so", RTLD_LAZY);
    void *minus_lib = dlopen("./minus.so", RTLD_LAZY);
    void *division_lib = dlopen("./division.so", RTLD_LAZY);
    void *multiplication_lib = dlopen("./multiplication.so", RTLD_LAZY);
    if (!plus_lib || !minus_lib || !division_lib || !multiplication_lib) {
        fprintf(stderr, "Не удалось загрузить одну или несколько библиотек\n");
        exit(1);
    }

    // Получаем указатели на функции
    void (*plus_func)(double, double) = dlsym(plus_lib, "plus");
    void (*minus_func)(double, double) = dlsym(minus_lib, "minus");
    void (*division_func)(double, double) = dlsym(division_lib, "division");
    void (*multiplication_func)(double, double) = dlsym(multiplication_lib, "multiplication");

    if (!plus_func || !minus_func || !division_func || !multiplication_func ) {
        fputs (dlerror(), stderr);
        fprintf(stderr, "Не удалось получить указатель на одну или несколько функций\n");
        dlclose(plus_lib);
        dlclose(minus_lib);
        dlclose(division_lib);
        dlclose(multiplication_lib);
        exit(1);
    }

    double a, b;
    int x;

    while (1) {
         
        printf("Введите два числа\n");
        scanf("%lf %lf", &a, &b);
         printf("Меню \n");
    printf("1 - Сложение\n");
    printf("2 - Вычетание\n");
    printf("3 - Деление\n");
    printf("4 - Умножение\n");
        scanf("%d", &x);

        switch (x) {
            case 1:
                plus_func(a, b);
                break;
            case 2:
                minus_func(a, b);
                break;
            case 3:
                division_func(a, b);
                break;
            case 4:
                multiplication_func(a, b);
                break;
            default:
                printf("Некорректный выбор\n");
        }
    }

    // Закрываем библиотеки
    dlclose(plus_lib);
    dlclose(minus_lib);
    dlclose(division_lib);
    dlclose(multiplication_lib);

    return 0;
}
