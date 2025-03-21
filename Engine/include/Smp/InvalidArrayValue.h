// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidArrayValue.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDARRAYVALUE_H_
#define SMP_INVALIDARRAYVALUE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/AnySimple.h"
#include "Smp/Exception.h"
#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This exception is raised when trying to assign an illegal value to an 
    /// array field.
    class InvalidArrayValue : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidArrayValue() noexcept = default;

        /// Get the index in the array where the first invalid value was found.
        /// @return  Index in the array where the first invalid value was found.
        virtual Smp::Int64 GetInvalidValueIndex() const noexcept = 0;

        /// Get the invalid value that was passed as new field value.
        /// @return  Invalid value that was passed as new field value.
        virtual Smp::AnySimple GetInvalidValue() const noexcept = 0;
    };
}

#endif // SMP_INVALIDARRAYVALUE_H_
