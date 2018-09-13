#include <stdio.h>
#include "simio.h"

static void __inline__ doclose(PSIMIO psimio)
{
  __asm__(".pword 0xDAC000" :: "a" (psimio) : "memory");
}

int __attribute__((__weak__, __section__(".libc"))) close(int handle) {
  register PSIMIO psimio asm("w0");
  SIMIO simio;

  simio.method = SIM_CLOSE;
  simio.u.close.handle = handle;
  psimio = &simio;
  doclose(psimio);

  return(simio.u.close.handle);
}
