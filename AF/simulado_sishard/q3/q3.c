// Leia o PDF ou MD antes de iniciar este exercício!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

struct sigaction s_sigint;
// Variável GLOBAL para armazenar o valor de PI aproximado
double pi = 0.0;
int kill_s = 0;

void sigint_handler(int num) {
    printf("\nChamou Ctrl+C\n");
    s_sigint.sa_handler = SIG_DFL;
    sigaction(SIGINT, &s_sigint, NULL);
    printf("O valor do PI %f\n", pi);

    char valor_de_PI[60];
    sprintf(valor_de_PI, "%f\n", pi);

    int file = open("valor_de_pi.txt", O_WRONLY | O_CREAT, 0700);
    int size_str = strlen(valor_de_PI);
    write(file, valor_de_PI, size_str);

    kill(getpid(), SIGINT);
}

// Função que gera um numero aleatorio uniformemente entre 0.0 e 1.0
// Você não deve alterar esta função
double random_zero_one() {
    return (double)random()/(double)RAND_MAX;
}

// Função que calcula o valor de pi por simulação (Monte Carlo)
// Você não deve alterar esta função
double aproxima_pi() {
    long dentro = 0;
    long total_pontos = 0;

    double x,y,d;
    while (1) {
        x = random_zero_one();
        y = random_zero_one();
        d = x*x + y*y;
        if (d<=1) {
            dentro++;
        }
        total_pontos++;
        pi = 4.0 * ((double)dentro/(double)total_pontos);
        if (random_zero_one() < 0.008) {
            sleep(1);
        }
    }
}

// Crie AQUI a função que exporta o valor de pi para um arquivo chamado pi.txt
// Esta função deve ser chamada pelo handler quando este for acionado

// Crie AQUI a função que será o handler do sinal

int main() {
    // Exiba o PID deste processo
    int id = getpid();
    printf("O id do processo é %d\n", id);
    // Registre AQUI seu handler para o sinal SIGINT!
    s_sigint.sa_handler = sigint_handler;
    sigemptyset(&s_sigint.sa_mask); 
    s_sigint.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s_sigint, NULL);

    srand(time(NULL));
    aproxima_pi();

    return 0;
}