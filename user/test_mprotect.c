#include "/home/gabriel/Sistemas_Operativos/xv6-riscv/kernel/types.h"
#include "/home/gabriel/Sistemas_Operativos/xv6-riscv/kernel/stat.h"
#include "user.h"
int main() {
    // dirección actual 
    char *addr = sbrk(0);
    // página adicional 
    if (sbrk(4096) == (void*)-1) {
        printf("Error al reservar memoria\n");
        exit(1);
    }
    // nueva página como solo lectura usando mprotect
    if (mprotect(addr, 1) == -1) {
        printf("Error en mprotect\n");
        exit(1);
    }

    // Intentar escribir en la página protegida
    printf("Prueba a escribir\n");
    *addr = 'A'; 
    printf("esto no deberia pasar\n");

    // Desproteger la página usando munprotect
    if (munprotect(addr, 1) == -1) {
        printf("Error en munprotect\n");
        exit(1);
    }
    printf("prueba de nuevo a escribir\n");
    *addr = 'B';
    printf("Ahora si: %c\n", *addr);
    exit(0);
}
