/* ========================================
 *
 *          Thomas Degn Larsen
 *
 * ========================================
*/

#include "StepperMotorDriver.h"
#include <stdio.h>

#define STEPS 8                         // number of steps before repeat (half step = 400 steps per rotation)
#define START_POSITION_AZIMUTH 5000     // Start position for azimuth (steps from left limit)
#define START_POSITION_ELEVATION 5000   // Start position for elevation (steps from down limit)

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

static int off[4] = {0, 0, 0, 0};       // step used to turn off motors
static int32_t azimuthSteps = 0;        // counting steps for stepper motor moving solar panel horizontally
static int32_t elevationSteps = 0;      // counting steps for stepper motor moving solar panel vertically
static int aStep = 0;                   // number of steps to be taken with azimuth motor
static int eStep = 0;                   // number of steps to be taken with elevation motor

/******************
**   Functions   **
******************/
void moveAzimuth(int steps)
{   // function to set steps to be taken by azimuth motor
    aStep = steps;
}

void azimuth()
{   // function to calculate next azimuth step and call azimuthStep()
    if (Azimuth_Pin_1_Read() == 0 && Azimuth_Pin_2_Read() == 0 && Azimuth_Pin_3_Read() == 0 && Azimuth_Pin_4_Read() == 0)
    {   // if the motor is off, turn it on, on the same step as last time
        azimuthStep(stepSequence[azimuthSteps % STEPS]);
        return;
    }
    if (aStep > 0)
    {   // turning left (positive steps)
        if (!Limit_Left_Read())
        {   // if left limit is reached, don't move
            aStep = 0;
            return;
        }
        // set azimuth motor pins to next step and decrease steps to be taken
        azimuthStep(stepSequence[++azimuthSteps % STEPS]);
        aStep = aStep - 1;
        return;
    }
    else if (aStep < 0)
    {   // turning right (negative steps)
        if (!Limit_Right_Read())
        {   // if right limit is reached, don't move
            aStep = 0;
            return;
        }
        // set azimuth motor pins to next step and decrease steps to be taken
        azimuthStep(stepSequence[--azimuthSteps % STEPS]);
        aStep = aStep + 1;
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
{   // function to set steps to be taken by elevation motor
    eStep = steps;
}

void elevation()
{   // function to calculate next elevation step and call elevationStep()
    if (Elevation_Pin_1_Read() == 0 && Elevation_Pin_2_Read() == 0 && Elevation_Pin_3_Read() == 0 && Elevation_Pin_4_Read() == 0)
    {   // if the motor is off, turn it on, on the same step as last time
        elevationStep(stepSequence[elevationSteps % STEPS]);
        return;
    }
    if (eStep > 0)
    {   // turning up (positive steps)
        if (!Limit_Up_Read())
        {   // if up limit is reached, don't move
            eStep = 0;
            return;
        }
        // set elevation motor pins to next step and decrease steps to be taken
        elevationStep(stepSequence[++elevationSteps % STEPS]);
        eStep = eStep - 1;
        return;
    }
    else if (eStep < 0)
    {   // turning down (negative steps)
        if (!Limit_Down_Read())
        {   // if down limit is reached, don't move
            eStep = 0;
            return;
        }
        // set elevation motor pins to next step and decrease steps to be taken
        elevationStep(stepSequence[--elevationSteps % STEPS]);
        eStep = eStep + 1;
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

void setStartPosition(void)
{   // function to set the starting position based on the limit switches
    // Move to the left limit
    while (Limit_Left_Read()) {
        moveAzimuth(-1);
        CyDelay(1);
    }
    azimuthSteps = START_POSITION_AZIMUTH;

    // Move to the down limit
    while (Limit_Down_Read()) {
        moveElevation(-1);
        CyDelay(1);
    }
    elevationSteps = START_POSITION_ELEVATION;
}

int32_t getAzimuthPosition(void) {
    return azimuthSteps;
}

int32_t getElevationPosition(void) {
    return elevationSteps;
}

CY_ISR(MOTOR_STEP)
{   // interrupt routine activated by clock to take steps
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

// to be deleted
CY_ISR(UART_HANDLER)
{
    uint8_t c = UART_1_GetByte();
    UART_1_PutChar(c);
    if (c == 'j')
    {
        aStep = aStep - 800;
    }
    else if (c == 'h')
    {
        aStep = aStep + 800;
    }
    else if (c == 'u')
    {
        eStep = eStep - 8000;
    }
    else if (c == 'n')
    {
        eStep = eStep + 8000;
    }
    else if (c == 'a')
    {
        eStep = eStep - 650;
    }
}
