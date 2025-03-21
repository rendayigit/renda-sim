// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidArraySize.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDARRAYSIZE_H_
#define SMP_INVALIDARRAYSIZE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exception.h"
#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This exception is raised when an invalid array size is specified.
    class InvalidArraySize : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidArraySize() noexcept = default;

        /// Get the array size.
        /// @return  Array size.
        virtual Smp::Int64 GetArraySize() const noexcept = 0;

        /// Get the invalid array size, i.e. the size of the array that was 
        /// passed as argument.
        /// @return  Invalid array size, i.e. the size of the array that was 
        ///          passed as argument.
        virtual Smp::Int64 GetInvalidSize() const noexcept = 0;
    };
}

#endif // SMP_INVALIDARRAYSIZE_H_
