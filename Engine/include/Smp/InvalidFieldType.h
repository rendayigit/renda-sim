// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidFieldType.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDFIELDTYPE_H_
#define SMP_INVALIDFIELDTYPE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exception.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Invalid field type.
    /// This exception is raised when trying to publish a field with invalid 
    /// type.
    /// @remarks This can happen, for example, when trying to publish a field 
    ///          of the variable-length simple type String8.
    class InvalidFieldType : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidFieldType() noexcept = default;

    };
}

#endif // SMP_INVALIDFIELDTYPE_H_
