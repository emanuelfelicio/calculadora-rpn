#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../src/pol.h"

/* Simple unit tests for the RPN calculator functions */

void test_my_atof(void)
{
    double r;
    Error err = my_atof("42", &r);
    assert(err.code == 0 && r == 42.0);

    err = my_atof("-3.5", &r);
    assert(err.code == 0 && r == -3.5);

    err = my_atof("+2.50", &r);
    assert(err.code == 0 && r == 2.5);

    err = my_atof("1a", &r);
    assert(err.code == -1);
    assert(strcmp(err.msg, "not a number") == 0);

    printf("test_my_atof: OK\n");
}

void test_is_operator(void)
{
    assert(is_operator("+") == '+');
    assert(is_operator("-") == '-');
    assert(is_operator("*") == '*');
    assert(is_operator("/") == '/');
    assert(is_operator("++") == -1);
    assert(is_operator("a") == -1);
    printf("test_is_operator: OK\n");
}

void test_push_pop(void)
{
    double r;
    /* push two values and pop them in LIFO order */
    assert(push(1.23).code == 0);
    assert(push(4.56).code == 0);

    Error err = pop(&r);
    assert(err.code == 0 && r == 4.56);

    err = pop(&r);
    assert(err.code == 0 && r == 1.23);

    /* popping empty stack returns error */
    err = pop(&r);
    assert(err.code == -1);
    assert(strcmp(err.msg, "stack is empty") == 0);

    printf("test_push_pop: OK\n");
}

void test_operation(void)
{
    double r;
    Error err;

    /* addition */
    push(2.0);
    push(3.0);
    err = operation("+");
    assert(err.code == 0);
    err = pop(&r);
    assert(err.code == 0 && r == 5.0);

    /* subtraction */
    push(10.0);
    push(4.0);
    err = operation("-");
    assert(err.code == 0);
    err = pop(&r);
    assert(err.code == 0 && r == 6.0);

    /* multiplication */
    push(2.0);
    push(3.0);
    err = operation("*");
    assert(err.code == 0);
    err = pop(&r);
    assert(err.code == 0 && r == 6.0);

    /* division */
    push(8.0);
    push(2.0);
    err = operation("/");
    assert(err.code == 0);
    err = pop(&r);
    assert(err.code == 0 && r == 4.0);

    /* division by zero: operation should set error and not push result */
    push(1.0);
    push(0.0);
    err = operation("/");
    assert(err.code == -1);
    assert(strcmp(err.msg, "cannot divide by zero") == 0);


    printf("test_operation: OK\n");
}

int main(void)
{
    test_my_atof();
    test_is_operator();
    stackpointer = 0;
    test_push_pop();
    stackpointer = 0;
    test_operation();
    printf("ALL TESTS PASSED\n");
    return 0;
}
