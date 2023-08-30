//-----------------------------------------------------------------------------
// \file    rk6748_timer.c
// \brief   implementation of a timer driver for RK6748.
//
//-----------------------------------------------------------------------------

#include <Includes.h>


//-----------------------------------------------------------------------------
// Static Variable Declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

void TaskLED(void* pvParameters)
{
    while (1)
    {
        UARTwrite("Hello", sizeof("Hello"), 2);
        LifeLedSwitch();
        vTaskDelay(500);
    }
}

