// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidArrayIndex.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDARRAYINDEX_H_
#define SMP_INVALIDARRAYINDEX_H_

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
    /// This exception is raised when an invalid index is specified.
    class InvalidArrayIndex : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidArrayIndex() noexcept = default;

        /// Get the invalid array index, i.e. the index that was passed as 
        /// argument, but is outside of the array.
        /// @return  Invalid array index, i.e. the index that was passed as 
        ///          argument, but is outside of the array.
        virtual Smp::Int64 GetInvalidIndex() const noexcept = 0;

        /// Get the array size.
        /// @return  Array size.
        virtual Smp::Int64 GetArraySize() const noexcept = 0;
    };
}

#endif // SMP_INVALIDARRAYINDEX_H_
