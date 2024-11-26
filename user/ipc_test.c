#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int pid = fork();

    if (pid == 0) { // hijo: escritor
        for (int i = 0; i < 5; i++) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Mensaje %d desde el hijo", i);
            if (sys_send(getpid(), msg) == 0) {
                printf("Hijo: mensaje enviado: %s\n", msg);
            } else {
                printf("Hijo: error al enviar mensaje\n");
            }
        }
    } else { // padre: lector
        for (int i = 0; i < 5; i++) {
            message msg;
            if (sys_receive(&msg) == 0) {
                printf("Padre: mensaje recibido de PID %d: %s\n", msg.sender_pid, msg.content);
            } else {
                printf("Padre: error al recibir mensaje\n");
            }
        }
        wait(0); 
    }

    exit(0);
}
