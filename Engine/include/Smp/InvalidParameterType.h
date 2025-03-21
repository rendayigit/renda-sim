// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidParameterType.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDPARAMETERTYPE_H_
#define SMP_INVALIDPARAMETERTYPE_H_

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
    /// This exception is raised by the Invoke() method when trying to invoke a
    /// method passing a parameter of wrong type.
    /// @remarks The index of the parameter of wrong type can be extracted from
    ///          the request using the method GetParameterIndex().
    class InvalidParameterType : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidParameterType() noexcept = default;

        /// Get the Operation name of request passed to the Invoke() method.
        /// @return  Operation name of request passed to the Invoke() method.
        virtual Smp::String8 GetOperationName() const noexcept = 0;

        /// Get the name of parameter of wrong type.
        /// @return  Name of parameter of wrong type.
        virtual Smp::String8 GetParameterName() const noexcept = 0;

        /// Get the Type that is not valid.
        /// @return  Type that is not valid.
        virtual Smp::PrimitiveTypeKind GetInvalidType() const noexcept = 0;

        /// Get the Type that was expected.
        /// @return  Type that was expected.
        virtual Smp::PrimitiveTypeKind GetExpectedType() const noexcept = 0;
    };
}

#endif // SMP_INVALIDPARAMETERTYPE_H_
