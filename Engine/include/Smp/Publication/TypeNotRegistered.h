// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Publication/TypeNotRegistered.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_PUBLICATION_TYPENOTREGISTERED_H_
#define SMP_PUBLICATION_TYPENOTREGISTERED_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exception.h"
#include "Smp/Uuid.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Namespace for publication
    namespace Publication
    {
        /// This exception is raised when trying to publish a feature with a 
        /// type Uuid that has not been registered.
        class TypeNotRegistered : public virtual Smp::Exception
        {
        public:

            /// Virtual destructor to release memory.
            virtual ~TypeNotRegistered() noexcept = default;

            /// Get the Uuid for which no type has been registered.
            /// @return  Uuid for which no type has been registered.
            virtual Smp::Uuid GetUuid() const noexcept = 0;
        };
    }
}

#endif // SMP_PUBLICATION_TYPENOTREGISTERED_H_
