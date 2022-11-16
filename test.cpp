#include "header.h"

void test_stack(void)
{
    stack stk1 = {};
    elem x = NAN;
    stack_ctor(&stk1, 5);

    stack_push(&stk1, 1.33);
    stack_push(&stk1, 2.99);
    stack_push(&stk1, 3.99);
    stack_push(&stk1, 4.99);

    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    // stk1.data = NULL;

    stack_dtor(&stk1);
}
