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

#include <rtthread.h>
#include "common.h"

/* Entry function for tid */
void consumer_thread_entry(void *parameter)
{
    rtduino_mq_data data;

    while(1)
    {
        /* Receive messages from the message queue */
#if RT_VER_NUM < 0x50001
        if (rt_mq_recv(rtduino_mq, &data, sizeof(rtduino_mq_data), RT_WAITING_FOREVER) == RT_EOK)
#else
        if (rt_mq_recv(rtduino_mq, &data, sizeof(rtduino_mq_data), RT_WAITING_FOREVER) > 0)
#endif /* RT_VER_NUM < 0x50001 */
        {
            rt_kprintf("Temperature: %f *C\n", data.temp);
            rt_kprintf("Humidity: %f %%\n", data.humidity);
        }
    }
}
