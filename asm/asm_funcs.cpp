#include "asm_header.h"

void run_comp(FILE * stream)
{
    struct Text commands = {};
    construct(&commands, stream);

    token * toks = (token *) calloc(commands.len * 2, sizeof(token));

    //int labels[10] = {};

    size_t i = 0, i_code = 0, size_toks = commands.len * 2;
    int len_cmd = 0, len_cmd_gap = 0;

    while (i < commands.len)
    {
        char cmd[20] = "";
        len_cmd = 0;
        len_cmd_gap = 0;
        sscanf(commands.strings[i], "%s%n", cmd, &len_cmd);

        if (is_without_text(cmd))
        {
            i++;
            continue;
        }

        while (len_cmd > 0)
        {
            toks[i_code].name = (char *) calloc(20, sizeof(char));

            if (strcmp(cmd, "push") == 0)
            {
                toks[i_code].type = CMD1;
                toks[i_code].value = PUSH;

            }
            else if (strcmp(cmd, "add") == 0)
            {
                toks[i_code].type = CMD0;
                toks[i_code].value = ADD;
            }
            else if (strcmp(cmd, "sub") == 0)
            {
                toks[i_code].type = CMD0;
                toks[i_code].value = SUB;
            }
            else if (strcmp(cmd, "div") == 0)
            {
                toks[i_code].type = CMD0;
                toks[i_code].value = DIV;
            }
            else if (strcmp(cmd, "mul") == 0)
            {
                toks[i_code].type = CMD0;
                toks[i_code].value = MUL;
            }
            else if (strcmp(cmd, "pop") == 0)
            {
                toks[i_code].type = CMD0;
                toks[i_code].value = POP;
            }
            else if (strcmp(cmd, "out") == 0)
            {
                toks[i_code].type = CMD0;
                toks[i_code].value = OUT;
            }
            else if (strcmp(cmd, "hlt") == 0)
            {
                toks[i_code].type = CMD0;
                toks[i_code].value = HLT;
            }
            else if (str_of_digitis(cmd))
            {
                int value = 0;
                sscanf(cmd, "%d", &value);

                toks[i_code].type = NUM;
                toks[i_code].value = value;
            }
            else
            {
                printf("Error: command not found at line %lu\n", i + 1);
                abort();
            }

            strcpy(toks[i_code].name, cmd);
            toks[i_code].line = (int) (i + 1);
            i_code++;

            len_cmd_gap += len_cmd;
            len_cmd = 0;

            sscanf(commands.strings[i] + len_cmd_gap, "%s%n", cmd, &len_cmd);

            check_toks_for_size(toks, i_code, &size_toks);
        }
        i++;
    }

    if (check_code(toks, i_code))
    {
        write_code_to_file(toks, i_code);
        printf("Compiled OK\n");
    }

    free(toks);
    destruct(&commands);
}

void write_code_to_file(token * toks, size_t n_cmd)
{
    assert(toks != NULL);

    FILE * fp = fopen("test.code", "w");
    FILE * fp_bin = fopen("test.bin", "wb");

    if (fp == NULL || fp_bin == NULL)
    {
        printf("Can't open file");
        abort();
    }

    elem * code = (elem *) calloc(n_cmd, sizeof(elem));

    for (size_t i = 0; i < n_cmd; i++)
    {
        code[i] = toks[i].value;
        fprintf(fp, "%d ", toks[i].value);
    }

    fwrite(code, sizeof(elem), n_cmd, fp_bin);

    fclose(fp);
    fclose(fp_bin);

    free(code);
}

int check_code(token * toks, size_t n_cmd)
{
    assert(toks != NULL);

    int is_hlt = 0, is_ok = 1;

    for (size_t i = 0; i < n_cmd; i++)
    {
        if (toks[i].type == CMD1 && toks[i].value == PUSH)
        {
            if ((i + 1 < n_cmd && toks[i + 1].type != NUM) || (i + 1 == n_cmd))
            {
                printf("Error: invalid syntax at line %d: %s has not given an argument, but it must have 1 argument\n",
                        toks[i].line, toks[i].name);
                is_ok = 0;
            }

            else if (i + 2 < n_cmd && toks[i + 1].type == NUM && toks[i + 2].type == NUM)
            {
                printf("Error: invalid syntax at line %d: %s has given more than 1 argument, but it must have 1 argument\n",
                        toks[i].line, toks[i].name);
                is_ok = 0;
            }
        }

        else if (toks[i].type == CMD0)
        {
            if (i + 1 < n_cmd && toks[i + 1].type == NUM)
            {
                printf("Error: invalid syntax at line %d: %s must not have arguments \n",
                        toks[i].line, toks[i].name);
                is_ok = 0;
            }

            else if (toks[i].value == HLT)
            {
                is_hlt = 1;
            }
        }
    }

    if (is_hlt == 0)
    {
        printf("Error: there is no hlt command in programm\n");
        is_ok = 0;
    }

    return is_ok;
}


int str_of_digitis(const char * cmd)
{
    size_t len_of_cmd = strlen(cmd);
    size_t i = 0;

    if (cmd[0] == '-')
        i = 1;

    for (; i < len_of_cmd; i++)
    {
        if (isdigit(cmd[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void check_toks_for_size(token * toks, size_t i_code, size_t * size_toks)
{
    if (*size_toks <= i_code)
    {
        *size_toks *= 2;
        toks = (token *) realloc(toks, *size_toks * sizeof(elem));
    }
}
