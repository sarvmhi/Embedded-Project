

#include "slave.h"
#include "rtwtypes.h"

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
    /* Check for overrun. Protect OverrunFlag against preemption */
    if (OverrunFlag++) {
        IsrOverrun = 1;
        OverrunFlag--;
        return;
    }

#ifndef _MW_ARDUINO_LOOP_

    sei();

#endif;

    slave_step();

    /* Get model outputs here */
#ifndef _MW_ARDUINO_LOOP_

    cli();

#endif;

    OverrunFlag--;
}

volatile boolean_T stopRequested;
volatile boolean_T runModel;
int main(void)
{
    float modelBaseRate = 1.0;
    float systemClock = 0;

    /* Initialize variables */
    stopRequested = false;
    runModel = false;
    init();
    MW_Arduino_Init();
    rtmSetErrorStatus(rtM, 0);
    slave_initialize();
    configureArduinoAVRTimer();
    runModel =
        rtmGetErrorStatus(rtM) == (NULL);

#ifndef _MW_ARDUINO_LOOP_

    sei();

#endif;

    sei();
    while (runModel) {
        stopRequested = !(
                          rtmGetErrorStatus(rtM) == (NULL));
        runModel = !(stopRequested);
        MW_Arduino_Loop();
    }

    /* Disable rt_OneStep() here */
    cli();
    return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
