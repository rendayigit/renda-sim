// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IArrayField.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IARRAYFIELD_H_
#define SMP_IARRAYFIELD_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IField.h"
#include "Smp/InvalidArrayIndex.h"
#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface of a field which is of array type.
    class IArrayField :
        public virtual Smp::IField
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IArrayField() noexcept = default;

        /// Get the size (number of array items) of the field.
        /// @return  Size (number of array items) of the field.
        virtual Smp::UInt64 GetSize() const = 0;

        /// Get an array item by index.
        /// @param   index Index of item to get.
        /// @return  Array item (Field) at given index.
        /// @throws  Smp::InvalidArrayIndex
        virtual Smp::IField* GetItem(
            Smp::UInt64 index) const = 0;
    };

}

#endif // SMP_IARRAYFIELD_H_
