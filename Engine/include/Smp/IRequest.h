// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IRequest.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IREQUEST_H_
#define SMP_IREQUEST_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/AnySimple.h"
#include "Smp/InvalidAnyType.h"
#include "Smp/InvalidParameterIndex.h"
#include "Smp/InvalidParameterValue.h"
#include "Smp/InvalidReturnValue.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/VoidOperation.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// A request holds information, which is passed between a client invoking 
    /// an operation via the IDynamicInvocation interface and a component being
    /// invoked.
    class IRequest
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IRequest() noexcept = default;

        /// Return the name of the operation that this request is for.
        /// @remarks A request is typically created using the CreateRequest() 
        ///          method to dynamically call a specific method of a 
        ///          component implementing the IDynamicInvocation interface. 
        ///          This method returns the name passed to it, to allow 
        ///          finding out which method is actually called on Invoke().
        /// @return  Name of the operation.
        virtual Smp::String8 GetOperationName() const = 0;

        /// Return the number of parameters stored in the request.
        /// This only considers parameters of direction in, out or in/out, but 
        /// not of type return.
        /// Parameters can be accessed by their 0-based index. This index
        ///      - must not be negative,
        ///      - must be smaller than the parameter count.
        /// @remarks The GetParameterIndex() method may be used to access 
        ///          parameters by name.
        /// @return  Number of parameters in request object.
        virtual Smp::Int32 GetParameterCount() const = 0;

        /// Query for a parameter index by parameter name.
        /// This only considers parameters of direction in, out or in/out, but 
        /// not of type return.
        /// The index values are 0-based. An index of -1 indicates a wrong 
        /// parameter name.
        /// @param   parameterName Name of parameter.
        /// @return  Index of parameter with the given name, or -1 if no 
        ///          parameter with the given name could be found.
        virtual Smp::Int32 GetParameterIndex(
            Smp::String8 parameterName) const = 0;

        /// Assign a value to a parameter at a given position.
        /// This only considers parameters of direction in, out or in/out, but 
        /// not of type return.
        /// This method raises an exception of type InvalidParameterIndex if 
        /// called with an illegal parameter index. If called with an invalid 
        /// parameter type, it raises an exception of type InvalidAnyType. If 
        /// called with an invalid value for the parameter, it raises an 
        /// exception of type InvalidParameterValue.
        /// @param   index Index of parameter (0-based).
        /// @param   value Value of parameter.
        /// @throws  Smp::InvalidAnyType
        /// @throws  Smp::InvalidParameterIndex
        /// @throws  Smp::InvalidParameterValue
        virtual void SetParameterValue(
            Smp::Int32 index,
            Smp::AnySimple value) = 0;

        /// Query a value of a parameter at a given position.
        /// This only considers parameters of direction in, out or in/out, but 
        /// not of type return.
        /// This method raises an exception of type InvalidParameterIndex if 
        /// called with an illegal parameter index.
        /// @param   index Index of parameter (0-based).
        /// @return  Value of parameter.
        /// @throws  Smp::InvalidParameterIndex
        virtual Smp::AnySimple GetParameterValue(
            Smp::Int32 index) const = 0;

        /// Assign the return value of the operation.
        /// This method raises an exception of type VoidOperation if called for
        /// a request object of a void operation. If called with an invalid 
        /// return type, it raises an exception of type InvalidAnyType. If 
        /// called with an invalid value for the return type, this method 
        /// raises an exception of type InvalidReturnValue.
        /// @param   value Return value.
        /// @throws  Smp::InvalidAnyType
        /// @throws  Smp::InvalidReturnValue
        /// @throws  Smp::VoidOperation
        virtual void SetReturnValue(
            Smp::AnySimple value) = 0;

        /// Query the return value of the operation.
        /// This method raises an exception of type VoidOperation if called for
        /// a request object of a void operation.
        /// @return  Return value of the operation.
        /// @throws  Smp::VoidOperation
        virtual Smp::AnySimple GetReturnValue() const = 0;
    };
}

#endif // SMP_IREQUEST_H_
