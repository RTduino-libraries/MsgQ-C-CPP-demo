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

#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

void consumer_thread_entry(void *parameter);

/*msg queue control block*/
extern rt_mq_t rtduino_mq;

/*data*/
typedef struct {
    volatile float temp;
    volatile float humidity;
}rtduino_mq_data;

#ifdef __cplusplus
}
#endif
#endif
