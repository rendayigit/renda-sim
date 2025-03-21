// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidTarget.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDTARGET_H_
#define SMP_INVALIDTARGET_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exception.h"
#include "Smp/IField.h"

// ----------------------------------------------------------------------------
// ---------------------------- Forward declarations --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    class IDataflowField;
}

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This exception is raised when trying to connect two data flow fields of
    /// incompatible types.
    class InvalidTarget : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidTarget() noexcept = default;

        /// Get the field for which the Connect operation was called.
        /// @return  Field for which the Connect operation was called
        virtual const Smp::IDataflowField* GetSource() const noexcept = 0;

        /// Get the target field that was passed to the Connect operation.
        /// @return  Target field that was passed to the Connect operation.
        virtual const Smp::IField* GetTarget() const noexcept = 0;
    };

}

#endif // SMP_INVALIDTARGET_H_
