#include <stdio.h>
#include <libpic30.h>

/*
 *  This file is intended to be used from only with MPLAB SIM30.
 *
 *  __attach_input_file(const char *) will associate stdin with the named 
 *  file on the host machine.  This function may be called repeatedly to
 *  attach new files to stdin, the currently open file will be closed.
 *
 *  By default stdin is attached using a message based format (which is 
 *  described as part of MPLAB IDE) which is ideal for those who wish to 
 *  simulate their actual hardware (and write input drivers that are more 
 *  complicated than those we provide here).
 *
 *  By attaching an external file as stdin, the data is read in an on-demmand
 *  fashion.
 */

/*
 *  handle 0 is stdin
 *  handle 1 is stdout
 *  handle 2 is stderr
 *  
 *  unless open() is provided by the user, all other handles are opened
 *    by the host operating system via the simulator
 */

extern int close(int handle);

#ifdef __C30_LEGACY_LIBC__
extern int _Foprep(const char *name, const char *mods, FILE *, int);
#endif

int __attach_input_file(const char *f) {
  int error;

  if (f == 0) return 0;
#ifdef __C30_LEGACY_LIBC__
  if (stdin->_Handle > 2) {
    error = close(stdin->_Handle);
    if (error) return error;
  }
  return (_Foprep(f, "r", stdin, 0) != 0);
#else
  stdin->_file = open(f, 0, 0666);
  return (stdin->_file != 0);
#endif
}
  
void __close_input_file(void) {
#ifdef __C30_LEGACY_LIBC__
  if (stdin->_Handle > 2) close(stdin->_Handle);
  stdin->_Handle = 0;
#else
  if (stdin->_file > 2) close(stdin->_file);
  stdin->_file = 0;
#endif
}
