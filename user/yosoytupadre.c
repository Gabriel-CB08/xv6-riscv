// user/yosoytupadre.c
#include "kernel/types.h"
#include "user.h"

int main(void)
{
  int ppid = getppid();
  printf("Mi padre es: %d\n", ppid);
  exit(0);
}
