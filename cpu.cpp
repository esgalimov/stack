#include "header.h"

void run_cpu(FILE * stream)
{
    struct Text commands = {};
    construct(&commands, stream);

    stack stk = {};
    stack_ctor(&stk, 5);

    char cmd[20];
    size_t i = 0;
    int len_cmd = 0;

    sscanf(commands.strings[i], "%s%n", cmd, &len_cmd);

    while (strcmp(cmd, "hlt") != 0 && i < commands.len)
    {
        if (is_without_text(commands.strings[i]))
        {
            i++;
            sscanf(commands.strings[i], "%s%n", cmd, &len_cmd);
            continue;
        }
        if (strcmp(cmd, "push") == 0)
        {
            elem value = 0;
            sscanf(commands.strings[i] + len_cmd, "%lf", &value);
            stack_push(&stk, value);
        }
        else if (strcmp(cmd, "add") == 0)
        {
            elem num1 = 0;
            elem num2 = 0;
            stack_pop(&stk, &num1);
            stack_pop(&stk, &num2);
            stack_push(&stk, num1 + num2);
        }
        else if (strcmp(cmd, "sub") == 0)
        {
            elem num1 = 0;
            elem num2 = 0;
            stack_pop(&stk, &num1);
            stack_pop(&stk, &num2);
            stack_push(&stk, num2 - num1);
        }
        else if (strcmp(cmd, "div") == 0)
        {
            elem num1 = 0;
            elem num2 = 0;
            stack_pop(&stk, &num1);
            stack_pop(&stk, &num2);
            stack_push(&stk, num2 / num1);
        }
        else if (strcmp(cmd, "mul") == 0)
        {
            elem num1 = 0;
            elem num2 = 0;
            stack_pop(&stk, &num1);
            stack_pop(&stk, &num2);
            stack_push(&stk, num2 * num1);
        }
        else if (strcmp(cmd, "pop") == 0)
        {
            elem num = 0;
            stack_pop(&stk, &num);
        }
        else if (strcmp(cmd, "out") == 0)
        {
            elem num = 0;
            stack_pop(&stk, &num);
            printf("%lg", num);
        }
        else
        {
            printf("Invalid syntax");
        }
        i++;
        sscanf(commands.strings[i], "%s%n", cmd, &len_cmd);
    }

    destruct(&commands);
    stack_dtor(&stk);
}

char ** import_text(struct Text * book, FILE * stream)
{
    assert(stream != NULL);
    assert(book != NULL);

    fseek(stream, 0L, SEEK_END);
    book->filesize = (size_t) ftell(stream);
    rewind(stream);

    book->buffer = (char *) calloc(book->filesize + 1, sizeof(char));
    fread(book->buffer, sizeof(char), book->filesize, stream);
    *(book->buffer + book->filesize) = '\0';

    book->len = count_symbol('\n', book->buffer, book->filesize);

    return get_ptrs(book->buffer, book->len, book->filesize);
}


size_t count_symbol(char ch, char * string, size_t filesize)
{
    assert(string != NULL);

    size_t cnt_strings = 0;
    for (size_t i = 0; i < filesize; i++)
        if (string[i] == ch)
            cnt_strings++;
    return cnt_strings;
}


char ** get_ptrs(char * strings, size_t n_strings, size_t filesize)
{
    assert(strings != NULL);
    char ** strptr = (char **) calloc((size_t) (n_strings + 1), sizeof(char *));

    if (strptr == NULL)
        return NULL;

    strptr[0] = &strings[0];
    size_t index = 1;
    for (size_t i = 1; i < filesize; i++)
        if (strings[i] == '\n')
        {
            if (index < n_strings)
            {
                strings[i] = '\0';
                strptr[index] = &strings[i + 1];
                index++;
            }
        }
    strptr[index] = NULL;

    return strptr;
}

int is_without_text(const char * str)
{
    assert(str != NULL);
    int flag = 1;
    int len = (int) strlen(str);
    for (int i = 0; i < len; i++)
        if (!isblank(str[i]))
        {
            flag = 0;
            break;
        }
    return flag;
}

void construct(struct Text * book, FILE * stream)
{
    assert(book != NULL);
    assert(stream != NULL);

    book->strings = NULL;
    book->buffer = NULL;
    book->len = 0;
    book->filesize = 0;

    book->strings = import_text(book, stream);
    fclose(stream);
}

void destruct(struct Text * book)
{
    assert(book != NULL);

    book->len = 0;
    book->filesize = 0;
    free(book->buffer);
    free(book->strings);
    book->strings = NULL;
    book->buffer = NULL;
}
