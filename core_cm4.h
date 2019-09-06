#ifndef __CORE_CM4_H_GENERIC
#define __CORE_CM4_H_GENERIC

#include <assert.h>

//static __INLINE void NVIC_SystemReset(void) {
//  SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)      |
//                 (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
//                 SCB_AIRCR_SYSRESETREQ_Msk);                   /* Keep priority group unchanged */
//
//  while(1);                                                    /* wait until reset */
//}

static void NVIC_SystemReset(void) {
	assert(0);
}

#endif
