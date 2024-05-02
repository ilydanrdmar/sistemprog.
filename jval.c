#include "jval.h"
#include <stdlib.h>

Jval new_jval_i(int i) {
    Jval j;
    j.j.i = i;
    return j;
}

Jval new_jval_l(long l) {
    Jval j;
    j.j.l = l;
    return j;
}

Jval new_jval_f(float f) {
    Jval j;
    j.j.f = f;
    return j;
}

Jval new_jval_d(double d) {
    Jval j;
    j.j.d = d;
    return j;
}

Jval new_jval_c(char c) {
    Jval j;
    j.j.c = c;
    return j;
}

Jval new_jval_uc(unsigned char uc) {
    Jval j;
    j.j.uc = uc;
    return j;
}

Jval new_jval_sh(short sh) {
    Jval j;
    j.j.sh = sh;
    return j;
}

Jval new_jval_ush(unsigned short ush) {
    Jval j;
    j.j.ush = ush;
    return j;
}

Jval new_jval_ui(unsigned int ui) {
    Jval j;
    j.j.ui = ui;
    return j;
}

Jval new_jval_s(char *s) {
    Jval j;
    j.j.s = s;
    return j;
}

Jval new_jval_v(void *v) {
    Jval j;
    j.j.v = v;
    return j;
}

int jval_i(Jval j) {
    return j.j.i;
}

long jval_l(Jval j) {
    return j.j.l;
}

float jval_f(Jval j) {
    return j.j.f;
}

double jval_d(Jval j) {
    return j.j.d;
}

char jval_c(Jval j) {
    return j.j.c;
}

unsigned char jval_uc(Jval j) {
    return j.j.uc;
}

short jval_sh(Jval j) {
    return j.j.sh;
}

unsigned short jval_ush(Jval j) {
    return j.j.ush;
}

unsigned int jval_ui(Jval j) {
    return j.j.ui;
}

char *jval_s(Jval j) {
    return j.j.s;
}

void *jval_v(Jval j) {
    return j.j.v;
}
