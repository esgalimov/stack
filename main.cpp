#include "header.h"

FILE * log_file = NULL;

int main(void)
{
    log_file = fopen("log.txt", "w");
    if (log_file == NULL)
    {
        printf("Can't open log file!");
        return 1;
    }

    test_stack();

    FILE * fp = NULL;
    fp = fopen("./input.txt", "r");
    if (fp == NULL)
    {
        printf("Can not open file\n");
        return 1;
    }

    //run_cpu(fp);

    fclose(fp);
    fclose(log_file);
    return 0;
}
