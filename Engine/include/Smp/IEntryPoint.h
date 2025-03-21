// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IEntryPoint.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IENTRYPOINT_H_
#define SMP_IENTRYPOINT_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/ICollection.h"
#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface of an entry point.
    /// This interface provides a notification method (event handler) that can 
    /// be called e.g. by the Scheduler or Event Manager when an event is 
    /// emitted.
    class IEntryPoint :
        public virtual Smp::IObject
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IEntryPoint() noexcept = default;

        /// This method shall be called when an associated event is emitted.
        virtual void Execute() const = 0;
    };

    /// An entry point collection is an ordered collection of entry points, 
    /// which allows iterating all members.
    typedef Smp::ICollection<IEntryPoint> EntryPointCollection;
}

#endif // SMP_IENTRYPOINT_H_
