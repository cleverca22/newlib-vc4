#include <errno.h>
#include <stdint.h>
#include "vc4-regs.h"

static void
vc4_putchar (unsigned int c)
{
  unsigned int tmp;
  
  do
    {
      tmp = MMIO_READ (AUX_MU_LSR_REG);
    }
  while ((tmp & 0x20) != 0x20);
  
  MMIO_WRITE (AUX_MU_IO_REG, c);
}

int
write (int fd, const void *buf, unsigned int count)
{
  int i;
  const char *bufc = buf;

  if (fd != 1 && fd != 2)
    {
      errno = EBADF;
      return -1;
    }

  for (i = 0; i < count; i++)
    vc4_putchar (bufc[i]);

  return count;
}