// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/DuplicateUuid.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_DUPLICATEUUID_H_
#define SMP_DUPLICATEUUID_H_

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
    /// This exception is raised when trying to register a factory under a Uuid
    /// that has already been used to register another (or the same) 
    /// factory.This would lead to duplicate implementation Uuids.
    class DuplicateUuid : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~DuplicateUuid() noexcept = default;

        /// Get the name of factory that tried to register under this Uuid.
        /// @return  Name of factory that tried to register under this Uuid.
        virtual Smp::String8 GetOldName() const noexcept = 0;

        /// Get the name of factory that tried to register under this Uuid.
        /// @return  Name of factory that tried to register under this Uuid.
        virtual Smp::String8 GetNewName() const noexcept = 0;
    };
}

#endif // SMP_DUPLICATEUUID_H_
