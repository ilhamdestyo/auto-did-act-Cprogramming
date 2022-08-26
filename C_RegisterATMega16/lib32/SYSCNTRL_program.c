/*
 *
 * Control sleep mode on AVR ATMega32
 *
 *
 */

#include "Macros.h"
#include "Std_Types.h"
#include "SYSCNTRL_private.h"
#include "SYSCNTRL_interface.h"

void SYSCNTRL_vidEnableSleep(u8 u8Mode)
{
	switch(u8Mode)
	{
		case SYSCNTRL_SLEEPMODE_IDLE:
		SET_BIT(MCUCR,SE);
		CLEAR_BIT(MCUCR,SM0);
		CLEAR_BIT(MCUCR,SM1);
		CLEAR_BIT(MCUCR,SM2);
		break;
		case SYSCNTRL_SLEEPMODE_PWDOWN:
		SET_BIT(MCUCR,SE);
		CLEAR_BIT(MCUCR,SM0);
		SET_BIT(MCUCR,SM1);
		CLEAR_BIT(MCUCR,SM2);
		break;
		case SYSCNTRL_SLEEPMODE_PWSAVE:
		SET_BIT(MCUCR,SE);
		SET_BIT(MCUCR,SM0);
		SET_BIT(MCUCR,SM1);
		CLEAR_BIT(MCUCR,SM2);
		break;
		case SYSCNTRL_SLEEPMODE_STANDBY:
		SET_BIT(MCUCR,SE);
		CLEAR_BIT(MCUCR,SM0);
		SET_BIT(MCUCR,SM1);
		SET_BIT(MCUCR,SM2);
		break;
		case SYSCNTRL_SLEEPMODE_ESTANDBY:
		SET_BIT(MCUCR,SE);
		SET_BIT(MCUCR,SM0);
		SET_BIT(MCUCR,SM1);
		SET_BIT(MCUCR,SM2);
		break;

	}

	asm("SLEEP");
}