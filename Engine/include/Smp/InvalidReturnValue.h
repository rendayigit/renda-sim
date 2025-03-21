// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidReturnValue.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDRETURNVALUE_H_
#define SMP_INVALIDRETURNVALUE_H_

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
    /// This exception is raised when trying to assign an invalid return value 
    /// of an operation in a request using SetReturnValue().
    class InvalidReturnValue : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidReturnValue() noexcept = default;

        /// Get the name of the operation.
        /// @return  Name of the operation.
        virtual Smp::String8 GetOperationName() const noexcept = 0;

        /// Get the value that was passed as return value.
        /// @return  Value that was passed as return value.
        virtual Smp::AnySimple GetValue() const noexcept = 0;
    };
}

#endif // SMP_INVALIDRETURNVALUE_H_
