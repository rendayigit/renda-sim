// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/AccessKind.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_ACCESSKIND_H_
#define SMP_ACCESSKIND_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// The Access Kind of a property defines whether it has getter and setter.
    enum class AccessKind : Smp::Int32
    {
        /// Read/Write access, i.e. getter and setter.
        AK_ReadWrite,

        /// Read only access, i.e. only getter method.
        AK_ReadOnly,

        /// Write only access, i.e. only setter method.
        AK_WriteOnly
    };

    /// Stream operator for AccessKind to be able to print an enum value.
    /// @param os Output stream to output to.
    /// @param obj Object to output to stream.
    std::ostream& operator << (std::ostream& os, const AccessKind& obj);
}

#endif // SMP_ACCESSKIND_H_
