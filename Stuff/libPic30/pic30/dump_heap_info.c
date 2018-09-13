#include <stdio.h>
#include <stdlib.h>

#ifdef __C30_LEGACY_LIBC__

/*
 * void _dump_heap_info(void)
 *
 * Writes a summary of heap usage to stderr.
 *
 * This function can be used to profile memory
 * allocation in the heap. It is designed to work
 * with C30 versions up through v3.12. Future
 * versions may revise heap data structures,
 * requiring modifications to this file.
 *
 */

typedef struct cell_info {
  unsigned int size;
  struct cell_info *next;
} cell_info;

typedef struct heap_info {
  cell_info **tail;
  cell_info *free_list;
} heap_info;

extern heap_info _Aldata;

/*
 * This is a fairly standard allocation strategy:
 *
 * an allocation proceeds by first examining whether or not there is
 * any unused allocation in the current heap block (by looking at tail)
 * 
 * if there is enough space left, grab some and update tail
 *
 * if there is no space left, check the free_list looking for the first
 *   freed block of sufficient size - freeing attempts to merge consecutive
 *   blocks to maintain the largest free block; a partially used block with
 *   'enough' space left is added back into the free list
 *
 * if no block is found, call sbrk() and add that space to the free_list,
 *   repeat the grab
 *
 */

void _dump_heap_info() {
  cell_info *c;
  cell_info *f;
  unsigned int s = 0;
  int i;
  int header =0;

  extern void _heap, _eheap;
  extern void *__curbrk;

  fprintf(stderr,"\n*** Unused Heap status:\n"
                 "***   start: 0x%8.8x   end: 0x%8.8x\n", &_heap, &_eheap);
  if (__curbrk) {
     s = (unsigned int)&_eheap - (unsigned int)__curbrk;
  } else {
     s = (unsigned int)&_eheap - (unsigned int)&_heap;
  }
  fprintf(stderr,"***   current:0x%8.8x remaining bytes: %d\n", __curbrk, s);

  c = &_heap;
  f = _Aldata.free_list;
  i = 0;
  do {
    if (f && (c == f)) {
      f = c->next;
    } else if ((void*)c < __curbrk) {
      if (header == 0) {
        fprintf(stderr,"***\n*** Allocated blocks:\n");
        fprintf(stderr,"***   [id ] address     size\n");
        header=1;
      }
      fprintf(stderr,"***   [%.3d] 0x%8.8x  %d\n", i, c, c->size);
      i++;
    }
    c = (cell_info*)(((unsigned int)(c)) + c->size);
  } while ((void*)c < __curbrk);
  if (_Aldata.free_list) {
    fprintf(stderr,"***\n*** Free blocks:\n");
    fprintf(stderr,"***   [id ] address     size\n");
    for (i = 0, c = _Aldata.free_list; c; i++,c = c->next) {
      fprintf(stderr,"***   [%.3d] 0x%8.8x  %d\n", i, c, c->size);
      s += c->size;
    }
  }
  fprintf(stderr,"***\n*** Total bytes left: %d\n\n", s);
}
#endif


#ifdef EXAMPLE

/*
 * Sample Program
 */

#include <libpic30.h>

void *allocations[20];

main() {

  int size;
  int a;

  _dump_heap_info();
  for (a = 0, size = 4; size <= 64; size += 6) {
    allocations[a] = (void *)malloc(size);
    fprintf(stderr,"\nAllocated: %d @ 0x%8.8x\n", size, allocations[a]);
    _dump_heap_info();
    a++;
  }

  fprintf(stderr,"Free:  0x%8.8x\n", allocations[4]);
  free(allocations[4]);
  _dump_heap_info();

  fprintf(stderr,"Free:  0x%8.8x\n", allocations[6]);
  free(allocations[6]);
  _dump_heap_info();

  fprintf(stderr,"Free:  0x%8.8x\n", allocations[5]);
  free(allocations[5]);
  _dump_heap_info();
}

#endif
