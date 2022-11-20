#include "asm_header.h"

void run_comp(FILE * stream)
{
    FILE * fp = NULL;
    fp = fopen("test.code", "w");
    if (fp == NULL)
    {
        printf("Can't open file");
        abort();
    }

    struct Text commands = {};
    construct(&commands, stream);

    char cmd[20] = "";
    size_t i = 0;
    int len_cmd = 0;

    sscanf(commands.strings[i], "%s%n", cmd, &len_cmd);

    while (i < commands.len)
    {
        if (is_without_text(commands.strings[i]))
        {
            i++;
            sscanf(commands.strings[i], "%s%n", cmd, &len_cmd);
            continue;
        }
        if (strcmp(cmd, "push") == 0)
        {
            one_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);

            elem value = 0;
            sscanf(commands.strings[i] + len_cmd, "%lf", &value);
            fprintf(fp, "%d %lg\n", PUSH, value);

        }
        else if (strcmp(cmd, "add") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", ADD);
        }
        else if (strcmp(cmd, "sub") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", SUB);
        }
        else if (strcmp(cmd, "div") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", DIV);
        }
        else if (strcmp(cmd, "mul") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", MUL);
        }
        else if (strcmp(cmd, "pop") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", POP);
        }
        else if (strcmp(cmd, "out") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", OUT);
        }
        else if (strcmp(cmd, "hlt") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", HLT);
            break;
        }
        else
        {
            printf("Error: command not found at line %lu\n", i + 1);
            abort();
        }
        i++;
        sscanf(commands.strings[i], "%s%n", cmd, &len_cmd);
    }

    destruct(&commands);
    fclose(fp);
}

void one_arg_cmd_verify(char * ptr_to_args, size_t line, const char * cmd_name)
{
    int len_arg = 0;
    elem value = NAN;

    sscanf(ptr_to_args, "%lf%n", &value, &len_arg);

    if (len_arg == 0)
    {
        printf("Error: invalid syntax at line %lu: %s has not given an argument, but it must have 1 argument\n", line + 1, cmd_name);
        abort();
    }
    else
    {
        int gap = len_arg;
        len_arg = 0;

        sscanf(ptr_to_args + gap, "%lf%n", &value, &len_arg);
        if (len_arg > 0)
        {
            printf("Error: invalid syntax at line %lu: %s has given more than 1 argument, but it must have 1 argument\n", line + 1, cmd_name);
            abort();
        }
    }
}

void no_arg_cmd_verify(char * ptr_to_args, size_t line, const char * cmd_name)
{
    int len_arg = 0;
    elem value = NAN;

    sscanf(ptr_to_args, "%lf%n", &value, &len_arg);

    if (len_arg > 0)
    {
        printf("Error: invalid syntax at line %lu: %s must not have arguments \n", line + 1, cmd_name);
        abort();
    }
}
