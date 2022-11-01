#include "header.h"

FILE * log_file = NULL;

int main(void)
{
    log_file = fopen("log.txt", "w");
    if (log_file == NULL)
    {
        printf("Can't open log file!");
        return 1;
    }

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


    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    // stk1.data = NULL;
    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);
    stack_pop(&stk1, &x);

    stack_dtor(&stk1);

    fclose(log_file);
    return 0;
}
