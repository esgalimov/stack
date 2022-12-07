#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

struct Text
{
    char ** strings;
    char * buffer;
    size_t len;
    size_t filesize;
};

struct token
{
    char * name;
    int type;
    int value;
    int line;
};

enum Command_type
{
    NUM = -1,
    CMD0 = 0,
    CMD1 = 1,
};

enum Commands
{
    HLT = 0,
    PUSH = 1,
    ADD = 2,
    SUB = 3,
    DIV = 4,
    MUL = 5,
    POP = 6,
    OUT = 7,
};


typedef int elem;

void run_comp(FILE * stream);

int str_of_digitis(const char * cmd);

void write_code_to_file(token * toks, size_t n_cmd);

void check_toks_for_size(token * toks, size_t i_code, size_t * size_toks);

int check_code(token * toks, size_t n_cmd);

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
