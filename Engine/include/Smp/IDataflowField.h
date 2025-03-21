// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IDataflowField.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IDATAFLOWFIELD_H_
#define SMP_IDATAFLOWFIELD_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/FieldAlreadyConnected.h"
#include "Smp/IField.h"
#include "Smp/InvalidTarget.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This interface is implemented by a Field that can take part in direct 
    /// inter-component data flow.
    class IDataflowField :
        public virtual Smp::IField
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IDataflowField() noexcept = default;

        /// Connect this field to a target field for direct data flow.
        /// As the Push() operation only requires to set a value, the target 
        /// field can be any field (it does not need to be of type 
        /// IDataflowField).
        /// @param   target Target field to connect to. The field type must be 
        ///          compatible.
        /// @throws  Smp::FieldAlreadyConnected
        /// @throws  Smp::InvalidTarget
        virtual void Connect(
            Smp::IField* target) = 0;

        /// Push the current field value to all connected target fields.
        virtual void Push() = 0;
    };

}

#endif // SMP_IDATAFLOWFIELD_H_
