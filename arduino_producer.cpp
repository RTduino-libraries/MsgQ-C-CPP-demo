/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-02-04     Stanley Lwin      first version
 * 2023-05-31     Chushicheng       re-organize
 */

#include <Adafruit_AHTX0.h>
#include <RTduino.h>
#include "common.h"

/*New thread configuration*/
#define THREAD_PRIORITY 21
#define THREAD_STACK_SIZE 1024
#define THREAD_TIMESLICE 5

rt_thread_t tid = RT_NULL;
Adafruit_AHTX0 aht;

struct rt_messagequeue mq;
rt_uint8_t msg_pool[2048];

static void aht_setup(void)
{
    Serial.begin();
    Serial.println("Adafruit AHT10/AHT20 demo!");

    if (! aht.begin())
    {
        Serial.println("Could not find AHT? Check wiring");
        while (1) delay(10);
    }

    Serial.println("AHT10 or AHT20 found");

    rt_mq_init(&mq, "c/cpp-RTduino", &msg_pool[0], sizeof(struct data), sizeof(msg_pool), RT_IPC_FLAG_FIFO);

    tid = rt_thread_create("c-consumer", thread_entry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);

    if(tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        rt_thread_delete(tid);
    }
}

static void aht_loop(void)
{
    sensors_event_t humidity, temp;
    struct data Data;

    aht.getEvent(&humidity, &temp);

    Data.temp= temp.temperature;
    Data.humidity = humidity.relative_humidity;

    rt_mq_send(&mq,&Data, sizeof(struct data));

    delay(500);
}
RTDUINO_SKETCH_LOADER("cpp-producer", aht_setup, aht_loop);
