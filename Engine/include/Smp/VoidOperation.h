// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/VoidOperation.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_VOIDOPERATION_H_
#define SMP_VOIDOPERATION_H_

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
    /// This exception is raised when trying to read (GetReturnValue()) or 
    /// write (SetReturnValue()) the return value of a void operation.
    class VoidOperation : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~VoidOperation() noexcept = default;

        /// Get the name of the operation.
        /// @return  Name of the operation.
        virtual Smp::String8 GetOperationName() const noexcept = 0;
    };
}

#endif // SMP_VOIDOPERATION_H_
