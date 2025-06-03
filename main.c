#include <stdio.h>
#include "funciones.h"

int main() {
    Libro libros[10];
    int totalLibros = 0;
    int opcion;
    int maxLibros = 10;

    do {
        printf("\n--- Biblioteca ---\n");
        printf("1. Agregar libro\n");
        printf("2. Prestar libro\n");
        printf("3. Devolver libro\n");
        printf("4. Buscar libro por cedula de usuario\n");
        printf("5. Imprimir todos los libros\n");
        printf("6. Eliminar libro\n");
        printf("7. Editar libro\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: agregarLibro(libros, &totalLibros, maxLibros); break;
            case 2: prestarLibro(libros, totalLibros); break;
            case 3: devolverLibro(libros, totalLibros); break;
            case 4: buscarPorCedula(libros, totalLibros); break;
            case 5: imprimirTodosLosLibros(libros, totalLibros); break;
            case 6: eliminarLibro(libros, &totalLibros); break;
            case 7: editarLibro(libros, totalLibros); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}

