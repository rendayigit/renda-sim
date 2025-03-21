// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IField.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IFIELD_H_
#define SMP_IFIELD_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/ICollection.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/Publication/IType.h"
#include "Smp/ViewKind.h"
#include "Smp/IObject.h"
#include "Smp/IPersist.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface of a field.
    class IField :
        public virtual Smp::IPersist
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IField() noexcept = default;

        /// Return View kind of the field.
        /// @return  The View kind of the field.
        /// The view kind indicates which user roles have visibility of the 
        /// field.
        virtual Smp::ViewKind GetView() const = 0;

        /// Return State flag of the field.
        /// @return  The State flag of the field.
        /// When true, the state of the field shall be stored by the simulation
        /// infrastructure persistence mechanism on Store(), and restored on 
        /// Restore().
        virtual Smp::Bool IsState() const = 0;

        /// Return Input flag of the field.
        /// @return  The Input flag of the field.
        /// When true, the field is considered an input into the model and can 
        /// be used as target of a field link in data flow based design.
        virtual Smp::Bool IsInput() const = 0;

        /// Return Output flag of the field.
        /// @return  The Output flag of the field.
        /// When true, the field is considered an output of the model and can 
        /// be used as source of a field link in data flow based design.
        virtual Smp::Bool IsOutput() const = 0;

        /// Returns the type of this field.
        /// @return  The type of this field.
        virtual const Smp::Publication::IType* GetType() const = 0;
    };

    /// A field collection is an ordered collection of fields, which allows 
    /// iterating all members.
    typedef Smp::ICollection<IField> FieldCollection;

}

#endif // SMP_IFIELD_H_
