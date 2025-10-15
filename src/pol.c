#include <stdio.h>
#include "pol.h"

/* Global variables for stack implementation */
double stack[STACK_SIZE]; 
int stackpointer = 0; 
   
int erro = 0;             

// Reverse Polish Notation (RPN) calculator.
// Evaluates expressions where operators follow operands, e.g. "4 5 +" => 4 + 5
#ifndef UNIT_TEST
int main(int argc, char **argv)
{
    double my_atof(const char *);
    void push(double);
    double pop(void);
    char is_operator(const char *);
    void operation(const char *);

    if (argc > 1)
    {

        for (int i = 1; i < argc; i++)
        {
            if (!erro)
            {
                char op;
                char *digit = argv[i];
                if (!(op = is_operator(digit)))
                {
                    push(my_atof(digit));
                }
                else
                {
                    operation(&op);
                }
            }
            else
            {
                break;
            }
        }

        if (stackpointer > 1)
        {
            printf("ERROR: too many operands\n");
            erro = -1;
        }

        if (!erro)
        {
            double result = pop();
            printf("the result is : %.2f\n", result);
        }
    }
    else
    {
        printf("input is empty\n");
    }
}
#endif /* UNIT_TEST */

// Return 1 if *digit is '0'..'9', otherwise 0
static int my_isdigit(const char *digit)
{
    int value = *digit - '0';
    if (value >= 0 && value <= 9)
    {
        return 1;
    }

    return 0;
}

// Convert string to double.
double my_atof(const char *digit)
{
    double result = 0.0;   /* Integer part */
    double fraction = 0.0; /* Decimal part */
    int sign = 1;          /* Number sign (1 or -1) */

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

    while (my_isdigit(digit))
    {
        result = result * 10.0 + (*digit - '0');
        digit++;
    }

    if (*digit == '.' && *(digit + 1) != '\0')
    {
        digit++;
        double divisor = 10.0;
        while (my_isdigit(digit))
        {
            fraction += (*digit - '0') / divisor;
            divisor *= 10.0;
            digit++;
        }
    }

    if (*digit != '\0')
    {
        char c = *digit;
        printf("ERROR :NOT A NUMBER:\"%c\"\n", c);
        return erro = -1;
    }

    result += fraction;
    result *= sign;
    return result;
}

void push(double value)
{
    if (stackpointer < STACK_SIZE)
    {
        stack[stackpointer++] = value;
    }
    else
    {
        printf("ERROR: cannot push stack is full\n");
        erro = -1;
    }
}

double pop(void)
{
    if (stackpointer > 0)
    {
        return stack[--stackpointer];
    }

    printf("ERROR: too many operators\n");
    return erro = -1;
}

// Return operator char if input is a single operator (+ - * /)
char is_operator(const char *operator)
{
    char op = *operator;

    if ((op == '-' || op == '+' || op == '*' || op == '/') && *++operator == '\0')
    {
        return op;
    }

    return 0;
}

// Perform arithmetic on the top two stack values.
void operation(const char *operator)
{
    double op2 = pop(); /* Right operand */
    double op1 = pop(); /* Left operand */

    switch (*operator)
    {
    case '-':
        push(op1 - op2);
        break;
    case '+':
        push(op1 + op2);
        break;
    case '*':
        push(op1 * op2);
        break;
    case '/':
        if (op2 == 0)
        {
            printf("ERROR: cannot divide by zero\n");
            erro = -1;
        }
        else
        {
            push(op1 / op2);
        }
        break;
    default:
        printf("ERROR: operation: invalid operator");
        erro = -1;
    }
}