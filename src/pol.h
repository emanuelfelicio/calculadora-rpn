#ifndef POL_H
#define POL_H

#define STACK_SIZE 1024

typedef struct {
    int code;
    char *msg;
} Error;

Error my_atof(const char *, double *);
Error push(double);
Error pop(double *);
char is_operator(const char *);
Error operation(const char *);
extern double stack[STACK_SIZE];
extern int stackpointer;
#endif