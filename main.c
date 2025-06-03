#include <stdio.h>
#include <string.h>

int totalLibros = 0;
int maxLibros = 100;
int maxTitulo = 100;
int maxAutor = 100;
int maxCedula = 20;

void quitarSaltoLinea(char *cadena);
int buscarLibroPorID(int id);
void agregarLibro();
void prestarLibro();
void buscarPorCedula();
void mostrarDisponibles();

// Arreglos paralelos para los atributos de los libros
char titulos[100][100];
char autores[100][100];
int ids[100];
int estados[100]; // 0 = DISPONIBLE, 1 = PRESTADO
char cedulas[100][20];

// Elimina salto de linea manualmente
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

// Buscar libro por ID
int buscarLibroPorID(int id) {
    for (int i = 0; i < totalLibros; i++) {
        if (ids[i] == id) {
            return i;
        }
    }
    return -1;
}

// Agregar un nuevo libro
void agregarLibro() {
    if (totalLibros >= maxLibros) {
        printf("No se pueden agregar mas libros.\n");
        return;
    }
    char tempTitulo[100], tempAutor[100];
    int tempID;

    printf("Ingrese el titulo del libro: ");
    fflush(stdin);
    fgets(tempTitulo, maxTitulo, stdin);
    quitarSaltoLinea(tempTitulo);

    printf("Ingrese el autor del libro: ");
    fflush(stdin);
    fgets(tempAutor, maxAutor, stdin);
    quitarSaltoLinea(tempAutor);

    printf("Ingrese el codigo unico (ID) del libro: ");
    scanf("%d", &tempID);
    fflush(stdin);

    if (buscarLibroPorID(tempID) != -1) {
        printf("Ya existe un libro con ese codigo.\n");
        return;
    }

    strcpy(titulos[totalLibros], tempTitulo);
    strcpy(autores[totalLibros], tempAutor);
    ids[totalLibros] = tempID;
    estados[totalLibros] = 0; // DISPONIBLE
    cedulas[totalLibros][0] = '\0';

    totalLibros++;
    printf("Libro agregado exitosamente.\n");
}

// Prestar un libro
void prestarLibro() {
    int id;
    printf("Ingrese el ID del libro a prestar: ");
    scanf("%d", &id);
    fflush(stdin);
    int idx = buscarLibroPorID(id);
    if (idx == -1) {
        printf("Libro no encontrado.\n");
        return;
    }
    if (estados[idx] == 1) {
        printf("El libro ya esta prestado.\n");
        return;
    }
    printf("Ingrese la cedula del usuario: ");
    fflush(stdin);
    fgets(cedulas[idx], maxCedula, stdin);
    quitarSaltoLinea(cedulas[idx]);
    estados[idx] = 1; // PRESTADO
    printf("Libro prestado exitosamente.\n");
}

// Buscar libros por cedula de usuario
void buscarPorCedula() {
    char cedula[20];
    int encontrado = 0;
    printf("Ingrese la cedula del usuario: ");
    fflush(stdin);
    fgets(cedula, maxCedula, stdin);
    quitarSaltoLinea(cedula);
    for (int i = 0; i < totalLibros; i++) {
        if (estados[i] == 1 && strcmp(cedulas[i], cedula) == 0) {
            printf("ID: %d | Titulo: %s | Autor: %s\n", ids[i], titulos[i], autores[i]);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontraron libros prestados a esa cedula.\n");
    }
}

// Mostrar libros disponibles
void mostrarDisponibles() {
    int encontrado = 0;
    printf("Libros disponibles:\n");
    for (int i = 0; i < totalLibros; i++) {
        if (estados[i] == 0) {
            printf("ID: %d | Titulo: %s | Autor: %s\n", ids[i], titulos[i], autores[i]);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No hay libros disponibles.\n");
    }
}

int main() {
    int opcion;
    do {
        printf("\n--- Biblioteca ---\n");
        printf("1. Agregar libro\n");
        printf("2. Prestar libro\n");
        printf("3. Buscar libro por cedula de usuario\n");
        printf("4. Mostrar libros disponibles\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: agregarLibro(); break;
            case 2: prestarLibro(); break;
            case 3: buscarPorCedula(); break;
            case 4: mostrarDisponibles(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}
