#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <pthread.h>

#define MAXLON 1000

void *suma(void *h1);
void vectorizar(char *nombre, int numeros[], int *tamano);

typedef struct
{
    int *numeros;
    int inicio;
    int fin;
    int *valor;
}parametros;

int main(int argc, char *argv[])
{
    clock_t start_t = clock();
    clock_t end_t;
    double total_t = 0;

    int numeros[100];
    int valor1 = 0;
    pthread_t t1;
    int valor2 = 0;
    pthread_t t2;
    int tamano = 0;
    if (argc != 2)
    {
        printf("Indica únicamente el nombre de un fichero.\n");
        exit(0);
    }
    vectorizar(argv[1], numeros, &tamano);
    parametros h1;
    h1.numeros = numeros;
    h1.inicio = 0;
    h1.fin = (int)tamano/2;
    h1.valor = &valor1;

    int mitad = tamano/2+1;

    parametros h2;
    h2.numeros = numeros;    
    h2.inicio = (int)(tamano/2);
    h2.fin = tamano;
    h2.valor = &valor2;


    pthread_create(&t1, NULL, suma, &h1);
    pthread_join(t1, NULL);
    pthread_create(&t2, NULL, suma, &h2);
    pthread_join(t2, NULL);

    
    printf("El valor de la suma1 es: %d\n", valor1);
    printf("El valor de la suma2 es: %d\n", valor2);
    int sumaTotal = valor1 + valor2;
    printf("El valor de la suma total es: %d\n", sumaTotal);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("El tiempo total tomado por la CPU es: %f segundos\n", total_t);
    return 0;
}

void vectorizar(char *nombre, int numeros[], int *tamano)
{
    int entero = 0;
    int sum = 0;
    FILE *file;
    file = fopen(nombre, "r");
    char aux = '0';
    int auxv[100];
    int j = 0;
    if (file != NULL)
    {
        while (!feof(file))
        {
            int longitud = 0;
            while (isdigit(aux))
            {
                entero = aux - '0';
                auxv[longitud] = entero;
                aux = fgetc(file);

                longitud++;
            }

            int potencia = 1;
            sum = 0;
            for (int i = 1; i <= longitud; i++)
            {
                int numero = 0;
                numero = auxv[longitud - i] * potencia;
                sum = sum + numero;
                potencia = potencia * 10;
            }
            if (sum != 0)
            {
                numeros[j] = sum;
                j = j + 1;
            }
            aux = fgetc(file);
        }
        *tamano = j;
    }
    else
    {
        exit(1);
    }
    fclose(file);
}

void *suma(void *h1)
{
    parametros *args = (parametros *)h1;
    int inicio = args->inicio;
    int fin = args->fin;
    int *valor = args->valor;
    int *numeros = args->numeros;

    for (int i = inicio; i < fin; i++)
    {
        *valor = *valor + numeros[i];
    }
}