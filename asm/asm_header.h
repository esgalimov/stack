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

struct label
{
    int value;
    size_t cnt;
};

struct s_asm
{
    Text commands;
    token * toks;
    label * labels;
    size_t size_toks;
    int len_cmd;
    int len_cmd_gap;
};

enum Command_type
{
    UNDEFIND = -4,
    LABEL_JMP = -3,
    LABEL = -2,
    NUM = -1,
    CMD0 = 0,
    CMD1 = 1,
    REG = 2,
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
    JMP = 8,
    JB = 9,
    JBE = 10,
    JA = 11,
    JAE = 12,
    JE = 13,
    JNE = 14,
    AX = 15,
    BX = 16,
    CX = 17,
    DX = 18,
    PUSH_REG = 19,
};

const int N_LABELS = 10;

typedef int elem;

void run_comp(FILE * stream);

int str_of_digits(const char * cmd);

void write_code_to_file(token * toks, size_t n_cmd);

void check_toks_for_size(s_asm * asem, size_t i_code);

int check_code(s_asm * asem, size_t n_cmd);

int is_label(const char * cmd);

void asm_ctor(s_asm * asem, FILE * stream);

void asm_dtor(s_asm * asem);

void make_label_jmp_push_reg(s_asm * asem, size_t n_toks);

//! @brief Function for finding labels in tokens and count each one,
//! write label's value and number of it to labels array in assembler
//!
//! @param [out] asem - pointer to assembler
//! @param [in] n_cmd - number of tokens

void labels_init(s_asm * asem, size_t n_toks);

//! @brief Function that import text from file and write it into the buffer
//! in allocated memory with calloc
//!
//! @param [out] book - pointer to struct with variables for text processing
//! @param [in] stream - pointer to the file with text
//!
//! @return Pointer to array with pointers to string
//! @note Function use get_ptrs to make array with pointers to strings

int count_labels_not_after_jump(s_asm * asem, int i_label);

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
