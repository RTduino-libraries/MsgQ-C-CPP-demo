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

#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

void thread_entry(void *parameter);

/*msg queue control block*/
extern struct rt_messagequeue mq;

/*data*/
struct data{
    volatile float temp;
    volatile float humidity;
};
typedef struct data Data;

#ifdef __cplusplus
}
#endif
#endif
