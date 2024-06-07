#ifndef CHEAD_H
#define CHEAD_H

//
//  MACROS
//
#define DEFAULT_LINES 10

//
//  Function prototypes
//
void usage(char *argv[]);

void panic(char *argv[]);

void process_files(void (*fnptr)(FILE*, long), int file_count, long count, char *argv[]);

void read_line(FILE *f, long count);

void read_char(FILE *f, long count);

void process_single_file(void (*fnptr)(FILE*, long), long count, char *argv[]);

#endif /* CHEAD_H */
