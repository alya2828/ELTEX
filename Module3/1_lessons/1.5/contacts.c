#include "contacts.h"

void menu()
{
    printf("\n Меню: \n");
    printf("1 - Добавить контакт\n");
    printf("2 - Вывести контакты\n");
    printf("3 - Удалить контакт\n");
    printf("4 - Изменить контакт\n");
    printf("5 - Выход\n");
    printf("Выберите действие: ");
    return;
}

void MoveContact(List* head){
    Person value;
    List *tmp = head;
    printf ("Введите имя, которое нужно изменить");
    fgets(value.Name, MAX_LENGTH, stdin);
    printf ("Введите фамилю, которое нужно изменить");
    fgets(value.LastName, MAX_LENGTH, stdin);
    do
    {
        if (CmpContactsEq(&value, &tmp->prev->value) == 0)
        {
            tmp->value=EnterData();
            return;
        }
        tmp = tmp->next;
    } while (tmp != head);
}

int CmpContactsLessOrEq(Person *vall, Person *valr)
{
    int res1 = strcmp(vall->Name, valr->Name);
    if (res1 < 0 || res1 > 0)
        return res1;
    return strcmp(vall->Name, valr->Name);
}

int CmpContactsEq(Person *vall, Person *valr)
{
    int res1 = strcmp(vall->Name, valr->Name);
    int res2 = strcmp(vall->LastName, valr->LastName);
    return res1 == 0 && res2 == 0;
}

Person EnterData()
{

    Person person;
    printf("Введите имя:");
    fgets(person.Name, MAX_LENGTH, stdin);
    printf("%ld\n", strlen(person.Name));
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
            strcpy(person.ContactInfo.Number[count], buf);
            break;
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
    
    if (head == NULL)
    {
        printf("Список пуст!\n");
        return NULL;
    }
    
    do
    {
        if (CmpContactsEq(&value, &tmp->value))
        {
           
            if (tmp->next == tmp->prev && tmp->next == tmp)
            {
                free(tmp);
                return NULL;
            }
            
            // Перестройка связей
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            
            if (tmp == head)
            {
                head = tmp->next;
            }
            
           
            free(tmp);
            
            
            return head;
        }
        
        tmp = tmp->next;
    } while (tmp != head);
    
    printf("Контакт с именем \"%s\" и фамилией \"%s\" не найден!\n", value.Name, value.LastName);
    
    return head;
}

void Print(Person *person)
{
    printf("Имя: %s\n", person->Name);
    printf("Фамилия: %s\n", person->LastName);

    if (strlen(person->Work.Post) <= 1)
        printf("Должность: - \n");
    else
        printf("Должность: %s\n", person->Work.Post);
    printf("\n");

    if (strlen(person->Work.Place_work) <= 1)
        printf("Место работы: - \n");
    else
        printf("Место работы: %s\n", person->Work.Place_work);
    printf("\n");

    if (strlen(person->ContactInfo.Email) <= 1)
        printf("Email: - \n");
    else
        printf("Email: %s\n", person->ContactInfo.Email);
    printf("\n");

    int i = 0;
    while (strlen(person->ContactInfo.Number[i]) > 2)
    {
        printf("Номер телефона: %s\n", person->ContactInfo.Number[i]);
        i++;
    }

    printf("\n");

    i = 0;
    while (strlen(person->Profile.Social_networks[i]) > 2)
    {
        printf("Ссылка на страницу: %s\n", person->Profile.Social_networks[i]);
        i++;
    }

    printf("\n");

    i = 0;
    while (strlen(person->Profile.Profiles_messengers[i]) > 2)
    {
        printf("Профиль в мессенджере: %s\n", person->Profile.Profiles_messengers[i]);
        i++;
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

List *read_contact(List *head) {

    int fd = open("contacts.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return head;
    }

    Person person;
    ssize_t bytes_read;

    while ((bytes_read = read(fd, &person, sizeof(Person))) > 0) {
        if (bytes_read == sizeof(Person)) {
            head = Add(head, person);
        } else {
            perror("Error reading file");
            close(fd);
            return head;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading file");
    return head;
    }

    close(fd);
    return head;
}
void save_contact(List *head) {
     int fd = open("contacts.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening file for writing");
        return;
    }

     List *tmp = head;
    if (head != NULL) {
        do {
            if (write(fd, &(tmp->value), sizeof(Person)) != sizeof(Person)) {
                printf("Error writing to file.\n");
                close(fd);
                return;
            }
            tmp = tmp->next;
        } while (tmp != head);
    }

    close(fd);
}