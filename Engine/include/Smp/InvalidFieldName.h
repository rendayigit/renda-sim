// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidFieldName.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDFIELDNAME_H_
#define SMP_INVALIDFIELDNAME_H_

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
    /// This exception is raised when an invalid field name is specified.
    class InvalidFieldName : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidFieldName() noexcept = default;

        /// Get the fully qualified field name that is invalid.
        /// @return  Fully qualified field name that is invalid.
        virtual Smp::String8 GetFieldName() const noexcept = 0;
    };
}

#endif // SMP_INVALIDFIELDNAME_H_
