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
#include <types.h>
#include "activity.h"

pok_sem_id_t apple, orange, empty, mutex;
plate_t plate;

int main()
{
  // init plate buffer
  plate_init(&plate);

  uint32_t tid;
  int ret;
  pok_thread_attr_t tattr;

  tattr.priority = 42;

  tattr.entry = father_job;
  ret = pok_thread_create(&tid, &tattr);

  tattr.entry = mother_job;
  ret = pok_thread_create(&tid, &tattr);

  tattr.entry = son_job;
  ret = pok_thread_create(&tid, &tattr);

  tattr.entry = daughter_job;
  ret = pok_thread_create(&tid, &tattr);

  ret = pok_sem_create(&mutex, 1, 1, POK_SEMAPHORE_DISCIPLINE_FIFO);
  ret = pok_sem_create(&apple, 0, CAPACITY - 1, POK_SEMAPHORE_DISCIPLINE_FIFO);
  ret = pok_sem_create(&orange, 0, CAPACITY - 1, POK_SEMAPHORE_DISCIPLINE_FIFO);
  ret = pok_sem_create(&empty, CAPACITY - 1, CAPACITY - 1, POK_SEMAPHORE_DISCIPLINE_FIFO);

  pok_partition_set_mode(POK_PARTITION_MODE_NORMAL);
  pok_thread_wait_infinite();

  return (1);
}
