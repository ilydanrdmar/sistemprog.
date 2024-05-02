#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "fields.h"

#define talloc(ty, sz) (ty *)malloc((sz) * sizeof(ty))
#define strdup(s) ((char *)strcpy(talloc(char, strlen(s) + 1), s))

static InputStruct make_input_struct(const char *filename, const char *key) {
    InputStruct is;
    int file;

    if (strcmp(key, "f") == 0) {
        file = 1;
    } else if (strcmp(key, "p") == 0) {
        file = 0;
    } else {
        return NULL;
    }

    is = talloc(struct inputstruct, 1);

    is->text1[MAXLEN - 1] = '\0';
    is->NF = 0;
    is->line = 0;
    if (filename == NULL) {
        is->name = "stdin";
        is->f = stdin;
    } else {
        is->name = filename;
        is->file = file;
        if (file) {
            is->f = fopen(filename, "r");
            if (is->f == NULL) {
                fprintf(stderr, "Dosya açılamadı: %s\n", filename);
                free(is);
                return NULL;
            }
        } else {
            is->f = popen(filename, "r");
            if (is->f == NULL) {
                fprintf(stderr, "Komut açılamadı: %s\n", filename);
                free(is);
                return NULL;
            }
        }
    }
    return is;
}

InputStruct new_input_struct(const char *filename) {
    return make_input_struct(filename, "f");
}

InputStruct pipe_input_struct(const char *command) {
    return make_input_struct(command, "p");
}

int get_line(InputStruct is) {
    int i, len;
    int f;
    char *tmp;
    char lastchar;
    char *line;

    is->NF = 0;

    if (fgets(is->text1, MAXLEN - 1, is->f) == NULL) {
        is->NF = -1;
        fprintf(stderr, "Dosya sonuna ulaşıldı veya okuma hatası oluştu.\n");
        return -1;
    }

    is->line++;
    strcpy(is->text2, is->text1);

    line = is->text2;
    lastchar = ' ';
    for (i = 0; line[i] != '\0' && i < MAXLEN - 1; i++) {
        if (isspace(line[i])) {
            lastchar = line[i];
            line[i] = '\0';
        } else {
            if (isspace(lastchar)) {
                is->fields[is->NF] = line + i;
                is->NF++;
            }
            lastchar = line[i];
        }
    }
    return is->NF;
}

void jettison_input_struct(InputStruct is) {
    if (is->f != stdin) {
        if (is->file) {
            fclose(is->f);
        } else {
            pclose(is->f);
        }
    }
    free(is);
    return;
}

void handle_sonagit(InputStruct is, char *buffer) {
    char line[MAXLEN];
    int last_line = 0; // Son okunan satırın indeksi
    // Sonagit komutuna kadar olan tüm satırları oku ve buffer'a ekle
    while (get_line(is) != -1) {
        if (strcmp(is->text1, "sonagit:\n") == 0) {
            // Sonagit komutu geldi, döngüden çık
            break;
        }
        strcat(buffer, is->text1); // Satırı tampona ekle
        last_line = is->line; // Son okunan satırın indeksini güncelle
    }
    // Son okunan satırın sonuna cursoru yerleştir
    fseek(is->f, 0, SEEK_SET);
    for (int i = 0; i < last_line; i++) {
        get_line(is); // Cursoru son okunan satırın sonuna taşı
    }
}
