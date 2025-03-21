// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IProperty.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IPROPERTY_H_
#define SMP_IPROPERTY_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/AccessKind.h"
#include "Smp/AnySimple.h"
#include "Smp/ICollection.h"
#include "Smp/Publication/IType.h"
#include "Smp/ViewKind.h"
#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This interface describes a published property.
    class IProperty :
        public virtual Smp::IObject
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IProperty() noexcept = default;

        /// Provides the type of the property.
        /// @return  Type of the property.
        virtual Smp::Publication::IType* GetType() const = 0;

        /// Provides the access kind of the property.
        /// @return  Access kind of the property.
        virtual Smp::AccessKind GetAccess() const = 0;

        /// Provides the view kind of the property.
        /// @return  View kind of the property.
        virtual Smp::ViewKind GetView() const = 0;

        /// Provides the value of the property.
        /// Throws InvalidAccess if the property is Write Only.
        /// @return  The current value of the property.
        virtual Smp::AnySimple GetValue() const = 0;

        /// Sets the value of the property.
        /// Throws InvalidAccess if the property is Read Only.
        /// @param   value New value of the property.
        virtual void SetValue(
            Smp::AnySimple value) = 0;
    };

    /// A field collection is an ordered collection of properties, which allows
    /// iterating all members.
    typedef Smp::ICollection<IProperty> PropertyCollection;

}

#endif // SMP_IPROPERTY_H_
