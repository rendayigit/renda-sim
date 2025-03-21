// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IFailure.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IFAILURE_H_
#define SMP_IFAILURE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/ICollection.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/IPersist.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface for a failure.
    /// A Failure allows to query and to set its state to Failed or Unfailed. 
    /// Failures can be exposed via the IFallibleModel interface.
    /// @remarks Even if a model exposes its failures via the IFallibleModel 
    ///          interface, it is still fully in charge of break-pointing the 
    ///          state of each failure.
    class IFailure :
        public virtual Smp::IPersist
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IFailure() noexcept = default;

        /// Sets the state of the failure to failed.
        virtual void Fail() = 0;

        /// Sets the state of the failure to unfailed.
        virtual void Unfail() = 0;

        /// Returns whether the failure's state is set to failed.
        /// @return  Returns true if the failure state is Failed, false 
        ///          otherwise.
        virtual Smp::Bool IsFailed() const = 0;
    };

    /// A failure collection is an ordered collection of failures, which allows
    /// iterating all members.
    typedef Smp::ICollection<IFailure> FailureCollection;
}

#endif // SMP_IFAILURE_H_
