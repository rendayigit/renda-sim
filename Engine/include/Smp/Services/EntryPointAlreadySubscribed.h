// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Services/EntryPointAlreadySubscribed.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_SERVICES_ENTRYPOINTALREADYSUBSCRIBED_H_
#define SMP_SERVICES_ENTRYPOINTALREADYSUBSCRIBED_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exception.h"
#include "Smp/IEntryPoint.h"
#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Namespace for simulation services
    namespace Services
    {
        /// This exception is raised when trying to subscribe an entry point to
        /// an event that is already subscribed.
        class EntryPointAlreadySubscribed : public virtual Smp::Exception
        {
        public:

            /// Virtual destructor to release memory.
            virtual ~EntryPointAlreadySubscribed() noexcept = default;

            /// Get the entry point that is already subscribed to the event.
            /// @return  Entry point that is already subscribed to the event.
            virtual const Smp::IEntryPoint* GetEntryPoint() const noexcept = 0;

            /// Get the name of the event that the entry point is already 
            /// subscribed to.
            /// @return  Name of the event that the entry point is already 
            ///          subscribed to.
            virtual Smp::String8 GetEventName() const noexcept = 0;
        };
    }
}

#endif // SMP_SERVICES_ENTRYPOINTALREADYSUBSCRIBED_H_
