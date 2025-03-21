// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Publication/IPublishOperation.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_PUBLICATION_IPUBLISHOPERATION_H_
#define SMP_PUBLICATION_IPUBLISHOPERATION_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/DuplicateName.h"
#include "Smp/InvalidObjectName.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/Publication/ParameterDirectionKind.h"
#include "Smp/Publication/TypeNotRegistered.h"
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
        /// This interface provides functionality to publish operation 
        /// parameters.
        class IPublishOperation
        {
        public:

            /// Virtual destructor to release memory.
            virtual ~IPublishOperation() noexcept = default;

            /// Publish a parameter of an operation with the given name, 
            /// description, type and direction.
            /// If a parameter with the same name has already been published, 
            /// and exception of type DuplicateName is thrown.
            /// If the name is not a valid name, an exception of type 
            /// InvalidObjectName is thrown.
            /// If no type with the given type UUID exists, an exception of 
            /// type TypeNotRegistered is thrown.
            /// @param   name Name of parameter.
            /// @param   description Description of parameter.
            /// @param   typeUuid Uuid of parameter type.
            /// @param   direction Direction kind of parameter.
            /// @throws  Smp::DuplicateName
            /// @throws  Smp::InvalidObjectName
            /// @throws  Smp::Publication::TypeNotRegistered
            virtual void PublishParameter(
                Smp::String8 name,
                Smp::String8 description,
                Smp::Uuid typeUuid,
                Smp::Publication::ParameterDirectionKind direction = ParameterDirectionKind::PDK_In) = 0;
        };
    }
}

#endif // SMP_PUBLICATION_IPUBLISHOPERATION_H_
