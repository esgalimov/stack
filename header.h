#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define LOCATION __PRETTY_FUNCTION__, __FILE__, __LINE__
#define stack_ctor(stk, size) stack_ctor_((stk), (size), var_info {#stk, LOCATION})
#define stack_dump(stk, error_number) stack_dump_((stk), (error_number), __PRETTY_FUNCTION__, __FILE__, __LINE__)

typedef double elem;

struct var_info
{
    const char * name;
    const char * func;
    const char * file;
    int line;
};

struct stack
{
    elem * data;
    size_t size;
    size_t capacity;
    var_info info;
};

struct Text
{
    char ** strings;
    char * buffer;
    size_t len;
    size_t filesize;
};

enum Errors
{
    NULL_DATA = 1,
    SIZE_ERROR = 2,
    CAP_ERROR = 4,
    SIZE_CAP_ERROR = 8,
    POP_ERROR = 16,
};

extern FILE * log_file;

int stack_ctor_(stack * stk, size_t capacity, var_info info);

int stack_verify(stack * stk);

void stack_push(stack * stk, elem value);

void stack_pop(stack * stk, elem * value);

void stack_resize(stack * stk, size_t new_size);

void error_num_translate(int error_number);

int power_two(int p);

void write_error_to_log(const char * error_string);

void stack_dump_(stack * stk, int error_number, const char * func, const char * file, int line);

void write_stack_elems(stack * stk);

void stack_dtor(stack * stk);

void test_stack(void);

void run_cpu(FILE * stream);

//! @brief Function that import text from file and write it into the buffer
//! in allocated memory with calloc
//!
//! @param [out] book - pointer to struct with variables for text processing
//! @param [in] stream - pointer to the file with text
//!
//! @return Pointer to array with pointers to string
//! @note Function use get_ptrs to make array with pointers to strings

char ** import_text(struct Text * book, FILE * stream);

//! @brief Function for counting number of particular symbol
//!
//! @param [in] ch - symbol that is counting
//! @param [in] string - pointer to string where we want to count
//! @param [in] filesize - size of string in bytes
//!
//! @return Number of symbol ch

size_t count_symbol(char ch, char * string, size_t filesize);

//! @brief Function that swap "\n" to "\0" in buffer and make array of pointers to strings in buffer
//!
//! @param [in] strings - pointer to buffer
//! @param [in] n_strings - number of strings
//! @param [in] filesize - size of file in bytes
//!
//! @return pointer to array with pointers to stings
char ** get_ptrs(char * strings, size_t n_strings, size_t filesize);

//! @brief Function for checking if string consists of blank symbol only
//! @param [in] str - pointer to string for checking
//! @return 1 - if only blank symbols, else - 0

int is_without_text(const char * str);

//! @brief Constructor for Text
//!
//! @param [out] book - pointer to struct with variables for text processing
//! @param [in] stream - pointer to file with text
//!
//! @note Initialize struct fields, use import_text, close file stream

void construct(struct Text * book, FILE * strem);

//! @brief Destruct for Text
//! @param [out] book - pointer to struct with variables for text processing

void destruct(struct Text * book);

#endif
