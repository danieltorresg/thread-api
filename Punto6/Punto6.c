#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <sys/queue.h>

#define MAXLON 1000

void *ejecutar(void *archivo);
float *textoAArreglo(char *, int *cantNotas);
char *csvAString(char *);
float calcularMedia(float *notas, int cantNotas);
void calculate_standard_deviation(float *notas, int cantNotas, float media);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Por favor ingresa los parámetros: nombre del csv y número de hilos\n");
        exit(0);
    }

    int cantHilos = atoi((char *)argv[2]);
    pthread_t hilosv[cantHilos];

    for (int i = 0; i < cantHilos; i++)
    {
        pthread_create(&hilosv[i], NULL, &ejecutar, argv[1]);
    }

    for (int i = 0; i < cantHilos; i++)
    {
        pthread_join(hilosv[i], NULL);
    }

    return 0;
}

void *ejecutar(void *archivo)
{
    int cantNotas = 0;

    char *cadena = csvAString(archivo);

    float *notas = textoAArreglo(cadena, &cantNotas);

    float media = calcularMedia(notas, cantNotas);
    calculate_standard_deviation(notas, cantNotas, media);
}

char *csvAString(char *nombre)
{
    FILE *file;
    file = fopen(nombre, "r");
    char aux;
    char *cadena = (char *)malloc(1 * sizeof(char));

    if (file != NULL)
    {
        aux = fgetc(file);
        while (aux != EOF)
        {
            char str[2] = "\0"; /* gives {\0, \0} */
            str[0] = aux;
            cadena = (char *)realloc(cadena, (strlen(cadena) + strlen(str) + 1) * sizeof(char));
            strcat(cadena, str);
            aux = fgetc(file);
        }
        return cadena;
    }
    else
    {
        exit(1);
    }
    fclose(file);
}

float *textoAArreglo(char *cadena, int *cantNotas)
{
    int tamano = 1;
    int pos = 0;
    char delim[] = ";";
    char *aux = strtok(cadena, delim);
    float *notas = (float *)malloc(0 * sizeof(float));
    while (aux != NULL)
    {

        notas = (float *)realloc(notas, (tamano) * sizeof(float));
        float numerito = atof(aux);
        *(notas + pos) = numerito;

        aux = strtok(NULL, delim);
        tamano = tamano + 1;
        pos = pos + 1;
        *cantNotas = *cantNotas + 1;
    }
    return notas;
}

float calcularMedia(float *notas, int cantNotas)
{
    int n = cantNotas;
    float sum = 0;
    float media = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum = sum + notas[i];
    }

    media = sum / n;
    return media;
}

void calculate_standard_deviation(float *notas, int cantNotas, float media)
{
    int n = cantNotas;
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum = sum + pow((notas[i] - media), 2);
    }

    float factor = 1 / ((float)n - 1);
    float s = sqrt(factor * sum);
    printf("El valor de la Desviación Estandar es: %f\n", s);
}