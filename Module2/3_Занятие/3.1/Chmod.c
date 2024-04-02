#include "Chmod.h"
void Change_Access_rights_number(char *buffer2)
{
    if (buffer2[0] >= 'a' && buffer2[0] <= 'z' ||
        buffer2[0] == '-')
    {
        Access_rights_char(buffer2);
        return;
    }
    else
    {
        printf("Строка имела неверный формат!");
    }
}

void Access_rights_number(int num)
{
    int bin = 0, k = 1;

    printf("%o\n", num);

    while (num)
    {
        bin += (num % 2) * k;
        k *= 10;
        num /= 2;
    }
    printf("\n%d\n", bin);
}

void Access_rights_char(char *buffer2)
{
    int bin = 0, k = 1;
    int result = 0;

    int mask_flags_str[10];
    int mask_flags[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

    int j = 0;
    for (int i = 0; i < 9; i++)
    {
        if (buffer2[i] == 'r' && i % 3 == 0)
        {
            switch (i)
            {
            case 0:
                mask_flags_str[j] = S_IRUSR;
                break;
            case 3:
                mask_flags_str[j] = S_IRGRP;
                break;
            case 6:
                mask_flags_str[j] = S_IROTH;
                break;
            default:
                break;
            }
            j++;
            continue;
        }

        if (buffer2[i] == 'w' && (i - 1) % 3 == 0)
        {
            switch (i)
            {
            case 1:
                mask_flags_str[j] = S_IWUSR;
                break;
            case 4:
                mask_flags_str[j] = S_IWGRP;
                break;
            case 7:
                mask_flags_str[j] = S_IWOTH;
                break;
            default:
                break;
            }
            j++;
            continue;
        }

        if (buffer2[i] == 'x' && (i - 2) % 3 == 0)
        {
            switch (i)
            {
            case 2:
                mask_flags_str[j] = S_IXUSR;
                break;
            case 5:
                mask_flags_str[j] = S_IXGRP;
                break;
            case 8:
                mask_flags_str[j] = S_IXOTH;
                break;
            default:
                break;
            }
            j++;
            continue;
        }

        if (buffer2[i] == '-')
        {
            mask_flags_str[j] = 0;
            j++;
            continue;
        }
    }
    for (int i = 0; i < 9; ++i)
    {
        // Если бит установлен, увеличиваем счетчик на 1
        if (mask_flags_str[i] & mask_flags_str[i])
        {
            result += mask_flags_str[i];
        }
    }

    while (result)
    {
        bin += (result % 2) * k;
        k *= 10;
        result /= 2;
    }
    
    printf("Битовое представление права доступа: %d ", bin);
    printf("\n");
}

void Stat(char *path, struct stat *buf)
{
    int ret;
    int num_bit = 0;

    if ((ret = stat(path, buf)) != 0)
    {
        fprintf(stderr, "stat failure error: %d\n", ret);
        abort();
    }

    int result = 0;

    int mask_flags[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    for (int i = 0; i < 9; ++i)
    {
        // Если бит установлен, увеличиваем счетчик на 1
        if (buf->st_mode & mask_flags[i])
        {
            result += mask_flags[i];
        }
    }
    printf("\nПрава доступа в цифоровом представлении: %o\n", result);

    int bin = 0, k = 1;
    while (result)
    {
        bin += (result % 2) * k;
        k *= 10;
        result /= 2;
    }
    printf("\nБитовое представление права доступа: %d\n ", bin);

    printf("\nБуквенное представление права доступа: ");

    // Проверяем каждый бит прав доступа и выводим соответствующий символ
    printf((buf->st_mode & S_IRUSR) ? "r" : "-");
    printf((buf->st_mode & S_IWUSR) ? "w" : "-");
    printf((buf->st_mode & S_IXUSR) ? "x" : "-");
    printf((buf->st_mode & S_IRGRP) ? "r" : "-");
    printf((buf->st_mode & S_IWGRP) ? "w" : "-");
    printf((buf->st_mode & S_IXGRP) ? "x" : "-");
    printf((buf->st_mode & S_IROTH) ? "r" : "-");
    printf((buf->st_mode & S_IWOTH) ? "w" : "-");
    printf((buf->st_mode & S_IXOTH) ? "x" : "-");
}
void menu()
{
    printf("\n1 - Ввести права доступа в буквенном виде\n");
    printf("2 - Ввести права доступа в цифровом виде\n");
    printf("3 - Вывести биты прав доступа указанного файла\n");
    printf("4 - Изменить права доступа\n");
    return;
}

int main()
{
    struct stat buf;
    char buffer[256];
    char buffer2[10];
    int num = 0;
    char x;

    while (1)
    {
        fputs("\n1 - Ввести права доступа в буквенном виде\n", stdout);
        fputs("2 - Ввести права доступа в цифровом виде\n", stdout);
        fputs("3 - Вывести биты прав доступа указанного файла\n", stdout);
        fputs("4 - Изменить права доступа\n", stdout);
       scanf("%s",&x);
       getchar();
        switch (x)
        {
        case '1':
            fputs("Введите права доступа:", stdout);
            fgets(buffer2, sizeof(buffer2), stdin);
            if(strlen(buffer2) < 9){
                printf("строка введена некорректно!\n");
                break;
            }
            Access_rights_char(buffer2);
            break;
        case '2':
            fputs("Введите права доступа: ", stdout);
            scanf("%o", &num);
            getchar();
            Access_rights_number(num);
            break;
        case '3':
            fputs("Введите имя файла: ", stdout);
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                buffer[strlen(buffer) - 1] = '\0';
            }
            Stat(buffer, &buf);
            break;

        case '4':
            fputs("Введите артибуты прав доступа: ", stdout);
            fgets(buffer2, sizeof(buffer2), stdin);
            Access_rights_char(buffer2);
            break;
        default:
            printf("Некорректный выбор\n");
            break;
        }
    }
    return 0;
}