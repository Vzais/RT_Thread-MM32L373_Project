/*
 * Copyright (c) 2017-2019, MindMotion AE Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-13     henryhuang   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "HAL_device.h"
#include "task.h"


int main(void)
{
    KEY_Task_Init();
    Blue_Task_Init();
    PWN_Task_Init();
}
