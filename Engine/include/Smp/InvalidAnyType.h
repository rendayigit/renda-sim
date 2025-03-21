// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidAnyType.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDANYTYPE_H_
#define SMP_INVALIDANYTYPE_H_

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
    /// This exception is raised when trying to use an AnySimple argument of 
    /// wrong type.
    /// @remarks This can happen when assigning a value to an AnySimple 
    ///          instance, but as well when e.g. registering an event sink with
    ///          an event source of another event argument type.
    class InvalidAnyType : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidAnyType() noexcept = default;

        /// Get the type that is not valid.
        /// @return  Type that is not valid.
        virtual Smp::PrimitiveTypeKind GetInvalidType() const noexcept = 0;

        /// Get the type that was expected.
        /// @return  Type that was expected.
        virtual Smp::PrimitiveTypeKind GetExpectedType() const noexcept = 0;
    };
}

#endif // SMP_INVALIDANYTYPE_H_
