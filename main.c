#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct palavrasRepetidas{
    char texto[101];
};

void sorteio(int i, char palavra [100], FILE *arq) {
    srand(time(NULL));
    struct palavrasRepetidas palavraRep;
    int l[100];
    int palavraReps;

    for (int j = 0; j < i; j++) {
        l[j] = 0;
    }
    for (int j = 0; j < i; j++) {
        //srand(time(NULL));
        int num;
        do {
            num = rand() % i;
        } while (l[num] != 0);

        l[num] = 1;
        palavraReps = strcmp(palavra, palavraRep.texto);
        if (palavraReps == 0) {
            fputc(palavra[num + 1], arq);
        } else {
            return sorteio(i, palavra, arq);
        }

       /* for (int b = 0; b < i; ++b) {
            if (palavraRep.texto[b] != palavra[num+1]) {
                fputc(palavra[num + 1], arq);
                printf("%c",palavra[num+1]);
            }
            sorteio(i, palavra, arq);
        }*/
    }
}
int main() {
    int i = 0, fat = 1, c = 1, l[100];

    char palavra[100];

    for (int j = 0; j < 100; j++) {
        palavra[j] = 0;
    }

    printf("Entre com uma palavra para decifrarmos possiveis anagramas:");
    for (int j = 1; j <= 100; ++j) {
        scanf("%c", &palavra[j]);
        if (palavra[j] == '\n') {
            break;
        }
        for (int k = (j - 1); k >= 0; k--) {
            if (palavra[k] == palavra[j]) {
                c++;
            } else {
            }
        }
        fat = fat * j;
        fat = fat / c;
        c = 1;
        i++;

    }

    printf("Com essa palavra eh possivel formar %d anagramas\n", fat);

    FILE *arq;
    srand(time(NULL));
    if ((arq = fopen("teste.txt", "w")) != NULL) {

        for (int j = 0; j < fat; ++j) {
            sorteio(i, palavra, arq);
            fputs("\n", arq);
        }

        fclose(arq);
    } else {
        fprintf(stderr, "Erro: arquivo nao pode seraberto\n");
        exit(EXIT_FAILURE);
    }
    return 0;

}