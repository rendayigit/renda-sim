// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/CannotStore.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_CANNOTSTORE_H_
#define SMP_CANNOTSTORE_H_

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
    /// This exception is raised when the component cannot store its data to 
    /// the storage writer given to the Store() method.
    /// @remarks This may e.g. be if there is no disk space left.
    class CannotStore : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~CannotStore() noexcept = default;

    };
}

#endif // SMP_CANNOTSTORE_H_
