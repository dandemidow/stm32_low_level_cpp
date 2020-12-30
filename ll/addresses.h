#if !defined(ADDRESSES_H_)
#define ADDRESSES_H_

#if defined(STM32L452)
# include "l4/52/addresses.h"
#elif defined(STM32F030x8)
# include "f0/30x8/addresses.h"
#else
# error "This board is not supported so far"
#endif

#endif
