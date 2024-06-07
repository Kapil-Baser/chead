#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "chead.h"


int main(int argc, char *argv[])
{
    int opt;
    int nflag = 0, cflag = 0;
    long count = DEFAULT_LINES;
    char *endptr;
    while ((opt = getopt(argc, argv, "n:c:")) != -1)
    {
        switch (opt)
        {
            case 'n':
            {
                nflag++;
                count = strtol(optarg, &endptr, 10);
                break;
            }
            case 'c':
            {
                cflag++;
                count = strtol(optarg, &endptr, 10);
                break;
            }
            default: /* ? */
            {
                usage(argv);
            }
        }
    }
// Check if multiple files needs to be processed
    int file_count = argc - optind;

    if (file_count > 1)
    {
        // Checking if cflag was given, if not we just process the lines instead, even if nflag was not given.
        if (cflag)
        {
            process_files(read_char, file_count, count, argv);
        }
        else
        {
            process_files(read_line, file_count, count, argv);
        }
        return 0;
    }

    if (file_count)
    {
        if (cflag)
        {
            process_single_file(read_char, count, argv);
        }
        else
        {
            process_single_file(read_line, count, argv);
        }
    }
    else
    {
        read_line(stdin, count);
    }

    return 0;
}

/**
 * @brief reads the given number of lines from a file or stdin stream.
 *
 * @f file pointer to read from.
 * @count the number of lines to read and then print out.
 */
void read_line(FILE *f, long count)
{
    char buf[1024];
    while (count != 0 && fgets(buf, sizeof(buf) / sizeof(buf[0]), f) != NULL)
    {
        printf("%s", buf);
        count--;
    }
}

/**
 * @brief reads the given number of characters from a file or stdin stream.
 *
 * @f file pointer to read from.
 * @count the number of characters to read and then print out.
 */
void read_char(FILE *f, long count)
{
    int c;

    while (count != 0 && (c = fgetc(f)) != EOF)
    {
        printf("%c", c);
        count--;
    }
}

/**
 * @brief prints out proper usages for program.
 *
 * @*argv[] the pointer to array of strings that will print out the program name.
 */
void usage(char *argv[])
{
    printf("Usage: %s [-n number] [file...]\n", argv[0]);
    exit(1);
}

/**
 * @brief prints out an error in case the given file could not be opened.
 *
 * @*argv[] the pointer to array of strings where file name is located.
 */
void panic(char *argv[])
{
    fprintf(stderr, "Error opening file: %s\n", argv[optind]);
    exit(2);
}

/**
 * @brief helper function which will print out multiple files one after another.
 *
 * @funptr function pointer that will either print lines or characters.
 * @file_count the number of files to read and print out.
 * @count the number of lines or characters to print.
 * @*argv[] the pointer to array of strings which contains the file names.
 */
void process_files(void (*fnptr)(FILE*, long), int file_count, long count, char *argv[])
{
    do
    {
        printf("==> %s <==\n", argv[optind]);
        FILE *fp = fopen(argv[optind], "r");
        if (fp == NULL)
        {
            panic(argv);
        }
        fnptr(fp, count);
        fclose(fp);
        optind++;
        file_count--;
    }while (file_count != 0);
}

/**
 * @brief reads a given file and prints out the given number of lines or characters.
 *
 * @fnptr function pointer that will either print lines or characters.
 * @count the number of lines or characters to print.
 * @*argv[] the pointer to array of strings which contains the file names.
 */
void process_single_file(void (*fnptr)(FILE*,long), long count, char *argv[])
{
    FILE *fp = fopen(argv[optind], "r");
    if (fp == NULL)
    {
        panic(argv);
    }

    fnptr(fp, count);
    fclose(fp);
}
