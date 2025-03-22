/*
 * app.c
 *
 *  Created on: Aug 25, 2024
 *      Author: rolo
 */

/* Includes *******************************************************************/

#include "cmsis_os.h"
#include "gpio.h"
#include "app.h"
#include "tusb.h"
#include "max31790.h"

/* Globals ********************************************************************/

/* Functions ******************************************************************/

void initOpenFanHub(void)
{
    ;
}

void fanDriverLoop(void)
{
    ;
}

void tUsbLoop(void)
{
    tud_task();
    tud_cdc_write_flush();
}

void cdcLoop(void)
{
    static uint8_t helloWorld[] = "Hello world!\n";

    if (tud_cdc_n_ready(0))
    {
        tud_cdc_write(helloWorld, sizeof(helloWorld));
    }
    tud_cdc_write_flush();

    osDelay(100);
}

void ledLoop(void)
{
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,
                      !HAL_GPIO_ReadPin(LD2_GPIO_Port, LD2_Pin));

    osDelay(1000);
}
