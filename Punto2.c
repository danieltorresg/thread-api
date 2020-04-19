#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void *factorial(void *numero);

int main(int argc, char *argv[])
{

    pthread_t threads[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        pthread_create(&threads[i - 1], NULL, &factorial, argv[i]);               
    }
    for (int i = 1; i < argc; i++)
    {
        pthread_join(threads[i - 1], NULL);
        printf("El hilo número %d ha terminado\n", i);
    }

    return 0;
}

void *factorial(void *numero)
{
    int n = atoi(numero);
    long long int resultado = 1;
    int num;
    for (num = 2; num <= n; num++)
    {
        resultado = resultado * num;
        printf("Factorial de %d, resultado parcial %lld\n", n, resultado);
    }
    printf("El factorial de %d es %lld\n", n, resultado);
}