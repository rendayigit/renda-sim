// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidParameterCount.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDPARAMETERCOUNT_H_
#define SMP_INVALIDPARAMETERCOUNT_H_

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
    /// method with a wrong number of parameters.
    class InvalidParameterCount : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidParameterCount() noexcept = default;

        /// Get the Operation name of request passed to the Invoke() method.
        /// @return  Operation name of request passed to the Invoke() method.
        virtual Smp::String8 GetOperationName() const noexcept = 0;

        /// Get the correct number of parameters of operation.
        /// @return  Correct number of parameters of operation.
        virtual Smp::Int32 GetOperationParameters() const noexcept = 0;

        /// Get the wrong number of parameters of operation.
        /// @return  Wrong number of parameters of operation.
        virtual Smp::Int32 GetRequestParameters() const noexcept = 0;
    };
}

#endif // SMP_INVALIDPARAMETERCOUNT_H_
