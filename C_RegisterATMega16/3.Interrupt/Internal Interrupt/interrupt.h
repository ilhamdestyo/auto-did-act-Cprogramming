#include <stdio.h>
#include "io.h"
#define __STRINGIFY(x) #x
#define _VECTOR(N) __vector_ ## N

//ISR
#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define __INTR_ATTRS __used__, __externally_visible__
#else /* GCC < 4.1 */
#  define __INTR_ATTRS __used__
#endif

#  define ISR(vector, ...)            \
    void vector (void) __attribute__ ((__signal__,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

//sei
# define sei()  __asm__ __volatile__ ("sei" ::: "memory")
//cli
# define cli()  __asm__ __volatile__ ("cli" ::: "memory")

#define bit0 	0
#define bit1 	1
#define bit2 	2
#define bit3 	3
#define bit4 	4
#define bit5 	5
#define bit6 	6
#define bit7 	7
