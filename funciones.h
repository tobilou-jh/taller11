#ifndef FUNCIONES_H
#define FUNCIONES_H

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    int anio_publicacion;
    int estado; // 0 = DISPONIBLE, 1 = PRESTADO
    char cedula[20];
} Libro;

// Prototipos de funciones
void quitarSaltoLinea(char *cadena);
int buscarLibroPorID(Libro libros[], int totalLibros, int id);
void agregarLibro(Libro libros[], int *totalLibros, int maxLibros);
void prestarLibro(Libro libros[], int totalLibros);
void devolverLibro(Libro libros[], int totalLibros);
void buscarPorCedula(Libro libros[], int totalLibros);
void imprimirTodosLosLibros(Libro libros[], int totalLibros);
void eliminarLibro(Libro libros[], int *totalLibros);
void editarLibro(Libro libros[], int totalLibros);

#endif