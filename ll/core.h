#if !defined(CORE_H_)
#define CORE_H_

#if defined(STM32L452)
# include "core/cm4.hpp"
#elif defined(STM32F030x8)
# include "core/m0/cm0.hpp"
#else
# error "This processor is not supported so far"
#endif

#endif
