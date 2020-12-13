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
#include <core/partition.h>
#include <core/semaphore.h>
#include <core/mutex.h>
#include <types.h>
#include "activity.h"

uint8_t empty1, full1, mutex1;
uint8_t empty2, full2, mutex2;
buffer_t buf1, buf2;

int main()
{
  // init buf
  buffer_init(&buf1), buffer_init(&buf2);

  uint8_t tid;
  pok_ret_t ret;
  pok_thread_attr_t tattr;

  tattr.priority = 42;
  tattr.entry = producer_job;
  ret = pok_thread_create(&tid, &tattr);

  tattr.priority = 42;
  tattr.entry = calculator_job(&tid, &tattr);
  ret = pok_thread_create(&tid, &tattr);

  tattr.priority = 42;
  tattr.entry = consumer_job;
  ret = pok_thread_create(&tid, &tattr);


  ret = pok_sem_create(&mutex1, 1, 1, POK_SEMAPHORE_DISCIPLINE_FIFO);
  ret = pok_sem_create(&empty1, CAPACITY, CAPACITY, POK_SEMAPHORE_DISCIPLINE_FIFO);
  ret = pok_sem_create(&full1, 0, CAPACITY, POK_SEMAPHORE_DISCIPLINE_FIFO);

  ret = pok_sem_create(&mutex2, 1, 1, POK_SEMAPHORE_DISCIPLINE_FIFO);
  ret = pok_sem_create(&empty2, CAPACITY, CAPACITY, POK_SEMAPHORE_DISCIPLINE_FIFO);
  ret = pok_sem_create(&full2, 0, CAPACITY, POK_SEMAPHORE_DISCIPLINE_FIFO);
  // printf("[P1] pok_sem_create return=%d, mid=%d\n", ret, sid);

  pok_partition_set_mode(POK_PARTITION_MODE_NORMAL);
  pok_thread_wait_infinite();

  return (0);
}
