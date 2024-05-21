#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dllist.h"
#include <ctype.h> // Buraya ekleyin
#define MAX_COMMAND_LENGTH 20
#define MAX_OPERAND_LENGTH 100

void process_write(Dllist output_list, char *operand);
void process_erase(Dllist output_list, char *operand);
void process_goto_end(Dllist output_list);
void process_exit(Dllist output_list, FILE *output_file);

int main(int argc, char *argv[]) {
    FILE *input_file;
    FILE *output_file;
    Dllist output_list = new_dllist();

    char command[MAX_COMMAND_LENGTH];
    char operand[MAX_OPERAND_LENGTH];

    char *input_filename = (argc > 1) ? argv[1] : "giris.dat";
    char *output_filename = (argc > 2) ? argv[2] : "data/cikis.dat";

    input_file = fopen(input_filename, "r");

    if (input_file == NULL) {
        printf("Giris dosyasi bulunamadi!\n");
        return 1;
    }

    output_file = fopen(output_filename, "w");

    if (output_file == NULL) {
        printf("Cikis dosyasi olusturulamadi!\n");
        fclose(input_file);
        return 1;
    }

    while (fscanf(input_file, "%s %[^\n]", command, operand) != EOF) {
        if (strcmp(command, "yaz:") == 0) {
            process_write(output_list, operand);
        } else if (strcmp(command, "sil:") == 0) {
            process_erase(output_list, operand);
        } else if (strcmp(command, "sonagit:") == 0) {
            process_goto_end(output_list);
        } else if (strcmp(command, "dur:") == 0) {
            break;
        } else {
            printf("Hatali komut: %s\n", command);
        }
    }

    // Çıkış dosyasına yazma işlemini gerçekleştir
    process_exit(output_list, output_file);

    free_dllist(output_list);

    fclose(input_file);
    fclose(output_file);

    return 0;
}



void process_write(Dllist output_list, char *operand) {
    char *token = strtok(operand, " ");
    int repeat = 1; // Varsayılan tekrar sayısı 1

    while (token != NULL) {
        if (isdigit(token[0])) { // Eleman bir sayı ise
            repeat = atoi(token); // Tekrar sayısını al
        } else if (strcmp(token, "\\b") == 0) { // \b karakteri ise
            dll_append(output_list, new_jval_s(strdup(" "))); // Boşluk ekle
            token = strtok(NULL, " "); // \b'den sonraki karakteri al
            if (token != NULL) {
                continue; // Döngüyü devam ettir, tekrar sayısını artırmadan
            } else {
                break; // Döngüyü sonlandır
            }
        } else if (strcmp(token, "\\n") == 0) { // \n karakteri ise
            // Satır sonu yap
            dll_append(output_list, new_jval_s(strdup("\n")));
        } else { // Diğer durumlar
            // Belirtilen sayı kadar elemanı ardı ardına ekle
            for (int i = 0; i < repeat; i++) {
                dll_append(output_list, new_jval_s(strdup(token)));
            }
        }
        
        token = strtok(NULL, " "); // Bir sonraki elemana geç
    }
}



void process_erase(Dllist output_list, char *operand) {
    char letter = operand[strlen(operand) - 1]; // Silinecek harfi al
    int count = atoi(operand); // Silinecek harf sayısı

    // İmleci listenin sonuna yerleştir
    Dllist curr = dll_last(output_list);

    // Harf bulunana kadar ve belirtilen sayıda silinene kadar işlemleri tekrarla
    while (count > 0 && curr != dll_nil(output_list)) {
        // İmleci listenin başına taşı
        while (dll_prev(curr) != dll_nil(output_list)) {
            curr = dll_prev(curr);
        }

        // Belirtilen harfi bul ve sil
        while (curr != dll_nil(output_list) && count > 0) {
            char val = (char)jval_s(dll_val(curr));
            // İmlecin kaldığı yerdeki harfi bulduysak, sil
            if (strlen(val) == 1 && val[0] == letter) {
                Dllist temp = dll_next(curr); // Bir sonraki düğümü geçici olarak sakla
                dll_delete_node(curr); // Harfi sil
                curr = temp; // İmleci bir sonraki düğüme taşı
                count--; // Silinen harf sayısını azalt
            } else {
                curr = dll_next(curr); // İmleci bir sonraki düğüme taşı
            }
        }
    }
}





void process_goto_end(Dllist output_list) {
    dll_append(output_list, new_jval_s(strdup("\n")));
}

void process_exit(Dllist output_list, FILE *output_file) {
    // output_file parametresini kullanarak dosyaya yazma işlemini gerçekleştir
    for (Dllist curr = dll_first(output_list); curr != dll_nil(output_list); curr = dll_next(curr)) {
        fprintf(output_file, "%s", (char*)jval_s(dll_val(curr)));
    }
}
