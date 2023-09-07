/* * Para essa avaliação foi selecionado dois algoritmos, um que calcula quantos anagramas
 * tem uma determinada palavra e outro que calcula a probabilidade de uma distribuição de poisson
 * */

 /* * No primeiro algoritimo (do anagrama) o tempo se comporta de forma fatorial, visto que uma palavra de 3 letras
 * onde as letras nao se repetem, o anagrama eh calculado como 3! e os seis possiveis anagramas são escritos em um arquivo criado no código.
 * Uma palavra onde as letras se repetem o calculo acontece, da seguinte forma N!/X! onde N eh o numero de letras da palavra e X eh a quantidadde
 * que determinada letra se repetiu. Nesse algoritmo são utilizados a função de tempo, sorteio e anagrama.
 *
 * Para os testes de tempo:
 * Palavra pequena = por   tempo: 0.005520  tempo CPU: 0.014000
 * Palavra media= violino   tempo: 0.012891 tempo CPU: 0.015000
 * Palavra grande= Configuracao tempo:143.698897    tempo CPU: 143.702000
 * Palavra BigO= inconstitucionalicimamente tempo:0.093724  tempo CPU: 0.102000, tempo pequeno mas os resultados
 * apresentados nao foram os compativeis.
 *
 * */

/* * No segundo algoritimo(distribuição de poisson o calculo eh o seguinte ((e^−λ)*(λ^x)) / x!, onde x eh
 * o numero designados de sucessos e lambda eh a media, o x pode ser o numero exato de sucessos ou pode ser ate
 * determinado sucesso. Nesse algoritimo são utilizados a função de tempo, potencia e distribbuicao de poisson.
 *
 * Para os testes de tempo: X numero exato de sucesso
 * media fixa = 700   x= 3  tempo:0.011038  tempo CPU: 0.014000
 * media fixa = 700   x= 50   tempo:0.012707    tempo CPU: 0.015000
 * media fixa = 700   x= 108 tempo:0.012234    tempo CPU: 0.014000
 * media fixa = 700   x= 109 tempo:0.010687    tempo CPU: 0.012000 (atingiu o espaço de memoria)
 *
 *
 * media fixa = 700   x= 3  tempo:0.007551   tempo CPU: 0.010000
 * media fixa = 700   x= 50   tempo:0.010018  tempo CPU: 0.013000
 * media fixa = 700   x= 108 tempo:0.012234    tempo CPU: 0.015000
 * media fixa = 700   x= 109 tempo:0.011138    tempo CPU: 0.014000 (atingiu o espaço de memoria)
 * */

//Declaracao das bibliotecas
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>



//função que calcula a potencia, recebe como argumento a base e o expoente
double potencia(double base, unsigned int expoente) {
    if (expoente == 0) return 1.0;
    long double r = potencia( base, expoente / 2);
    r *= r;
    if (expoente % 2 == 1) r *= base;
    return r;
}
//função sorteio recebe como parametro a palavra digitada para fazer anagramas, i que eh a quantia de letras que tem a palavra e o arquivo recem criado
void sorteio(int i, char palavra [], FILE *arq) {
    int l[100];
    int num;

    //enquanto j for menor que a quantia de letras que tem na palavra preenche vetor de 0
    for (int j = 0; j < i; j++) {
        l[j] = 0;
    }

    //enquanto j for menor que a quantia de letras que tem na palavra, sorteia numeros ate 5
    for (int j = 0; j < i; j++) {
        do {
            num = rand() % i;
        } while (l[num] != 0);

        l[num] = 1;

        //escreve no arquivo
        fputc(palavra[num+1], arq);
    }
}

//Recebe o tempo gasto inicial e o tempo incial de CPU e calcula o tempo final
void tempo(struct timeval inicio, clock_t start){

    //declaracoes das variaveis
    clock_t end;
    double cpu_time_used;
    struct timeval fim;

    //finalização do tempo
    gettimeofday(&fim, 0);

    //calculo do tempo gasto
    long seg = fim.tv_sec - inicio.tv_sec;
    long mseg = fim.tv_usec - inicio.tv_usec;
    double tempo_total = seg + mseg * 1e-6;

    //printa o tempo gasto
    printf("Tempo gasto: %f segundos.\n", tempo_total);

    //finaliza o tempo de CPU
    end = clock();

    //calculo do tempo gasto
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    //printa o tempo de CPU
    printf("Tempo gasto de CPU: %f segundos.\n", cpu_time_used);
}


void poisson(){

    //declacao das variaveis
    struct timeval inicio;
    clock_t start;
    int lambda;
    int valor,x;
    double fat=1;
    long double Prob;
    long double Probaux = 0;
    long double AUX;
    double numeroEuler = 2.718281;

    //recebe o lambida
    scanf("%d", &lambda);

    //recebe o x
    printf("E 'x' que sera o numero designados de sucessos.\n");
    scanf("%d", &x);

    //ve se o numero de sucessos é exato ou não
    //se sim, caso 1
    //se não, caso 2
    printf("OK, ja temos quase todas as informacoes necessarias\n");
    printf("Mas antes preciso saber se %d eh o numero exato de sucessos, se sim digite 1, ou voce gostaria de saber a probabilidade ate %d sucessos, se sim digite 2\n",x, x);
    scanf("%d", &valor);

    switch (valor) {

        case 1:
            //inicializacao do tempo
            start = clock();
            gettimeofday(&inicio, 0);

            //calcula fatorial
            for(int i=x; i>1; i--){
                fat= fat*i;
            }

            //calcula a porcentagem da distribuicao de Poisson
            Prob = potencia(lambda,x);
            AUX = potencia(numeroEuler,lambda);
            AUX = 1 / AUX;
            Prob = Prob * AUX;
            Prob = Prob / fat;
            Prob = Prob * 100;

            //printa a probabilidade
            printf("A probabilidade de ocorrer %d eventos dado que a media eh %d eh= %LG\n", x, lambda, Prob);
            break;

        case 2:
            //inicializacao do tempo
            start = clock();
            gettimeofday(&inicio, 0);


            for(int j = x; j >= 0; j--){
                fat = 1;
                //calcula fatorial
                for(int i=j; i>1; i--){
                    fat= fat*i;
                }
                //calcula a porcentagem da distribuicao de Poisson
                Prob = potencia(lambda,j);
                AUX = 1 / (potencia(numeroEuler,lambda));
                Prob = Prob * AUX;
                Prob = Prob / fat;
                Prob = Prob * 100;
                Probaux = Probaux + Prob;

            }

            //printa a probabilidade
            printf("A probabilidade de ocorrer ate %d eventos dado que a media eh %d eh= %LG\n", x, lambda, Probaux);
            break;
        default:
            //chama a função que encerra o tempo
            start = clock();
            gettimeofday(&inicio, 0);
            break;
    }
    //chama a função que encerra o tempo
    tempo(inicio,start);
}

void anagrama(){

    //declaracao das variaveis
    struct timeval inicio;
    clock_t start;
    long int fat = 1;
    int i = 0,c = 1;
    char palavra[100];


    //inicializacao do tempo
    start = clock();
    gettimeofday(&inicio, 0);

    //loop preenchendo o vetor com 0
    for (int j = 0; j < 100; j++) {
        palavra[j] = 0;
    }
    //enquanto j for menor que 100 ou ate digitar enter
    for (int j = 1; j <= 100; ++j) {
        scanf("%c", &palavra[j]);
        if (palavra[j] == '\n') {
            break;
        }
        //loop que compara se tem letra repetida
        for (int k = (j - 1); k >= 0; k--) {
            if (palavra[k] == palavra[j]) {
                c++;
            }
        }
        //calculo de anagrama
        fat = fat * j;
        fat = fat / c;
        c = 1;
        //contador de letras
         i++;

    }
    //printa o numero de anagramas
    printf("Com essa palavra eh possivel formar %ld anagramas\n", fat);

    FILE *arq;

    //cria um arquivo chamadp teste
    if ((arq = fopen("teste.txt", "w")) != NULL) {

        //loop que chama novas palavras sorteadas
        //chama a quantia de anagramas, gerada no calculo e pula as linhas
        for (int j = 0; j < fat; ++j) {
            sorteio(i, palavra, arq);
            fputs("\n", arq);
        }

        //fecha o arquivo
        fclose(arq);

    } else {
        //se der erro na abertura do arquivo imprime mensagem
        fprintf(stderr, "Erro: arquivo nao pode ser aberto\n");
        exit(EXIT_FAILURE);
    }
    //chama a função que encerra o tempo
    tempo(inicio,start);
}
int main() {
    //prints menu
    int escolha;
    printf("Escolha 1 para calcular anagrama e 2 para calcular a Distribuicao de Poisson\n");
    printf("Apos a escolha, digite espaco ou enter e se sua escolha for o primeiro caso, digite a palavra a ser calculada\n");
    printf("Se for o segundo caso, coloque o valor de lambda\n");
    scanf("%d system(\"pause\")", &escolha);

    //se a escolha for 1 vai para a função de anagrama
    //se for 2 vai para poisson
    //se for outra escolha retorna 0
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

/* *Dificuldades encontradas:
 * Na distribuicao de Poisson -> A maior dificuldade encontrada nesse algoritmo foi em relacao a logica matematica
 * tive dificuldade para usar a biblioteca math.h (simplesmente nao funcionou), entao optei por nao utilizar a funcao pronta.
 *
 * Anagrama -> A primeira dificuldade encontrada, foi quanto ao tamanho do vetor char, o loop esperava a quantia que declarava no vetor
 * o sizeof tambem pegava o valor do vetor, entao como saida foi colocada a excessao \n, o que mais tarde se tornou probleme no switch case.
 * Outro problema relacionado ao anagrama foi quanto as letras repetidas, o fatorial usado na distribuicao de poisson, nao era tao eficaz visto que
 * era preciso dividir pela quantia de letras que se repetiam, entao como solucao foi feito o loop que conta quantas vezes a letra se repete e depois
 * divide o fatorial por esse valor.
 * Depois de calculado quantos anagramas era possivel com determinada palavra, as letras precisavam ser embaralhadas, pensei entao em usar o rand()
 * que sorteia valores aleatorios. Incrementar o rand() da forma que embaralhasse os numeros dos vetores da palavra já foi um tremendo desafio, mas após isso
 * o numero repedia diversas vezes dentro de um determinado sorteio, ex: l[j] =  rand() % 5 = l[ 1 2 1 3 5] sendo j ate 5.
 * Esse problema se repetiu diversas vezes ate que enfim foi solucionado a funcao comecou a gerar sempre a mesma semente. Pesquisei a respeito
 * e vi que a solucao seria usar o srand em relação ao tempo, tentei utilizar de diversas formas ate ver que ele era o problema, entao a melhor escolha era nao utilizar ele.
 * Enfim sorteando palavras diferentes em alguns momentos as palavras se repetiam, tentei utilizar strcmp, tentei tambem comparar algorismo por algorismo
 * e ainda nao consegui solucionar.
 *
 * Apos as dificuldades com os problemas em particular, foi feito o swith case para juntas os dois programas em um soh.
 * Mas em ambos os casos apos apertar enter, ao escolher a opcao de escolher um codigo ou outro. Colocava um \n e o anagrama dava 1 que é o valor inicial do fatorial.
 * Para corigir esse erro coloquei o system("pause") com o objetivo de clicar qualquer botao e fazer o papel de enter, mas ao inves disso voce pode escolher a opcao, apertar qualquer tecla e digitar
 * uma palavra. PRONTO, PROBLEMA RESOLVIDO? Nao. Agora na segunda opcao tambem precisava de um segundo argumento, entao foi preciso em caso de ser aprimeira opcao digitar uma palavra
 * e caso for a segunda opcao digitar o valor de lambda.
 *
 * */