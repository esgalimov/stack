#include "header.h"

int main(void)
{
    clear_log();
    stack stk1 = {};
    double x = NAN;
    stack_ctor(&stk1, 5);

    //--------------------------------------------------

    //--------------------------------------------------
    stack_push(&stk1, 1.33);
    stack_push(&stk1, 2.99);
    stack_push(&stk1, 3.99);
    stack_push(&stk1, 4.99);
    stack_push(&stk1, 5.99);
    stack_push(&stk1, 6.99);
    stack_push(&stk1, 7.33);
    stack_push(&stk1, 8.99);
    stack_push(&stk1, 9.99);
    stack_push(&stk1, 10.99);
    stack_push(&stk1, 11.99);
    stack_push(&stk1, 12.99);


    for (size_t i = 0; i < stk1.size; i++)
        printf("%lg\n", stk1.data[i]);
    printf("capacity %lu\n", stk1.capacity);
    printf("size %lu\n\n", stk1.size);

    stack_pop(&stk1, &x);
    printf("%lg\n", x);
    stack_pop(&stk1, &x);
    printf("%lg\n", x);
    stack_pop(&stk1, &x);
    printf("%lg\n", x);
    stack_pop(&stk1, &x);
    printf("%lg\n", x);
    stack_pop(&stk1, &x);
    printf("%lg\n", x);
    stk1.data = NULL;
    stack_pop(&stk1, &x);
    printf("%lg\n", x);
    stack_pop(&stk1, &x);
    printf("%lg\n", x);
    stack_pop(&stk1, &x);
    printf("%lg\n", x);
    stack_pop(&stk1, &x);
    printf("%lg\n", x);


    // for (size_t i = 0; i < stk1.size; i++)
    //     printf("%lg\n", stk1.data[i]);
    printf("capacity %lu\n", stk1.capacity);
    printf("size %lu\n", stk1.size);
    return 0;
}
