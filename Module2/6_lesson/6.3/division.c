#include <stdio.h>
#include <stdlib.h>
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