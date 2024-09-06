// user/yosoytupadre.c
#include "kernel/types.h"
#include "user/user.h"

int main(void)
{
  int ppid = getppid();
  printf("El ID de mi padre es el siguiente: %d\n", ppid);
  exit(0);
}
