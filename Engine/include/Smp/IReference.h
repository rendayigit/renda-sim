// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IReference.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IREFERENCE_H_
#define SMP_IREFERENCE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "ICollection.h"
#include "Smp/CannotRemove.h"
#include "Smp/IComponent.h"
#include "Smp/InvalidObjectType.h"
#include "Smp/NotReferenced.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/ReferenceFull.h"
#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface for a reference.
    /// A reference allows querying for the referenced components.
    /// @remarks References are used together with the IAggregate interface for
    ///          aggregation.
    class IReference :
        public virtual Smp::IObject
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IReference() noexcept = default;

        /// Query for the collection of all referenced components.
        /// The returned collection may be empty if no components are 
        /// referenced.
        /// @return  Collection of referenced components.
        virtual const Smp::ComponentCollection* GetComponents() const = 0;

        /// Query for a referenced component by its name.
        /// The returned component may be null if no component with the given 
        /// name could be found.
        /// Multiple components with the same name, but with a different parent
        /// (and hence path) may end up in a single reference. In this case, 
        /// retrieving a component by name is not save, as any of the 
        /// components that match the name may be returned
        /// @param   name Component name.
        /// @return  Referenced component with the given name, or null if no 
        ///          referenced component with the given name could be found.
        ///          If multiple components matching the given name argument 
        ///          are found, it returns one of the references.
        virtual Smp::IComponent* GetComponent(
            Smp::String8 name) const = 0;

        /// Add a referenced component.
        /// This method raises an exception of type ReferenceFull if called for
        /// a full reference, i.e. when the Count has reached the Upper limit. 
        /// This method may raise an exception of type InvalidObjectType when 
        /// it expects the given component to implement another interface as 
        /// well.
        /// Adding a component with a name that already exists in the reference
        /// does not throw an exception, although GetComponent() will no longer
        /// allow to return both referenced components by name.
        /// @param   component New referenced component.
        /// @throws  Smp::InvalidObjectType
        /// @throws  Smp::ReferenceFull
        virtual void AddComponent(
            Smp::IComponent* component) = 0;

        /// Remove a referenced component.
        /// This method raises an exception of type NotReferenced if called 
        /// with a component that is not referenced. If the number of 
        /// referenced components is less than or equal to the Lower limit, 
        /// this method raises an exception of type CannotRemove.
        /// @param   component Referenced component to remove.
        /// @throws  Smp::CannotRemove
        /// @throws  Smp::NotReferenced
        virtual void RemoveComponent(
            Smp::IComponent* component) = 0;

        /// Query for the number of components in the collection.
        /// @return  Current number of components in the collection.
        virtual Smp::Int64 GetCount() const = 0;

        /// Query the maximum number of components in the collection.
        /// A return value of -1 indicates that the collection has no upper 
        /// limit.
        /// 
        /// @remarks This information can be used to check whether another 
        ///          component can be added to the collection.
        /// @remarks This is consistent with the use of upper bounds in UML, 
        ///          where a value of -1 represents no limit (typically shown 
        ///          as *).
        /// @return  Maximum number of components in the collection (-1 = 
        ///          unlimited).
        virtual Smp::Int64 GetUpper() const = 0;

        /// Query the minimum number of components in the collection.
        /// @remarks This information can be used to validate a model 
        ///          hierarchy. If a collection specifies a Lower value above 
        ///          its current Count, then it is not properly configured. An 
        ///          external component may use this information to validate 
        ///          the configuration before executing it.
        /// @return  Minimum number of components in the collection or 0 when 
        ///          no minimum number has been defined.
        virtual Smp::Int64 GetLower() const = 0;
    };

    /// A reference collection is an ordered collection of references, which 
    /// allows iterating all members.
    typedef Smp::ICollection<IReference> ReferenceCollection;

}

#endif // SMP_IREFERENCE_H_
