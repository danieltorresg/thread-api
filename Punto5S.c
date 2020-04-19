#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#define MAXLON 1000
void suma(char *);
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Indica el nombre de un fichero.\n");
        exit(0);
    }
    suma(argv[1]);
    return 0;
}
void suma(char *nombre)
{
    int pos, sum = 0, leidos;
    char cadena[MAXLON];
    int entero;
    int fd;
    char aux[10];
    fd = open(nombre, O_RDONLY);
    while ((leidos = read(fd, cadena, MAXLON)) != 0)
    {
        for (pos = 0; pos < leidos; pos++)
        {
            int longitud = 0;
            while ((isdigit(cadena[pos])) && (pos < leidos))
            {
                entero = cadena[pos] - '0';
                aux[longitud] = entero;
                pos++;
                longitud++;
            }

            int potencia = 1;
            for (int i = 1; i <= longitud; i++)
            {
                int numero = 0;
                numero = aux[longitud - i] * potencia;
                sum = sum + numero;
                potencia = potencia * 10;
            }   
        }
    }
    printf("La suma de los números del fichero %s es: %d \n", nombre, sum);
    close(fd);
}