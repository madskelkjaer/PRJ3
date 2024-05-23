#include "SensorDriver.h"

bool sunLeft()
{
    return !sunLeft_Read();
}

bool sunRight()
{
    return !sunRight_Read();
}

bool sunUp()
{
    return !sunUp_Read();
}

bool sunDown()
{
    return !sunDown_Read();
}
