#ifndef _FIELDS_H_
#define _FIELDS_H_

#include <stdio.h>

#define MAXLEN 1001
#define MAXFIELDS 1000

typedef struct inputstruct {
    char *name;               /* File name */
    FILE *f;                  /* File descriptor */
    int line;                 /* Line number */
    char text1[MAXLEN];       /* The line */
    char text2[MAXLEN];       /* Working -- contains fields */
    int NF;                   /* Number of fields */
    char *fields[MAXFIELDS];  /* Pointers to fields */
    int file;                 /* 1 for file, 0 for popen */
} *IS;

extern IS new_inputstruct(/* FILENAME -- NULL for stdin */);
extern IS pipe_inputstruct(/* COMMAND -- NULL for stdin */);
extern int get_line(/* IS */); /* returns NF, or -1 on EOF.  Does not close the file */
extern void jettison_inputstruct(/* IS */);  /* frees the IS and fcloses the file */

// Additional functions for handling commands
void sonagit(IS input);
void sil(IS input, char *silinecek);
void dur(IS input);

#endif /* _FIELDS_H_ */
//////////// ya da boyle yazılcak.
#ifndef _FIELDS_H_
#define _FIELDS_H_

#include <stdio.h>

// Maksimum satır uzunluğu
#define MAXLEN 1001

// Giriş yapısının tanımı
typedef struct inputstruct {
    char *name;               /* Dosya adı */
    FILE *f;                  /* Dosya işaretçisi */
    int line;                 /* Satır numarası */
    char text1[MAXLEN];       /* Satır */
    char text2[MAXLEN];       /* Çalışma belleği -- alanları içerir */
    int NF;                   /* Alan sayısı */
    char *fields[MAXFIELDS];  /* Alan işaretçileri */
    int file;                 /* Dosya için 1, popen için 0 */
} *IS;

// Yeni bir giriş yapısı oluşturur
extern IS new_input_struct(const char *filename);

// Boru hattı giriş yapısı oluşturur
extern IS pipe_input_struct(const char *command);

// Satır alır
extern int get_line(IS);

// Giriş yapısını temizler ve dosyayı kapatır
extern void jettison_input_struct(IS);

// Maksimum alan sayısı
#define MAXFIELDS 1000

#endif /* _FIELDS_H_ */




