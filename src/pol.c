#include <stdio.h>
#include <stdlib.h>
#include "pol.h"

/* Global variables for stack implementation */
double stack[STACK_SIZE];
int stackpointer = 0;
// Reverse Polish Notation (RPN) calculator.
// Evaluates expressions where operators follow operands, e.g. "4 5 +" => 4 + 5
#ifndef UNIT_TEST
int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        fprintf(stderr, "too few arguments\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++)
    {
        Error err;
        char op;
        char *digit = argv[i];
        op = is_operator(digit);
        if (op == -1)
        {
            double number;
            err = my_atof(digit, &number);
            if (err.code == -1)
            {
                fprintf(stderr, "%s\n", err.msg);
                exit(1);
            }
            err = push(number);
            if (err.code == -1)
            {
                fprintf(stderr, "%s\n", err.msg);
                exit(1);
            }
        }
        else
        {
            Error err = operation(&op);
            if (err.code == -1)
            {
                fprintf(stderr, "%s\n", err.msg);
                exit(1);
            }
        }
    }


    if (stackpointer > 1)
    {
        fprintf(stderr, "too many operands\n");
        exit(1);
    }

    double result;
    Error err = pop(&result);
    if (err.code == -1)
    {
        fprintf(stderr, "%s\n", err.msg);
        exit(1);
    }
    printf("the result is : %.2f\n", result);

    return 0;
}
#endif /* UNIT_TEST */

//stack operations
Error push(double value)
{
    if (stackpointer < STACK_SIZE)
    {
        stack[stackpointer++] = value;
        return (Error){0, NULL};
    }
    else
    {
        return (Error){-1, "stack is full"};
    }
}
Error pop(double *result)
{
    if (stackpointer > 0)
    {
        *result = stack[--stackpointer];
        return (Error){0, NULL};
    }
    return (Error){-1, "stack is empty"};
}

// Return 1 if *digit is '0'..'9', otherwise -1
static int my_isdigit(const char *digit)
{
    if (digit == NULL || *digit == '\0')
    {
        return -1;
    }
    int value = *digit - '0';
    if (value >= 0 && value <= 9)
    {
        return 1;
    }

    return -1;
}

// Convert string to double.
Error my_atof(const char *digit, double *result)
{
    *result = 0.0;
    double fraction = 0.0;
    int sign = 1;

    if (*digit == '-')
    {
        digit++;
        sign = -1;
    }
    else if (*digit == '+')
    {
        digit++;
        sign = 1;
    }

    while (my_isdigit(digit) == 1)
    {
        *result = *result * 10.0 + (*digit - '0');
        digit++;
    }

    if (*digit == '.' && *(digit + 1) != '\0')
    {
        digit++;
        double divisor = 10.0;
        while (my_isdigit(digit) == 1)
        {
            fraction += (*digit - '0') / divisor;
            divisor *= 10.0;
            digit++;
        }
    }

    if (*digit != '\0')
    {
        return (Error){-1, "not a number"};
    }

    *result += fraction;
    *result *= sign;
    return (Error){0, NULL};
}

// Return operator char if input is a single operator (+ - * /) otherwise -1
char is_operator(const char *operator)
{
    char op = *operator;

    if ((op == '-' || op == '+' || op == '*' || op == '/') && *(operator + 1) == '\0')
    {
        return op;
    }

    return -1;
}

// Perform arithmetic on the top two stack values.
Error operation(const char *operator)
{
    double op2;
    Error err = pop(&op2);
    if (err.code == -1)
    {
        return err;
    }
    double op1;
    err = pop(&op1);
    if (err.code == -1)
    {
        return err;
    }
    switch (*operator)
    {
    case '-':
        return push(op1 - op2);
    case '+':
        return push(op1 + op2);
    case '*':
        return push(op1 * op2);
    case '/':
        if (op2 == 0)
        {
            return (Error){-1, "cannot divide by zero"};
        }
        else
        {
            return push(op1 / op2);
        }
    default:
        return (Error){-1, "invalid operator"};
    }
}