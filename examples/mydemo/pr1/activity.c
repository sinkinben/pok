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
#include <types.h>
#include "activity.h"

#define N 8

extern uint8_t sid;
extern uint8_t mutex;
uint8_t val;

extern buffer_t buf1, buf2;

void *pinger_job()
{
   pok_ret_t ret;
   while (1)
   {
      printf("P1T1: I will signal semaphores\n");
      ret = pok_sem_signal(sid);
      printf("P1T1: pok_sem_signal, ret=%d\n", ret);
      pok_thread_sleep(2000000);
   }
}

void *producer_job()
{
   pok_ret_t ret = 0;
   int i;
   char item = 'a';
   for (i = 0; i < N; i++)
   {
      ret = pok_sem_signal(sid);
      item = 'a' + i;
      buffer_put_item(&buf1, item);
      printf("[Producer] put item [%c] into buf1. \n", item);
      pok_thread_sleep(20000);
   }
   return NULL;
}

void *consumer_job()
{
   pok_ret_t ret;
   int i;
   char item;
   for (i = 0; i < N; i++)
   {
      pok_sem_wait(sid, 0);
      item = buffer_get_item(&buf1);
      printf("\t[Consumer] get item [%c] from buf1. \n", item);
      pok_thread_sleep(40000);
   }
   return NULL;
}

void *pinger_job2()
{
   pok_ret_t ret;
   while (1)
   {
      printf("P1T2: I will wait for the semaphores\n");
      ret = pok_sem_wait(sid, 0);
      printf("P1T2: pok_sem_wait, ret=%d\n", ret);
      ret = pok_sem_wait(sid, 0);
      printf("P1T2: pok_sem_wait, ret=%d\n", ret);
      pok_thread_sleep(2000000);
   }
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
