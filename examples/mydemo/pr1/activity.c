/*
 *                               POK header
 * 
 * The following file is a part of the POK project. Any modification should
 * made according to the POK licence. You CANNOT use this file or a part of
 * this file is this part of a file for your own project
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 *                                      Copyright (c) 2007-2009 POK team 
 *
 * Created by julien on Thu Jan 15 23:34:13 2009 
 */

#include <libc/stdio.h>
#include <core/thread.h>
#include <core/semaphore.h>
#include <core/mutex.h>
#include <core/time.h>
#include <types.h>
#include "activity.h"

static const int N = 30;
static const int limit = 26;

extern uint8_t empty1, full1, mutex1;
extern uint8_t empty2, full2, mutex2;
extern buffer_t buf1, buf2;

static pok_time_t start, end;

void *producer_job()
{
   pok_time_get(&start);
   int i;
   char item = 'a';
   for (i = 0; i < N; i++)
   {
      pok_sem_wait(empty1, 0);
      pok_sem_wait(mutex1, 0);
      item = 'a' + (i % limit);
      buffer_put_item(&buf1, item);
      printf("[Producer] put item [%c] into buf1. \n", item);
      pok_sem_signal(mutex1);
      pok_sem_signal(full1);
   }
   return NULL;
}

void *calculator_job()
{
   int i;
   char item;
   for (i = 0; i < N;i++)
   {
      pok_sem_wait(full1, 0);
      pok_sem_wait(mutex1, 0);
      item = buffer_get_item(&buf1);
      pok_sem_signal(mutex1);
      pok_sem_signal(empty1);

      item = item - 'a' + 'A';

      pok_sem_wait(empty2, 0);
      pok_sem_wait(mutex2, 0);
      buffer_put_item(&buf2, item);
      pok_sem_signal(mutex2);
      pok_sem_signal(full2);
   }
   return NULL;
}

void *consumer_job()
{
   int i;
   char item;
   for (i = 0; i < N; i++)
   {
      pok_sem_wait(full2, 0);
      pok_sem_wait(mutex2, 0);
      item = buffer_get_item(&buf2);
      printf("\t[Consumer] get item [%c] from buf2. \n", item);
      pok_sem_signal(mutex2);
      pok_sem_signal(empty2);
   }
   pok_time_get(&end);
   printf("[PR1] time = %d \n", end - start);
   return NULL;
}

// buf functions
void buffer_init(buffer_t *b) { b->in = b->out = 0; }
int buffer_is_full(buffer_t *b) { return ((b->in + 1) % CAPACITY) == (b->out); }
int buffer_is_empty(buffer_t *b) { return b->in == b->out; }
void buffer_put_item(buffer_t *buf, char item)
{
   buf->items[buf->in] = item;
   buf->in = (buf->in + 1) % CAPACITY;
}
char buffer_get_item(buffer_t *buf)
{
   char item = buf->items[buf->out];
   buf->out = (buf->out + 1) % CAPACITY;
   return item;
}
