#ifndef atm_h
#define atm_h
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif
#define SIZE 100
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

struct banking{
    char name[20];
    char pin[5];
    double amt;
};
typedef struct {
   struct banking customer[SIZE];
   int cscount;
}user;

void withdrwal(user* user);
void deposite(user* user);
void create();
void balance(user* user);
void pin(user* user);
void intialize(user* user);
void load(user* user);
void save(user* user);
void withdt(user* user);
void depot(user* user);
void balt(user* user);
void pt(user* user);
void bill_print(user* user,int,int);
#endif
