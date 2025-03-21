// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Publication/IType.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_PUBLICATION_ITYPE_H_
#define SMP_PUBLICATION_ITYPE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/PrimitiveTypes.h"
#include "Smp/Uuid.h"
#include "Smp/ViewKind.h"
#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ---------------------------- Forward declarations --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    class IPublication;
}

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Namespace for publication
    namespace Publication
    {
        /// This base interface defines a type in the type registry.
        class IType :
            public virtual Smp::IObject
        {
        public:

            /// Virtual destructor to release memory.
            virtual ~IType() noexcept = default;

            /// Get primitive type kind that this type maps to, or PTK_None 
            /// when the type cannot be mapped to a primitive type.
            /// @return  Primitive type kind that this type can be mapped to, 
            ///          or PTK_None for none.
            virtual Smp::PrimitiveTypeKind GetPrimitiveTypeKind() const = 0;

            /// Get Universally Unique Identifier of type.
            /// @return  Universally Unique Identifier of type.
            virtual Smp::Uuid GetUuid() const = 0;

            /// Publish an instance of the type against a receiver.
            /// @param   receiver Receiver to publish against.
            /// @param   name Name of instance.
            /// @param   description Description of instance.
            /// @param   address Address of instance.
            /// @param   view View kind of instance.
            /// @param   state State flag of instance.
            /// @param   input Input flag of instance.
            /// @param   output Output flag of instance.
            virtual void Publish(
                Smp::IPublication* receiver,
                Smp::String8 name,
                Smp::String8 description,
                void* address,
                Smp::ViewKind view = Smp::ViewKind::VK_All,
                Smp::Bool state = true,
                Smp::Bool input = false,
                Smp::Bool output = false) = 0;
        };
    }
}

#endif // SMP_PUBLICATION_ITYPE_H_
