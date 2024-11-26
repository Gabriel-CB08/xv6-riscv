#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    char *filename = "testfile";
    int fd;

    // Creación del archivo
    fd = open(filename, O_CREATE | O_RDWR);
    if (fd < 0) {
        printf("Error al crear el archivo\n");
        exit(1);
    }
    write(fd, "Hello", 5);
    close(fd);

    // Cambiar a solo lectura
    if (chmod(filename, 1) < 0) {
        printf("Error al cambiar permisos a solo lectura\n");
        exit(1);
    }

    // Intento de abrir en escritura (debería fallar)
    fd = open(filename, O_WRONLY);
    if (fd >= 0) {
        printf("Error: se abrió el archivo en modo escritura cuando no debería\n");
        close(fd);
        exit(1);
    }

    // Cambiar a inmutable
    if (chmod(filename, 5) < 0) {
        printf("Error al cambiar permisos a inmutable\n");
        exit(1);
    }

    // Intento de modificar permisos (debería fallar)
    if (chmod(filename, 3) == 0) {
        printf("Error: se cambiaron los permisos de un archivo inmutable\n");
        exit(1);
    }

    printf("Pruebas completadas exitosamente\n");
    exit(0);
}
