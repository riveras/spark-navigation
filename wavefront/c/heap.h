/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) 2008-
 *     Brian Gerkey gerkey@willowgarage.com
 *                      
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

/*
 * An implementation of a heap, as seen in "Introduction to Algorithms," by
 * Cormen, Leiserson, and Rivest, pages 140-152.
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>

#define HEAP_PARENT(i) ((i)/2)
#define HEAP_LEFT(i) (2*(i))
#define HEAP_RIGHT(i) (2*(i)+1)

#ifdef __cplusplus
extern "C" {
#endif

struct heap;

typedef void (*heap_free_elt_fn_t) (void* elt);

typedef struct heap
{
  int len;
  int size;
  heap_free_elt_fn_t free_fn;
  double* A;
  double** data; // FIXME: void**
} heap_t;
/*@ type invariant heap_len_and_size (heap_t h) =
  @   0 <= h.len <= h.size;
  @*/   

/*@ requires size > 0;
  @ ensures \result->len == 0;
  @ ensures \valid(\result);
  @ ensures \separated(__fc_stdout,\result);
 */
heap_t* heap_alloc(int size, heap_free_elt_fn_t free_fn);

/*@ requires \valid(h);
  @ assigns \nothing;
 */
void heap_free(heap_t* h);

/*@ requires \valid(h);
  @ requires 0 <= i;
  @ requires h->len >= 0;
  @ requires \valid(h->A+(0..h->len-1));
  @ requires \valid(h->data+(0..h->len-1));
  @ requires \forall int i;
  @ 0 <= i <= h->len-1 ==>
  @ \separated(h,h->A,h->data,h->data[i]);
  @ assigns h->A[0..h->len-1],h->data[0..h->len-1];
 */
void heap_heapify(heap_t* h, int i);

/*@ requires \valid(h);
  @ requires h->len > 0;
  @ requires \valid(h->A+(0..h->len-1));
  @ requires \valid(h->data+(0..h->len-1));
  @ requires \forall int i;
  @ 0 <= i <= h->len-1 ==>
  @ \separated(h,h->A,h->data,h->data[i]);
  @ ensures h->len == \old(h->len)-1;
  @ assigns h->len,h->A[0..h->len-1],h->data[0..h->len-1];
 */
void* heap_extract_max(heap_t* h);

/*@ requires \valid(h);
  @ requires \valid(h->A+(0..h->len-1));
  @ requires \valid(h->data+(0..h->len-1));
  @ assigns h->len;
  @ //assigns ...;
  @ ensures h->len == \old(h->len)+1;
  @ ensures \valid(h->A+(0..h->len-1));
  @ ensures \valid(h->data+(0..h->len-1));
 */
void heap_insert(heap_t* h, double key, void* data);

/*@ requires \valid(h);
  @ requires \separated(__fc_stdout,h);
  @ requires h->len >= 0;
  @ requires \valid(h->A+(0..h->len-1));
  @ behavior empty:
  @   assumes (h->len == 0);
  @   assigns \nothing;
  @ behavior non_empty:
  @   assumes (h->len > 0);
  @   assigns *__fc_stdout;
  @ disjoint behaviors;
  @ complete behaviors;
  @*/
void heap_dump(heap_t* h);

/*@ requires \valid(h);
  @ requires h->len >= 0;
  @ requires \valid((h->A)+(0..h->len-1));
  @ assigns \nothing;
 */
int heap_valid(heap_t* h);

/*@ requires \valid(h);
  @ assigns \nothing;
  @ ensures \result == 0 || \result == 1;
 */
int heap_empty(heap_t* h);

/*@ requires \valid(h);
  @ assigns *h;
  @ ensures h->len == 0;
 */
void heap_reset(heap_t* h);

#ifdef __cplusplus
}
#endif

#endif
