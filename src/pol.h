#ifndef POL_H
#define POL_H
#define STACK_SIZE 1024
double my_atof(const char *);
void push(double);
double pop(void);
char is_operator(const char *);
void operation(const char *);
extern int erro;
extern double stack[STACK_SIZE];
extern int stackpointer;
#endif