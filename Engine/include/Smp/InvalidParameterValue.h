// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidParameterValue.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDPARAMETERVALUE_H_
#define SMP_INVALIDPARAMETERVALUE_H_

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
    /// This exception is raised when trying to assign an illegal value to a 
    /// parameter of an operation in a request using SetParameterValue().
    class InvalidParameterValue : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidParameterValue() noexcept = default;

        /// Get the name of parameter value was assigned to.
        /// @return  Name of parameter value was assigned to.
        virtual Smp::String8 GetParameterName() const noexcept = 0;

        /// Get the value that was passed as parameter.
        /// @return  Value that was passed as parameter.
        virtual Smp::AnySimple GetValue() const noexcept = 0;
    };
}

#endif // SMP_INVALIDPARAMETERVALUE_H_
