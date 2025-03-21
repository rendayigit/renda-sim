// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Services/InvalidEventName.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_SERVICES_INVALIDEVENTNAME_H_
#define SMP_SERVICES_INVALIDEVENTNAME_H_

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
        /// This exception is thrown by the QueryEventId() method of the event 
        /// manger when an empty event name has been provided.
        class InvalidEventName : public virtual Smp::Exception
        {
        public:

            /// Virtual destructor to release memory.
            virtual ~InvalidEventName() noexcept = default;

        };
    }
}

#endif // SMP_SERVICES_INVALIDEVENTNAME_H_
