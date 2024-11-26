#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}



int
sys_send(void) {
    int target_pid;
    char *msg_content;

    // PID destino y mensaje
    if (argint(0, &target_pid) < 0 || argstr(1, &msg_content) < 0)
        return -1;

    acquire(&msg_queue.lock);

    if (msg_queue.count == MSG_QUEUE_SIZE) {
        release(&msg_queue.lock);
        return -1;
    }

    // Agregar mensaje
    msg_queue.messages[msg_queue.rear].sender_pid = myproc()->pid;
    strncpy(msg_queue.messages[msg_queue.rear].content, msg_content, sizeof(msg_queue.messages[0].content));
    msg_queue.rear = (msg_queue.rear + 1) % MSG_QUEUE_SIZE;
    msg_queue.count++;

    wakeup(&msg_queue); // Despierta procesos bloqueados
    release(&msg_queue.lock);

    return 0;
}


int
sys_receive(void) {
    message *msg_ptr;

    // Obtén puntero
    if (argptr(0, (void*)&msg_ptr, sizeof(message)) < 0)
        return -1;

    acquire(&msg_queue.lock);

    while (msg_queue.count == 0) {
        sleep(&msg_queue, &msg_queue.lock);
    }

    // Extraer mensaje
    *msg_ptr = msg_queue.messages[msg_queue.front];
    msg_queue.front = (msg_queue.front + 1) % MSG_QUEUE_SIZE;
    msg_queue.count--;

    release(&msg_queue.lock);

    return 0;
}
