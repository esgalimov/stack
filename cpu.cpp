#include "header.h"

void run_cpu(FILE * stream)
{
    assert(stream != NULL);

    s_cpu cpu = {};
    size_t n_cmd = cpu_ctor(&cpu, stream);

    elem num1 = 0;
    elem num2 = 0;

    for (size_t i = 0; i < n_cmd && cpu.cmd_buffer[i] != HLT; i++)
    {
        switch (cpu.cmd_buffer[i])
        {
        case PUSH:
            stack_push(&cpu.stk, cpu.cmd_buffer[++i]);
            break;

        case ADD:
            stack_pop(&cpu.stk, &num1);
            stack_pop(&cpu.stk, &num2);
            stack_push(&cpu.stk, num1 + num2);
            break;

        case SUB:
            stack_pop(&cpu.stk, &num1);
            stack_pop(&cpu.stk, &num2);
            stack_push(&cpu.stk, num2 - num1);
            break;

        case DIV:
            stack_pop(&cpu.stk, &num1);
            stack_pop(&cpu.stk, &num2);
            stack_push(&cpu.stk, num2 / num1);
            break;

        case MUL:
            stack_pop(&cpu.stk, &num1);
            stack_pop(&cpu.stk, &num2);
            stack_push(&cpu.stk, num2 * num1);
            break;

        case POP:
            stack_pop(&cpu.stk, &num1);
            break;

        case OUT:
            stack_pop(&cpu.stk, &num1);
            printf("%d\n", num1);
            break;

        default:
            printf("Error: undefind command\n");
            abort();
            break;
        }
    }

    cpu_dtor(&cpu);
}

size_t cpu_ctor(s_cpu * cpu, FILE * stream)
{
    assert(cpu != NULL);
    assert(stream != NULL);

    stack_ctor(&cpu->stk, 5);

    fseek(stream, 0L, SEEK_END);
    size_t filesize = (size_t) ftell(stream);
    rewind(stream);

    size_t n_cmd = filesize / sizeof(elem);

    cpu->cmd_buffer = (elem *) calloc(n_cmd, sizeof(elem));
    fread(cpu->cmd_buffer, sizeof(elem), n_cmd, stream);

    return n_cmd;
}

void cpu_dtor(s_cpu * cpu)
{
    stack_dtor(&cpu->stk);
    free(cpu->cmd_buffer);
    //free(cpu->cpu_ram);

    cpu->cmd_buffer = NULL;
    cpu->cpu_ram = NULL;
    cpu->ax = 0;
    cpu->bx = 0;
    cpu->cx = 0;
    cpu->dx = 0;
}
