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
#define N 4

extern uint8_t apple, orange, empty;

void *father_job()
{
   int i;
   for (i = 0; i < N; i++)
   {
      pok_sem_wait(empty, 0);
      printf("[Father] apple++ \n");
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
      printf("[Mother] orange++ \n");
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
      printf("\t[Son] apple-- \n");
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
      printf("\t[Daughter] orange-- \n");
      pok_sem_signal(empty);
   }
   return NULL;
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
