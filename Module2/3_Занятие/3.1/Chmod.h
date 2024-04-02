#ifndef CHMOD_H
#define CHMOD_H_
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
void Change_Access_rights_number(char *buffer2);
void Access_rights_number(int num);
void Access_rights_char(char *buffer2);
void Stat(char *path, struct stat *buf);
void menu();
#endif 