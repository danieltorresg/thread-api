#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void *factorial(void *numero);

int main(int argc, char *argv[])
{
    
    pthread_t t1;
    pthread_t t2;
    
    if (argc == 3)
    {
        pthread_create(&t1, NULL, &factorial, argv[1]);
        pthread_create(&t2, NULL, &factorial, argv[2]);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
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
    printf ("El factorial de %d es %lld\n", n, resultado);
}