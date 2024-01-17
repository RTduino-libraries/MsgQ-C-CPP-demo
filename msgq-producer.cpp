/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * https://github.com/RTduino/RTduino
 * https://gitee.com/rtduino/RTduino
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-02-17     Stanley Lwin      first version
 * 2023-05-31     Chushicheng       re-organize
 */

#include <RTduino.h>
#include "common.h"
#ifdef PKG_USING_ARDUINO_ADAFRUIT_AHTX0
#include <Adafruit_AHTX0.h>
#endif /* PKG_USING_ARDUINO_ADAFRUIT_AHTX0 */

/* New thread configuration */
#define CONSUMER_THREAD_PRIORITY 21
#define CONSUMER_THREAD_STACK_SIZE 1024

rt_mq_t rtduino_mq = RT_NULL;

#ifdef PKG_USING_ARDUINO_ADAFRUIT_AHTX0
static Adafruit_AHTX0 aht10;
#endif /* PKG_USING_ARDUINO_ADAFRUIT_AHTX0 */

static void _get_humi_temp_setup(void)
{
    Serial.begin();

#ifdef PKG_USING_ARDUINO_ADAFRUIT_AHTX0
    Serial.println("Adafruit AHT10/AHT20 demo!");

    if (!aht10.begin())
    {
        Serial.println("Could not find AHT? Check wiring");
        while(1) delay(50);
    }

    Serial.println("AHT10 or AHT20 has found!");
#endif /* PKG_USING_ARDUINO_ADAFRUIT_AHTX0 */

    /* create RTduino producer-consumer message queue */
    rtduino_mq = rt_mq_create("mesg-RTduino", sizeof(rtduino_mq_data), 2 /*msg size*/, RT_IPC_FLAG_FIFO);
    if (rtduino_mq == RT_NULL)
    {
        Serial.println("Fail to create RTduino producer-consumer message queue!");
        return;
    }

    /* create consumer typical C thread */
    rt_thread_t tid = rt_thread_create("c-consumer", consumer_thread_entry, RT_NULL, CONSUMER_THREAD_STACK_SIZE, CONSUMER_THREAD_PRIORITY, 10);
    if(tid == RT_NULL)
    {
        Serial.println("Fail to create Consumer C thread!");
        return;
    }

    rt_thread_startup(tid);
}

static void _get_humi_temp_loop(void)
{
#ifdef PKG_USING_ARDUINO_ADAFRUIT_AHTX0
    sensors_event_t humidity, temp;
#endif /* PKG_USING_ARDUINO_ADAFRUIT_AHTX0 */
    rtduino_mq_data data;

#ifdef PKG_USING_ARDUINO_ADAFRUIT_AHTX0
    aht10.getEvent(&humidity, &temp);
    data.temp= temp.temperature;
    data.humidity = humidity.relative_humidity;
#else
    /* dummy temperature and humidity data */
    data.temp = 20.0;
    data.humidity = 10.0;
#endif /* PKG_USING_ARDUINO_ADAFRUIT_AHTX0 */

    rt_mq_send(rtduino_mq, &data, sizeof(rtduino_mq_data));

    delay(2000);
}
RTDUINO_SKETCH_LOADER("cpp-producer", _get_humi_temp_setup, _get_humi_temp_loop);
