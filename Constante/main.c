#include <time.h>
#include <sys/time.h>
#include <stdio.h>

//Função que calcula o tempo em segundos
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
int main(){
    struct timeval inicio;
    clock_t start;
    unsigned int lambda;
    unsigned int valor,x;
    double fat=1;
    long double Prob;
    long double Probaux = 0;
    long double AUX = 0;
    double numeroEuler = 2.718281;

    printf("Distribuicao de Poisson eh aplicavel quando o numero de possiveis ocorrencias discretas eh muito maior o que \n"
           "o numero medio de ocorrencias em um determinado intervalo de tempo ou espaco.\n\n");

    printf("Para efetuar a distribuicao precisaremos primeiro saber o numero medio em determinado intervalo de tempo. (Lambda)\n");
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

            printf("A probabilidade de ocorrer %d eventos dado que a media é %d eh= %LG\n", x, lambda, Prob);
            tempo(inicio,start);
            break;

        case 2:
            start = clock();
            gettimeofday(&inicio, 0);
            for(int j = x; j >= 0; j--){

                fat = 1;
                Prob = 0;
                AUX = 0;
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
            tempo(inicio,start);
            break;
        default:
            return 0;
    }
    return 0;
}