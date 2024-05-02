#ifndef JVAL_H
#define JVAL_H

typedef struct Jval {
    union {
        int i;
        long l;
        float f;
        double d;
        char c;
        unsigned char uc;
        short sh;
        unsigned short ush;
        unsigned int ui;
        char *s;
        void *v;
    } j;
} Jval;

Jval new_jval_i(int i);
Jval new_jval_l(long l);
Jval new_jval_f(float f);
Jval new_jval_d(double d);
Jval new_jval_c(char c);
Jval new_jval_uc(unsigned char uc);
Jval new_jval_sh(short sh);
Jval new_jval_ush(unsigned short ush);
Jval new_jval_ui(unsigned int ui);
Jval new_jval_s(char *s);
Jval new_jval_v(void *v);

int jval_i(Jval j);
long jval_l(Jval j);
float jval_f(Jval j);
double jval_d(Jval j);
char jval_c(Jval j);
unsigned char jval_uc(Jval j);
short jval_sh(Jval j);
unsigned short jval_ush(Jval j);
unsigned int jval_ui(Jval j);
char *jval_s(Jval j);
void *jval_v(Jval j);

#endif
