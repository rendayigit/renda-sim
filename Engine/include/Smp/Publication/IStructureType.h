// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Publication/IStructureType.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_PUBLICATION_ISTRUCTURETYPE_H_
#define SMP_PUBLICATION_ISTRUCTURETYPE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/PrimitiveTypes.h"
#include "Smp/Uuid.h"
#include "Smp/ViewKind.h"
#include "Smp/Publication/IType.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Namespace for publication
    namespace Publication
    {
        /// This interface defines a user defined structure type.
        class IStructureType :
            public virtual Smp::Publication::IType
        {
        public:

            /// Virtual destructor to release memory.
            virtual ~IStructureType() noexcept = default;

            /// Add a field to the Structure.
            /// @param   name Name of field.
            /// @param   description Description of field.
            /// @param   uuid Uuid of field Type, which must be a value type, 
            ///          but not String8.
            /// @param   offset Memory offset of field relative to Structure.
            /// @param   view View kind of field.
            /// @param   state State flag of field. When true, the field shall 
            ///          be part of a state vector (Store/Restore).
            /// @param   input Input flag of field. When true, the field can be
            ///          used as target of a dataflow connection.
            /// @param   output Output flag of field. When true, the field can 
            ///          be used as source of a dataflow connection.
            virtual void AddField(
                Smp::String8 name,
                Smp::String8 description,
                Smp::Uuid uuid,
                Smp::Int64 offset,
                Smp::ViewKind view = Smp::ViewKind::VK_All,
                Smp::Bool state = true,
                Smp::Bool input = false,
                Smp::Bool output = false) = 0;
        };
    }
}

#endif // SMP_PUBLICATION_ISTRUCTURETYPE_H_
