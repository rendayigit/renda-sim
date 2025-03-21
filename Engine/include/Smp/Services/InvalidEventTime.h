// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Services/InvalidEventTime.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_SERVICES_INVALIDEVENTTIME_H_
#define SMP_SERVICES_INVALIDEVENTTIME_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exception.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Namespace for simulation services
    namespace Services
    {
        /// This exception is thrown by one of the AddEvent() methods of the 
        /// scheduler when the time specified for the first execution of the 
        /// event is in the past.
        class InvalidEventTime : public virtual Smp::Exception
        {
        public:

            /// Virtual destructor to release memory.
            virtual ~InvalidEventTime() noexcept = default;

        };
    }
}

#endif // SMP_SERVICES_INVALIDEVENTTIME_H_
