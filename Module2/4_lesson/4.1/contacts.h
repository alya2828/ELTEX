#ifndef CONTACTS_H_
#define CONTACTS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 30
#define MAX 5

typedef struct Link
{
    char Social_networks[4][MAX_LENGTH];
    char Profiles_messengers[4][MAX_LENGTH];

} Link;

typedef struct Contacts
{
    char Email[MAX_LENGTH];
    char Number[4][MAX_LENGTH];
} Contacts;

typedef struct Job
{
    char Post[MAX_LENGTH];
    char Place_work[MAX_LENGTH];
} Job;

typedef struct Person
{
    char Name[MAX_LENGTH];
    char LastName[MAX_LENGTH];
    Job Work;
    Contacts ContactInfo;
    Link Profile;

} Person;
typedef struct List
{
    Person value;
    struct List *next;
    struct List *prev;
} List;

void menu();
int CmpContactsLessOrEq(Person *vall, Person *valr);
int CmpContactsEq(Person *vall, Person *valr);
Person EnterData();
List *Add(List *head, Person value);
List *Delete(Person value, List *head);
Person EnterData();
void MoveContact(List* head);
void Print(Person *person);
void PrintList(List *head);
void FreeList(List *head);

#endif /* CONTACTS_H_*/
