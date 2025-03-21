// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidParameterIndex.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDPARAMETERINDEX_H_
#define SMP_INVALIDPARAMETERINDEX_H_

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
    /// This exception is raised when using an invalid parameter index to set 
    /// (SetParameterValue()) or get (GetParameterValue()) a parameter value of
    /// an operation in a request.
    class InvalidParameterIndex : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidParameterIndex() noexcept = default;

        /// Get the name of the operation.
        /// @return  Name of the operation.
        virtual Smp::String8 GetOperationName() const noexcept = 0;

        /// Get the invalid parameter index used.
        /// @return  Invalid parameter index used.
        virtual Smp::Int32 GetParameterIndex() const noexcept = 0;

        /// Get the number of parameters of the operation.
        /// @return  Number of parameters of the operation.
        virtual Smp::Int32 GetParameterCount() const noexcept = 0;
    };
}

#endif // SMP_INVALIDPARAMETERINDEX_H_
