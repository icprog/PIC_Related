#include <stdio.h>
#include "simio.h"
static void __inline__ dorename(PSIMIO psimio) {
  __asm__(".pword 0xDAC000" :: "a" (psimio) : "memory");
}

int __attribute__((__weak__, __section__(".libc")))
rename(const char *oldname, const char *newname) {
  SIMIO simio;
  register PSIMIO psimio asm("w0") = &simio;

  simio.method = SIM_RENAME;
  simio.u.rename.oldname = oldname;
  simio.u.rename.newname = newname;
  dorename(psimio);

  return(simio.u.rename.rc);
}
