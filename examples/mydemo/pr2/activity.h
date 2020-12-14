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
#define CAPACITY 3
typedef struct
{
    uint8_t fruits[CAPACITY];
    uint32_t in, out;
} plate_t;
typedef enum
{
    APPLE = 0,
    ORANGE
} fruit_t;

void *pinger_job();
void *father_job();
void *mother_job();
void *son_job();
void *daughter_job();

void plate_init(plate_t *p);
void plate_put_fruit(plate_t *p, fruit_t f);
uint8_t plate_get_fruit(plate_t *p);

#endif
