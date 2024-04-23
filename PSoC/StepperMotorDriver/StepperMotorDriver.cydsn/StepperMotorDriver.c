/* ========================================
 *
 *          Thomas Degn Larsen
 *
 * ========================================
*/

#include "project.h"
#include "StepperMotorDriver.h"
#include <stdio.h>
#define STEPS 8                         // number of steps before repeat (half step = 400 steps pr rotation)

/******************
**   Variables   **
******************/
static int stepSequence[STEPS][4] = {   // step sequence for motors
    {1, 0, 0, 0},                       // step 1
    {1, 1, 0, 0},                       // step 2
    {0, 1, 0, 0},                       // step 3
    {0, 1, 1, 0},                       // step 4
    {0, 0, 1, 0},                       // step 5
    {0, 0, 1, 1},                       // step 6
    {0, 0, 0, 1},                       // step 7
    {1, 0, 0, 1}                        // step 8
};
static int off[4] = {0, 0, 0, 0};       // step used to turn of motors
static long azimuthSteps = 8000000;     // counting steps for steppermotor moving solar panel horitontal
static long elevationSteps = 8000000;   // counting steps for steppermotor moving solar panel vertical
static int aStep = 0;                   // number of steps to be taken with azimuth motor
static int eStep = 0;                   // number of steps to be taken with elevation motor


/******************
**   Functions   **
******************/
void moveAzimuth(int steps)
{   // function to set steps to be takben by azimuth motor
    aStep = steps;
}

int azimuth()
{   // function to calculate next azimutgh step based and call azimuthStep()
    if (Azimuth_Pin_1_Read() == 0 && Azimuth_Pin_2_Read() == 0 && Azimuth_Pin_3_Read() == 0 && Azimuth_Pin_4_Read() == 0)
    {   // if the motor is off turn it on, on the same step as last time
        azimuthStep(stepSequence[azimuthSteps % STEPS]);
        return 0;
    }
    if (aStep > 0)
    {   // turning right (positiv steps)
        if (!Limit_Right_Read())
        {   // if right limit is reached, don't move
            aStep = 0;
            return 0;
        }
        // set azimuth motor pins to next step and decrease steps to be taken
        azimuthStep(stepSequence[++azimuthSteps % STEPS]);
        aStep = aStep - 1;
        return 1;
    }
    else if (aStep < 0)
    {    // turning left (negativ steps)
        if (!Limit_Left_Read())
        {   // if left limit is reached, don't move
            aStep = 0;
            return 0;
        }
        // set azimuth motor pins to next step and decrease steps to be taken
        azimuthStep(stepSequence[--azimuthSteps % STEPS]);
        aStep = aStep + 1;
        return 1;
    }
    return -1;
}

void azimuthStep(int sequence[4])
{   // function to write sequence to azimuth motor pins
    Azimuth_Pin_1_Write(sequence[0]);
    Azimuth_Pin_2_Write(sequence[1]);
    Azimuth_Pin_3_Write(sequence[2]);
    Azimuth_Pin_4_Write(sequence[3]);
}


void moveElevation(int steps)
{   // function to set steps to be takben by elevation motor
    eStep = steps;
}

int elevation()
{   // function to calculate next elevation step based and call elevationStep()
    if (Elevation_Pin_1_Read() == 0 && Elevation_Pin_2_Read() == 0 && Elevation_Pin_3_Read() == 0 && Elevation_Pin_4_Read() == 0)
    {   // if the motor is off turn it on, on the same step as last time
        elevationStep(stepSequence[elevationSteps % STEPS]);
        return 0;
    }
    if (eStep > 0)
    {   // turning up (positiv steps)
        if (!Limit_Up_Read())
        {   // if up limit is reached, don't move
            eStep = 0;
            return 0;
        }
        // set elevation motor pins to next step and decrease steps to be taken
        elevationStep(stepSequence[++elevationSteps % STEPS]);
        eStep = eStep - 1;
        return 1;
    }
    
    else if (eStep < 0)
    {   // turning down (negativ steps)
        if (!Limit_Down_Read())
        {   // if down limit is reached, don't move
            eStep = 0;
            return 0;
        }
        // set elevation motor pins to next step and decrease steps to be taken
        elevationStep(stepSequence[--elevationSteps % STEPS]);
        eStep = eStep + 1;
        return 1;
    }
    return -1;
}

void elevationStep(int sequence[4])
{   // function to write sequence to elevation motor pins
    Elevation_Pin_1_Write(sequence[0]);
    Elevation_Pin_2_Write(sequence[1]);
    Elevation_Pin_3_Write(sequence[2]);
    Elevation_Pin_4_Write(sequence[3]);
}


CY_ISR(MOTOR_STEP)
{   // interupt rutine activated by clock to take steps
    if (aStep)
    {   // if aStep != 0 move
        azimuth();
    }
    else if (Azimuth_Pin_1_Read() == 1 || Azimuth_Pin_2_Read() == 1 || Azimuth_Pin_3_Read() == 1 || Azimuth_Pin_4_Read() == 1)
    {   // if we didn't move and motor is on, turn it off
        azimuthStep(off);
    }
    
    if (eStep)
    {   // if eStep != 0 move
        elevation();
    }
    else if (Elevation_Pin_1_Read() == 1 || Elevation_Pin_2_Read() == 1 || Elevation_Pin_3_Read() == 1 || Elevation_Pin_4_Read() == 1)
    {   // if we didn't move and motor is on, turn it off
        elevationStep(off);
    }
}

// to be deleted
CY_ISR(UART_HANDLER)
{
    uint8_t c = UART_1_GetByte();
    UART_1_PutChar(c);
    if (c == 'f')
    {
        aStep = aStep - 1;
    }
    else if (c == 'h')
    {
        aStep = aStep + 1;
    }
    else if (c == 'd')
    {
        aStep = aStep - 80;
    }
    else if (c == 'j')
    {
        aStep = aStep + 80;
    }
    else if (c == 'b')
    {
        eStep = eStep - 1;
    }
    else if (c == 't')
    {
        eStep = eStep + 1;
    }
    else if (c == 'n')
    {
        eStep = eStep - 80;
    }
    else if (c == 'y')
    {
        eStep = eStep + 80;
    }
}
/* [] END OF FILE */
