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
#include <core/time.h>
#include <core/semaphore.h>
#include "activity.h"
#define N 8

extern uint8_t apple, orange, empty, mutex;
extern plate_t plate;
static const char *strs[] = {"apple", "orange"};
void *father_job()
{
   int i;
   for (i = 0; i < N; i++)
   {
      pok_sem_wait(empty, 0);
      pok_sem_wait(mutex, 0);
      printf("[Father] apple++ \n");
      plate_put_fruit(&plate, APPLE);
      pok_sem_signal(mutex);
      pok_sem_signal(apple);
   }
   return NULL;
}

void *mother_job()
{
   int i;
   for (i = 0; i < N; i++)
   {
      pok_sem_wait(empty, 0);
      pok_sem_wait(mutex, 0);
      printf("[Mother] orange++ \n");
      plate_put_fruit(&plate, ORANGE);
      pok_sem_signal(mutex);
      pok_sem_signal(orange);
   }
   return NULL;
}

void *son_job()
{
   int i;
   for (i = 0; i < N; i++)
   {
      pok_sem_wait(apple, 0);
      pok_sem_wait(mutex, 0);
      printf("\t[Son] %s-- \n", strs[plate_get_fruit(&plate)]);
      pok_sem_signal(mutex);
      pok_sem_signal(empty);
   }
   return NULL;
}

void *daughter_job()
{
   int i;
   for (i = 0; i < N; i++)
   {
      pok_sem_wait(orange, 0);
      pok_sem_wait(mutex, 0);
      printf("\t[Daughter] %s-- \n", strs[plate_get_fruit(&plate)]);
      pok_sem_signal(mutex);
      pok_sem_signal(empty);
   }
   return NULL;
}

void plate_init(plate_t *plate)
{
   plate->in = plate->out = 0;
}

void plate_put_fruit(plate_t *p, fruit_t f)
{
   p->fruits[p->in] = f;
   p->in = (p->in + 1) % CAPACITY;
}

uint8_t plate_get_fruit(plate_t *p)
{
   uint8_t f = p->fruits[p->out];
   p->out = (p->out + 1) % CAPACITY;
   return f;
}

void *pinger_job()
{
   pok_time_t t;
   while (1)
   {
      pok_time_get(&t);
      printf("t = %u\n", t);
      printf("P2T1: begin of task\n");
      pok_thread_sleep(12345);
   }
}
