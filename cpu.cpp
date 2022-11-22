#include "header.h"

void run_cpu(FILE * stream)
{
    assert(stream != NULL);

    stack stk = {};
    stack_ctor(&stk, 5);

    int cmd = 0;

    elem num1 = NAN;
    elem num2 = NAN;
    elem value = NAN;

    fscanf(stream, "%d", &cmd);

    while (cmd != HLT)
    {
        switch (cmd)
        {
        case PUSH:
            fscanf(stream, "%lf", &value);
            stack_push(&stk, value);
            break;

        case ADD:
            stack_pop(&stk, &num1);
            stack_pop(&stk, &num2);
            stack_push(&stk, num1 + num2);
            break;

        case SUB:
            stack_pop(&stk, &num1);
            stack_pop(&stk, &num2);
            stack_push(&stk, num2 - num1);
            break;

        case DIV:
            stack_pop(&stk, &num1);
            stack_pop(&stk, &num2);
            stack_push(&stk, num2 / num1);
            break;

        case MUL:
            stack_pop(&stk, &num1);
            stack_pop(&stk, &num2);
            stack_push(&stk, num2 * num1);
            break;

        case POP:
            stack_pop(&stk, &num1);
            break;

        case OUT:
            stack_pop(&stk, &num1);
            printf("%lg", num1);
            break;

        default:
            printf("Error: undefind command");
            abort();
            break;
        }
        fscanf(stream, "%d", &cmd);
    }

    stack_dtor(&stk);
}
