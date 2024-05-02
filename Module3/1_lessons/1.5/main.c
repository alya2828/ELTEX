#include "contacts.h"
int main() {
    List *head = NULL;

    head = read_contact(head);
    int choice;
if (head == NULL){
    printf("Мне жаль\n ");
}
    // Считываем контакты из файла в начале программы
   

    do {
        menu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
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
        case 5:
         save_contact(head);
          return 0;
        default:
            printf("Ошибка: некорректный выбор. Пожалуйста, выберите действие из меню.\n");
             break;
        }
    } while (choice != 6);

    // Сохраняем контакты в файл перед завершением программы
    
    FreeList(head);

    return 0;
}