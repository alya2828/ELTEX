#include "Exampl.h"


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

int CmpContactsLessOrEq(Person *vall, Person *valr) {
    int res1 = strcmp(vall->Name, valr->Name);
    if (res1 < 0 || res1 > 0) return res1;
    return strcmp(vall->Name, valr->Name);
} 


int CmpContactsEq(Person *vall, Person *valr) {
    int res1 = strcmp(vall->Name, valr->Name);
    int res2 = strcmp(vall->LastName, valr->LastName);
    return res1 == 0 && res2 == 0;
}


Person EnterData()
{

    Person person;
    printf("Введите имя:");
    fgets(person.Name, MAX_LENGTH, stdin);
    while (strlen(person.Name) <= 1)
    {
        printf("Введите имя:");
        fgets(person.Name, MAX_LENGTH, stdin);
    }

    printf("Введите фамилию: ");
    fgets(person.LastName, MAX_LENGTH, stdin);
    while (strlen(person.LastName) <= 1)
    {
        printf("Введите фамилию: ");
        fgets(person.LastName, MAX_LENGTH, stdin);
    }

    printf("Введите должность:");
    fgets(person.Work.Post, MAX_LENGTH, stdin);
    printf("Введите место работы: ");
    fgets(person.Work.Place_work, MAX_LENGTH, stdin);

    printf("Введите Email: ");
    fgets(person.ContactInfo.Email, MAX_LENGTH, stdin);

    int count = 0;
    char buf[MAX_LENGTH];
    while (count < MAX)
    {
        printf("Введите номер телефона %d ", count + 1);
        getchar();
        fgets(buf, MAX_LENGTH, stdin);

        if (strlen(buf) < 2)
        {
            buf[0] = '\0';
            break;
            strcpy(person.ContactInfo.Number[count], buf);
        }

        if (strlen(buf) < 10)
        {
            printf("Неправильно записан номер\n");
            buf[0] = '\0';

            continue;
        }
        strcpy(person.ContactInfo.Number[count], buf);

        count++;
    }

    count = 0;
    while (count < MAX)
    {
        printf("Введите ссылки на профиль %d ", count + 1);

        fgets(buf, MAX_LENGTH, stdin);
        if (strlen(buf) < 2)
        {
            buf[0] = '\0';
            strcpy(person.Profile.Social_networks[count], buf);
            break;
        }
        strcpy(person.Profile.Social_networks[count], buf);
        count++;
    }

    count = 0;
    while (count < MAX)
    {
        printf("Введите профили на мессенджеры %d ", count + 1);
        fgets(buf, MAX_LENGTH, stdin);
        if (strlen(buf) < 2)
        {
            buf[0] = '\0';

            strcpy(person.Profile.Profiles_messengers[count], buf);
            break;
        }
        strcpy(person.Profile.Profiles_messengers[count], buf);

        count++;
    }
    return person;
}


List *Add(List *head, Person value)
{
    List *newItem = malloc(sizeof(List));
    if (newItem == NULL)
    {
        // Обработка ошибки выделения памяти
        printf("Memory allocation failed.\n");
        return head; // Возвращаем текущую голову списка
    }

    newItem->value = value;

    // Вставка элемента в пустой список
    if (head == NULL)
    {
        newItem->prev = newItem;
        newItem->next = newItem;
        return newItem; // Возвращаем новый элемент в качестве головы списка
    }

    List *tmp = head;
    // Вставка элемента в начало или середину
    do
    {
        if (CmpContactsLessOrEq(&newItem->value, &tmp->value) != 0)
        {
            newItem->next = tmp;
            newItem->prev = tmp->prev;
            tmp->prev->next = newItem;
            tmp->prev = newItem;
            if (tmp == head)
                return newItem; // Возвращаем новый элемент в качестве головы списка
            return head;        // Возвращаем текущую голову списка
        }
        tmp = tmp->next;
    } while (tmp != head);

    // Вставка элемента в конец списка
    newItem->next = tmp;
    newItem->prev = tmp->prev;
    tmp->prev->next = newItem;
    tmp->prev = newItem;

    return head; // Возвращаем текущую голову списка
}


List *Delete(Person value, List *head)
{
    List *tmp = head;
    // Удаление элемента из пустого списка
    if (NULL == head)
    {
        printf("List empty!\n");
        return head;
    }
    // Поиск и удаление элемента
    do
    {

        if (CmpContactsEq(&value, &tmp->prev->value) != 0)
        {
            // Если удаляется единственный элемент списка
            if (tmp->next == tmp->prev)
            {
                free(tmp);
                return NULL;
            }
            // Перестраиваем связи
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            // Если элемент удаляется из начала списка, изменяем head
            if (tmp == head)
                head = head->next;
            // Удаляем найденный элемент
            free(tmp);
            return head;
        }
        tmp = tmp->next;
    } while (tmp != head);
    // Если элемент не найден, выводим сообщение
    printf("Контакт с именем \"%s\" не найден!\n", value.Name);
    return head;
}


void Print(Person *person)
{
    printf("Имя: %s\n", person->Name);
    printf("Фамилия: %s\n", person->LastName);

    if (strlen(person->Work.Post) <= 1 )
    printf("Должность: - \n");
    else 
    printf("Должность: %s\n", person->Work.Post);
    printf("\n");

    if (strlen(person->Work.Place_work) <= 1 )
    printf("Место работы: - \n");
    else 
    printf("Место работы: %s\n", person->Work.Place_work);
    printf("\n");

    if (strlen(person->ContactInfo.Email) <= 1 )
    printf("Email: - \n");
    else 
    printf("Email: %s\n", person->ContactInfo.Email);
    printf("\n");
    // Печать номеров телефонов, если они не пустые
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(person->ContactInfo.Number[i]) < 4)
        {
            break;
            
        }
        if (strlen(person->ContactInfo.Number[i]) >= 1)
        {
            printf("Номер телефона: %s\n", person->ContactInfo.Number[i]);
        }
        else
        printf("Номер телефона: - \n");
        // Для Кирилла тут брейк не прокатит он выведет только один номер даже если ввели 5 номеров
            
    }
    
    printf("\n");

    // Печать ссылок на страницы, если они не пустые
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(person->Profile.Social_networks[i]) >= 2)
        {
            printf("Ссылка на страницу: %s\n", person->Profile.Social_networks[i]);
        }
        else
        printf("Ссылка на страницу: - \n");
           
    }
    printf("\n");
    // Печать профилей мессенджеров, если они не пустые
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(person->Profile.Profiles_messengers[i]) >= 2)
        {
            printf("Профиль в мессенджере: %s\n", person->Profile.Profiles_messengers[i]);
        }
        else
        printf("Профиль в мессенджере: - \n");
           
    }
}


void PrintList(List *head)
{
    List *tmp = head;
    if (NULL == head)
    {
        printf("List empty!\n");
        return;
    }
    do
    {
        Print(&(tmp->value));
        tmp = tmp->next;
    } while (tmp != head);
}


void FreeList(List *head)
{
    List *current = head;
    while (current != NULL)
    {
        List *temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL; // Устанавливаем указатель на голову списка в NULL
}


int main()
{
    List *head = NULL;
    int choice;

    do
    {
        menu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            head = Add(head, EnterData());
            break;
        case 2:
            PrintList(head);
            break;
        case 3:
            Person contactToDelete = EnterData(); // Введите имя и фамилию контакта для удаления
            head = Delete(contactToDelete, head);
            break;

        default:
            printf("Ошибка: некорректный выбор. Пожалуйста, выберите действие из меню.\n");
        }
    } while (choice != 4);

    FreeList(head);

    return 0;
}
