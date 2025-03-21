// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/CannotRestore.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_CANNOTRESTORE_H_
#define SMP_CANNOTRESTORE_H_

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
    /// This exception is raised when the content of the storage reader passed 
    /// to the Restore() method contains invalid data.
    /// @remarks This typically happens when a Store() has been created from a 
    ///          different configuration of objects.
    class CannotRestore : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~CannotRestore() noexcept = default;

    };
}

#endif // SMP_CANNOTRESTORE_H_
