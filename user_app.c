/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    //LATA = 0x80;
    T0CON0 = 0x90;
    T0CON1 = 0x54;

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
#if 1
    // Graphic for sawtooth and triangle waveform
    while (DAC1DATL < 0xFF)
    {
        DAC1DATL ++;
        TimeXus(0x04);
        while (PIR3bits.TMR0IF == 0x00);
    }
    
    if (DAC1DATL == 0xFF)
    {
        DAC1DATL == 0;
        TimeXus(0x04);
        while (PIR3bits.TMR0IF == 0x00);
    }
#endif
    
#if 0
    // Graphing code for sinusoid
    for(int i = 0; i < 256; i += 1)
    {
        DAC1DATL = UserApp_au8sinTable[i];
        TimeXus(11);
        while(PIR3bits.TMR0IF == 0);
    }
#endif

} /* end UserAppRun */

/*!--------------------------------------------------------------------------
 * void TimeXus(INPUT_PARAMETER_)
 * Sets Timer0 to count u16Microseconds_
 * 
 * Requires:
 * -Timer0 configured such that each timer tick is 1 microsecond
 * -INPUT_PARAMETER_is the value in microseconds to time from 1 to 65535
 * 
 * Promises:
 * -Pre-loads TMR0H:L to clock out desired period
 * -TMR0IF cleared-Timer0 enabled
 */

void TimeXus(u16 u16Time)
{
    T0CON0 = T0CON0 & 0x7F;
       
    u16 u16userIN = 0xFFFF - u16Time;
    TMR0L = u16userIN & 0xFF;
    TMR0H = (u16userIN >> 8) & 0xFF;
       
    PIR3 &= 0x7F;
       
    T0CON0 |= 0x80;

#if 0
    while((PIR3 & 0x80) != 0x80) {}
#endif
}

/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
