#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>

#define MAXLON 1000

void suma(int *numeros, int inicio, int fin, int *valor);
void vectorizar(char *nombre, int numeros[], int *tamano);
int main(int argc, char *argv[])
{
    clock_t start_t = clock();
    clock_t end_t;
    double total_t = 0;

    int numeros[100];
    int valor = 0;
    int tamano = 0;
    if (argc != 2)
    {
        printf("Indica únicamente el nombre de un fichero.\n");
        exit(0);
    }
    vectorizar(argv[1], numeros, &tamano);
    suma(numeros, 0, tamano, &valor);
    printf("El valor de la suma es: %d\n", valor);
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

void suma(int *numeros, int inicio, int fin, int *valor)
{
    for (int i = inicio; i < fin; i++)
    {
        *valor = *valor + numeros[i];
    }
}