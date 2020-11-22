#if !defined(ADDRESSES_H_)
#define ADDRESSES_H_

#if defined(STM32L452)
# include "l4/52/addresses.h"
#else
# error "This board is not supported so far"
#endif

#endif
