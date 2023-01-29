#ifndef ASSIGN4_H
#define ASSIGN4_H

typedef struct {
    char name[80];
    char schedule[4];
    unsigned hours;
    unsigned size;
    unsigned padding;
} COURSE;

void create(FILE* courseFile);
void update(FILE* courseFile);
void read(FILE* courseFile);
void fdelete(FILE* courseFile);

#endif

