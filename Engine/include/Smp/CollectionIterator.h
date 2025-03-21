// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/CollectionIterator.h
// Version:   Issue 1.0 from 15/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_COLLECTIONITERATOR_H_
#define SMP_COLLECTIONITERATOR_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    template <typename T>
    class ICollection;

    /// Iterator implementation for ICollection interfaces.
    /// The C++ language requires iterator to be actual final types rather than
    /// interfaces. To allow collections to be iterated, the Collection
    /// Iterator implements the C++ iterator concept accessing the ICollection
    /// elements sequentially.
    template <typename T>
    class CollectionIterator final
    {
    public:
        /// Constructor.
        /// @param collection The collection referenced by the iterator.
        /// @param index The index of the element referenced by the iterator.
        CollectionIterator(
            const Smp::ICollection<T>& collection,
            size_t index)
            : collection(&collection), index(index)
        {
        }

        /// Defaulted copy constructor.
        /// @param other Other instance to copy from.
        CollectionIterator(const CollectionIterator<T>& other) = default;

        /// Defaulted copy operator.
        /// @param other Other instance to copy from.
        /// @return collection iterator.
        CollectionIterator& operator=(const CollectionIterator<T>& other) = default;

        /// Defaulted move constructor.
        CollectionIterator(CollectionIterator<T>&& other) = default;
        /// @param other Other instance to move from.

        /// Defaulted move operator.
        /// @param other Other instance to move from.
        /// @return collection iterator.
        CollectionIterator& operator=(CollectionIterator<T>&& other) = default;

        /// Pre increment operator
        CollectionIterator<T>& operator++()
        {
            ++(this->index);
            return *this;
        }

        /// Inequality operator
        /// @param other Other instance to compare with.
        /// @return True if instances are different, false otherwise.
        Smp::Bool operator!=(const CollectionIterator<T>& other)
        {
            return !((collection == other.collection) && (index == other.index));
        }

        /// Dereference operator
        T* operator*()
        {
            return collection->at(index);
        }

    private:
        /// Pointer to collection
        const Smp::ICollection<T>* collection;

        /// Pointer to index
        size_t index;
    };
}

#endif // SMP_COLLECTIONITERATOR_H_
