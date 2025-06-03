#include <stdio.h>
#include <string.h>
#include "funciones.h"

void quitarSaltoLinea(char *cadena) {
    int i = 0;
    while (cadena[i] != '\0') {
        if (cadena[i] == '\n') {
            cadena[i] = '\0';
            break;
        }
        i++;
    }
}

int buscarLibroPorID(Libro libros[], int totalLibros, int id) {
    for (int i = 0; i < totalLibros; i++) {
        if (libros[i].id == id) {
            return i;
        }
    }
    return -1;
}

void agregarLibro(Libro libros[], int *totalLibros, int maxLibros) {
    if (*totalLibros >= maxLibros) {
        printf("No se pueden agregar mas libros (maximo %d).\n", maxLibros);
        return;
    }
    Libro temp;
    printf("Ingrese el titulo del libro: ");
    fflush(stdin);
    fgets(temp.titulo, sizeof(temp.titulo), stdin);
    quitarSaltoLinea(temp.titulo);

    printf("Ingrese el autor del libro: ");
    fflush(stdin);
    fgets(temp.autor, sizeof(temp.autor), stdin);
    quitarSaltoLinea(temp.autor);

    printf("Ingrese el ano de publicacion: ");
    scanf("%d", &temp.anio_publicacion);
    fflush(stdin);

    printf("Ingrese el codigo unico (ID) del libro: ");
    scanf("%d", &temp.id);
    fflush(stdin);

    if (buscarLibroPorID(libros, *totalLibros, temp.id) != -1) {
        printf("Ya existe un libro con ese codigo.\n");
        return;
    }

    temp.estado = 0; // DISPONIBLE
    temp.cedula[0] = '\0';
    libros[*totalLibros] = temp;
    (*totalLibros)++;

    printf("Libro agregado exitosamente.\n");
}

void prestarLibro(Libro libros[], int totalLibros) {
    int id;
    imprimirTodosLosLibros(libros, totalLibros);
    printf("Ingrese el ID del libro a prestar: ");
    scanf("%d", &id);
    fflush(stdin);
    int idx = buscarLibroPorID(libros, totalLibros, id);
    if (idx == -1) {
        printf("Libro no encontrado.\n");
        return;
    }
    if (libros[idx].estado == 1) {
        printf("El libro ya esta prestado.\n");
        return;
    }
    printf("Ingrese la cedula del usuario: ");
    fflush(stdin);
    fgets(libros[idx].cedula, sizeof(libros[idx].cedula), stdin);
    quitarSaltoLinea(libros[idx].cedula);
    libros[idx].estado = 1; // PRESTADO
    printf("Libro prestado exitosamente.\n");
    
}

void devolverLibro(Libro libros[], int totalLibros) {
    int id;
    imprimirTodosLosLibros(libros, totalLibros);
    printf("Ingrese el ID del libro a devolver: ");
    scanf("%d", &id);
    fflush(stdin);
    int idx = buscarLibroPorID(libros, totalLibros, id);
    if (idx == -1) {
        printf("Libro no encontrado.\n");
        return;
    }
    if (libros[idx].estado == 0) {
        printf("El libro ya esta disponible.\n");
        return;
    }
    libros[idx].estado = 0; // DISPONIBLE
    libros[idx].cedula[0] = '\0'; // Limpiar cedula
    printf("Libro devuelto exitosamente.\n");
    
}

void buscarPorCedula(Libro libros[], int totalLibros) {
    char cedula[20];
    int encontrado = 0;
    printf("Ingrese la cedula del usuario: ");
    fflush(stdin);
    fgets(cedula, sizeof(cedula), stdin);
    quitarSaltoLinea(cedula);
    for (int i = 0; i < totalLibros; i++) {
        if (libros[i].estado == 1 && strcmp(libros[i].cedula, cedula) == 0) {
            printf("ID: %d | Titulo: %s | Autor: %s | Ano: %d\n", libros[i].id, libros[i].titulo, libros[i].autor, libros[i].anio_publicacion);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontraron libros prestados a esa cedula.\n");
    }
}

void imprimirTodosLosLibros(Libro libros[], int totalLibros) {
    printf("\n%-15s | %-30s | %-20s | %-6s | %-11s\n", "ID", "Titulo", "Autor", "Publicacion", "Estado");
    printf("-------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < totalLibros; i++) {
        printf("%-15d | %-30s | %-20s | %-11d | %-11s\n",
            libros[i].id,
            libros[i].titulo,
            libros[i].autor,
            libros[i].anio_publicacion,
            libros[i].estado == 0 ? "DISPONIBLE" : "PRESTADO"
        );
    }
    if (totalLibros == 0) {
        printf("No hay libros registrados.\n");
    }
}

void eliminarLibro(Libro libros[], int *totalLibros) {
    int id;
    printf("Ingrese el ID del libro a eliminar: ");
    scanf("%d", &id);
    fflush(stdin);
    int idx = buscarLibroPorID(libros, *totalLibros, id);
    if (idx == -1) {
        printf("Libro no encontrado.\n");
        return;
    }
    for (int i = idx; i < (*totalLibros) - 1; i++) {
        libros[i] = libros[i + 1];
    }
    (*totalLibros)--;
    printf("Libro eliminado exitosamente.\n");
    
}

void editarLibro(Libro libros[], int totalLibros) {
    int id;
    printf("Ingrese el ID del libro a editar: ");
    scanf("%d", &id);
    fflush(stdin);
    int idx = buscarLibroPorID(libros, totalLibros, id);
    if (idx == -1) {
        printf("Libro no encontrado.\n");
        return;
    }

    printf("Editar titulo actual (%s): ", libros[idx].titulo);
    fgets(libros[idx].titulo, sizeof(libros[idx].titulo), stdin);
    quitarSaltoLinea(libros[idx].titulo);

    printf("Editar autor actual (%s): ", libros[idx].autor);
    fgets(libros[idx].autor, sizeof(libros[idx].autor), stdin);
    quitarSaltoLinea(libros[idx].autor);

    printf("Editar ano de publicacion actual (%d): ", libros[idx].anio_publicacion);
    scanf("%d", &libros[idx].anio_publicacion);
    fflush(stdin);

    printf("Libro editado exitosamente.\n");
}