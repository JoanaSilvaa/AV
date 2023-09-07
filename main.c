#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double potencia(double base, unsigned int expoente) {
    if (expoente == 0) return 1.0;
    long double r = potencia( base, expoente / 2);
    r *= r;
    if (expoente % 2 == 1) r *= base;
    return r;
}
double expo(double base, unsigned int expoent) {
    if (expoent == 0) return 1.0;
    long double r = expo( base, expoent / 2);
    r *= r;
    if (expoent % 2 == 1) r *= base;
    return r;
}

void sorteio(int i, char palavra [], FILE *arq) {
    int l[100];
    int num;
    char palavraNova[100];

    for (int j = 0; j < i; j++) {
        l[j] = 0;
    }
    for (int j = 0; j < i; j++) {
        do {
            num = rand() % i;
        } while (l[num] != 0);

        l[num] = 1;


        int palavraReps = strcmp(palavraNova, palavra);
        if (palavraReps == 0) {
            palavraNova[i]=palavra[num+1];
            fputc(palavraNova[i], arq);
        } else {
            return sorteio(i, palavra, arq);
        }
    }

}

void tempo(struct timeval inicio, clock_t start){
    clock_t end;
    double cpu_time_used;
    struct timeval fim;
    gettimeofday(&fim, 0);

    long seg = fim.tv_sec - inicio.tv_sec;
    long mseg = fim.tv_usec - inicio.tv_usec;
    double tempo_total = seg + mseg * 1e-6;

    printf("Tempo gasto: %f segundos.\n", tempo_total);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo gasto de CPU: %f segundos.\n", cpu_time_used);
}
void poisson(){
    struct timeval inicio;
    clock_t start;
    int lambda;
    int valor,x;
    double fat=1;
    long double Prob;
    long double Probaux = 0;
    long double AUX;
    double numeroEuler = 2.718281;

    scanf("%d", &lambda);

    printf("E 'x' que sera o numero designados de sucessos.\n");
    scanf("%d", &x);

    printf("OK, ja temos quase todas as informacoes necessarias\n");
    printf("Mas antes preciso saber se %d eh o numero exato de sucessos, se sim digite 1, ou voce gostaria de saber a probabilidade ate %d sucessos, se sim digite 2\n",x, x);
    scanf("%d", &valor);

    switch (valor) {

        case 1:
            start = clock();
            gettimeofday(&inicio, 0);
            for(int i=x; i>1; i--){
                fat= fat*i;
            }
            Prob = potencia(lambda,x);
            AUX = expo(numeroEuler,lambda);
            AUX = 1 / AUX;
            Prob = Prob * AUX;
            Prob = Prob / fat;
            Prob = Prob * 100;

            printf("A probabilidade de ocorrer %d eventos dado que a media eh %d eh= %LG\n", x, lambda, Prob);
            break;

        case 2:
            start = clock();
            gettimeofday(&inicio, 0);
            for(int j = x; j >= 0; j--){

                fat = 1;
                for(int i=j; i>1; i--){
                    fat= fat*i;
                }
                Prob = potencia(lambda,j);
                AUX = 1 / (expo(numeroEuler,lambda));
                Prob = Prob * AUX;
                Prob = Prob / fat;
                Prob = Prob * 100;
                Probaux = Probaux + Prob;

            }

            printf("A probabilidade de ocorrer ate %d eventos dado que a media eh %d eh= %LG\n", x, lambda, Probaux);
            break;
        default:
            start = clock();
            gettimeofday(&inicio, 0);
            break;
    }
    tempo(inicio,start);
}

void anagrama(){

    struct timeval inicio;
    clock_t start;
    long int fat = 1;
    int i = 0,c = 1;
    char palavra[100];

    start = clock();
    gettimeofday(&inicio, 0);

    for (int j = 0; j < 100; j++) {
        palavra[j] = 0;
    }
    for (int j = 1; j <= 100; ++j) {
        scanf("%c", &palavra[j]);
        if (palavra[j] == '\n') {
            break;
        }
        for (int k = (j - 1); k >= 0; k--) {
            if (palavra[k] == palavra[j]) {
                c++;
            }
        }
        fat = fat * j;
        fat = fat / c;
        c = 1;
        i++;

    }

    printf("Com essa palavra eh possivel formar %ld anagramas\n", fat);

    FILE *arq;

    if ((arq = fopen("teste.txt", "w")) != NULL) {

        for (int j = 0; j < fat-1; ++j) {
            sorteio(i, palavra, arq);
            fputs("\n", arq);
        }

        fclose(arq);
    } else {
        fprintf(stderr, "Erro: arquivo nao pode seraberto\n");
        exit(EXIT_FAILURE);
    }
    tempo(inicio,start);
}
int main() {
    int escolha;
    printf("Escolha 1 para calcular anagrama e 2 para calcular a Distribuicao de Poisson\n");
    printf("Apos a escolha, digite espaco ou enter e se sua escolha for o primeiro caso, digite a palavra a ser calculada\n");
    printf("Se for o segundo caso, coloque o valor de lambda\n");
    scanf("%d system(\"pause\")", &escolha);


    switch (escolha) {
        case 1:
            anagrama();
            break;
        case 2:
            poisson();
        default:
            return 0;
    }
    return 0;
}
