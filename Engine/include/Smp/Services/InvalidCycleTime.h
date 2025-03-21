// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Services/InvalidCycleTime.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_SERVICES_INVALIDCYCLETIME_H_
#define SMP_SERVICES_INVALIDCYCLETIME_H_

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
        /// scheduler when the event is a cyclic event (i.e. repeat is not 0), 
        /// but the cycle time specified is not a positive duration.
        class InvalidCycleTime : public virtual Smp::Exception
        {
        public:

            /// Virtual destructor to release memory.
            virtual ~InvalidCycleTime() noexcept = default;

        };
    }
}

#endif // SMP_SERVICES_INVALIDCYCLETIME_H_
