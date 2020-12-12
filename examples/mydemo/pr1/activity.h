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

#ifndef __POK_USER_GENERATED_ACTIVITY_H_
#define __POK_USER_GENERATED_ACTIVITY_H_
void *pinger_job();
void *pinger_job2();
void *producer_job();
void *consumer_job();
#define CAPACITY 4 // buffer 的容量
typedef struct
{
    char items[CAPACITY];
    int in, out;
} buffer_t;

void buffer_init(buffer_t *b);
int buffer_is_full(buffer_t *b);
int buffer_is_empty(buffer_t *b);
void buffer_put_item(buffer_t *buf, char item);
char buffer_get_item(buffer_t *buf);

#endif
