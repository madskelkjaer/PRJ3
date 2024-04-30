#include <stdint.h> 

#define MODE_AUTO 1
#define MODE_MANUAL 0

void trackSun(void);
void setMode(int mode);
void manualControl(uint8_t command); 
int getCurrentMode(void); 

