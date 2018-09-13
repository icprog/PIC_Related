#include <stdio.h>
#include "simio.h"

static void __inline__ dolseek(PSIMIO psimio) {
  __asm__(".pword 0xDAC000" :: "a" (psimio) : "memory" );
}

long __attribute__((__weak__, __section__(".libc")))
lseek(int handle, long offset, int origin) {
  SIMIO simio;
  register PSIMIO psimio asm("w0") = &simio;

  simio.method = SIM_LSEEK;
  simio.u.lseek.handle = handle;
  simio.u.lseek.offset = offset;
  simio.u.lseek.origin = origin;
  dolseek(psimio);

  return(simio.u.lseek.offset);
}
