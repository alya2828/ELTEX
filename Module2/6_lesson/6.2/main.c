#include "contacts.h"

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
        case 4:
            MoveContact(head);
            break;
        default:
            printf("Ошибка: некорректный выбор. Пожалуйста, выберите действие из меню.\n");
        }
    } while (choice != 5);

    //FreeList(head);

    return 0;
}

