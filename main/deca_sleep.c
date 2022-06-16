/*! ----------------------------------------------------------------------------
 * @file    deca_sleep.c
 * @brief   platform dependent sleep implementation
 *
 * @attention
 *
 * Copyright 2015 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "deca_sleep.h"


void deca_sleep(unsigned int time_ms)
{
    vTaskDelay(time_ms/10);
}
