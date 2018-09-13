/*
 *  Copyright 2012 Microchip Technology Inc
 */


#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <libpic30.h>

/* 
 * Fully packed
 *
 */

extern volatile int TBLPAG __attribute__((sfr));

#if 0
/* inlined the code */
/* fast 32-bit divide by 3 */
uint32_t rdivide_exact(uint32_t n, unsigned int *remainder) {
  uint32_t r;
  unsigned int rr;

  r = ((0x55555555UL*n) + (n >> 1) - (n>>3));
  rr = r >> 30;
  *remainder = rr;
  return (uint32_t)((n-rr)*0xAAAAAAABUL);
}
#endif

static union {
  unsigned int word;
  struct {
    unsigned char low, med;
  } s;
} data_buffer;

static union physical_address {
  unsigned long addr;
  struct {
    unsigned int offset;
    unsigned int page;
  } s;
} addr;

static long next_offset;
static unsigned int word_offset;

/*
 * unpacks the offset, sets TBLPAG and seeds the data_buffer
 */
void __attribute__((optimize(1))) 
  __unpack_offset(unsigned long offset, unsigned int size) {

#ifdef DEBUG
  fprintf(stderr,"__unpack_offset: %lx (last %lx)\n", offset, next_offset);
#endif

  if (offset != next_offset) {
#ifdef N_INLINE
    addr.addr = rdivide_exact(offset, &word_offset);
#else
    {  uint32_t r;
       unsigned int rr;

       r = ((0x55555555UL*offset) + (offset >> 1) - (offset>>3));
       rr = r >> 30;
       word_offset = rr;
       addr.addr = (uint32_t)((offset-rr)*0xAAAAAAABUL);

    }
#endif
    addr.addr *= 2;
  }

  TBLPAG = addr.s.page;

  if (offset != next_offset) {
    if (word_offset < 2) data_buffer.word = __builtin_tblrdl(addr.addr);
  }

  next_offset = offset + size;
}

/*
 * called by the compiler to read a scalar
 *  up to the size long long int
 */

void _memcpy_df(__pack_upper_byte void *src, void *dst, unsigned int size);

unsigned long long int __attribute__((optimize(1))) 
  __P32DFrd(__pack_upper_byte void *src, unsigned int size) {
#if 0
  /* The specialized approach costs us more than it saves */
  int c;

  union {
    unsigned long long int result;
    unsigned char buffer[sizeof(unsigned long long int)];
  } result;

  __unpack_offset(offset,size);

  c = 0;
  do {
    if (word_offset == 0) {
      result.buffer[c++] = data_buffer.s.low;
      word_offset++;
      if (--size == 0) return result.result;
    }
    if (word_offset == 1) {
      result.buffer[c++] = data_buffer.s.med;
      word_offset++;
      if (--size == 0) return result.result;
    }
    if (word_offset == 2) {
      result.buffer[c++] = __builtin_tblrdh(addr.addr);
      word_offset = 0;
      addr.addr += 2;
      if (addr.addr == 0) {
        TBLPAG++;
      }
      data_buffer.word = __builtin_tblrdl(addr.addr);
      if (--size == 0) return result.result;
    }
  } while (1);
#else
  unsigned long long int result;

  _memcpy_df(src, (unsigned char *)&result, size);
  return result;
#endif
}

void __attribute__((optimize(2))) 
  _memcpy_df(__pack_upper_byte void *src, void *dst, unsigned int size) {

  unsigned long offset = (unsigned long)src;
  unsigned char *dest = dst;

  __unpack_offset(offset,size);

  do {
    if (word_offset == 0) {
      *dest++ = data_buffer.s.low;
      word_offset++;
      if (--size == 0) return;
    }
    if (word_offset == 1) {
      *dest++ = data_buffer.s.med;
      word_offset++;
      if (--size == 0) return;
    }
    if (word_offset == 2) {
      *dest++ = __builtin_tblrdh(addr.addr);
      word_offset = 0;
      addr.addr += 2;
      if (addr.addr == 0) {
        TBLPAG++;
      }
      data_buffer.word = __builtin_tblrdl(addr.addr);
      if (--size == 0) return;
    }
  } while (1);
}
