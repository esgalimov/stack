#include "asm_header.h"

void run_comp(FILE * stream)
{
    FILE * fp = fopen("test.code", "w");
    FILE * fp_bin = fopen("test.bin", "wb");

    if (fp == NULL || fp_bin == NULL)
    {
        printf("Can't open file");
        abort();
    }

    struct Text commands = {};
    construct(&commands, stream);

    size_t i = 0;
    int len_cmd = 0, is_hlt = 0;

    elem * code = (elem *) calloc(commands.len * 2, sizeof(elem));
    size_t i_code = 0;

    while (i < commands.len)
    {
        char cmd[20] = "";
        sscanf(commands.strings[i], "%s%n", cmd, &len_cmd);

        if (is_without_text(cmd))
        {
            i++;
            continue;
        }
        if (strcmp(cmd, "push") == 0)
        {
            one_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);

            elem value = 0;
            sscanf(commands.strings[i] + len_cmd, "%d", &value);
            fprintf(fp, "%d %d\n", PUSH, value);

            code[i_code++] = PUSH;
            code[i_code++] = value;

        }
        else if (strcmp(cmd, "add") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", ADD);

            code[i_code++] = ADD;
        }
        else if (strcmp(cmd, "sub") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", SUB);

            code[i_code++] = SUB;
        }
        else if (strcmp(cmd, "div") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", DIV);

            code[i_code++] = DIV;
        }
        else if (strcmp(cmd, "mul") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", MUL);

            code[i_code++] = MUL;
        }
        else if (strcmp(cmd, "pop") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", POP);

            code[i_code++] = POP;
        }
        else if (strcmp(cmd, "out") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", OUT);

            code[i_code++] = OUT;
        }
        else if (strcmp(cmd, "hlt") == 0)
        {
            no_arg_cmd_verify(commands.strings[i] + len_cmd, i, cmd);
            fprintf(fp, "%d\n", HLT);
            is_hlt = 1;

            code[i_code++] = HLT;

            break;
        }
        else
        {
            printf("Error: command not found at line %lu\n", i + 1);
            abort();
        }
        i++;
    }

    if (is_hlt == 0)
    {
        printf("Error: there is no hlt command in programm\n");
        abort();
    }

    fwrite(code, sizeof(elem), i_code, fp_bin);
    free(code);

    destruct(&commands);
    fclose(fp);
}

void one_arg_cmd_verify(char * ptr_to_args, size_t line, const char * cmd_name)
{
    assert(ptr_to_args != NULL);

    int len_arg = 0;
    elem value = 0;

    sscanf(ptr_to_args, "%d%n", &value, &len_arg);

    if (len_arg == 0)
    {
        printf("Error: invalid syntax at line %lu: %s has not given an argument, but it must have 1 argument\n", line + 1, cmd_name);
        abort();
    }
    else
    {
        int gap = len_arg;
        len_arg = 0;

        sscanf(ptr_to_args + gap, "%d%n", &value, &len_arg);
        if (len_arg > 0)
        {
            printf("Error: invalid syntax at line %lu: %s has given more than 1 argument, but it must have 1 argument\n", line + 1, cmd_name);
            abort();
        }
    }
}

void no_arg_cmd_verify(char * ptr_to_args, size_t line, const char * cmd_name)
{
    assert(ptr_to_args != NULL);

    int len_arg = 0;
    elem value = 0;

    sscanf(ptr_to_args, "%d%n", &value, &len_arg);

    if (len_arg > 0)
    {
        printf("Error: invalid syntax at line %lu: %s must not have arguments \n", line + 1, cmd_name);
        abort();
    }
}
