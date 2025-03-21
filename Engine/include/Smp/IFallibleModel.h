// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IFallibleModel.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IFALLIBLEMODEL_H_
#define SMP_IFALLIBLEMODEL_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IFailure.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/IModel.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface for a fallible model that exposes its failure state and a 
    /// collection of failures.
    /// A fallible model allows querying for its failures by name.
    /// @remarks Even if a model exposes its failures via the IFallibleModel 
    ///          interface, it is still fully in charge of break-pointing the 
    ///          state of each failure.
    class IFallibleModel :
        public virtual Smp::IModel
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IFallibleModel() noexcept = default;

        /// Query for whether the model is failed. A model is failed when at 
        /// least one of its failures is failed.
        /// @return  Whether the model is failed or not.
        virtual Smp::Bool IsFailed() const = 0;

        /// Query for the collection of all failures.
        /// The returned collection may be empty if no failures exist for the 
        /// fallible model.
        /// @return  Failure collection of the model.
        virtual const Smp::FailureCollection* GetFailures() const = 0;

        /// Get a failure by name.
        /// The returned failure may be null if no child with the given name 
        /// could be found.
        /// @param   name Name of the failure to return.
        /// @return  Failure queried for by name, or null if no failure with 
        ///          this name exists.
        virtual Smp::IFailure* GetFailure(
            Smp::String8 name) const = 0;
    };

}

#endif // SMP_IFALLIBLEMODEL_H_
