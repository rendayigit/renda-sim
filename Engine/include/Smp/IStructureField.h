// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IStructureField.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_ISTRUCTUREFIELD_H_
#define SMP_ISTRUCTUREFIELD_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IField.h"
#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface of a structure field.
    class IStructureField :
        public virtual Smp::IField
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IStructureField() noexcept = default;

        /// Return the collection of fields of the structure.
        /// @return  Collection of fields of the structure.
        virtual const Smp::FieldCollection* GetFields() const = 0;

        /// Return a field by name.
        /// @param   name Name of the field to retrieve.
        /// @return  Field object, or null if no field with the given name 
        ///          exists.
        virtual Smp::IField* GetField(
            Smp::String8 name) const = 0;
    };

}

#endif // SMP_ISTRUCTUREFIELD_H_
