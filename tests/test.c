#include <stdio.h>
#include <assert.h>

#include "../src/pol.h"

/* Simple unit tests for the RPN calculator functions */

void test_my_atof(void)
{
    assert(my_atof("42") == 42.0);
    assert(my_atof("-3.5") == -3.5);
    assert(my_atof("+2.50") == 2.5);
    assert(my_atof("1a") == -1.0);
    printf("test_my_atof: OK\n");
}

void test_is_operator(void)
{
    assert(is_operator("+") == '+');
    assert(is_operator("-") == '-');
    assert(is_operator("*") == '*');
    assert(is_operator("/") == '/');
    assert(is_operator("++") == 0);
    assert(is_operator("a") == 0);
    printf("test_is_operator: OK\n");
}

void test_push_pop(void)
{
    /* push two values and pop them in LIFO order */
    push(1.23);
    push(4.56);
    assert(pop() == 4.56);
    assert(pop() == 1.23);
    /* popping empty stack returns -1 */
    assert(pop() == -1.0);
    printf("test_push_pop: OK\n");
}

void test_operation(void)
{
    /* addition */
    push(2.0);
    push(3.0);
    operation("+");
    assert(pop() == 5.0);

    /* subtraction */
    push(10.0);
    push(4.0);
    operation("-");
    assert(pop() == 6.0);

    /* multiplication */
    push(2.0);
    push(3.0);
    operation("*");
    assert(pop() == 6.0);

    /* division */
    push(8.0);
    push(2.0);
    operation("/");
    assert(pop() == 4.0);

    /* division by zero: operation should set error and not push result; pop should return -1 */
    push(1.0);
    push(0.0);
    operation("/");
    assert(pop() == -1.0);

    printf("test_operation: OK\n");
}

int main(void)
{
    test_my_atof();
    test_is_operator();
    test_push_pop();
    test_operation();
    printf("ALL TESTS PASSED\n");
    return 0;
}
