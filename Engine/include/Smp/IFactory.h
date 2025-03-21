// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IFactory.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IFACTORY_H_
#define SMP_IFACTORY_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/ICollection.h"
#include "Smp/IComponent.h"
#include "Smp/IComposite.h"
#include "Smp/InvalidObjectName.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/Uuid.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface for a component factory.
    class IFactory :
        public virtual Smp::IObject
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IFactory() noexcept = default;

        /// Get Universally unique identifier of the type instantiated by the 
        /// factory.
        /// @return  Universally unique identifier of component.
        virtual Smp::Uuid GetUuid() const = 0;

        /// Returns the fully qualified C++ name of the type.
        /// @return  Fully qualified C++ name of type that is created by this 
        ///          factory.
        virtual Smp::String8 GetTypeName() const = 0;

        /// Create a new instance with given name, description and parent.
        /// @param   name Name of the new instance.
        /// f the name provided is not a valid object name, an exception of 
        /// type InvalidObjectName is raised.
        /// @param   description Description of the new instance.
        /// @param   parent Parent object of the new instance.
        /// @return  New component instance.
        /// @throws  Smp::InvalidObjectName
        virtual Smp::IComponent* CreateInstance(
            Smp::String8 name,
            Smp::String8 description,
            Smp::IComposite* parent) = 0;

        /// Delete an existing instance.
        /// @param   instance Instance to delete.
        virtual void DeleteInstance(
            Smp::IComponent* instance) = 0;
    };

    /// A factory collection is an ordered collection of factories, which 
    /// allows iterating all members.
    typedef Smp::ICollection<IFactory> FactoryCollection;
}

#endif // SMP_IFACTORY_H_
