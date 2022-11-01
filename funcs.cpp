#include "header.h"

int stack_ctor_(stack * stk, size_t capacity, const char * name,
                const char * func, const char * file, int line)
{
    if (stk == NULL || capacity < 1)
        return 1;


    if (capacity < 8)
        capacity = 8;

    stk->data = (elem *) calloc(capacity, sizeof(elem));
    stk->capacity = capacity;
    stk->size = 0;

    stk->name = name;
    stk->func = func;
    stk->file = file;
    stk->line = line;

    return 0;
}

int stack_verify(struct stack * stk)
{
    assert(stk != NULL);
    int error_number = 0;
    if (stk->data == NULL)
        error_number += NULL_DATA;
    if (stk->size < 0)
        error_number += SIZE_ERROR;
    if (stk->capacity < 0)
        error_number += CAP_ERROR;
    if (stk->capacity < stk->size)
        error_number += SIZE_CAP_ERROR;
    return error_number;
}

void error_number_translate(int error_number)
{
    int current = 0;
    int current_error = 0;
    while (error_number >= 1)
    {
        if (error_number % 2 == 1)
        {
            current_error = power_two(current);

            switch (current_error)
            {
                case NULL_DATA:
                    write_error_to_log("data have NULL pointer");
                    break;
                case SIZE_ERROR:
                    write_error_to_log("cize is lower than 0");
                    break;
                case CAP_ERROR:
                    write_error_to_log("capacity is lower than 0");
                    break;
                case SIZE_CAP_ERROR:
                    write_error_to_log("cize bigger than capacity");
                    break;
                default:
                    write_error_to_log("unknown error");
                    break;
            }
        }
        current++;
        error_number /= 2;
    }
}

void write_error_to_log(char * error_string)
{
    fputs(error_string, log_file);
    fputs("\n", log_file);
}

void stack_push(stack * stk, elem value)
{
    assert(stk != NULL);
    int is_ok = 0;
    is_ok = stack_dump(stk);
    if (!is_ok)
    {
        if (stk->size >= stk->capacity)
            stack_resize(stk, stk->capacity * 2);
        stk->data[stk->size] = value;
        stk->size++;
    }
    stack_dump(stk);
}

void stack_pop(stack * stk, elem * value)
{
    assert(stk != NULL);
    int is_ok = 0;
    is_ok = stack_dump(stk);
    if (!is_ok)
    {
        *value = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = NAN;
        stk->size--;
        if (stk->size < stk->capacity / 4 && stk->size > 0)
            stack_resize(stk, stk->capacity / 4);
    }
    stack_dump(stk);
}

void stack_resize(stack * stk, size_t new_size)
{
    assert(stk != NULL);
    int is_ok = 0;
    is_ok = stack_dump(stk);
    if (!is_ok)
    {
        stk->data = (elem *) realloc(stk->data, new_size * sizeof(elem));
        stk->capacity = new_size;
    }
    stack_dump(stk);
}

int power_two(int p)
{
    int ans = 1;
    for (int i = 0; i < p; i++)
        ans *= 2;
    return ans;
}

int stack_dump_(stack * stk, const char * func, const char * file, int line)
{
    int error_number = 0;
    error_number = stack_verify(stk);
    fprintf(log_file, "%s at %s(%d):\n", func, file, line);
    if (!error_number)
    {
        fprintf(log_file, "Stack %p (OK) \"%s\" at %s at %s(%d):\n",
                stk, stk->name, stk->func, stk->file, stk->line);
    }
    else
    {
        fprintf(log_file, "Stack %p (ERROR) \"%s\" at %s at %s(%d):\n",
                stk, stk->name, stk->func, stk->file, stk->line);
        error_number_translate(error_number);
    }
    fprintf(log_file, "{\n    size     = %lu\n    capacity = %lu\n",
            stk->size, stk->capacity);
    fprintf(log_file, "    data %p", stk->data);
    fprintf(log_file, "\n}\n\n\n");

    return error_number;
}
