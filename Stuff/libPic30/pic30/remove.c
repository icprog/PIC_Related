#include <stdio.h>
#include "simio.h"
static void __inline__ doremove(PSIMIO psimio) {
  __asm__(".pword 0xDAC000" :: "a" (psimio) : "memory");
}

int __attribute__((__weak__, __section__(".libc")))
remove(const char *filename) {
  SIMIO simio;
  register PSIMIO psimio asm("w0") = &simio;

  simio.method = SIM_UNLINK;
  simio.u.unlink.filename = filename;
  doremove(psimio);

  return(simio.u.unlink.rc);
}
