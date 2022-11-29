#include "header.h"

void run_cpu(FILE * stream)
{
    assert(stream != NULL);

    stack stk = {};
    stack_ctor(&stk, 5);

    elem num1 = 0;
    elem num2 = 0;

    fseek(stream, 0L, SEEK_END);
    size_t filesize = (size_t) ftell(stream);
    rewind(stream);

    size_t n_cmd = filesize / sizeof(elem);

    elem * cmd_buffer = (elem *) calloc(n_cmd, sizeof(elem));
    fread(cmd_buffer, sizeof(elem), n_cmd, stream);

    for (size_t i = 0; i < n_cmd && cmd_buffer[i] != HLT; i++)
    {
        switch (cmd_buffer[i])
        {
        case PUSH:
            stack_push(&stk, cmd_buffer[++i]);
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
            printf("%d\n", num1);
            break;

        default:
            printf("Error: undefind command\n");
            abort();
            break;
        }
    }

    stack_dtor(&stk);
}
