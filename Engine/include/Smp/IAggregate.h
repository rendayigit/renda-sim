// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IAggregate.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IAGGREGATE_H_
#define SMP_IAGGREGATE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IReference.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/IComponent.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface for an aggregate component.
    /// A component with references to other components implements this 
    /// interface. Referenced components are held in named references.
    /// @remarks This interface represents the Aggregation mechanism in the SMP
    ///          Metamodel (via References). In UML 2.0, this is represented by
    ///          a required interface.
    class IAggregate :
        public virtual Smp::IComponent
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IAggregate() noexcept = default;

        /// Query for the collection of all references of the aggregate 
        /// component.
        /// The returned collection may be empty if no references exist for the
        /// aggregate.
        /// @return  Collection of references.
        virtual const Smp::ReferenceCollection* GetReferences() const = 0;

        /// Query for a reference of this aggregate component by its name.
        /// The returned reference may be null if no reference with the given 
        /// name could be found. If more than one reference with this name 
        /// exists, it is not defined which one is returned.
        /// @param   name Reference name.
        /// @return  Reference queried for by name, or null if no reference 
        ///          with this name exists.
        virtual Smp::IReference* GetReference(
            Smp::String8 name) const = 0;
    };

}

#endif // SMP_IAGGREGATE_H_
