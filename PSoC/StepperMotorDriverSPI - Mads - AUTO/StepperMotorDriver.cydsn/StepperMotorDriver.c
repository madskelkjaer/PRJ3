/* ========================================
 *
 *          Thomas Degn Larsen
 *
 * ========================================
*/

#include "project.h"
#include "StepperMotorDriver.h"
#include <stdio.h>
#include <math.h>
#define STEPS 8                         // number of steps before repeat (half step = 400 steps pr rotation)

/******************
**   Variables   **
******************/
static int stepSequence[STEPS][4] = {   // step sequence for motors
    {1, 0, 0, 1},                       // step 1
    {0, 0, 0, 1},                       // step 2
    {0, 0, 1, 1},                       // step 3
    {0, 0, 1, 0},                       // step 4
    {0, 1, 1, 0},                       // step 5
    {0, 1, 0, 0},                       // step 6
    {1, 1, 0, 0},                       // step 7
    {1, 0, 0, 0}                        // step 8
};
    
static int off[4] = {0, 0, 0, 0};       // step used to turn of motors
static long azimuthSteps = 8000000;     // counting steps for steppermotor moving solar panel horitontal
static long elevationSteps = 8000000;   // counting steps for steppermotor moving solar panel vertical
static int aStep = 0;                   // number of steps to be taken with azimuth motor
static int eStep = 0;                   // number of steps to be taken with elevation motor
static int16_t currentAsteps = 0;
static int16_t currentEsteps = 0;


/******************
**   Functions   **
******************/
void moveAzimuth(int steps)
{   // function to set steps to be takben by azimuth motor
    aStep = steps;
}

int16_t getAzimuth()
{
    const float degress_per_step = 0.9 / 18; // 1:18 gear ratio
    
    float total_degrees = currentAsteps * degress_per_step;
    int16_t rounded = (int16_t)round(total_degrees);
    
    char buff[64];
    sprintf(buff, "Asteps: %i - Rounded: %i \r\n", currentAsteps, rounded);
    UART_1_PutString(buff);
    
    return rounded;
}

int16_t getElevation()
{
    const float degress_per_step = 0.9 / 20; // 1:20 gear ratio
    
    float total_degrees = currentEsteps * degress_per_step;
    int16_t rounded = (int16_t)round(total_degrees);
    
    char buff[64];
    sprintf(buff, "Esteps: %i - Rounded: %i \r\n", currentAsteps, rounded);
    UART_1_PutString(buff);
    
    return rounded;
}

void resetAzimuth()
{
    currentAsteps = 0;
}
void resetElevation()
{
    currentEsteps = 0;
}

void azimuth()
{   // function to calculate next azimutgh step based and call azimuthStep()
    if (Azimuth_Pin_1_Read() == 0 && Azimuth_Pin_2_Read() == 0 && Azimuth_Pin_3_Read() == 0 && Azimuth_Pin_4_Read() == 0)
    {   // if the motor is off turn it on, on the same step as last time
        azimuthStep(stepSequence[azimuthSteps % STEPS]);
        return;
    }
    if (aStep > 0)
    {   // turning left (positiv steps)
        if (!Limit_Left_Read())
        {   // if left limit is reached, don't move
            aStep = 0;
            return;
        }
        // set azimuth motor pins to next step and decrease steps to be taken
        azimuthStep(stepSequence[++azimuthSteps % STEPS]);
        aStep = aStep - 1;
        currentAsteps = currentAsteps + 1;
        return;
    }
    else if (aStep < 0)
    {    // turning right (negativ steps)
        if (!Limit_Right_Read())
        {   // if right limit is reached, don't move
            aStep = 0;
            return;
        }
        // set azimuth motor pins to next step and decrease steps to be taken
        azimuthStep(stepSequence[--azimuthSteps % STEPS]);
        aStep = aStep + 1;
        currentAsteps = currentAsteps - 1;
        return;
    }
    return;
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

void elevation()
{   // function to calculate next elevation step based and call elevationStep()
    if (Elevation_Pin_1_Read() == 0 && Elevation_Pin_2_Read() == 0 && Elevation_Pin_3_Read() == 0 && Elevation_Pin_4_Read() == 0)
    {   // if the motor is off turn it on, on the same step as last time
        elevationStep(stepSequence[elevationSteps % STEPS]);
        return;
    }
    if (eStep > 0)
    {   // turning up (positiv steps)
        if (!Limit_Up_Read())
        {   // if up limit is reached, don't move
            eStep = 0;
            return;
        }
        // set elevation motor pins to next step and decrease steps to be taken
        elevationStep(stepSequence[++elevationSteps % STEPS]);
        eStep = eStep - 1;
        currentEsteps = currentEsteps + 1;
        return;
    }
    
    else if (eStep < 0)
    {   // turning down (negativ steps)
        if (!Limit_Down_Read())
        {   // if down limit is reached, don't move
            eStep = 0;
            return;
        }
        // set elevation motor pins to next step and decrease steps to be taken
        elevationStep(stepSequence[--elevationSteps % STEPS]);
        eStep = eStep + 1;
        currentEsteps = currentEsteps - 1;
        return;
    }
    return;
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

bool limitLeft(){return !Limit_Left_Read();}

bool limitRight(){return !Limit_Right_Read();}

bool limitUp(){return !Limit_Up_Read();}

bool limitDown(){return !Limit_Down_Read();}

/* [] END OF FILE */
