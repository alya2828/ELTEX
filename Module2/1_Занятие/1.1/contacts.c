#include "contacts.h"

void menu()
{
    printf("\n Меню: \n");
    printf("1 - Добавить контакт\n");
    printf("2 - Вывести контакты\n");
    printf("3 - Удалить контакт\n");
    printf("4 - Изменить контакт\n");
    printf("Выберите действие: ");
    return;
}

void Add(Person contact[], int *num)
{
    int count;
    printf("Введите имя:");
    fgets(contact[*num].Name, MAX_LENGTH, stdin);

    int x = strlen(contact[*num].Name);

    while (x <= 1)
    {
        printf("Введите имя: ");
        fgets(contact[*num].Name, MAX_LENGTH, stdin);
        x = strlen(contact[*num].Name);
    }

    do
    {
        printf("Введите фамилию: ");
        fgets(contact[*num].LastName, MAX_LENGTH, stdin);
        x = strlen(contact[*num].LastName);
    } while (x <= 1);
    printf("Введите должность:");
    fgets(contact[*num].Work.Post, MAX_LENGTH, stdin);
    printf("Введите место работы: ");
    fgets(contact[*num].Work.Place_work, MAX_LENGTH, stdin);

    printf("Введите Email: ");
    fgets(contact[*num].ContactInfo.Email, MAX_LENGTH, stdin);

    for (int i = 0; i < MAX; i++)
    {
        strcpy(contact[*num].ContactInfo.Number[i], "");

        strcpy(contact[*num].Profile.Social_networks[i],"");

        strcpy(contact[*num].Profile.Profiles_messengers[i],"");
    }

    count = 0;
    char buf[MAX_LENGTH];
    while (count < MAX)
    {
        printf("Введите номер телефона %d ", count + 1);
        fgets(buf, MAX_LENGTH, stdin);
        if (strlen(buf) < 2){
            break;        
        }
        if (strlen(buf) < 10){
            printf("Неправильно записан номер\n");
            continue;        
        }
        strcpy(contact[*num].ContactInfo.Number[count], buf);

        count++;
    }

    count = 0;
    while (count < MAX)
    {
        printf("Введите ссылки на профиль %d ", count + 1);

        fgets(buf, MAX_LENGTH, stdin);
        if (strlen(buf) < 2)
            break;
        strcpy(contact[*num].Profile.Social_networks[count], buf);
        count++;
    }

    count = 0;
    while (count < MAX)
    {
        printf("Введите профили на мессенджеры %d ", count + 1);
        fgets(buf, MAX_LENGTH, stdin);
        if (strlen(buf) < 2)
            break;
        strcpy(contact[*num].Profile.Profiles_messengers[count], buf);

        count++;
    }

    (*num)++;
}

void Delete(Person contact[], int *num)
{
    printf("Укажите какой контакт удалить:");
    int x;
    scanf("%d", &x);
    getchar();

    // Перемещаем все контакты после удаленного на одну позицию вперед
    for (int i = x - 1; i < *num - 1; i++)
    {
        contact[i] = contact[i + 1];
    }

    (*num)--;

    printf("Контакт успешно удален\n");
}

void Print(Person contact[], int *num)
{

    printf("Список контактов:\n");
    for (int i = 0; i < *num; i++)
    {
        printf("Контакт %d\n\n", i + 1);
        printf("Имя: %s\n", contact[i].Name);
        printf("Фамилия: %s\n", contact[i].LastName);
        printf("Должность: %s\n", contact[i].Work.Post);
        printf("Место работы: %s\n", contact[i].Work.Place_work);
        printf("Email: %s\n", contact[i].ContactInfo.Email);

        for (int j = 0; j < MAX; j++)
        {
            if (strlen(contact[i].ContactInfo.Number[j]) < 2)
                break;
            printf("Номер телефона: %s\n", contact[i].ContactInfo.Number[j]);
        }
        
        for (int j = 0; j < MAX; j++)
        {
            if (strlen(contact[i].Profile.Social_networks[j]) < 2)
                break;
            printf("Ссылки на страницы: %s\n", contact[i].Profile.Social_networks[j]);
            
        }
        
        for (int j = 0; j < MAX; j++)
        {
            if (strlen(contact[i].Profile.Profiles_messengers[j]) < 2)
                break;
            printf("Профили в мессенджерах: %s\n", contact[i].Profile.Profiles_messengers[j]);
        }
    }
}

void Move(Person contact[], int *num)
{
    int x;
    int p;
    int index;

    printf("Введите контакт, который необходимо изменить:");
    scanf("%d", &x);
    getchar();
    if (x < 1 || x > *num)
    {
        printf("Упс, такого контакта нет! Попробуй еще раз n");
        scanf("%d", &x); 
        getchar();
    }
    printf("Введите, что необхдимо изменить\n 1 - Имя\n 2 - Фамилия\n");
    scanf("%d", &p);
    getchar();

    index = x - 1;

    if (p == 1)
    {
        printf("Введите имя: ");
        fgets(contact[index].Name, sizeof(contact[index].Name), stdin);
        printf("Имя измененно!");
    }

    if (p == 2)
    {
        printf("Введите фамилию: ");
        scanf("%s", contact[index].LastName);
        getchar();
        printf("Фамилия успешно изменина!");
    }
}

int main()
{
    Person contact[160];
    int num = 0;
    int x;

    while (1)
    {
        menu();
        scanf("%d", &x);
        getchar();

        switch (x)
        {
        case 1:
            Add(contact, &num);
            break;
        case 2:
            Print(contact, &num);
            break;
        case 3:
            Delete(contact, &num);
            break;
        case 4:
            Move(contact, &num);
            break;
        default:
            printf("Некорректный выбор\n");
            break;
        }
    }

    return 0;
}
