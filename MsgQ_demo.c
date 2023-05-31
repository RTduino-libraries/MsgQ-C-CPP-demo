/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-05-31     Chushicheng       first version
 */

#include <rtthread.h>
#include "common.h"

/*Entry function for tid*/
void thread_entry(void *parameter)
{
    struct data mainData;
    while(1)
    {
        /* Receive messages from the message queue */
        if (rt_mq_recv(&mq, &mainData, sizeof(struct data), RT_WAITING_FOREVER) == RT_EOK)
        {
            rt_kprintf("Temperature: %f\n",mainData.temp);
            rt_kprintf("Humidity: %f\n",mainData.humidity);
        }
    }
}