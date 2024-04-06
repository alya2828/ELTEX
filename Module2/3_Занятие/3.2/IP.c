#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

__uint32_t matchingIP(__uint32_t Net_Dst, __uint32_t *Net_Src, int num)
{
    int counter = 0;
    __uint32_t result;
   
    for (int i = 0; i < num; i++)
    {
      
        result =  Net_Src[i] ^ Net_Dst  ;
        if (result == 0)
        {
            counter++;
        }
        
    }

    return counter;
}

__uint32_t compareIP(char *IP_Dst,__uint32_t mask) // преобразование строки в 32 битное представление
{
    __uint32_t ip = 0;
    int octet_value = 0;
    int octet_count = 0;
    char *p;
    char *token = strtok((char *)IP_Dst, ".");
    while (token != NULL && octet_count < 4)
    {
        octet_value = strtol(token, &p, 10);
        if (octet_value < 0 || octet_value > 255)
            printf("Некорректно введен октет IP\n");
        ip = (ip << 8) | octet_value;
        token = strtok(NULL, ".");
        octet_count++;
    }
    printf("IP-адрес в десятичной системе: %u.%u.%u.%u\n",
           (ip >> 24) & 0xFF, (ip >> 16) & 0xFF,
           (ip >> 8) & 0xFF, ip & 0xFF);
    __uint32_t Net_Dst = ip & mask;
    printf("Сопоставленный адрес сети: %u.%u.%u.%u\n",
           (Net_Dst >> 24) & 0xFF, (Net_Dst >> 16) & 0xFF,
           (Net_Dst >> 8) & 0xFF, Net_Dst & 0xFF);
           

    return Net_Dst;
}
__uint32_t *compareNet_Src(__uint32_t mask, int num, __uint32_t *IP_Src, __uint32_t *Net_Src)//узнать можно ли сюда передпть маску, например сделать ее в майн 
{
     
    Net_Src = malloc(sizeof(__uint32_t) * num);
    for (int i = 0; i < num; i++)
    {
        Net_Src[i] = IP_Src[i] & mask;

    }
    return Net_Src;
}

__uint32_t *generation(int num)
{
    srand(time(NULL));
    __uint32_t *IP_Src = malloc(num * sizeof(__uint32_t)); // Выделяем память под массив
    __uint32_t ip_src = 0;
    if (IP_Src == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }

    for (int i = 0; i < num; i++)
    {
        ip_src = 0;
        for (int j = 0; j < 4; j++)
        {
            ip_src = (ip_src << 8) | (rand() % 256);
        }
        IP_Src[i] = ip_src;
       
    }

    return IP_Src;
}

int main()
{ 
    char IP_Dst[20];
    char Mask[20];
    int Quantity;

    __uint32_t *IP_Src, Net_Dst, *Net_Src = NULL;
    fputs("\n1 - Ведите IP шлюза\n", stdout);
    fgets(IP_Dst, sizeof(IP_Dst), stdin);

    fputs("\n1 - Ведите Маску\n", stdout);
    fgets(Mask, sizeof(Mask), stdin);
    __uint32_t mask = 0;
    int octet_value = 0;
    int octet_count = 0;
    char *p;
    octet_count = 0;
    char *token  = strtok((char *)Mask, ".");
    p = NULL;
    while (token != NULL && octet_count < 4)
    {

        octet_value = strtol(token, &p, 10);
        if (octet_value < 0 || octet_value > 255)
            printf("Некорректно введен октет IP\n");
        mask = (mask << 8) | octet_value;
        token = strtok(NULL, ".");
        octet_count++;
    }

    printf("Маски в десятичной системе: %u.%u.%u.%u\n",
           (mask >> 24) & 0xFF, (mask >> 16) & 0xFF,
           (mask >> 8) & 0xFF, mask & 0xFF);
    

    fputs("\n1 - Ведите количесвто пакетов\n", stdout);
    scanf("%d", &Quantity);

    IP_Src = generation(Quantity);
    Net_Dst = compareIP(IP_Dst, mask);
    Net_Src = compareNet_Src(mask, Quantity,IP_Src,Net_Src);


    printf(" Количесвто  %d\n", matchingIP(Net_Dst, Net_Src, Quantity));

    return 0;
}