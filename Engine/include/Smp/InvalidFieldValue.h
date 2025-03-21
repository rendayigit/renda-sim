// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidFieldValue.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDFIELDVALUE_H_
#define SMP_INVALIDFIELDVALUE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/AnySimple.h"
#include "Smp/Exception.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This exception is raised when trying to assign an illegal value to a 
    /// field.
    class InvalidFieldValue : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidFieldValue() noexcept = default;

        /// Get the value that was passed as new field value.
        /// @return  Value that was passed as new field value.
        virtual Smp::AnySimple GetInvalidFieldValue() const noexcept = 0;
    };
}

#endif // SMP_INVALIDFIELDVALUE_H_
