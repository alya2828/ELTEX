#ifndef CONTACTS_H
#define CONTACTS_H_
#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 20 
#define MAX 5

typedef struct Link
{
    char Social_networks[4][MAX_LENGTH];
    char Profiles_messengers[4][MAX_LENGTH];

}Link;

typedef struct Contacts
{
    char Email[MAX_LENGTH];
    char Number[4][MAX_LENGTH];
}Contacts;

typedef struct Job
{
char Post[MAX_LENGTH];
char Place_work[MAX_LENGTH];
}Job;

typedef struct Person 
{
    char Name[MAX_LENGTH];
    char LastName[MAX_LENGTH];
    Job Work;
    Contacts ContactInfo;
    Link Profile; 
} Person;

void menu();
void Add(Person contact[], int *num);
void Delete(Person contact[], int *num);
void Print(Person contact[], int *num);
void Move();

#endif /* CONTACTS_H_*/